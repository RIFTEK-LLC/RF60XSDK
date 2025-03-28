#include "rf60Xsdk.h"

#include "serialmanager.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

int SDK::SCANNERS::RF60X::sdk_version() { return 2; }
namespace SDK {
namespace SCANNERS {
namespace RF60X {

/**
 * Replaces specific bits in a byte with new values.
 *
 * @param byte: The original byte.
 * @param replacement: The new value to replace the bits with.
 * @param mask: The mask indicating which bits to replace.
 * @return The byte with the specified bits replaced.
 */
uint8_t replaceBits(uint8_t byte, uint8_t replacement, uint8_t mask) {
  return (byte & ~mask) | (replacement & mask);
}

/**
 * @brief Destructor for the rf60x class.
 * 
 * This destructor is responsible for cleaning up any resources allocated by the rf60x class.
 * It is automatically called when an object of the rf60x class goes out of scope or is explicitly deleted.
 * 
 * @note This destructor is set to the default implementation.
 * 
 */
rf60x::~rf60x() = default;
rf60x::rf60x() : m_SerialManager(std::make_unique<SerialManager>()) {}

rf60x::rf60x(const rf60x &other)
    : m_NetworkAddress(other.m_NetworkAddress),
      m_SerialManager(std::make_unique<SerialManager>()), m_Timer(other.m_Timer) {}

rf60x &rf60x::operator=(const rf60x &other) {
  if (this != &other) {

    if (m_SerialManager) {
      m_SerialManager.reset();
    }
    m_SerialManager = std::make_unique<SerialManager>();
    m_Timer = other.m_Timer;
    m_NetworkAddress = other.m_NetworkAddress;
  }
  return *this;
}

rf60x::rf60x(rf60x &&other) noexcept
    : m_NetworkAddress{std::exchange(other.m_NetworkAddress,0)},
      m_SerialManager{std::exchange(other.m_SerialManager,nullptr)}, m_Timer{std::exchange(other.m_Timer,std::chrono::milliseconds(0))} {

}

rf60x &rf60x::operator=(rf60x &&other) noexcept {
  if (this != &other) {
    m_SerialManager = std::move(other.m_SerialManager);
    m_NetworkAddress = other.m_NetworkAddress;
    m_Timer = other.m_Timer;
    other.m_NetworkAddress = 0;
    other.m_Timer = std::chrono::milliseconds(0);
    other.m_SerialManager = nullptr;
  }
  return *this;
}

/**
 * Sends a custom command to a device and receives a response.
 * Extracts specific information from the response and returns it as a struct.
 *
 * @return The extracted information as a struct of type `uart_hello_t`.
 */
uart_hello_t rf60x::hello_msg_uart() {
  // Construct the command buffer
  char ucBuffer[2]{};
  ucBuffer[0] = static_cast<char>(m_NetworkAddress & 0xFF);
  ucBuffer[1] = static_cast<char>(0x80 | (static_cast<char>(RF60X_COMMAND::HELLO) & 0x0F));

  // Send the command buffer to the device
  if (!request_custom_command(ucBuffer, 2)) {
    return {}; // Return an empty struct if the command fails
  }

  // Read the response from the device
  char tempButeBufferArray[sizeof(uart_hello_t) * 2];
  size_t sizeType = sizeof(tempButeBufferArray);

  if (!read_data_burst(tempButeBufferArray, sizeType))
    return {};

  // Extract specific information from the buffer and assign it to the fields of
  // the struct
  uart_hello_t tempHello = {};
  tempHello.deviceType = (tempButeBufferArray[0] & 0x0F) |
                         ((tempButeBufferArray[1] & 0x0F) << 4);
  tempHello.deviceModificaton = (tempButeBufferArray[2] & 0x0F) |
                                ((tempButeBufferArray[3] & 0x0F) << 4);
  tempHello.deviceSerial = (tempButeBufferArray[4] & 0x0F) |
                           ((tempButeBufferArray[5] & 0x0F) << 4) |
                           ((tempButeBufferArray[6] & 0x0F) << 8) |
                           ((tempButeBufferArray[7] & 0x0F) << 12);
  tempHello.deviceMaxDistance = ((tempButeBufferArray[8] & 0x0F) |
                                 ((tempButeBufferArray[9] & 0x0F) << 4) |
                                 ((tempButeBufferArray[10] & 0x0F) << 8) |
                                 ((tempButeBufferArray[11] & 0x0F) << 12));
  tempHello.deviceRange = ((tempButeBufferArray[12] & 0x0F) |
                           ((tempButeBufferArray[13] & 0x0F) << 4) |
                           ((tempButeBufferArray[14] & 0x0F) << 8) |
                           ((tempButeBufferArray[15] & 0x0F) << 12));

  return tempHello;
}

void rf60x::bind_network_address(uint32_t value) { m_NetworkAddress = value; }

void rf60x::set_wait_timer(std::chrono::milliseconds value) {

  m_SerialManager->set_timeout(value);
}

bool rf60x::set_sensor(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::USER_POWER);
}

bool rf60x::set_analog_out(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::POWER_ANALOG_OUTPUT);
}

bool rf60x::set_AL_mode(AL_MODE value) {

  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return false;
  uint8_t mask = 0b01001100;
  uint8_t newValue =
      replaceBits(currentValue.second, static_cast<uint8_t>(value), mask);

  return set_param(newValue, CODE::PARAM_NAME_KEY::CONTROL_OF_AVERAGING);
}

bool rf60x::set_averaging_mode(AVERAGING_MODE value) {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return false;
  uint8_t mask = 0b00100000;
  uint8_t newValue =
      replaceBits(currentValue.second, static_cast<uint8_t>(value), mask);

  return set_param(newValue, CODE::PARAM_NAME_KEY::CONTROL_OF_AVERAGING);
}

bool rf60x::set_analog_ouput_mode(ANALOG_OUTPUT_MODE value) {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return false;
  uint8_t mask = 0b00000010;
  uint8_t newValue =
      replaceBits(currentValue.second, static_cast<uint8_t>(value), mask);

  return set_param(newValue, CODE::PARAM_NAME_KEY::CONTROL_OF_AVERAGING);
}

bool rf60x::set_sampling_mode(SAMPLING_MODE value) {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return false;
  uint8_t mask = 0b00000001;
  uint8_t newValue =
      replaceBits(currentValue.second, static_cast<uint8_t>(value), mask);

  return set_param(newValue, CODE::PARAM_NAME_KEY::CONTROL_OF_AVERAGING);
}

bool rf60x::set_network_address(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::NETWORK_ADDRESS_UART);
}

