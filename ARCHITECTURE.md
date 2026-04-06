# ARCHITECTURE.md — rf60xsdk

## Overview

C++ SDK for communicating with **RIFTEK RF60X laser displacement scanners**. Provides a high-level C++ API (`rf60x` class) and language bindings (C, Delphi) for device configuration, parameter read/write, and measurement streaming over **UART (RS-485)** and **UDP (Ethernet)**.

**Version:** 1.1.0 (root CMakeLists.txt) / 1.0.1 (rf60Xsdk subproject)

## Tech Stack

| Category | Technology |
|---|---|
| Language | C++14 (SDK), C++20 (RF60X_C wrapper) |
| Build | CMake 3.18+, Ninja (default), MSVC/MinGW/GCC |
| Networking | ASIO (header-only, fetched via FetchContent) |
| Serial | ASIO `serial_port` (cross-platform) |
| UDP | ASIO `udp::socket` |
| CI/CD | GitHub Actions (Linux GCC, Windows MinGW, Windows MSVC) |
| Docs | Doxygen + m.css (configured, not active) |
| Packaging | CPack (ZIP, component-based) |

## Directory Structure

```
rf60xsdk/
├── CMakeLists.txt              # Root build config (options, CPack)
├── cmake/
│   └── docs.cmake              # Doxygen doc target (hardcoded path, needs fix)
├── rf60Xsdk/                   # Core SDK library
│   ├── CMakeLists.txt          # SDK build config, ASIO fetch
│   ├── rf60Xsdk.h              # Main API: rf60x class
│   ├── rf60Xsdk.cpp            # Implementation
│   ├── rf60Xtypes.h            # Types, enums, protocol structs
│   ├── serialmanager.h         # Serial/UDP I/O abstraction
│   ├── serialmanager.cpp       # ASIO-based implementation
│   ├── rf60xencoder.h          # Encoder extension class
│   └── rf60xencoder.cpp        # Encoder implementation
├── wrapper/
│   ├── RF60X_C/                # C FFI wrapper (extern "C")
│   │   ├── CMakeLists.txt
│   │   ├── RF60X_C.h           # C API header
│   │   └── RF60X_C.cpp         # Thin wrapper over C++ API
│   └── RF60X_Delphi/           # Delphi/Pascal binding
│       └── RF60X_Delphi.pas    # Imports RF60X_C.dll via cdecl
├── Examples/
│   ├── CMakeLists.txt
│   ├── Cpp/
│   │   ├── RF60X_UART_Measure/           # Basic UART measurement
│   │   ├── RF60X_UDP_Measure/            # UDP measurement
│   │   └── RF60X_UART_MEASURE_EXTENDED_PROTOCOLS/  # Extended protocols
│   └── Delphi/                           # Lazarus/Delphi example app
├── docs/                         # Doxygen config files
│   ├── Doxyfile.in
│   ├── Doxyfile-mcss.in
│   ├── conf.py.in
│   └── pages/
└── .github/workflows/c-cpp.yml  # CI: build + release on push to master
```

## Core Components

### 1. `SDK::SCANNERS::RF60X::rf60x` (rf60Xsdk.h/cpp)

The main SDK class. Responsibilities:
- **Device configuration** — 30+ `set_*` / `get_*` methods for scanner parameters (laser power, averaging, baud rate, IP settings, CAN, etc.)
- **UART communication** — open/close serial port, send commands, read measurements
- **UDP communication** — connect/disconnect, async and sync measure retrieval
- **Protocol handling** — RIFTEK binary protocol with nibble-encoded frames
- **Flash operations** — write params, factory reset, restore defaults

Key internal members:
- `m_SerialManager` — `unique_ptr<SerialManager>` for I/O
- `m_NetworkAddress` — device address on RS-485 bus (default: 1)
- `m_Timer` — read timeout (default: 5000ms)

### 2. `SerialManager` (serialmanager.h/cpp)

Low-level I/O layer using ASIO:
- **Serial port** — async read with timeout, sync write, platform-specific buffer flush
- **UDP socket** — connect, async receive (with invalid data filtering), sync receive
- **Timeout handling** — ASIO timer-based with platform-specific error codes (Win: 995, macOS: 45, Linux: 125)

