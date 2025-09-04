#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cstdint>
typedef struct {
  uint16_t measure;
  uint16_t rotationMarks;
  uint16_t encoderValue;
} uart_result_with_encoder_t;

#pragma pack(push, 1)
typedef struct {
  uint16_t value;
  uint8_t status;
} udp_value_t;

typedef struct {
  udp_value_t rf60xValArray[168];
  uint16_t deviceSerial;
  uint16_t deviceBaseDistance;
  uint16_t deviceMeasureRange;
  uint8_t packCount;
  uint8_t packetControlSumm;
} udp_measure_t;

typedef struct {
  uint16_t measure;
  uint16_t exposition;
  uint8_t status;
} binocular_udp_value_t;

typedef struct {
  binocular_udp_value_t rf60xBValArray[100];
  uint16_t reserved;
  uint16_t reserved2;
  uint16_t deviceSerial;
  uint16_t deviceBaseDistance;
  uint16_t deviceMeasureRange;
  uint8_t packCount;
  uint8_t packetControlSumm;
} binocular_udp_measure_t;

#pragma pack(pop)

typedef struct {
    uint16_t value;
    uint16_t counter;
}uart_stream_extended_measure_t;

typedef struct {
  uint16_t value;
  uint8_t count;
  uint8_t status;
  uint8_t reserverd;
} uart_stream_measure_t;

typedef struct {
  uint16_t value;
  uint8_t status;
  uint8_t dir;
  uint8_t cnt;
} uart_stream_advanced_measure_t;

typedef struct {
  uint16_t value;
  uint8_t status;
  uint8_t dir;
  uint8_t cnt;
  uint16_t cnt_stream;
} uart_stream_modified_measure_t;

typedef struct {
  uint8_t deviceType;
  uint8_t deviceModificaton;
  uint16_t deviceSerial;
  uint16_t deviceMaxDistance;
  uint16_t deviceRange;

} uart_hello_t;

typedef struct {
  uint8_t id;
  uint8_t command;
  uint16_t address;
  uint16_t count_or_value;
  uint16_t crc;
} modbus_rtu_command;

enum class SCANNER_TYPE { RF60x = 1, RF60xHS = 2, RF60xB = 3 };

enum class PROTOCOLS : uint8_t {
  RIFTEK_BIN_PROTOCOL = 1,
  ASCII = 2,
  MODBUS_RTU = 3,
};

////////////////////////////////////////////////////////////////////

const static std::string param_value_types[] = {
    "unkn_t",    "uint8_t",   "uint32_t",    "uint64_t",    "int32_t",
    "int64_t",   "float_t",   "double_t",    "u32_arr_t",   "u64_arr_t",
    "i32_arr_t", "i64_arr_t", "flt_array_t", "dbl_array_t", "string_t"};

typedef struct ParamType {
  std::string name;
  std::string type;
  std::string access;
  uint16_t index;
  uint32_t offset;
  uint32_t size;
  std::string units;
  template <typename T> auto get_value() -> decltype(std::declval<T>().value) {
    return ((T *)this)->value;
  }
  template <typename T>
  void set_value(decltype(std::declval<T>().value) value) {
    ((T *)this)->value = value;
  }
  template <typename T> auto get_min() -> decltype(std::declval<T>().min) {
    return ((T *)this)->min;
  }
  template <typename T> auto get_max() -> decltype(std::declval<T>().max) {
    return ((T *)this)->max;
  }
  template <typename T>
  auto get_default_value() -> decltype(std::declval<T>().defaultValue) {
    return ((T *)this)->defaultValue;
  }
  template <typename T>
  auto get_values_enum() -> decltype(std::declval<T>().valuesEnum) {
    return ((T *)this)->valuesEnum;
  }
  template <typename T> auto get_units() -> decltype(std::declval<T>().units) {
    return ((T *)this)->units;
  }
  template <typename T>
  auto get_count() -> decltype(std::declval<T>().maxCount) {
    return ((T *)this)->maxCount;
  }
  template <typename T>
  auto get_default_count() -> decltype(std::declval<T>().defCount) {
    return ((T *)this)->defCount;
  }
  template <typename T>
  auto get_max_length() -> decltype(std::declval<T>().maxLen) {
    return ((T *)this)->maxLen;
  }
} param_t;