bool rf60x::set_baute_rate(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::BAUD_RATE_UART);
}

bool rf60x::set_number_of_averaged_values(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::NUMBER_OF_AVERAGED_VALUES);
}

bool rf60x::set_sampling_period(uint16_t value) {
  return set_param(value,
                   CODE::PARAM_NAME_KEY::LOW_BYTE_OF_THE_SAMPLING_PERIOD);
}

bool rf60x::set_maximum_integration_time(uint16_t value) {
  return set_param(value,
                   CODE::PARAM_NAME_KEY::LOW_BYTE_OF_MAX_INTEGRATION_TIME);
}

bool rf60x::set_begin_analog_range(uint16_t value) {
  return set_param(
      value,
      CODE::PARAM_NAME_KEY::LOW_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE);
}

bool rf60x::set_end_analog_range(uint16_t value) {
  return set_param(
      value, CODE::PARAM_NAME_KEY::LOW_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE);
}

bool rf60x::set_time_lock_of_result(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::TIME_LOCK_OF_RESULT);
}

bool rf60x::set_zero_point(uint16_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::LOW_BYTE_OF_A_ZERO_POINT);
}

bool rf60x::set_CAN_interface_speed(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::TIME_LOCK_OF_RESULT);
}

bool rf60x::set_standard_identifier(uint16_t value) {
  return set_param(value,
                   CODE::PARAM_NAME_KEY::LOW_BYTE_OF_STANDARD_IDENTIFIER);
}

