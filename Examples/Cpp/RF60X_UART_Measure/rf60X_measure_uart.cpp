#include <iomanip>
#include <iostream>
#include <memory>
#include <rf60Xsdk.h>
#include <rf60Xtypes.h>
#include <memory>
#include <stdexcept> // For std::exception

using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;

constexpr double RESOLUTION_FACTOR = 16384.0;

int main() {
  std::cout.precision(2);
  std::cout << std::fixed;

  // Declare dev outside the try block
  std::unique_ptr<rf60x> dev;

  try {
    uart_stream_measure_t measure;

    // Create a unique pointer to an rf60x object
    dev = std::make_unique<rf60x>();

    // Set network address(UART) and open serial port
    dev->bind_network_address(1);
    if (!dev->open_serial_port("COM3", 9600)) {
      std::cerr << "Error opening serial port." << std::endl;
      return 1; // Or handle it differently, like trying another port.
    }

    // Retrieve device information and output it
    uart_hello_t const hello = dev->hello_msg_uart();
    if (hello.deviceType == 0) {
      std::cerr << "Wrong hello message values." << std::endl;
      return 1;
    }
    std::cout << "Device information" << std::endl;
    std::cout << "Type :" << static_cast<uint32_t>(hello.deviceType) << "\n"
              << "Serial number : " << static_cast<uint32_t>(hello.deviceSerial)
              << "\n"
              << "Range  :" << hello.deviceRange << std::endl;

    // Retrieve and output a single measurement
    std::cout << "Device measurements" << std::endl;
    if (dev->get_single_measure(&measure)) {
      if (measure.status == 0) {
        double single_measure = measure.value * hello.deviceRange / RESOLUTION_FACTOR;
        std::cout << "Measure :" << single_measure << " mm" << std::endl;
      } else {
        std::cout << "Error in single measure:  measurement status : " << static_cast<uint32_t>(measure.status) << std::endl;
      }
    } else {
      std::cerr << "Error get single measure." << std::endl;
      if(dev) dev->close_serial_port();
      std::cin.get();
      return 1;
    }

    // Start streaming measurements and retrieve data 20 times
    if (!dev->send_command(COMMAND_UART::START_STREAM)) {
      std::cerr << "Error sending START_STREAM command." << std::endl;
      if(dev) dev->close_serial_port();
      std::cin.get();
      return 1;
    }

    for (int i = 0; i < 20; ++i) {
      if (dev->get_measure_uart(&measure, PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T)) {
        if (measure.status == 0) { // 0 - status OK, all other status - some kind of error.
          double stream_measure = measure.value * hello.deviceRange / RESOLUTION_FACTOR;
          std::cout << "Measure : " << stream_measure
                    << " mm,"
                    << "  measurement status : "
                    << static_cast<uint32_t>(measure.status) << std::endl;
        } else {
          std::cout << "Error in measure:  measurement status : " << static_cast<uint32_t>(measure.status) << std::endl;
        }
      } else {
        std::cerr << "Measurement not received " << std::endl;
      }
    }

    // Stop streaming measurements and close the serial port
    if (!dev->send_command(COMMAND_UART::STOP_STREAM)) {
      std::cerr << "Error sending STOP_STREAM command." << std::endl;
      if(dev) dev->close_serial_port();
      std::cin.get();
      return 1;
    }

    if(dev) dev->close_serial_port();
  } catch (const std::exception& e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    // if exception happen - close serial port.
    if (dev) {
      dev->close_serial_port();
    }
    return 1; // Or other appropriate error handling
  }

  return 0;
}