typedef struct value_uint8 : param_t {
  uint8_t min;
  uint8_t max;
  uint8_t defaultValue;
  uint8_t value;
} value_uint8;

typedef struct value_raw : param_t {
  void *raw_data;
} value_raw;

const static std::string parameter_names[] = {
    "user_power",
    "power_analog_output",
    "control_of_averaging",
    "network_address_uart",
    "baud_rate_uart",
    "number_of_averaged_values",
    "low_byte_of_the_sampling_period",
    "high_byte_of_the_sampling_period",
    "low_byte_of_max_integration_time",
    "high_byte_of_max_integration_time",
    "low_byte_for_the_beginning_of_analog_out_range",
    "high_byte_for_the_beginning_of_analog_out_range",
    "low_byte_for_the_end_of_analog_out_range",
    "high_byte_for_the_end_of_analog_out_range",
    "time_lock_of_result",
    "low_byte_of_a_zero_point",
    "high_byte_of_a_zero_point",
    "data_transfer_rate_via_CAN_interface",
    "low_byte_of_standard_identifier",
    "high_byte_of_standard_identifier",
    "zero_byte_of_extended_identifier",
    "first_byte_of_extended_identifie",
    "second_byte_of_extended_identifier",
    "third_byte_of_extended_identifier",
    "CAN_interface_identifier",
    "CAN_interface_power_switch",
    "zero_byte_of_destination_ip_address",
    "first_byte_of_destination_ip_address",
    "second_byte_of_destination_ip_address",
    "third_byte_of_destination_ip_address",
    "zero_byte_of_gateway_ip_address",
    "first_byte_of_gateway_ip_address",
    "second_byte_of_gateway_ip_address",
    "third_byte_of_gateway_ip_address",
    "zero_byte_of_subnet_mask",
    "first_byte_of_subnet_mask",
    "second_byte_of_subnet_mask",
    "third_byte_of_subnet_mask",
    "zero_byte_of_source_ip_address",
    "first_byte_of_source_ip_address",
    "second_byte_of_source_ip_address",
    "third_byte_of_source_ip_address",
    "low_byte_of_the_number_of_measurements_in_the_packet",
    "high_byte_of_the_number_of_measurements_in_the_packet",
    "eth_interface_on_off",
    "auto_of_the_stream",
    "protocols_interface",
};
enum class PARAM_NAME_KEY {
  USER_POWER = 0,
  POWER_ANALOG_OUTPUT,
  CONTROL_OF_AVERAGING,
  NETWORK_ADDRESS_UART,
  BAUD_RATE_UART,
  NUMBER_OF_AVERAGED_VALUES,
  LOW_BYTE_OF_THE_SAMPLING_PERIOD,
  HIGH_BYTE_OF_THE_SAMPLING_PERIOD,
  LOW_BYTE_OF_MAX_INTEGRATION_TIME,
  HIGH_BYTE_OF_MAX_INTEGRATION_TIME,
  LOW_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE,
  HIGH_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE,
  LOW_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE,
  HIGH_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE,
  TIME_LOCK_OF_RESULT,
  LOW_BYTE_OF_A_ZERO_POINT,
  HIGH_BYTE_OF_A_ZERO_POINT,
  DATA_TRANSFER_RATE_VIA_CAN_INTERFACE,
  LOW_BYTE_OF_STANDARD_IDENTIFIER,
  HIGH_BYTE_OF_STANDARD_IDENTIFIER,
  ZERO_BYTE_OF_EXTENDED_IDENTIFIER,
  FIRST_BYTE_OF_EXTENDED_IDENTIFIE,
  SECOND_BYTE_OF_EXTENDED_IDENTIFIER,
  THIRD_BYTE_OF_EXTENDED_IDENTIFIER,
  CAN_INTERFACE_IDENTIFIER,
  CAN_INTERFACE_POWER_SWITCH,
  ZERO_BYTE_OF_DESTINATION_IP_ADDRESS,
  FIRST_BYTE_OF_DESTINATION_IP_ADDRESS,
  SECOND_BYTE_OF_DESTINATION_IP_ADDRESS,
  THIRD_BYTE_OF_DESTINATION_IP_ADDRESS,
  ZERO_BYTE_OF_GATEWAY_IP_ADDRESS,
  FIRST_BYTE_OF_GATEWAY_IP_ADDRESS,
  SECOND_BYTE_OF_GATEWAY_IP_ADDRESS,
  THIRD_BYTE_OF_GATEWAY_IP_ADDRESS,
  ZERO_BYTE_OF_SUBNET_MASK,
  FIRST_BYTE_OF_SUBNET_MASK,
  SECOND_BYTE_OF_SUBNET_MASK,
  THIRD_BYTE_OF_SUBNET_MASK,
  ZERO_BYTE_OF_SOURCE_IP_ADDRESS,
  FIRST_BYTE_OF_SOURCE_IP_ADDRESS,
  SECOND_BYTE_OF_SOURCE_IP_ADDRESS,
  THIRD_BYTE_OF_SOURCE_IP_ADDRESS,
  LOW_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET,
  HIGH_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET,
  ETH_INTERFACE_ON_OFF,
  AUTO_OF_THE_STREAM,
  PROTOCOLS_INTERFACE

};