bool rf60x::set_extend_identifier(uint32_t value) {
  return set_param(value,
                   CODE::PARAM_NAME_KEY::ZERO_BYTE_OF_EXTENDED_IDENTIFIER);
}

bool rf60x::set_CAN_interface_identifier(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::CAN_INTERFACE_IDENTIFIER);
}

bool rf60x::set_CAN_interface(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::CAN_INTERFACE_IDENTIFIER);
}

bool rf60x::set_destination_ip_address(std::string value) {

  return set_param(converIPString(value),
                   CODE::PARAM_NAME_KEY::ZERO_BYTE_OF_DESTINATION_IP_ADDRESS);
}

bool rf60x::set_gateway_ip_address(std::string value) {

  return set_param(converIPString(value),
                   CODE::PARAM_NAME_KEY::ZERO_BYTE_OF_GATEWAY_IP_ADDRESS);
}

bool rf60x::set_subnet_mask(std::string value) {

  return set_param(converIPString(value),
                   CODE::PARAM_NAME_KEY::ZERO_BYTE_OF_SUBNET_MASK);
}

bool rf60x::set_source_ip_address(std::string value) {

  return set_param(converIPString(value),
                   CODE::PARAM_NAME_KEY::ZERO_BYTE_OF_SOURCE_IP_ADDRESS);
}

bool rf60x::set_number_of_measurements_in_the_packet(uint16_t value) {
  return set_param(value,
                   CODE::LOW_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET);
}

bool rf60x::set_ethernet_inteface(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::ETH_INTERFACE_ON_OFF);
}

bool rf60x::set_autostart_of_measurement_stream(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::AUTO_OF_THE_STREAM);
}

bool rf60x::set_protol_type(uint8_t value) {
  return set_param(value, CODE::PARAM_NAME_KEY::PROTOCOLS_INTERFACE);
}

bool rf60x::open_serial_port(std::string comPortName, uint32_t baudRate) {
  try {
    m_SerialManager->setBaud_rate(static_cast<BAUR_RATE_UART>(baudRate));
    return m_SerialManager->open_serial_port(comPortName);
  } catch (std::system_error &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return false;
  }
}

void rf60x::close_serial_port() { m_SerialManager->close_serial_port(); }

bool rf60x::get_raw_measure_uart(char* bufferArray, size_t size) {
  return read_data_burst(bufferArray, size);
}

bool rf60x::read_data_burst(char* buffer, size_t size) {
  size_t read = 0;
#ifdef DEBUG_READ_DATA_BURST
  std::cout << "READ " << size << " bytes:";
#endif

  while (read != size) {
    // size > 0 here
    try {
      if (!m_SerialManager->read_command(buffer + read, size - read))
        return false;
    } catch (const std::exception& e) {
      std::cout << "Error when reading serial port: " << e.what() << std::endl;
      return false;
    }

#ifdef DEBUG_READ_DATA_BURST
    for (size_t i = read; i < size; i++)
      std::cout << " " << std::hex << (int)((unsigned char) buffer[i]) << std::dec;
#endif

    // Count the number of bytes from the same burst in the buffer beginning.
    char byteLo = buffer[0] & 0xF0;
    while (read < size && (char) (buffer[read] & 0xF0) == byteLo)
      ++read;

    // If the buffer is inconsistent:
    // - drop the beginning
    // - keep only the last consistent bytes.
    if (read < size) {
#ifdef DEBUG_READ_DATA_BURST
      std::cout << " |";
#endif
      // Count the number of bytes from the same burst in the buffer end.
      byteLo = buffer[size - 1] & 0xF0;
      read = 1;
      while (read < size && (char) (buffer[size - read - 1] & 0xF0) == byteLo)
        ++read;

      // Move consistent data from the end to the beginning of the buffer.
      for (int i = 0; i < read; i++)
        buffer[i] = buffer[size - read + i];
    }
  }

#ifdef DEBUG_READ_DATA_BURST
  std::cout << "\n";
#endif

  return true;
}

