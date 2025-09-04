#include "RF60X_C.h"
#include "../../rf60Xsdk/rf60Xsdk.h"
#include <vector>
#include <string>
#include <chrono>
#include <cstring>


using namespace SDK::SCANNERS::RF60X;

// Helper to cast device pointer
static inline rf60x* to_rf60x(rf60x_device dev) {
    return static_cast<rf60x*>(dev);
}

extern "C" {

    EXPORTCALL int sdk_version() {
        return SDK::SCANNERS::RF60X::sdk_version();
    }

    EXPORTCALL rf60x_device create_rf60x() {
        return new rf60x();
    }

    EXPORTCALL void destroy_rf60x(rf60x_device dev) {
        delete to_rf60x(dev);
    }

    EXPORTCALL bool open_serial_port(rf60x_device dev, const char* comPortName, uint32_t baudRate) {
        return to_rf60x(dev)->open_serial_port(comPortName, baudRate);
    }

    EXPORTCALL void close_serial_port(rf60x_device dev) {
        to_rf60x(dev)->close_serial_port();
    }

    EXPORTCALL bool connect_udp(rf60x_device dev, const char* hostAddress, uint32_t port) {
        return to_rf60x(dev)->connect_udp(hostAddress, port);
    }

    EXPORTCALL void disconnect_udp(rf60x_device dev) {
        to_rf60x(dev)->disconnect_udp();
    }

    EXPORTCALL void clear_serial_buffer(rf60x_device dev) {
        to_rf60x(dev)->clear_serial_buffer();
    }

    EXPORTCALL void bind_network_address(rf60x_device dev, uint32_t value) {
        to_rf60x(dev)->bind_network_address(value);
    }

    EXPORTCALL void set_wait_timer(rf60x_device dev, uint32_t value_ms) {
        to_rf60x(dev)->set_wait_timer(std::chrono::milliseconds(value_ms));
    }

    EXPORTCALL bool set_sensor(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_sensor(value);
    }
    
    EXPORTCALL bool set_analog_out(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_analog_out(value);
    }

    EXPORTCALL bool set_AL_mode(rf60x_device dev, C_AL_MODE value) {
        return to_rf60x(dev)->set_AL_mode(static_cast<AL_MODE>(value));
    }

    EXPORTCALL bool set_averaging_mode(rf60x_device dev, C_AVERAGING_MODE value) {
        return to_rf60x(dev)->set_averaging_mode(static_cast<AVERAGING_MODE>(value));
    }

    EXPORTCALL bool set_analog_ouput_mode(rf60x_device dev, C_ANALOG_OUTPUT_MODE value) {
        return to_rf60x(dev)->set_analog_ouput_mode(static_cast<ANALOG_OUTPUT_MODE>(value));
    }

    EXPORTCALL bool set_sampling_mode(rf60x_device dev, C_SAMPLING_MODE value) {
        return to_rf60x(dev)->set_sampling_mode(static_cast<SAMPLING_MODE>(value));
    }

    EXPORTCALL bool set_network_address(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_network_address(value);
    }

    EXPORTCALL bool set_baute_rate(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_baute_rate(value);
    }

    EXPORTCALL bool set_number_of_averaged_values(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_number_of_averaged_values(value);
    }

    EXPORTCALL bool set_sampling_period(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_sampling_period(value);
    }

    EXPORTCALL bool set_maximum_integration_time(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_maximum_integration_time(value);
    }

    EXPORTCALL bool set_begin_analog_range(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_begin_analog_range(value);
    }

    EXPORTCALL bool set_end_analog_range(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_end_analog_range(value);
    }

    EXPORTCALL bool set_time_lock_of_result(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_time_lock_of_result(value);
    }

    EXPORTCALL bool set_zero_point(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_zero_point(value);
    }

    EXPORTCALL bool set_CAN_interface_speed(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_CAN_interface_speed(value);
    }

    EXPORTCALL bool set_standard_identifier(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_standard_identifier(value);
    }

    EXPORTCALL bool set_extend_identifier(rf60x_device dev, uint32_t value) {
        return to_rf60x(dev)->set_extend_identifier(value);
    }

    EXPORTCALL bool set_CAN_interface_identifier(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_CAN_interface_identifier(value);
    }

    EXPORTCALL bool set_CAN_interface(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_CAN_interface(value);
    }

    EXPORTCALL bool set_destination_ip_address(rf60x_device dev, const char* value) {
        return to_rf60x(dev)->set_destination_ip_address(value);
    }

    EXPORTCALL bool set_gateway_ip_address(rf60x_device dev, const char* value) {
        return to_rf60x(dev)->set_gateway_ip_address(value);
    }

    EXPORTCALL bool set_subnet_mask(rf60x_device dev, const char* value) {
        return to_rf60x(dev)->set_subnet_mask(value);
    }

    EXPORTCALL bool set_source_ip_address(rf60x_device dev, const char* value) {
        return to_rf60x(dev)->set_source_ip_address(value);
    }

    EXPORTCALL bool set_number_of_measurements_in_the_packet(rf60x_device dev, uint16_t value) {
        return to_rf60x(dev)->set_number_of_measurements_in_the_packet(value);
    }

    EXPORTCALL bool set_ethernet_inteface(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_ethernet_inteface(value);
    }

    EXPORTCALL bool set_autostart_of_measurement_stream(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_autostart_of_measurement_stream(value);
    }

    EXPORTCALL bool set_protocol_type(rf60x_device dev, uint8_t value) {
        return to_rf60x(dev)->set_protocol_type(value);
    }

    // Getters for parameters
    EXPORTCALL bool get_sensor(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_sensor();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_analog_out(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_analog_out();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_AL_mode(rf60x_device dev, C_AL_MODE* value_out) {
        auto [success, value] = to_rf60x(dev)->get_AL_mode();
        if (success && value_out) *value_out = static_cast<C_AL_MODE>(value);
        return success;
    }

    EXPORTCALL bool get_averaging_mode(rf60x_device dev, C_AVERAGING_MODE* value_out) {
        auto [success, value] = to_rf60x(dev)->get_averaging_mode();
        if (success && value_out) *value_out = static_cast<C_AVERAGING_MODE>(value);
        return success;
    }

    EXPORTCALL bool get_analog_ouput_mode(rf60x_device dev, C_ANALOG_OUTPUT_MODE* value_out) {
        auto [success, value] = to_rf60x(dev)->get_analog_ouput_mode();
        if (success && value_out) *value_out = static_cast<C_ANALOG_OUTPUT_MODE>(value);
        return success;
    }

    EXPORTCALL bool get_sampling_mode(rf60x_device dev, C_SAMPLING_MODE* value_out) {
        auto [success, value] = to_rf60x(dev)->get_sampling_mode();
        if (success && value_out) *value_out = static_cast<C_SAMPLING_MODE>(value);
        return success;
    }

    EXPORTCALL bool get_network_address(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_network_address();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_baute_rate(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_baute_rate();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_number_of_averaged_values(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_number_of_averaged_values();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_sampling_period(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_sampling_period();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_maximum_integration_time(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_maximum_integration_time();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_begin_analog_range(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_begin_analog_range();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_end_analog_range(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_end_analog_range();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_time_lock_of_result(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_time_lock_of_result();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_zero_point(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_zero_point();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_CAN_interface_speed(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_CAN_interface_speed();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_standard_identifier(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_standard_identifier();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_extend_identifier(rf60x_device dev, uint32_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_extend_identifier();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_CAN_interface_identifier(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_CAN_interface_identifier();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_CAN_interface(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_CAN_interface();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_number_of_measurements_in_the_packet(rf60x_device dev, uint16_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_number_of_measurements_in_the_packet();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_ethernet_inteface(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_ethernet_inteface();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_autostart_of_measurement_stream(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_autostart_of_measurement_stream();
        if (success && value_out) *value_out = value;
        return success;
    }

    EXPORTCALL bool get_protocol_type(rf60x_device dev, uint8_t* value_out) {
        auto [success, value] = to_rf60x(dev)->get_protocol_type();
        if (success && value_out) *value_out = value;
        return success;
    }

    // String getters
    EXPORTCALL bool get_source_ip_address(rf60x_device dev, char* buffer, size_t buffer_size) {
        auto [success, value] = to_rf60x(dev)->get_source_ip_address();
        if (success && buffer) {
            strncpy(buffer, value.c_str(), buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
        return success;
    }

    EXPORTCALL bool get_destination_ip_address(rf60x_device dev, char* buffer, size_t buffer_size) {
        auto [success, value] = to_rf60x(dev)->get_destination_ip_address();
        if (success && buffer) {
            strncpy(buffer, value.c_str(), buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
        return success;
    }

    EXPORTCALL bool get_gateway_ip_address(rf60x_device dev, char* buffer, size_t buffer_size) {
        auto [success, value] = to_rf60x(dev)->get_gateway_ip_address();
        if (success && buffer) {
            strncpy(buffer, value.c_str(), buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
        return success;
    }

    EXPORTCALL bool get_subnet_mask(rf60x_device dev, char* buffer, size_t buffer_size) {
        auto [success, value] = to_rf60x(dev)->get_subnet_mask();
        if (success && buffer) {
            strncpy(buffer, value.c_str(), buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
        return success;
    }

    // Commands and Measurements
    EXPORTCALL C_uart_hello_t hello_msg_uart(rf60x_device dev) {
        uart_hello_t cpp_hello = to_rf60x(dev)->hello_msg_uart();
        C_uart_hello_t c_hello;
        c_hello.deviceType = cpp_hello.deviceType;
        c_hello.deviceModificaton = cpp_hello.deviceModificaton;
        c_hello.deviceSerial = cpp_hello.deviceSerial;
        c_hello.deviceMaxDistance = cpp_hello.deviceMaxDistance;
        c_hello.deviceRange = cpp_hello.deviceRange;
        return c_hello;
    }

    EXPORTCALL bool get_raw_measure_uart(rf60x_device dev, char* bufferArray, size_t size) {
        return to_rf60x(dev)->get_raw_measure_uart(bufferArray, size);
    }

    EXPORTCALL bool get_single_measure(rf60x_device dev, void* measure) {
        return to_rf60x(dev)->get_single_measure(measure);
    }

    EXPORTCALL bool get_measure_uart(rf60x_device dev, void* measure, C_PROTOCOL_MEASURE_UART type) {
        return to_rf60x(dev)->get_measure_uart(measure, static_cast<PROTOCOL_MEASURE_UART>(type));
    }

    EXPORTCALL bool send_command(rf60x_device dev, C_COMMAND_UART value) {
        return to_rf60x(dev)->send_command(static_cast<COMMAND_UART>(value));
    }

    EXPORTCALL bool request_custom_command(rf60x_device dev, char* data, uint8_t size) {
        return to_rf60x(dev)->request_custom_command(data, size);
    }

    EXPORTCALL bool read_custom_command(rf60x_device dev, uint8_t command, uint8_t size, char* vec_ref, size_t vec_size) {
        std::vector<char> temp_vec;
        bool result = to_rf60x(dev)->read_custom_command(command, size, temp_vec);
        if (result && vec_ref) {
            size_t copy_size = temp_vec.size() < vec_size ? temp_vec.size() : vec_size;
            memcpy(vec_ref, temp_vec.data(), copy_size);
        }
        return result;
    }
}