namespace CODE {

enum class PARAM_NAME_KEY_BYTE : uint8_t {
  USER_POWER = 0x00,
  POWER_ANALOG_OUTPUT = 0x01,
  CONTROL_OF_AVERAGING = 0x02,
  NETWORK_ADDRESS_UART = 0x03,
  BAUD_RATE_UART = 0x04,
  NUMBER_OF_AVERAGED_VALUES = 0x06,
  TIME_LOCK_OF_RESULT = 0x10,
  DATA_TRANSFER_RATE_VIA_CAN_INTERFACE = 0x20,
  CAN_INTERFACE_IDENTIFIER = 0x28,
  CAN_INTERFACE_POWER_SWITCH = 0x29,
  ETH_INTERFACE_ON_OFF = 0x88,
  AUTO_OF_THE_STREAM = 0x89,
  PROTOCOLS_INTERFACE = 0x8A
};

enum class PARAM_NAME_KEY_USHORT : uint16_t {
  LOW_BYTE_OF_THE_SAMPLING_PERIOD = 0x08,
  HIGH_BYTE_OF_THE_SAMPLING_PERIOD = 0x09,
  LOW_BYTE_OF_MAX_INTEGRATION_TIME = 0x0A,
  HIGH_BYTE_OF_MAX_INTEGRATION_TIME = 0x0B,
  LOW_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE = 0x0C,
  HIGH_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE = 0x0D,
  LOW_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE = 0x0E,
  HIGH_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE = 0x0F,
  LOW_BYTE_OF_A_ZERO_POINT = 0x17,
  HIGH_BYTE_OF_A_ZERO_POINT = 0x18,
  LOW_BYTE_OF_STANDARD_IDENTIFIER = 0x22,
  HIGH_BYTE_OF_STANDARD_IDENTIFIER = 0x23,
  LOW_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET = 0x7C,
  HIGH_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET = 0x7D
};

enum class PARAM_NAME_KEY_UINT : uint32_t {
  ZERO_BYTE_OF_EXTENDED_IDENTIFIER = 0x24,
  FIRST_BYTE_OF_EXTENDED_IDENTIFIER = 0x25,
  SECOND_BYTE_OF_EXTENDED_IDENTIFIER = 0x26,
  THIRD_BYTE_OF_EXTENDED_IDENTIFIER = 0x27,
  ZERO_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6C,
  FIRST_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6D,
  SECOND_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6E,
  THIRD_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6F,
  ZERO_BYTE_OF_GATEWAY_IP_ADDRESS = 0x70,
  FIRST_BYTE_OF_GATEWAY_IP_ADDRESS = 0x71,
  SECOND_BYTE_OF_GATEWAY_IP_ADDRESS = 0x72,
  THIRD_BYTE_OF_GATEWAY_IP_ADDRESS = 0x73,
  ZERO_BYTE_OF_SUBNET_MASK = 0x74,
  FIRST_BYTE_OF_SUBNET_MASK = 0x75,
  SECOND_BYTE_OF_SUBNET_MASK = 0x76,
  THIRD_BYTE_OF_SUBNET_MASK = 0x77,
  ZERO_BYTE_OF_SOURCE_IP_ADDRESS = 0x78,
  FIRST_BYTE_OF_SOURCE_IP_ADDRESS = 0x79,
  SECOND_BYTE_OF_SOURCE_IP_ADDRESS = 0x7A,
  THIRD_BYTE_OF_SOURCE_IP_ADDRESS = 0x7B,
};

enum PARAM_NAME_KEY {
  USER_POWER = 0x00,
  POWER_ANALOG_OUTPUT = 0x01,
  CONTROL_OF_AVERAGING = 0x02,
  NETWORK_ADDRESS_UART = 0x03,
  BAUD_RATE_UART = 0x04,
  NUMBER_OF_AVERAGED_VALUES = 0x06,
  LOW_BYTE_OF_THE_SAMPLING_PERIOD = 0x08,
  HIGH_BYTE_OF_THE_SAMPLING_PERIOD = 0x09,
  LOW_BYTE_OF_MAX_INTEGRATION_TIME = 0x0A,
  HIGH_BYTE_OF_MAX_INTEGRATION_TIME = 0x0B,
  LOW_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE = 0x0C,
  HIGH_BYTE_FOR_THE_BEGINNING_OF_ANALOG_OUT_RANGE = 0x0D,
  LOW_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE = 0x0E,
  HIGH_BYTE_FOR_THE_END_OF_ANALOG_OUT_RANGE = 0x0F,
  TIME_LOCK_OF_RESULT = 0x10,
  LOW_BYTE_OF_A_ZERO_POINT = 0x17,
  HIGH_BYTE_OF_A_ZERO_POINT = 0x18,
  DATA_TRANSFER_RATE_VIA_CAN_INTERFACE = 0x20,
  LOW_BYTE_OF_STANDARD_IDENTIFIER = 0x22,
  HIGH_BYTE_OF_STANDARD_IDENTIFIER = 0x23,
  ZERO_BYTE_OF_EXTENDED_IDENTIFIER = 0x24,
  FIRST_BYTE_OF_EXTENDED_IDENTIFIER = 0x25,
  SECOND_BYTE_OF_EXTENDED_IDENTIFIER = 0x26,
  THIRD_BYTE_OF_EXTENDED_IDENTIFIER = 0x27,
  CAN_INTERFACE_IDENTIFIER = 0x28,
  CAN_INTERFACE_POWER_SWITCH = 0x29,
  ZERO_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6C,
  FIRST_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6D,
  SECOND_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6E,
  THIRD_BYTE_OF_DESTINATION_IP_ADDRESS = 0x6F,
  ZERO_BYTE_OF_GATEWAY_IP_ADDRESS = 0x70,
  FIRST_BYTE_OF_GATEWAY_IP_ADDRESS = 0x71,
  SECOND_BYTE_OF_GATEWAY_IP_ADDRESS = 0x72,
  THIRD_BYTE_OF_GATEWAY_IP_ADDRESS = 0x73,
  ZERO_BYTE_OF_SUBNET_MASK = 0x74,
  FIRST_BYTE_OF_SUBNET_MASK = 0x75,
  SECOND_BYTE_OF_SUBNET_MASK = 0x76,
  THIRD_BYTE_OF_SUBNET_MASK = 0x77,
  ZERO_BYTE_OF_SOURCE_IP_ADDRESS = 0x78,
  FIRST_BYTE_OF_SOURCE_IP_ADDRESS = 0x79,
  SECOND_BYTE_OF_SOURCE_IP_ADDRESS = 0x7A,
  THIRD_BYTE_OF_SOURCE_IP_ADDRESS = 0x7B,
  LOW_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET = 0x7C,
  HIGH_BYTE_OF_THE_NUMBER_OF_MEASUREMENTS_IN_THE_PACKET = 0x7D,
  ETH_INTERFACE_ON_OFF = 0x88,
  AUTO_OF_THE_STREAM = 0x89,
  PROTOCOLS_INTERFACE = 0x8A
};
} // namespace CODE