bool rf60x::execute_flash_command(COMMAND_VALUE_PARAM_FLASH param_value)
{

    static constexpr std::size_t COMMAND_BUFFER_SIZE = 4;
    static constexpr std::size_t RESPONSE_BUFFER_SIZE = 2;
    static constexpr std::uint8_t HIGH_BIT_MASK = 0x80;
    static constexpr std::uint8_t LOW_NIBBLE_MASK = 0x0F;
    static constexpr std::uint8_t HIGH_NIBBLE_MASK = 0xF0;

    std::array<char, COMMAND_BUFFER_SIZE> command_buffer;

    const auto command_uart_val = static_cast<std::underlying_type_t<COMMAND_UART>>(COMMAND_UART::FLASH);


    const auto param_byte_val = static_cast<std::uint8_t>(param_value);

    command_buffer[0] = static_cast<unsigned char>(m_NetworkAddress & 0xFF);
    command_buffer[1] = HIGH_BIT_MASK | (static_cast<unsigned char>(command_uart_val) & LOW_NIBBLE_MASK);
    command_buffer[2] = HIGH_BIT_MASK | (param_byte_val & LOW_NIBBLE_MASK);
    command_buffer[3] = HIGH_BIT_MASK | ((param_byte_val>>4) & LOW_NIBBLE_MASK);

    if (!request_custom_command(command_buffer.data(), command_buffer.size())) {
        return false;
    }

    std::array<char, RESPONSE_BUFFER_SIZE> response_buffer;
    if (!read_data_burst(response_buffer.data(), response_buffer.size())) {

        return false;
    }

    const std::uint16_t response_value = static_cast<std::uint8_t>(response_buffer[0] & 0x0F) |
                                         (static_cast<std::uint8_t>(response_buffer[1]& 0x0F) << 4);


    const std::uint16_t expected_value = static_cast<std::uint16_t>(param_value);

    if (response_value != expected_value) {

        return false;
    }

    return true;
}


bool rf60x::write_params_to_flash() {
    return execute_flash_command(COMMAND_VALUE_PARAM_FLASH::FLASH);
}

bool rf60x::write_factory_params() {
    return execute_flash_command(COMMAND_VALUE_PARAM_FLASH::FACTORY);
}

bool rf60x::restore_default_params() {
    return execute_flash_command(COMMAND_VALUE_PARAM_FLASH::RESET_DEFAULT_PARAMS_MEMORY);
}



bool rf60x::get_single_measure(void *measure) {

  if (!send_command(COMMAND_UART::GETRESULT)) {
    return false;
  }
  return this->get_measure_uart(measure,
                                PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T);
}

bool rf60x::send_command(COMMAND_UART value) {
  char ucBuffer[2];

  ucBuffer[0] = m_NetworkAddress & 0xFF;
  ucBuffer[1] = 0x80 | (static_cast<char>(value) & 0x0F);

  if (!request_custom_command(ucBuffer, 2)) {
    return false;
  }

  return true;
}

bool rf60x::read_custom_command(uint8_t command, uint8_t size,
                                std::vector<char> &vec_ref) {
  vec_ref.resize(size);
  return read_data_burst(vec_ref.data(), size);
}

bool rf60x::request_custom_command(char *data, uint8_t size) {

  return m_SerialManager->write_command(data, size);
}

