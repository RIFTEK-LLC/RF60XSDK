// This program demonstrates the use of RF60X SDK to manipulate sensor settings
// and retrieve information.

#include <bitset>
#include <iostream>
#include <memory>
#include <rf60Xsdk.h>

using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;
using namespace std::chrono_literals;

int main() {
    // Output SDK version
    std::cout << sdk_version() << std::endl;

    // Create a shared pointer to an rf60x object
    std::shared_ptr<rf60x> dev = std::make_shared<rf60x>();

    // Open serial port and bind network address
    std::cout << dev->open_serial_port("COM8", 9600) << std::endl;  //Replace the port address and speed with yours.
    dev->bind_network_address(1);

    // Retrieve device information and output it
    uart_hello_t const hello = dev->hello_msg_uart();
    std::cout << std::fixed;
    std::cout << "Device information " << std::endl;
    std::cout << "Type :" << static_cast<uint32_t>(hello.deviceType) << "\n"
        << "Serial number : " << static_cast<uint32_t>(hello.deviceSerial)
        << "\n"
        << "Range  :" << hello.deviceRange << std::endl;

    // Start streaming measurements and retrieve data 20 times
    if (!dev->send_command(COMMAND_UART::START_STREAM_EXTEND)) {
        std::cout << "Command not sent" << std::endl;
        std::cin.get();
        return 0;
    }

    uart_stream_extended_measure_t measure;
    for (int i = 0; i < 20; ++i) {
        if (dev->get_measure_uart(&measure,
            PROTOCOL_MEASURE_UART::UART_STREAM_EXTENDED_T)) {
            std::cout << "Measure : "
                << (measure.value * hello.deviceRange) / 16384.0
                << " mm,"
                << "  measurement counter : "
                << static_cast<uint32_t>(measure.counter) << std::endl;
        }
        else {
            std::cout << "Measurement not received " << std::endl;
        }
    }

    // Stop streaming measurements and close the serial port
    if (!dev->send_command(COMMAND_UART::STOP_STREAM)) {
        std::cout << "Command not sent" << std::endl;
        std::cin.get();
        return 0;
    }

    // Close the serial port
    dev->close_serial_port();

    return 0;
}