enum class PARAM_VALUE_TYPE {
  UNKN_PARAM_TYPE = 0,
  UINT8_PARAM_TYPE,
  UINT_PARAM_TYPE,
  UINT64_PARAM_TYPE,
  INT_PARAM_TYPE,
  INT64_PARAM_TYPE,
  FLOAT_PARAM_TYPE,
  DOUBLE_PARAM_TYPE,
  UINT32_ARRAY_PARAM_TYPE,
  UINT64_ARRAY_PARAM_TYPE,
  INT32_ARRAY_PARAM_TYPE,
  INT64_ARRAY_PARAM_TYPE,
  FLT_ARRAY_PARAM_TYPE,
  DBL_ARRAY_PARAM_TYPE,
  STRING_PARAM_TYPE
};

enum class BAUR_RATE_UART : uint32_t {
  Baud9600 = 9600,
  Baud115200 = 115200,
  Baud230400 = 230400,
  Baud460800 = 460800,
  Baud921600 = 921600,
};

enum class COMMAND_UART {
  WRITEPARAM = 0x03,
  FLASH = 0x04,
  GETRESULT = 0x06,
  START_STREAM = 0x07,
  START_STREAM_EXTEND=0x0B,
  START_STREAM_ADVANCED = 0x0C,
  START_STREAM_MODIFIED = 0x0D,
  STOP_STREAM = 0x08
};