bool rf60x::get_measure_uart(void* measure, PROTOCOL_MEASURE_UART type) {
    size_t sizeType = static_cast<size_t>(type);
    char tempButeBufferArray[12];

    if (!read_data_burst(tempButeBufferArray, sizeType)) {
        return false;
    }

    switch (type) {
    case PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T: {
        uint8_t tempCNT = (tempButeBufferArray[0] & 0x30) >> 4;
        reinterpret_cast<uart_stream_measure_t*>(measure)->count = tempCNT;

        reinterpret_cast<uart_stream_measure_t*>(measure)->value =
            (tempButeBufferArray[0] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4 |
            (tempButeBufferArray[2] & 0x0F) << 8 |
            (tempButeBufferArray[3] & 0x0F) << 12;
        reinterpret_cast<uart_stream_measure_t*>(measure)->status =
            (tempButeBufferArray[0] & 0x40) >> 6;

        break;
    }
    case PROTOCOL_MEASURE_UART::UART_RESULT_WITH_ENCODER_T: {
        reinterpret_cast<uart_result_with_encoder_t*>(measure)->measure =
            (tempButeBufferArray[0] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4 |
            (tempButeBufferArray[2] & 0x0F) << 8 |
            (tempButeBufferArray[3] & 0x0F) << 12;
        reinterpret_cast<uart_result_with_encoder_t*>(measure)->rotationMarks =
            (tempButeBufferArray[4] & 0x0F) | (tempButeBufferArray[5] & 0x0F) << 4 |
            (tempButeBufferArray[6] & 0x0F) << 8 |
            (tempButeBufferArray[7] & 0x0F) << 12;
        reinterpret_cast<uart_result_with_encoder_t*>(measure)->encoderValue =
            (tempButeBufferArray[8] & 0x0F) | (tempButeBufferArray[9] & 0x0F) << 4 |
            (tempButeBufferArray[10] & 0x0F) << 8 |
            (tempButeBufferArray[11] & 0x0F) << 12;
        break;
    }
    case PROTOCOL_MEASURE_UART::UART_STREAM_ADVANCED_MEASURE_T: {
        uint8_t tempCNT = (tempButeBufferArray[0] & 0x30) >> 4;

        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->cnt = tempCNT;

        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->value =
            (tempButeBufferArray[0] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4 |
            (tempButeBufferArray[2] & 0x0F) << 8 |
            (tempButeBufferArray[3] & 0x0F) << 12;
        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->status =
            (tempButeBufferArray[0] & 0x40) >> 6;

        uint8_t advanced =
            (tempButeBufferArray[4] & 0x0F) | (tempButeBufferArray[5] & 0x0F) << 4;

        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->status =
            (advanced >> 0) & 1;

        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->dir =
            (advanced >> 1) & 1;

        reinterpret_cast<uart_stream_advanced_measure_t*>(measure)->cnt =
            (advanced >> 2) & 1;

        break;
    }

    case PROTOCOL_MEASURE_UART::UART_STREAM_MODIFIED_MEASURE_T: {

        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->value =
            (tempButeBufferArray[0] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4 |
            (tempButeBufferArray[2] & 0x0F) << 8 |
            (tempButeBufferArray[3] & 0x0F) << 12;
        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->status =
            (tempButeBufferArray[0] & 0x40) >> 6;

        uint8_t advanced =
            (tempButeBufferArray[4] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4;

        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->status =
            (advanced >> 0) & 1;

        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->dir =
            (advanced >> 1) & 1;

        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->cnt =
            (advanced >> 2) & 1;

        reinterpret_cast<uart_stream_modified_measure_t*>(measure)->cnt_stream =
            (tempButeBufferArray[6] & 0x0F) | (tempButeBufferArray[7] & 0x0F) << 4 |
            (tempButeBufferArray[8] & 0x0F) << 8 |
            (tempButeBufferArray[9] & 0x0F) << 12;

        break;
    }

    case PROTOCOL_MEASURE_UART::UART_STREAM_EXTENDED_T: {
        reinterpret_cast<uart_stream_extended_measure_t*>(measure)->value =
            (tempButeBufferArray[0] & 0x0F) | (tempButeBufferArray[1] & 0x0F) << 4 |
            (tempButeBufferArray[2] & 0x0F) << 8 |
            (tempButeBufferArray[3] & 0x0F) << 12;

        reinterpret_cast<uart_stream_extended_measure_t*>(measure)->counter =
            (tempButeBufferArray[4] & 0x0F) | (tempButeBufferArray[5] & 0x0F) << 4 |
            (tempButeBufferArray[6] & 0x0F) << 8 |
            (tempButeBufferArray[7] & 0x0F) << 12;
        break;

    }

 return true;
    }
    return false;
}

// enum class someenum
//{
//     e1,
//     e2
// };

// template <someenum T>
// struct someMap;

// template <> struct someMap<someenum::e1> {using return_t = uint32_t;};

// template <someenum T>
// typename someMap<T>::return_t foo()
//{
//   return 0;
// }

// void goo()
//{
//   foo<someenum::e1>();
// }

template <typename T>
std::pair<bool, T> rf60x::get_param(CODE::PARAM_NAME_KEY key) {
  std::vector<char> ip_values;
  T result = 0;
  size_t num_bytes = sizeof(T);

  char ucBuffer[4];
  ucBuffer[0] = m_NetworkAddress & 0xFF;
  ucBuffer[1] = 0x80 | (static_cast<char>(RF60X_COMMAND::READPARAM) & 0x0F); //

  try {
    for (int i = 0; i < num_bytes; i++) {
      uint8_t param_key = key + i;

      ucBuffer[2] = 0x80 | (param_key & 0x0F);
      ucBuffer[3] = 0x80 | ((param_key >> 4) & 0x0F);

      if (!request_custom_command(ucBuffer, 4)) {
        return {false, 0};
      }

      if (!read_custom_command(param_key, 2, ip_values)) {
        return {false, 0};
      }

      result |= static_cast<int>((ip_values.at(0) & 0x0F) |
                                 ((ip_values.at(1) & 0x0F) << 4))
                << (8 * i);

      ip_values.clear();
    }

    return {true, result};
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return {false, 0};
  }
}

template <typename T>
bool rf60x::set_param(const T &value, CODE::PARAM_NAME_KEY key) {
  char ucBuffer[6];
  const std::size_t size = sizeof(T);
  const std::uint8_t *bytes = reinterpret_cast<const std::uint8_t *>(&value);

  std::cout << "Value: " << value << std::endl;
  std::cout << "Bytes: ";

  ucBuffer[0] = m_NetworkAddress & 0xFF;
  ucBuffer[1] = 0x80 | (static_cast<uint8_t>(RF60X_COMMAND::WRITEPARAM) & 0x0F);

  try {
    for (std::size_t i = 0; i < size; ++i) {
      uint8_t param_key = key + i;

      ucBuffer[2] = 0x80 | (param_key & 0x0F);
      ucBuffer[3] = 0x80 | ((param_key >> 4) & 0x0F);

      std::cout << std::hex << static_cast<int>(bytes[i]) << " ";

      ucBuffer[4] = 0x80 | ((bytes[i] & 0x000F));
      ucBuffer[5] = 0x80 | (((bytes[i] & 0x00F0) >> 4));

      if (!request_custom_command(ucBuffer, 6)) {
        return false;
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return false;
  }

  return true;
}

template <typename T, typename U> std::pair<bool, U> rf60x::get_param_2(T key) {

  std::vector<char> ip_values;
  U result = 0;
  size_t num_bytes = sizeof(T);

  char ucBuffer[4];
  ucBuffer[0] = m_NetworkAddress & 0xFF;
  ucBuffer[1] =
      0x80 | (static_cast<uint8_t>(RF60X_COMMAND::READPARAM) & 0x0F); //

  try {
    for (int i = 0; i < num_bytes; i++) {
      uint8_t param_key = static_cast<uint8_t>(key) + i;

      ucBuffer[2] = 0x80 | (param_key & 0x0F);
      ucBuffer[3] = 0x80 | ((param_key >> 4) & 0x0F);

      if (!request_custom_command(ucBuffer, 4)) {
        return {false, 0};
      }

      if (!read_custom_command(param_key, 2, ip_values)) {
        return {false, 0};
      }

      result |= static_cast<int>((ip_values.at(0) & 0x0F) |
                                 ((ip_values.at(1) & 0x0F) << 4))
                << (8 * i);

      ip_values.clear();
    }

    return {true, result};
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return {false, 0};
  }
}

std::pair<bool, uint8_t> rf60x::get_sensor() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::USER_POWER);
}

std::pair<bool, uint8_t> rf60x::get_analog_out() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::POWER_ANALOG_OUTPUT);
}

std::pair<bool, AL_MODE> rf60x::get_AL_mode() {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return {false, AL_MODE::OUT_OF_RANGE};
  uint8_t mask = 0b01001100;

  return {true, static_cast<AL_MODE>(currentValue.second & mask)};
}

std::pair<bool, AVERAGING_MODE> rf60x::get_averaging_mode() {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return {false, AVERAGING_MODE::AVERAGING_OVER_RESULTS};
  uint8_t mask = 0b00100000;

  return {true, static_cast<AVERAGING_MODE>(currentValue.second & mask)};
}

std::pair<bool, ANALOG_OUTPUT_MODE> rf60x::get_analog_ouput_mode() {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return {false, ANALOG_OUTPUT_MODE::WINDOW_MODE};
  uint8_t mask = 0b00000010;

  return {true, static_cast<ANALOG_OUTPUT_MODE>(currentValue.second & mask)};
}

std::pair<bool, SAMPLING_MODE> rf60x::get_sampling_mode() {
  auto currentValue =
      get_param_2(CODE::PARAM_NAME_KEY_BYTE::CONTROL_OF_AVERAGING);

  if (!currentValue.first)
    return {false, SAMPLING_MODE::TIME_SAMPLING};
  uint8_t mask = 0b00000001;

  return {true, static_cast<SAMPLING_MODE>(currentValue.second & mask)};
}

std::pair<bool, uint8_t> rf60x::get_network_address() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::NETWORK_ADDRESS_UART);
}

std::pair<bool, uint8_t> rf60x::get_baute_rate() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::BAUD_RATE_UART);
}

