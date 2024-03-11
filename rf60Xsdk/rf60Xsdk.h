#pragma once

#include "rf60Xtypes.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#if (defined _WIN32 && defined RF60X_LIBRARY)
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

class SerialManager;
namespace SDK {
namespace SCANNERS {
namespace RF60X {

/**
 * @brief sdk_version - Return info about SDK version
 * @return SDK version
 */
API_EXPORT int sdk_version();

class API_EXPORT rf60x {
public:
  explicit rf60x();

  rf60x(const rf60x &other);

  rf60x &operator=(const rf60x &other);

  rf60x(rf60x &&other) noexcept;

  rf60x &operator=(rf60x &&other) noexcept;

  ~rf60x();

  //-------------------------------------------------------//

  void bind_network_address(uint32_t value);

  uart_hello_t hello_msg_uart();

  void set_wait_timer(std::chrono::milliseconds value);

  bool set_sensor(uint8_t value);

  bool set_analog_out(uint8_t value);

  bool set_AL_mode(AL_MODE value); //

  bool set_averaging_mode(AVERAGING_MODE value);

  bool set_analog_ouput_mode(ANALOG_OUTPUT_MODE value);

  bool set_sampling_mode(SAMPLING_MODE value);

  bool set_network_address(uint8_t value);

  bool set_baute_rate(uint8_t value);

  bool set_number_of_averaged_values(uint8_t value);

  bool set_sampling_period(uint16_t value);

  bool set_maximum_integration_time(uint16_t value);

  bool set_begin_analog_range(uint16_t value);

  bool set_end_analog_range(uint16_t value);

  bool set_time_lock_of_result(uint8_t value);

  bool set_zero_point(uint16_t value);

  bool set_CAN_interface_speed(uint8_t value);

  bool set_standard_identifier(uint16_t value);

  bool set_extend_identifier(uint32_t value);

  bool set_CAN_interface_identifier(uint8_t value);

  bool set_CAN_interface(uint8_t value);

  bool set_destination_ip_address(std::string value);

  bool set_gateway_ip_address(std::string value);

  bool set_subnet_mask(std::string value);

  bool set_source_ip_address(std::string value);

  bool set_number_of_measurements_in_the_packet(uint16_t value);

  bool set_ethernet_inteface(uint8_t value);

  bool set_autostart_of_measurement_stream(uint8_t value);

  bool set_protol_type(uint8_t value);

  //-------------------------------------------------------//

  bool open_serial_port(std::string comPortName, uint32_t baudRate);

  void close_serial_port();

  bool get_raw_measure_uart(char *bufferArray, size_t size);

  bool get_single_measure(void *measure);

  bool send_command(COMMAND_UART value);

  bool read_custom_command(uint8_t command, uint8_t size,
                           std::vector<char> &vec_ref);

  bool request_custom_command(char *data, uint8_t size);

  bool get_measure_uart(void *measure, PROTOCOL_MEASURE_UART type);

  std::pair<bool, uint8_t> get_sensor();

  std::pair<bool, uint8_t> get_analog_out();

  std::pair<bool, AL_MODE> get_AL_mode();

  std::pair<bool, AVERAGING_MODE> get_averaging_mode();

  std::pair<bool, ANALOG_OUTPUT_MODE> get_analog_ouput_mode();

  std::pair<bool, SAMPLING_MODE> get_sampling_mode();

  std::pair<bool, uint8_t> get_network_address();

  std::pair<bool, uint8_t> get_baute_rate();

  std::pair<bool, uint8_t> get_number_of_averaged_values();

  std::pair<bool, uint16_t> get_sampling_period();

  std::pair<bool, uint16_t> get_maximum_integration_time();

  std::pair<bool, uint16_t> get_begin_analog_range();

  std::pair<bool, uint16_t> get_end_analog_range();

  std::pair<bool, uint8_t> get_time_lock_of_result();

  std::pair<bool, uint16_t> get_zero_point();

  std::pair<bool, uint8_t> get_CAN_interface_speed();

  std::pair<bool, uint16_t> get_standard_identifier();

  std::pair<bool, uint32_t> get_extend_identifier();

  std::pair<bool, uint8_t> get_CAN_interface_identifier();

  std::pair<bool, uint8_t> get_CAN_interface();

  std::pair<bool, std::string> get_source_ip_address();

  std::pair<bool, std::string> destination_ip_address();

  std::pair<bool, std::string> gateway_ip_address();

  std::pair<bool, std::string> subnet_mask();

  std::pair<bool, uint16_t> get_number_of_measurements_in_the_packet();

  std::pair<bool, uint8_t> get_ethernet_inteface();

  std::pair<bool, uint8_t> get_autostart_of_measurement_stream();

  std::pair<bool, uint8_t> get_protol_type();

  bool connect_udp(const std::string &hostAddress, uint32_t port);

  void disconnect_udp();
  /**
   * Retrieves a measure using the UDP protocol.
   *
   * @tparam T The type of the protocolUDP parameter.
   * @param protocolUDP The UDP protocol object used to retrieve the measure.
   * @return True if the measure was successfully retrieved, false otherwise.
   */
  template <typename T> bool get_measure_udp(T &protocolUDP);
  protected:
  uint32_t m_NetworkAddress{1};
private:
  std::pair<bool, std::string> get_ip_address(CODE::PARAM_NAME_KEY key);
  template <typename T> std::pair<bool, T> get_param(CODE::PARAM_NAME_KEY key);

  /**
   * Template function to test the get_param_2 method.
   *
   * @tparam T The type of the key parameter.
   * @tparam U The underlying type of the enum T.
   * @param key The key parameter of type T.
   * @return A pair of bool and U, indicating the success of the operation and
   * the value of the underlying type of the enum T.
   */
  template <typename T, typename U = typename std::enable_if_t<
                            std::is_enum<T>::value,
                            typename std::underlying_type_t<T>>>
  std::pair<bool, U> get_param_2(T key);

  template <typename T>
  bool set_param(const T &value, CODE::PARAM_NAME_KEY key);

  uint32_t converIPString(const std::string &str);

  enum class RF60X_COMMAND {
    HELLO = 0x01,
    READPARAM = 0x02,
    WRITEPARAM = 0x03,
    SAVETOFLASH = 0xF4, // 0x04
    GETRESULT = 0x06,
    RESTOREFORMFLASH = 0x04,
    START_STREAM = 0x07,
    STOP_STREAM = 0x08
  };

  std::unique_ptr<SerialManager> m_SerialManager{nullptr};
  std::chrono::milliseconds m_Timer{5000};
};

} // namespace RF60X
} // namespace SCANNERS
} // namespace SDK