enum class COMMAND_UART_ENCODER{
    HELLO = 0x01,
    READPARAM = 0x02,
    WRITEPARAM = 0x03,
    SAVETOFLASH = 0xF4, // 0x04
    LATCHING_RESULT=0x05,
    GET_VALTAGE = 0x06,
    RESTORE_FROM_FLASH = 0x04,
    START_STREAM_VALTAGE = 0x07,
    STOP_STREAM = 0x08,
    GET_VALUE_ENCODER=0x0B,
    START_STREAM_VALUE_ENCODER=0x0C
};

enum class COMMAND_VALUE_PARAM_FLASH:uint16_t{
    FLASH=0xAA,
    FACTORY=0x96,
    RESET_DEFAULT_PARAMS_MEMORY=0x69
};

enum class PARAM_KEY_ENCODE{
    MODE=0x07
};

enum class PROTOCOL_MEASURE_UART : uint8_t {
  UART_STREAM_MEASURE_T = 4,
  UART_STREAM_ADVANCED_MEASURE_T = 6,
  UART_STREAM_EXTENDED_T = 8,
  UART_STREAM_MODIFIED_MEASURE_T = 10,
  UART_RESULT_WITH_ENCODER_T = 12

};

enum class AL_MODE {
  OUT_OF_RANGE = 0b00000000,      // out of the range indication (by default)
  SLAVE_MODE = 0b00000100,        // 'slave' mode (mutual synchronization)
  HARDWARE_ZERO_SET = 0b00001000, // hardware zero set mode
  LASER_SWITCH = 0b00001100,      // laser switch OFF/ON
  ENCODER_MODE = 0b01000000,      // encoder mode
  INPUT_MODE = 0b01000100,        // input mode
  RESET_ETHERNET_COUNTER = 0b01101000, // reset of the Ethernet packets counter
  MASTER_MODE = 0b01001100             // 'master' mode (mutual synchronization)
};

enum class AVERAGING_MODE {
  AVERAGING_OVER_RESULTS =
      0b00000000, // averaging over a number of results (by default);
  TIME_AVERAGING = 0b00100000 // time averaging (5 ms)
};

enum class ANALOG_OUTPUT_MODE {
  WINDOW_MODE = 0b00000000, // window mode (by default)
  FULL_RANGE = 0b00000010   // full range
};

enum class SAMPLING_MODE {
  TIME_SAMPLING = 0b00000000,   // time sampling (by default)
  TRIGGER_SAMPLING = 0b00000001 // trigger sampling
};

typedef struct {
  SCANNER_TYPE type;
  BAUR_RATE_UART baud_rate;
  uint8_t network_address;
  std::string number_serial_port;
  PROTOCOLS protocol;
  char *recv_ip_addrs;
} config_base_information_rf60x_t;

///////////////////////////////////////////////////////////////////