std::pair<bool, uint8_t> rf60x::get_number_of_averaged_values() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::NUMBER_OF_AVERAGED_VALUES);
}

std::pair<bool, uint16_t> rf60x::get_sampling_period() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_USHORT::LOW_BYTE_OF_THE_SAMPLING_PERIOD);
}

std::pair<bool, uint16_t> rf60x::get_maximum_integration_time() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_USHORT::LOW_BYTE_OF_MAX_INTEGRATION_TIME);
}

std::pair<bool, uint16_t> rf60x::get_begin_analog_range() {
  return get_param_2(CODE::PARAM_NAME_KEY_USHORT::
                         LOW_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE);
}

std::pair<bool, uint16_t> rf60x::get_end_analog_range() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_USHORT::LOW_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE);
}

std::pair<bool, uint8_t> rf60x::get_time_lock_of_result() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::TIME_LOCK_OF_RESULT);
}

std::pair<bool, uint16_t> rf60x::get_zero_point() {
  return get_param_2(CODE::PARAM_NAME_KEY_USHORT::LOW_BYTE_OF_A_ZERO_POINT);
}

std::pair<bool, uint8_t> rf60x::get_CAN_interface_speed() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_BYTE::DATA_TRANSFER_RATE_VIA_CAN_INTERFACE);
}

