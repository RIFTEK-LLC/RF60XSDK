// This program demonstrates the use of RF60X SDK to connect to a device and
// retrieve measurement data via UART.

#include <iomanip>
#include <iostream>
#include <memory>
#include <rf60Xsdk.h>
#include <rf60Xtypes.h>
#include <memory>

using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;

int main() {
  std::cout.precision(2);

  uart_stream_measure_t measure;

  // Create a unique pointer to an rf60x object
  std::unique_ptr<rf60x> dev = std::make_unique<rf60x>();

  // Set network address(UART) and open serial port
  dev->bind_network_address(1);
  dev->open_serial_port("COM3", 9600);

  // Retrieve device information and output it
  uart_hello_t const hello = dev->hello_msg_uart();
  std::cout << std::fixed;
  std::cout << "Device information " << std::endl;
  std::cout << "Type :" << static_cast<uint32_t>(hello.deviceType) << "\n"
            << "Serial number : " << static_cast<uint32_t>(hello.deviceSerial)
            << "\n"
            << "Range  :" << hello.deviceRange << std::endl;

  // Retrieve and output a single measurement
  std::cout << "Device measurements" << std::endl;
  if (dev->get_single_measure(&measure)) {
    std::cout << "Measure :" << (measure.value * hello.deviceRange / 16384.0)
              << " mm" << std::endl;
  } else {
    std::cout << "Measurement not received " << std::endl;
    std::cin.get();
    return 0;
  }

  // Start streaming measurements and retrieve data 20 times
  if (!dev->send_command(COMMAND_UART::START_STREAM)) {
    std::cout << "Command not sent" << std::endl;
    std::cin.get();
    return 0;
  }

  for (int i = 0; i < 20; ++i) {
    if (dev->get_measure_uart(&measure,
                              PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T)) {
      std::cout << "Measure : "
                << static_cast<double>(measure.value * hello.deviceRange /
                                       16384.0)
                << " mm,"
                << "  measurement status : "
                << static_cast<uint32_t>(measure.status) << std::endl;
    } else {
      std::cout << "Measurement not received " << std::endl;
    }
  }

  // Stop streaming measurements and close the serial port
  if (!dev->send_command(COMMAND_UART::STOP_STREAM)) {
    std::cout << "Command not sent" << std::endl;
    std::cin.get();
    return 0;
  }

  dev->close_serial_port();
}
