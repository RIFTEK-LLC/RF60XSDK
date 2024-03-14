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
  std::cout << dev->open_serial_port("COM3", 9600) << std::endl;
  dev->bind_network_address(1);

  // Retrieve AL mode and output as a bitset
  auto result = dev->get_AL_mode();
  if (result.first) {
    std::cout << std::bitset<8>(static_cast<uint8_t>(result.second))
              << std::endl;
  }
  else{
      std::cout<<"Error receiving parameter "<<std::endl;
  }

  auto ipAddress=dev->get_source_ip_address();
  if(ipAddress.first){

      std::cout<<"IP address: "<<ipAddress.second<<std::endl;
  }

  // Set sensor and handle error
  if (!dev->set_sensor(1)) {
    std::cout << "Error writing new values" << std::endl;
  }

  // Close the serial port
  dev->close_serial_port();

  return 0;
}
