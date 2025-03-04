// This program demonstrates the use of RF60X SDK to connect to a device and
// retrieve measurement data via UDP.

#include <iostream>
#include <memory>
#include <rf60Xsdk.h>
#include <rf60Xtypes.h>

using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;

int main()
{

  // Set precision for output
  std::cout.precision(2);
  std::cout << std::fixed;

  // Output SDK version
  std::cout << sdk_version() << std::endl;

  udp_measure_t measure;
  // Create a shared pointer to an rf60x object
  std::shared_ptr<rf60x> dev = std::make_shared<rf60x>();

  // Connects to the RF60X scanner via UDP with the IP address “192.168.1.2” and
  // port 603.
  dev->connect_udp("192.168.1.2", 603);

  // Retrieve and output measurement data 20 times
  for (size_t i = 0; i < 20; i++)
  {

    if (dev->get_measure_udp(measure))
    {
      // Calculate and output the measured value in millimeters
      std::cout << "Measure  :"
                << static_cast<double>((measure.rf60xValArray[0].value *
                                        measure.deviceMeasureRange) /
                                       16384.0)
                << "mm," << std::endl;
    }
    else
    {
      std::cout << "Measurement not received" << std::endl;
    }
  }

  // Disconnect from the device via UDP
  dev->disconnect_udp();

  return 0;
}