### 3. `SDK::RFENCODER::rf60xEncoder` (rf60xencoder.h/cpp)

Extends `rf60x` with encoder-specific operations:
- Voltage reading (`get_single_valtage_encoder`)
- Encoder value reading (`get_single_value_encoder`, `get_stream_value_encoder`)
- Mode query (`get_mode_encoder`)

### 4. C Wrapper (`wrapper/RF60X_C/`)

Opaque-handle C API (`rf60x_device` = `void*`) for FFI:
- `create_rf60x()` / `destroy_rf60x()` lifecycle
- All SDK methods mirrored as C functions with `EXPORTCALL` (`__declspec(dllexport)` on Windows)
- C-style enums/structs prefixed with `C_`

### 5. Delphi Wrapper (`wrapper/RF60X_Delphi/`)

Pascal unit that imports `RF60X_C.dll` via `cdecl` external declarations, wrapped in a `TRF60X` class.

## Data Flow

### UART Measurement Flow
```
Application → rf60x::open_serial_port("COM3", 9600)
            → SerialManager::open_serial_port()
            → ASIO serial_port::open() + configure (9600, even parity, 8N1)

            → rf60x::send_command(START_STREAM)
            → build 2-byte command frame [addr | 0x80|cmd]
            → SerialManager::write_command()
            → ASIO serial_port::write()

            → rf60x::get_measure_uart(&measure, type)
            → read_data_burst(buffer, size)
            → SerialManager::read_command() (async read + timer)
            → parse nibble-encoded bytes into measure struct
```

### UDP Measurement Flow
```
Application → rf60x::connect_udp("192.168.1.2", 603)
            → SerialManager::connect_udp()
            → ASIO udp::socket open + bind + set recv timeout

            → rf60x::get_measure_udp(measure)
            → SerialManager::get_measure_udp() (async) 
              OR get_measure_udp_sync() (sync)
            → ASIO udp::socket::async_receive / receive_from
            → filter invalid FF 7F prefix
            → populate udp_measure_t struct
```

### Parameter Read/Write Flow
```
set_param(value, key) → build 6-byte frame per byte of value:
  [addr | 0x80|WRITEPARAM | 0x80|key_lo | 0x80|key_hi | 0x80|val_lo | 0x80|val_hi]
  → request_custom_command() → SerialManager::write_command()

get_param<T>(key) → build 4-byte read frame per byte:
  [addr | 0x80|READPARAM | 0x80|key_lo | 0x80|key_hi]
  → read_custom_command(key, 2, vec) → read_data_burst()
  → reassemble bytes into T
```

## External Integrations

| Integration | Protocol | Details |
|---|---|---|
| RF60X Scanner | UART (RS-485) | 9600–921600 baud, even parity, 8 data, 1 stop |
| RF60X Scanner | UDP (Ethernet) | Default port 603, binary protocol |
| RF60X Scanner | CAN | Optional, configurable speed/identifiers |
| ASIO Library | Header-only | Fetched from GitHub at build time |

## Configuration

### CMake Options (root)
| Option | Default | Description |
|---|---|---|
| `ENABLE_SDK_SOURCE` | ON | Build rf60Xsdk library |
| `ENABLE_SDK_EXAMPLES` | ON | Build example programs |
| `ENABLE_RF60X_C` | OFF | Build legacy C wrapper |
| `ENABLE_RF60X_C_WRAPPER` | ON | Build new C FFI wrapper |
| `BUILD_STATIC_WRAPPER` | ON | Link wrapper against static SDK |

### Environment
- No environment variables used; all config via CMake options or runtime API calls

## Build & Deploy

### Local Build
```bash
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . --prefix ./install
```

### Cross-Platform CI
- **Linux GCC** — Ubuntu latest, g++, Ninja
- **Windows MinGW** — MSYS2 MINGW64, mingw-w64-gcc
- **Windows MSVC** — Visual Studio 17 2022, x64

### Packaging
- CPack generates ZIP archives with `Examples` and `Library` components
- Version: 1.1.0, filename: `SDK-rf60XSDK-1.1.0.zip`
- Release auto-created on push to `master` with timestamp tag
