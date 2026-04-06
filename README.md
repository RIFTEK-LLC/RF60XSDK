# RF60X SDK

[![C++](https://img.shields.io/badge/C%2B%2B-14-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.18%2B-064F8C.svg)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)]()
[![CI](https://img.shields.io/github/actions/workflow/status/nikolay-kozhuro/rf60xsdk/c-cpp.yml?branch=master&label=CI&logo=github)]()
[![Release](https://img.shields.io/github/v/release/nikolay-kozhuro/rf60xsdk?label=Release)]()

SDK for **RIFTEK RF60X** laser displacement scanners. Provides a high-level C++ API with language bindings (C, Delphi) for device configuration, parameter read/write, and measurement streaming over **UART (RS-485)** and **UDP (Ethernet)**.

---

<details>
<summary><strong>🇷🇺 Русская версия</strong></summary>

# RF60X SDK

SDK для лазерных дальномеров **RIFTEK RF60X**. Предоставляет высокоуровневый C++ API с привязками на C и Delphi для конфигурации устройства, чтения/записи параметров и потокового получения измерений по **UART (RS-485)** и **UDP (Ethernet)**.

</details>

---

## Features / Возможности

- **UART (RS-485)** — serial communication with configurable baud rate (9600–921600), even parity
- **UDP (Ethernet)** — async and sync measurement retrieval over network
- **30+ parameters** — laser power, averaging, sampling, IP settings, CAN interface, and more
- **5 protocol types** — standard, extended, advanced, modified, and encoder measurement formats
- **Flash operations** — save parameters, factory reset, restore defaults
- **C FFI wrapper** — opaque-handle API for Delphi, Python, and other languages
- **Cross-platform** — Windows (MinGW, MSVC) and Linux

---

## Quick Start / Быстрый старт

### C++ / C++

```cpp
#include "rf60Xsdk.h"

using namespace SDK::SCANNERS::RF60X;

int main() {
    auto dev = std::make_unique<rf60x>();

    // Open serial port / Открыть COM-порт
    dev->open_serial_port("COM3", 9600);

    // Get device info / Получить информацию об устройстве
    auto hello = dev->hello_msg_uart();
    std::cout << "Device type: " << static_cast<int>(hello.deviceType) << std::endl;

    // Start measurement stream / Запустить поток измерений
    dev->send_command(rf60x::RF60X_COMMAND::START_STREAM);

    // Read measurements / Чтение измерений
    uart_stream_measure_t measure;
    if (dev->get_measure_uart(&measure, PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T)) {
        std::cout << "Value: " << measure.value << std::endl;
    }

    return 0;
}
```

### C / C

```c
#include "RF60X_C.h"

int main() {
    rf60x_device dev = create_rf60x();
    open_serial_port(dev, "COM3", 9600);

    C_uart_hello_t hello = hello_msg_uart(dev);
    printf("Device type: %d\n", hello.deviceType);

    destroy_rf60x(dev);
    return 0;
}
```

### UDP / UDP

```cpp
#include "rf60Xsdk.h"

using namespace SDK::SCANNERS::RF60X;

int main() {
    auto dev = std::make_unique<rf60x>();

    // Connect via UDP / Подключение по UDP
    dev->connect_udp("192.168.1.2", 603);

    // Async measurement / Асинхронное измерение
    udp_measure_t measure;
    if (dev->get_measure_udp(measure)) {
        std::cout << "Value: " << measure.rf60xValArray[0].value << std::endl;
    }

    return 0;
}
```

---

## Building / Сборка

### Prerequisites / Требования

- CMake 3.18+
- C++14 compiler (GCC, Clang, MSVC, MinGW)
- ASIO (downloaded automatically via FetchContent)

### Build / Сборка

```bash
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### CMake Options / Опции CMake

| Option | Default | Description |
|---|---|---|
| `ENABLE_SDK_SOURCE` | ON | Build rf60Xsdk library |
| `ENABLE_SDK_EXAMPLES` | ON | Build example programs |
| `ENABLE_RF60X_C_WRAPPER` | ON | Build C FFI wrapper |
| `BUILD_STATIC_WRAPPER` | ON | Link wrapper against static SDK |

### Install / Установка

```bash
cmake --install . --prefix ./install
```

---

## API Reference / Справочник API

### Key Classes / Основные классы

| Class | Description |
|---|---|
| `SDK::SCANNERS::RF60X::rf60x` | Main SDK class — device config, I/O, measurements |
| `SDK::RFENCODER::rf60xEncoder` | Extends `rf60x` with encoder voltage/value reading |
| `SerialManager` | Low-level ASIO-based serial/UDP I/O (internal) |

### Parameter Categories / Категории параметров

- **Laser** — power, analog output mode, AL mode
- **Signal** — averaging mode, number of averaged values, sampling mode/period
- **Integration** — max integration time, analog range, zero point
- **Communication** — network address, baud rate, IP settings, Ethernet interface
- **CAN** — interface on/off, identifier type, speed
- **Stream** — autostart, protocol type (RIFTEK/ASCII/MODBUS RTU), measurements per packet

### Measurement Protocols / Протоколы измерений

| Protocol | Struct | Description |
|---|---|---|
| `UART_STREAM_MEASURE_T` | `uart_stream_measure_t` | Standard 16-bit value + status |
| `UART_STREAM_ADVANCED_MEASURE_T` | `uart_stream_advanced_measure_t` | Value + status + direction + counter |
| `UART_STREAM_MODIFIED_MEASURE_T` | `uart_stream_modified_measure_t` | Value + status + direction + stream counter |
| `UART_STREAM_EXTENDED_T` | `uart_stream_extended_measure_t` | Value + 32-bit counter |
| `UART_STREAM_ENCODER_T` | `uart_result_with_encoder_t` | Value + rotation marks + encoder value |

---

## Examples / Примеры

Ready-to-run examples in `Examples/`:

| Example | Language | Description |
|---|---|---|
| `RF60X_UART_Measure` | C++ | Basic UART measurement |
| `RF60X_UDP_Measure` | C++ | UDP measurement |
| `RF60X_PARAMS` | C++ | Parameter read/write |
| `RF60X_UART_MEASURE_EXTENDED_PROTOCOLS` | C++ | Extended protocol measurements |
| `RF60X_ENCODER` | C++ | Encoder voltage and value reading |
| `R60X_UART_FLASH_FACTORY_RESTORE_PARAMS` | C++ | Flash save/restore/factory reset |
| `Delphi/RF60X_UART_Measure` | Delphi | UART measurement with Lazarus GUI |

---

## Architecture / Архитектура

```
Application (C++ / C / Delphi)
    │
    ├── rf60x (C++ API) ──┐
    │                     │
    ├── RF60X_C.dll ──────┤
    │                     │
    └── Delphi wrapper ───┤
                          │
              SerialManager (ASIO)
                 │         │
            UART (RS-485)  UDP (Ethernet)
                 │         │
            RF60X Scanner  RF60X Scanner
```

See [ARCHITECTURE.md](ARCHITECTURE.md) for detailed design documentation.

---

## Supported Devices / Поддерживаемые устройства

| Device | Description |
|---|---|
| RF60X | Standard laser displacement scanner |
| RF60XHS | High-speed variant |
| RF60xB | Binocular (dual-channel) variant |

---

## Links / Ссылки

- [RIFTEK Official](http://riftek.com/)
- [Architecture Docs](ARCHITECTURE.md)
