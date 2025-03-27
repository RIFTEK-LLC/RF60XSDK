/**
 * @file rf60x_sensor_control.cpp
 * @brief Demonstrates RF60X SDK usage for sensor settings manipulation
 */

#include <bitset>
#include <iostream>
#include <memory>
#include <rf60Xsdk.h>
#include <thread>

// Using declarations for better readability
using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;
using namespace std::chrono_literals;

// Avoid "using namespace std" to prevent namespace pollution

/**
 * @brief Displays laser power status in binary format
 * @param valueLaserPower Pair where:
 *        first - operation status (true if successful),
 *        second - laser power value
 */
void showLaserPower(const std::pair<bool, uint8_t> &valueLaserPower) {
  if (!valueLaserPower.first) {
    std::cerr << "Error: Failed to get laser power value" << std::endl;
    return;
  }

  std::cout << "Laser power (binary): "
            << std::bitset<8>(valueLaserPower.second) << std::endl;
}

/**
 * @brief Handles device operation with error checking
 * @param operation Result of device operation (first=true if success)
 * @param errorMsg Error message to display if operation failed
 * @return true if operation succeeded, false otherwise
 */
bool handleDeviceOperation(const std::pair<bool, AL_MODE> &operation,
                           const std::string &errorMsg) {
  if (!operation.first) {
    std::cerr << "Error: " << errorMsg << std::endl;
    return false;
  }
  return true;
}

int main() {
  try {
    // 1. SDK Initialization
    std::cout << "SDK Version: " << sdk_version() << std::endl;

    // 2. Device Initialization
    std::shared_ptr<rf60x> dev = std::make_shared<rf60x>();

    // 3. Device Connection
    std::cout << "Opening serial port: " << dev->open_serial_port("COM3", 9600)
              << std::endl;

    dev->bind_network_address(1);

    // 4. Get and display AL mode
    auto alModeResult = dev->get_AL_mode();
    if (handleDeviceOperation(alModeResult, "Failed to get AL mode")) {
      std::cout << "AL mode (binary): "
                << std::bitset<8>(static_cast<uint8_t>(alModeResult.second))
                << std::endl;
    }

    // 5. Laser power operations
    std::cout << "\nInitial laser power:" << std::endl;
    showLaserPower(dev->get_sensor());

    // 6. Configuration changes
    if (!dev->set_sensor(0)) {
      std::cerr << "Error: Failed to set sensor" << std::endl;
    }

    if (!dev->write_params_to_flash()) {
      std::cerr << "Error: Failed to write parameters to flash" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\nAfter setting new values:" << std::endl;
    showLaserPower(dev->get_sensor());

    // 7. Restore operations
    if (!dev->restore_default_params()) {
      std::cerr << "Error: Failed to restore default parameters" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "\nAfter restore operations:" << std::endl;
    showLaserPower(dev->get_sensor());

    // 8. Cleanup
    dev->close_serial_port();

  } catch (const std::exception &e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
