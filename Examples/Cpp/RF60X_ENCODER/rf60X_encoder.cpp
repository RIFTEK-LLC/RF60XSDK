#include <iostream>
#include <memory>
#include <rf60Xtypes.h>
#include <rf60xencoder.h>
#include <tuple>
using namespace SDK;
using namespace SCANNERS;
using namespace RFENCODER;

int main() {

  // Set precision for output
  std::cout.precision(2);
  std::cout << std::fixed;

  uint8_t value{0};
  bool stateOp{false};

  // Create a shared pointer to an rf60xencoder object
  auto dev = std::make_shared<rf60xEncoder>();
  dev->bind_network_address(1); // Bind the object to network address 1
  dev->open_serial_port("COM3",
                        9600); // Open serial port "COM3" with baud rate 9600

  // Get device information
  auto const hello = dev->hello_msg_uart();
  std::cout << std::fixed;
  std::cout << "Device information " << std::endl;
  std::cout << "Type :" << static_cast<uint32_t>(hello.deviceType) << "\n"
            << "Serial number : " << static_cast<uint32_t>(hello.deviceSerial)
            << "\n"
            << "Range  :" << hello.deviceRange << std::endl;

  std::tie(stateOp, value) = dev->get_baute_rate();
  if (stateOp) {
    std::cout << static_cast<uint32_t>(value) << std::endl;
  }

  std::cout << "Request voltage result" << std::endl;
  std::cout << "Voltage value :" << dev->get_single_valtage_encoder()
            << std::endl;

  // Start streaming voltage values
  dev->send_command_encoder(COMMAND_UART_ENCODER::START_STREAM_VALTAGE);

  for (size_t i = 0; i < 10; ++i) {
    float value{0};
    if (dev->get_stream_valtage_encoder(value)) {
      std::cout << "Voltage value :" << value << std::endl;
    }
  }

  // Stop streaming voltage values
  dev->send_command_encoder(COMMAND_UART_ENCODER::STOP_STREAM);

  std::cout << "Request encoder value" << std::endl;
  std::cout << "Encoder value :" << dev->get_single_value_encoder()
            << std::endl;

  // Start streaming encoder values
  dev->send_command_encoder(COMMAND_UART_ENCODER::START_STREAM_VALUE_ENCODER);

  for (size_t i = 0; i < 10; ++i) {

    std::cout << "Encoder value :" << dev->get_stream_value_encoder()
              << std::endl;
  }

  // Stop streaming encoder values
  dev->send_command_encoder(COMMAND_UART_ENCODER::STOP_STREAM);

  dev->close_serial_port(); // Close the serial port

  return 0;
}
