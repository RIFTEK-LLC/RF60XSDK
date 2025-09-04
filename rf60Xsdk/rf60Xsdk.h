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

  /**
   * Binds the RF60X scanner's network address to the specified value for UART
   * protocols.
   *
   * @param value The network address to bind to the RF60X scanner.
   */
  void bind_network_address(uint32_t value);

  uart_hello_t hello_msg_uart();

  /**
   * Sets the wait timer to the specified value.
   *
   * @param value The wait timer value in milliseconds.
   */
  void set_wait_timer(std::chrono::milliseconds value);

  /**
   * Sets the sensor laser power value to the specified value.
   *
   * @param value The sensor value.
   * @return True if the sensor value was successfully set, false otherwise.
   */
  bool set_sensor(uint8_t value);

  /**
   * Sets the analog output power of the RF60X scanner.
   *
   * This function sets the analog output power of the RF60X scanner to the
   * specified value.
   *
   * @param value The value to set the analog output power to.
   * @return True if the analog output power was successfully set, false
   * otherwise.
   */
  bool set_analog_out(uint8_t value);

  /**
   * Sets the AL mode of the RF60X scanner.
   *
   * @param value The AL mode to set. This should be one of the values from the
   * AL_MODE enum, which can be one of the following:
   *              - out of the range indication (by default);
   *              - 'slave' mode (mutual synchronization);
   *              - hardware zero set mode;
   *              - laser switch OFF/ON;
   *              - encoder mode input mode;
   *              - reset of the Ethernet packets counter;
   *              - 'master' mode (mutual synchronization).
   * @return True if the AL mode was successfully set, false otherwise.
   */
  bool set_AL_mode(AL_MODE value); //

  /**
   * Sets the averaging mode for the RF60X scanner.
   *
   * This function sets the averaging mode for the RF60X scanner. The averaging
   mode determines how the scanner calculates the average value of multiple
   measurements.

   * @param value The averaging mode to set. This should be one of the values
   from the AVERAGING_MODE enum.
   *   which can be one of the following:
   *   -averaging over a number of results (by default);
   *   -time averaging (5 ms).
   * @return True if the averaging mode was successfully set, false otherwise.
   */
  bool set_averaging_mode(AVERAGING_MODE value);

  /**
   * Sets the analog output mode of the RF60X scanner.
   *
   * This function sets the analog output mode of the RF60X scanner to the
   * specified value.
   *
   * @param value The value to set the analog output mode to. This should be one
   * of the values from the ANALOG_OUTPUT_MODE enum. which can be one of the
   * following: -window mode (by default); -full range.
   * @return True if the analog output mode was successfully set, false
   * otherwise.
   */
  bool set_analog_ouput_mode(ANALOG_OUTPUT_MODE value);

  /**
   * Sets the sampling mode of the RF60X scanner.
   *
   * This function sets the sampling mode of the RF60X scanner to the specified
   * value.
   *
   * @param value The value to set the sampling mode to. This should be one of
   * the values from the SAMPLING_MODE enum. which can be one of the following:
   *   -time sampling (by default)
   *   -trigger sampling.
   * @return True if the sampling mode was successfully set, false otherwise.
   */
  bool set_sampling_mode(SAMPLING_MODE value);

  /**
   * Sets the network address ( RS-485 ) to the specified value.
   *
   * @param value The value to set the network address to.
   * @return True if the network address was successfully set, false otherwise.
   */
  bool set_network_address(uint8_t value);

  /**
   * Sets the baud rate to the specified value.
   *
   * @param value The value to set the baud rate to.
   * @return True if the baud rate was successfully set, false otherwise.
   */
  bool set_baute_rate(uint8_t value);

  /**
   * Sets the number of averaged values to the specified value.
   *
   * @param value The value to which you want to set the number of averaged
   * values and this value can be set in the range 1..128.
   * @return True if the number of averaged values was successfully set, false
   * otherwise.
   */
  bool set_number_of_averaged_values(uint8_t value);
  /**
   * Sets the sampling period of the RF60X scanner.
   *
   * The function defines the time interval after which the sensor should
   * automatically transmit the measurement result. The time interval value is
   * set in in 1 µs increments.
   * @param value The value to set the sampling period to. (default 5000)
   * @return True if the sampling period was successfully set, false otherwise.
   */
  bool set_sampling_period(uint16_t value);

  /**
   * Sets the maximum integration time to the specified value.
   *
   * @param value The value to set the maximum integration time to. Can be set
   * in the range 2..3200. (default 3200)
   * @return True if the maximum integration time was successfully set, false
   * otherwise.
   */
  bool set_maximum_integration_time(uint16_t value);

  /**
   * Sets the beginning analog range to the specified value.
   *
   * @param value The value to set the beginning analog range to. Can be set in
   * the range 0..16383. (default 0)
   * @return True if the beginning analog range was successfully set, false
   * otherwise.
   */
  bool set_begin_analog_range(uint16_t value);

  /**
   * Sets the end analog range to the specified value.
   *
   * @param value The value to set the end analog range to.Can be set in the
   * range 0..16383. (default 16383)
   * @return True if the end analog range was successfully set, false otherwise.
   */
  bool set_end_analog_range(uint16_t value);

  /**
   * Sets the time lock of the result to the specified value.
   * This function sets the time interval in 5 ms increments.
   * @param value The value to set the time lock of the result to. Can be set in
   * the range 0..255.
   * @return True if the time lock of the result was successfully set, false
   * otherwise.
   */
  bool set_time_lock_of_result(uint8_t value);

  /**
   * Sets the zero point to the specified value.
   * This function set value indicates the start absolute coordinate system.
   * @param value The value to set the zero point to. Can be set in the range
   * 0..16383 (default 0).
   * @return True if the zero point was successfully set, false otherwise.
   */
  bool set_zero_point(uint16_t value);

  /**
   * Sets the CAN interface speed to the specified value.
   * This function set value sets the baud rate
   *  data in increments of 5,000 baud, for example the value 50
   *  sets the speed to 50*5,000= 250,000 baud.
   * @param value The value to set the CAN interface speed to. Can be set in the
   * range 10..200 (default 25).
   * @return True if the CAN interface speed was successfully set, false
   * otherwise.
   */
  bool set_CAN_interface_speed(uint8_t value);

  /**
   * Sets the standard identifier for the CAN interface.
   *
   * @param value The value of the standard identifier. Can be set in the range
   * 0x00..0x7FF. (default 0x7FF)
   * @return True if the standard identifier was successfully set, false
   * otherwise.
   */
  bool set_standard_identifier(uint16_t value);

  /**
   * Sets the extended identifier for the CAN interface.
   *
   * @param value The value of the extended identifier. Can be set in the range
   * 0x00..0x1FFFFFFF. (default 0x1FFFFFFF)
   * @return True if the extended identifier was successfully set, false
   * otherwise.
   */
  bool set_extend_identifier(uint32_t value);

  /**
   * Sets the CAN interface identifier.
   *
   * @param value The value of the CAN interface identifier.
   *  which can be one of the following:
   *  1 — extended identifier;
   *  0 — standard identifier.
   * @return True if the CAN interface identifier was successfully set, false
   * otherwise.
   */
  bool set_CAN_interface_identifier(uint8_t value);

  /**
   * Sets the CAN interface to the specified value.
   *
   * @param value The value to set the CAN interface to.
   *  which can be one of the following:
   *  1 — CAN interface ON;
   *  0 — CAN interface OFF.
   * @return True if the CAN interface was successfully set, false otherwise.
   */
  bool set_CAN_interface(uint8_t value);

  /**
   * Sets the destination IP address to the specified value.
   *
   * @param value The value to set the destination IP address to.
   * @return True if the destination IP address was successfully set, false
   * otherwise.
   */
  bool set_destination_ip_address(std::string value);

  /**
   * Sets the gateway IP address to the specified value.
   *
   * @param value The value to set the gateway IP address to.
   * @return True if the gateway IP address was successfully set, false
   * otherwise.
   */
  bool set_gateway_ip_address(std::string value);

  /**
   * Sets the subnet mask to the specified value.
   *
   * @param value The subnet mask value to set.
   * @return True if the subnet mask was successfully set, false otherwise.
   */
  bool set_subnet_mask(std::string value);

  /**
   * Sets the source IP address to the specified value.
   *
   * @param value The source IP address value to set.
   * @return True if the source IP address was successfully set, false
   * otherwise.
   */
  bool set_source_ip_address(std::string value);

  /**
   * Sets the number of measurements in the packet to the specified value.
   * This function set value specifies the number of measurements in one
   * Ethernet packet.
   * @param value The number of measurements in the packet value to set. Can be
   * set in the range 1..168. (default 168)
   * @return True if the number of measurements in the packet was successfully
   * set, false otherwise.
   */
  bool set_number_of_measurements_in_the_packet(uint16_t value);

  /**
   * Sets the Ethernet interface to the specified value.
   *
   * @param value The Ethernet interface value to set.
   *  which can be one of the following:
   * 1 — Ethernet interface ON (UDP);
   * 0 — Ethernet interface OFF.
   * @return True if the Ethernet interface was successfully set, false
   * otherwise.
   */
  bool set_ethernet_inteface(uint8_t value);

  /**
   * Sets the autostart of the measurement stream to the specified value.
   *
   * @param value The value to set for autostart of the measurement stream.
   * which can be one of the following:
   * 1 — autostart of the measurement stream ON;
   * 0 — autostart of the measurement stream OFF (default).
   * @return True if the autostart of the measurement stream was successfully
   * set, false otherwise.
   */
  bool set_autostart_of_measurement_stream(uint8_t value);

  /**
   * Sets the protocol type to the specified value.
   *
   * @param value The value to set for the protocol type.
   * which can be one of the following:
   * 2 - MODBUS RTU protocol;
   * 1 - ASCII protocol;
   * 0 - RIFTEK protocol (default).
   * @return True if the protocol type was successfully set, false otherwise.
   */
  bool set_protocol_type(uint8_t value);

  //-------------------------------------------------------//

  /**
   * Opens a serial port with the specified COM port name and baud rate.
   *
   * @param comPortName The name of the COM port to open.
   * @param baudRate The baud rate to use for the serial port.
   * @return True if the serial port was successfully opened, false otherwise.
   */
  bool open_serial_port(std::string comPortName, uint32_t baudRate);

  /**
   * Closes the currently open serial port.
   */
  void close_serial_port();

  /**
   * Receives raw measure data from UART.
   *
   * @param bufferArray The buffer to store the raw measure data.
   * @param size The size of the buffer.
   * @return True if the raw measure data was successfully retrieved, false
   * otherwise.
   */
  bool get_raw_measure_uart(char *bufferArray, size_t size);

  /**
   * Receives a single measure.
   *
   * @param measure The pointer to store the single measure.
   * @return True if the single measure was successfully retrieved, false
   * otherwise.
   */
  bool get_single_measure(void *measure);




  bool write_params_to_flash();

  bool write_factory_params();

  bool restore_default_params();

  /**
   * Sends a command via UART.
   *
   * @param value The command to send.
   * which can be one of the following:
   * - WRITEPARAM;
   * - SAVETOFLASH;
   * - RESTORE_FROM_FLASH;
   * - GETRESULT;
   * - START_STREAM;
   * - START_STREAM_ADVANCED;
   * - START_STREAM_MODIFIED;
   * - STOP_STREAM;
   * @return True if the command was successfully sent, false otherwise.
   */
  bool send_command(COMMAND_UART value);

  /**
   * Reads a custom command from the RF60X scanner.
   *
   * @param command The command code to be sent.
   * @param size The size of the command data.
   * @param vec_ref A reference to a vector to store the command response.
   * @return True if the command was successfully read, false otherwise.
   */
  bool read_custom_command(uint8_t command, uint8_t size,
                           std::vector<char> &vec_ref);

  /**
   * Requests a custom command from the RF60X scanner.
   *
   * @param data The command data to be sent.
   * @param size The size of the command data.
   * @return True if the command was successfully requested, false otherwise.
   */
  bool request_custom_command(char *data, uint8_t size);

  /**
   * Gets a measure from the RF60X scanner using UART protocol.
   *
   * @param measure A pointer to the memory location to store the measure.
   * @param type The type of the measure protocol.
   * which can be one of the following:
   *  - UART_STREAM_MEASURE_T;
   *  - UART_STREAM_ADVANCED_MEASURE_T;
   *  - UART_STREAM_MODIFIED_MEASURE_T;
   *  - UART_RESULT_WITH_ENCODER_T.
   *  
   * @return True if the measure was successfully retrieved, false otherwise.
   */
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

  std::pair<bool, std::string> get_destination_ip_address();

  std::pair<bool, std::string> get_gateway_ip_address();

  std::pair<bool, std::string> get_subnet_mask();

  std::pair<bool, uint16_t> get_number_of_measurements_in_the_packet();

  std::pair<bool, uint8_t> get_ethernet_inteface();

  std::pair<bool, uint8_t> get_autostart_of_measurement_stream();

  std::pair<bool, uint8_t> get_protocol_type();

  void clear_serial_buffer();

  /**
   * Connects to a UDP server at the specified host address and port.
   *
   * @param hostAddress The IP address or hostname of the UDP server.
   * @param port The port number of the UDP server.
   * @return True if the connection is successful, false otherwise.
   */
  bool connect_udp(const std::string &hostAddress, uint32_t port);

  /**
   * Disconnects from the UDP server.
   */
  void disconnect_udp();
  /**
   * Retrieves a measure using the UDP protocol.
   *
   * @param T The type of the protocolUDP parameter.
   * @param protocolUDP The UDP protocol object used to retrieve the measure.
   * @return True if the measure was successfully retrieved, false otherwise.
   */
  template <typename T> bool get_measure_udp(T &protocolUDP);


  /**
   * Retrieves a measure using the UDP protocol.
   * This method uses synchronous operations for receiving data from a socket.
   *
   * @param T The type of the protocolUDP parameter.
   * @param protocolUDP The UDP protocol object used to retrieve the measure.
   * @return True if the measure was successfully retrieved, false otherwise.
   */

  template <typename T> bool get_measure_udp_sync(T &protocolUDP);

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
  template <typename T,
            typename U = typename std::enable_if_t<
                std::is_enum<T>::value, typename std::underlying_type_t<T>>>
  std::pair<bool, U> get_param_2(T key);

  template <typename T>
  bool set_param(const T &value, CODE::PARAM_NAME_KEY key);

  /**
   * Converts an IP address string to a 32-bit unsigned integer representation.
   * The IP address string should be in the format "x.x.x.x", where x is a
   * decimal number between 0 and 255. Returns the 32-bit unsigned integer
   * representation of the IP address.
   */
  uint32_t converIPString(const std::string &str);

  /**
   * Enum class RF60X_COMMAND represents the commands used in the RF60X class.
   * The available commands are:
   * - HELLO;
   * - READPARAM;
   * - WRITEPARAM;
   * - SAVETOFLASH;
   * - GETRESULT;
   * - RESTOREFORMFLASH;
   * - START_STREAM;
   * - STOP_STREAM;
   */
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

  /**
   * This code snippet declares a unique pointer variable named m_SerialManager
   * of type SerialManager and initializes it with a nullptr.
   */
  std::unique_ptr<SerialManager> m_SerialManager{nullptr};
  /**
   * Initializes a std::chrono::milliseconds object with a value of 5000
   * milliseconds.
   */
  std::chrono::milliseconds m_Timer{5000};

  bool read_data_burst(char* buffer, size_t size);

  bool execute_flash_command(COMMAND_VALUE_PARAM_FLASH param_value);
};

} // namespace RF60X
} // namespace SCANNERS
} // namespace SDK