std::pair<bool, uint16_t> rf60x::get_standard_identifier() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_USHORT::LOW_BYTE_OF_STANDARD_IDENTIFIER);
}

std::pair<bool, uint32_t> rf60x::get_extend_identifier() {
  return get_param_2(
      CODE::PARAM_NAME_KEY_UINT::ZERO_BYTE_OF_EXTENDED_IDENTIFIER);
}

std::pair<bool, uint8_t> rf60x::get_CAN_interface_identifier() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::CAN_INTERFACE_IDENTIFIER);
}

std::pair<bool, uint8_t> rf60x::get_CAN_interface() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::CAN_INTERFACE_POWER_SWITCH);
}

std::pair<bool, std::string> rf60x::get_source_ip_address() {
  return get_ip_address(CODE::PARAM_NAME_KEY::THIRD_BYTE_OF_SOURCE_IP_ADDRESS);
}

std::pair<bool, std::string> rf60x::get_destination_ip_address() {
  return get_ip_address(
      CODE::PARAM_NAME_KEY::THIRD_BYTE_OF_DESTINATION_IP_ADDRESS);
}

std::pair<bool, std::string> rf60x::get_gateway_ip_address() {
  return get_ip_address(CODE::PARAM_NAME_KEY::THIRD_BYTE_OF_GATEWAY_IP_ADDRESS);
}

