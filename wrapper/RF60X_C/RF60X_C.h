#ifndef RF60X_C_H
#define RF60X_C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if (defined _WIN32)
#define EXPORTCALL __declspec(dllexport)
#else
#define EXPORTCALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Opaque pointer to the rf60x class instance
    typedef void* rf60x_device;

    // C-style enums
    typedef enum  {
        C_OUT_OF_RANGE = 0b00000000,
        C_SLAVE_MODE = 0b00000100,
        C_HARDWARE_ZERO_SET = 0b00001000,
        C_LASER_SWITCH = 0b00001100,
        C_ENCODER_MODE = 0b01000000,
        C_INPUT_MODE = 0b01000100,
        C_RESET_ETHERNET_COUNTER = 0b01101000,
        C_MASTER_MODE = 0b01001100
    } C_AL_MODE;

    typedef enum {
        C_AVERAGING_OVER_RESULTS = 0b00000000,
        C_TIME_AVERAGING = 0b00100000
    } C_AVERAGING_MODE;

    typedef enum {
        C_WINDOW_MODE = 0b00000000,
        C_FULL_RANGE = 0b00000010
    } C_ANALOG_OUTPUT_MODE;

    typedef enum {
        C_TIME_SAMPLING = 0b00000000,
        C_TRIGGER_SAMPLING = 0b00000001
    } C_SAMPLING_MODE;

    typedef enum {
        C_UART_STREAM_MEASURE_T = 4,
        C_UART_STREAM_ADVANCED_MEASURE_T = 6,
        C_UART_STREAM_MODIFIED_MEASURE_T = 10,
        C_UART_RESULT_WITH_ENCODER_T = 12
    } C_PROTOCOL_MEASURE_UART;

    typedef enum {
        C_WRITEPARAM = 0x03,
        C_SAVETOFLASH = 0xF4,
        C_RESTORE_FROM_FLASH = 0x04,
        C_GETRESULT = 0x06,
        C_START_STREAM = 0x07,
        C_START_STREAM_EXTEND = 0x0B,
        C_START_STREAM_ADVANCED = 0x0C,
        C_START_STREAM_MODIFIED = 0x0D,
        C_STOP_STREAM = 0x08
    } C_COMMAND_UART;

    // C-style structs
    typedef struct {
        uint8_t deviceType;
        uint8_t deviceModificaton;
        uint16_t deviceSerial;
        uint16_t deviceMaxDistance;
        uint16_t deviceRange;
    } C_uart_hello_t;

    // SDK version
    EXPORTCALL int sdk_version();

    // Object lifecycle
    EXPORTCALL rf60x_device create_rf60x();
    EXPORTCALL void destroy_rf60x(rf60x_device dev);

    // Connection management
    EXPORTCALL bool open_serial_port(rf60x_device dev, const char* comPortName, uint32_t baudRate);
    EXPORTCALL void close_serial_port(rf60x_device dev);
    EXPORTCALL bool connect_udp(rf60x_device dev, const char* hostAddress, uint32_t port);
    EXPORTCALL void disconnect_udp(rf60x_device dev);
    EXPORTCALL void clear_serial_buffer(rf60x_device dev);

    // Configuration and Settings
    EXPORTCALL void bind_network_address(rf60x_device dev, uint32_t value);
    EXPORTCALL void set_wait_timer(rf60x_device dev, uint32_t value_ms);

    // Setters for parameters
    EXPORTCALL bool set_sensor(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_analog_out(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_AL_mode(rf60x_device dev, C_AL_MODE value);
    EXPORTCALL bool set_averaging_mode(rf60x_device dev, C_AVERAGING_MODE value);
    EXPORTCALL bool set_analog_ouput_mode(rf60x_device dev, C_ANALOG_OUTPUT_MODE value);
    EXPORTCALL bool set_sampling_mode(rf60x_device dev, C_SAMPLING_MODE value);
    EXPORTCALL bool set_network_address(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_baute_rate(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_number_of_averaged_values(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_sampling_period(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_maximum_integration_time(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_begin_analog_range(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_end_analog_range(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_time_lock_of_result(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_zero_point(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_CAN_interface_speed(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_standard_identifier(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_extend_identifier(rf60x_device dev, uint32_t value);
    EXPORTCALL bool set_CAN_interface_identifier(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_CAN_interface(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_destination_ip_address(rf60x_device dev, const char* value);
    EXPORTCALL bool set_gateway_ip_address(rf60x_device dev, const char* value);
    EXPORTCALL bool set_subnet_mask(rf60x_device dev, const char* value);
    EXPORTCALL bool set_source_ip_address(rf60x_device dev, const char* value);
    EXPORTCALL bool set_number_of_measurements_in_the_packet(rf60x_device dev, uint16_t value);
    EXPORTCALL bool set_ethernet_inteface(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_autostart_of_measurement_stream(rf60x_device dev, uint8_t value);
    EXPORTCALL bool set_protocol_type(rf60x_device dev, uint8_t value);

    // Getters for parameters
    EXPORTCALL bool get_sensor(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_analog_out(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_AL_mode(rf60x_device dev, C_AL_MODE* value_out);
    EXPORTCALL bool get_averaging_mode(rf60x_device dev, C_AVERAGING_MODE* value_out);
    EXPORTCALL bool get_analog_ouput_mode(rf60x_device dev, C_ANALOG_OUTPUT_MODE* value_out);
    EXPORTCALL bool get_sampling_mode(rf60x_device dev, C_SAMPLING_MODE* value_out);
    EXPORTCALL bool get_network_address(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_baute_rate(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_number_of_averaged_values(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_sampling_period(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_maximum_integration_time(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_begin_analog_range(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_end_analog_range(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_time_lock_of_result(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_zero_point(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_CAN_interface_speed(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_standard_identifier(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_extend_identifier(rf60x_device dev, uint32_t* value_out);
    EXPORTCALL bool get_CAN_interface_identifier(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_CAN_interface(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_number_of_measurements_in_the_packet(rf60x_device dev, uint16_t* value_out);
    EXPORTCALL bool get_ethernet_inteface(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_autostart_of_measurement_stream(rf60x_device dev, uint8_t* value_out);
    EXPORTCALL bool get_protocol_type(rf60x_device dev, uint8_t* value_out);
    
    // String getters
    EXPORTCALL bool get_source_ip_address(rf60x_device dev, char* buffer, size_t buffer_size);
    EXPORTCALL bool get_destination_ip_address(rf60x_device dev, char* buffer, size_t buffer_size);
    EXPORTCALL bool get_gateway_ip_address(rf60x_device dev, char* buffer, size_t buffer_size);
    EXPORTCALL bool get_subnet_mask(rf60x_device dev, char* buffer, size_t buffer_size);

    // Commands and Measurements
    EXPORTCALL C_uart_hello_t hello_msg_uart(rf60x_device dev);
    EXPORTCALL bool get_raw_measure_uart(rf60x_device dev, char* bufferArray, size_t size);
    EXPORTCALL bool get_single_measure(rf60x_device dev, void* measure);
    EXPORTCALL bool get_measure_uart(rf60x_device dev, void* measure, C_PROTOCOL_MEASURE_UART type);
    EXPORTCALL bool send_command(rf60x_device dev, C_COMMAND_UART value);
    EXPORTCALL bool request_custom_command(rf60x_device dev, char* data, uint8_t size);
    EXPORTCALL bool read_custom_command(rf60x_device dev, uint8_t command, uint8_t size, char* vec_ref, size_t vec_size);

#ifdef __cplusplus
}
#endif

#endif // RF60X_C_H