std::pair<bool, std::string> rf60x::get_subnet_mask() {
  return get_ip_address(CODE::PARAM_NAME_KEY::THIRD_BYTE_OF_SUBNET_MASK);
}

std::pair<bool, uint16_t> rf60x::get_number_of_measurements_in_the_packet() {
  return get_param_2(CODE::PARAM_NAME_KEY_USHORT::
                         LOW_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET);
}

std::pair<bool, uint8_t> rf60x::get_ethernet_inteface() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::ETH_INTERFACE_ON_OFF);
}

std::pair<bool, uint8_t> rf60x::get_autostart_of_measurement_stream() {
  return get_param_2(CODE::PARAM_NAME_KEY_BYTE::AUTO_OF_THE_STREAM);
}

std::pair<bool, uint8_t> rf60x::get_protocol_type() {

 return get_param<uint16_t>(CODE::PARAM_NAME_KEY::PROTOCOLS_INTERFACE);
}

void rf60x::clear_serial_buffer()
{
    m_SerialManager->clear_IO_buffer();
}


bool rf60x::connect_udp(const std::string &hostAddress, uint32_t port) {
  return m_SerialManager->connect_udp(hostAddress, port);
}

void rf60x::disconnect_udp() { return m_SerialManager->disconnect_udp(); }

template <typename T> bool rf60x::get_measure_udp(T &protocolUDP) {
  return m_SerialManager->get_measure_udp(
      reinterpret_cast<char *>(&protocolUDP), sizeof(protocolUDP));
}

std::pair<bool, std::string> rf60x::get_ip_address(CODE::PARAM_NAME_KEY key) {
  std::vector<char> ip_values;
  bool result = 0;

  char ucBuffer[4];
  ucBuffer[0] = m_NetworkAddress & 0xFF;
  ucBuffer[1] = 0x80 | (static_cast<char>(RF60X_COMMAND::READPARAM) & 0x0F); //

  try {
    std::ostringstream oss;

    for (int i = 0; i < 4; i++) {
      uint8_t const param_key = key - i;

      ucBuffer[2] = 0x80 | (param_key & 0x0F);
      ucBuffer[3] = 0x80 | ((param_key >> 4) & 0x0F);

      if (!request_custom_command(ucBuffer, 4)) {
        return {false, "An error occurred while sending the request."};
      }

      if (!read_custom_command(param_key, 2, ip_values)) {
        return {false, "An error occurred while reading the query response."};
      }


      oss << static_cast<int>((ip_values.at(0) & 0x0F) |
                              ((ip_values.at(1) & 0x0F) << 4));

      ip_values.clear();
      if (i < 3) {
        oss << ".";
      }
    }

    return {true, oss.str()};
  } catch (std::exception &e) {
    return {false, e.what()};
  }
}

uint32_t rf60x::converIPString(const std::string &str) {
  uint8_t ipValues[4];

  sscanf(str.c_str(), "%hhu.%hhu.%hhu.%hhu", &ipValues[0],
                        &ipValues[1], &ipValues[2], &ipValues[3]);

  return (ipValues[0] << 24) | (ipValues[1] << 16) | (ipValues[2] << 8) |
         (ipValues[3]);
}
template bool rf60x::get_measure_udp(udp_measure_t &);
template bool rf60x::get_measure_udp(binocular_udp_measure_t &);

} // namespace RF60X
} // namespace SCANNERS
} // namespace SDK
