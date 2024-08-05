
#if (defined _WIN32)
#define EXPORTCALL __declspec(dllexport)
#else
#define EXPORTCALL
#endif

#include "RF60X_C.h"

using namespace SDK;
using namespace SCANNERS;
using namespace RF60X;

#ifdef __cplusplus
extern "C" {
#endif

	struct result_8t {
		bool success;
		uint8_t value;
	};

	struct result_16t {
		bool success;
		uint16_t value;
	};


	struct result_32t {
		bool success;
		uint32_t value;
	};

	struct result_char {
		bool success;
		char value[16];
	};

	enum AL_MODE_C {
		OUT_OF_RANGE = 0b00000000,      // out of the range indication (by default)
		SLAVE_MODE = 0b00000100,        // 'slave' mode (mutual synchronization)
		HARDWARE_ZERO_SET = 0b00001000, // hardware zero set mode
		LASER_SWITCH = 0b00001100,      // laser switch OFF/ON
		ENCODER_MODE = 0b01000000,      // encoder mode
		INPUT_MODE = 0b01000100,        // input mode
		RESET_ETHERNET_COUNTER = 0b01101000, // reset of the Ethernet packets counter
		MASTER_MODE = 0b01001100             // 'master' mode (mutual synchronization)
	};

	enum AVERAGING_MODE_C {
		AVERAGING_OVER_RESULTS =
		0b00000000, // averaging over a number of results (by default);
		TIME_AVERAGING = 0b00100000 // time averaging (5 ms)
	};

	enum ANALOG_OUTPUT_MODE_C {
		WINDOW_MODE = 0b00000000, // window mode (by default)
		FULL_RANGE = 0b00000010   // full range
	};

	enum SAMPLING_MODE_C {
		TIME_SAMPLING = 0b00000000,   // time sampling (by default)
		TRIGGER_SAMPLING = 0b00000001 // trigger sampling
	};

	enum PROTOCOL_MEASURE_UART_C{
		UART_STREAM_MEASURE_T = 4,
		UART_STREAM_ADVANCED_MEASURE_T = 6,
		UART_STREAM_MODIFIED_MEASURE_T = 10,
		UART_RESULT_WITH_ENCODER_T = 12

	};

	struct result_AL_MODE {
		bool success;
		AL_MODE_C value;
	};

	struct result_AVERAGING_MODE {
		bool success;
		AVERAGING_MODE_C value;
	};


	struct result_ANALOG_OUTPUT_MODE {
		bool success;
		ANALOG_OUTPUT_MODE_C value;
	};


	struct result_SAMPLING_MODE {
		bool success;
		SAMPLING_MODE_C value;
	};

	EXPORTCALL void* __cdecl create_rf60x() {

		return static_cast<void*>(new rf60x());
}

	EXPORTCALL void __cdecl destroy_rf60x(void* dev) {

		delete static_cast<rf60x*>( dev);
	}


	EXPORTCALL void __cdecl bind_network_address(void* dev, uint32_t value) {

		 static_cast<rf60x*>(dev)->bind_network_address(value);
	}

	EXPORTCALL uart_hello_t __cdecl hello_msg_uart(void* dev) {

		return static_cast<rf60x*>(dev)->hello_msg_uart();
	}

	EXPORTCALL void set_wait_timer(void* dev,uint32_t value) {

		static_cast<rf60x*>(dev)->set_wait_timer(std::chrono::duration<uint32_t, std::milli>(value));
	}

	EXPORTCALL bool set_sensor(void* dev,uint8_t value) {

		return static_cast<rf60x*>(dev)->set_sensor(value);
	}

	EXPORTCALL bool set_analog_out(void* dev,uint8_t value) {
		return static_cast<rf60x*>(dev)->set_analog_out(value);
	}

	EXPORTCALL bool __cdecl open_serial_port(void* dev, char* comPortName, uint32_t baudRate) {
		return static_cast<rf60x*>(dev)->open_serial_port(comPortName, baudRate);
	}

	EXPORTCALL bool set_AL_mode(void* dev, AL_MODE_C value) {
		return static_cast<rf60x*>(dev)->set_AL_mode(static_cast<AL_MODE>(value));
	}

	EXPORTCALL bool set_averaging_mode(void* dev, AVERAGING_MODE_C value) {
		return static_cast<rf60x*>(dev)->set_averaging_mode(static_cast<AVERAGING_MODE>(value));
	}

	EXPORTCALL bool set_analog_ouput_mode(void* dev, ANALOG_OUTPUT_MODE_C value) {
		return static_cast<rf60x*>(dev)->set_analog_ouput_mode(static_cast<ANALOG_OUTPUT_MODE>(value));
	}

	EXPORTCALL bool set_sampling_mode(void* dev, SAMPLING_MODE_C value) {
		return static_cast<rf60x*>(dev)->set_sampling_mode(static_cast<SAMPLING_MODE>(value));
	}

	EXPORTCALL bool set_network_address(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_network_address(value);
	}

	EXPORTCALL bool set_baute_rate(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_baute_rate(value);
	}

	EXPORTCALL bool set_number_of_averaged_values(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_number_of_averaged_values(value);
	}

	EXPORTCALL bool set_sampling_period(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_sampling_period(value);
	}

	EXPORTCALL bool set_maximum_integration_time(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_maximum_integration_time(value);
	}

	EXPORTCALL bool set_begin_analog_range(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_begin_analog_range(value);
	}

	EXPORTCALL bool set_end_analog_range(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_end_analog_range(value);
	}

	EXPORTCALL bool set_time_lock_of_result(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_time_lock_of_result(value);
	}

	EXPORTCALL bool set_zero_point(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_zero_point(value);
	}

	EXPORTCALL bool set_CAN_interface_speed(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_CAN_interface_speed(value);
	}

	EXPORTCALL bool set_standard_identifier(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_standard_identifier(value);
	}

	EXPORTCALL bool set_extend_identifier(void* dev, uint32_t value) {
		return static_cast<rf60x*>(dev)->set_extend_identifier(value);
	}

	EXPORTCALL bool set_CAN_interface_identifier(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_CAN_interface_identifier(value);
	}

	EXPORTCALL bool set_CAN_interface(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_CAN_interface(value);
	}

	EXPORTCALL bool set_destination_ip_address(void* dev, char* value) {
		return static_cast<rf60x*>(dev)->set_destination_ip_address(value);
	}

	EXPORTCALL bool set_gateway_ip_address(void* dev, char* value) {
		return static_cast<rf60x*>(dev)->set_gateway_ip_address(value);
	}

	EXPORTCALL bool set_subnet_mask(void* dev, char* value) {
		return static_cast<rf60x*>(dev)->set_subnet_mask(value);
	}

	EXPORTCALL bool set_source_ip_address(void* dev, char* value) {
		return static_cast<rf60x*>(dev)->set_source_ip_address(value);
	}

	EXPORTCALL bool set_number_of_measurements_in_the_packet(void* dev, uint16_t value) {
		return static_cast<rf60x*>(dev)->set_number_of_measurements_in_the_packet(value);
	}

	EXPORTCALL bool set_ethernet_inteface(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_ethernet_inteface(value);
	}

	EXPORTCALL bool set_autostart_of_measurement_stream(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_autostart_of_measurement_stream(value);
	}

	EXPORTCALL bool set_protol_type(void* dev, uint8_t value) {
		return static_cast<rf60x*>(dev)->set_protol_type(value);
	}


	EXPORTCALL bool get_raw_measure_uart(void* dev, char* bufferArray, size_t size) {
		return static_cast<rf60x*>(dev)->get_raw_measure_uart(bufferArray, size);
	}

	EXPORTCALL void __cdecl close_serial_port(void* dev) {
		return static_cast<rf60x*>(dev)->close_serial_port();
	}

	EXPORTCALL bool get_single_measure(void* dev,void* measure) {
		return static_cast<rf60x*>(dev)->get_single_measure(measure);
	}

	EXPORTCALL bool get_measure_uart(void* dev,void* measure, PROTOCOL_MEASURE_UART_C type) {
		return static_cast<rf60x*>(dev)->get_measure_uart(measure,static_cast<PROTOCOL_MEASURE_UART>(type));
	}



	EXPORTCALL bool send_command(void* dev,uint16_t value) {
		return static_cast<rf60x*>(dev)->send_command(static_cast<COMMAND_UART>(value));
	}

	/*EXPORTCALL bool read_custom_command(void* dev, uint8_t command, uint8_t size,
		char* vec_ref) {
		return static_cast<rf60x*>(dev)->read_custom_command(command, size,vec_ref);
	}*/


	EXPORTCALL bool request_custom_command(void* dev, char* data, uint8_t size) {
		return static_cast<rf60x*>(dev)->request_custom_command(data,size);
	}

	EXPORTCALL bool connect_udp(void* dev, char* hostAddress, uint32_t port) {
		return static_cast<rf60x*>(dev)->connect_udp(hostAddress, port);
	}

	EXPORTCALL void disconnect_udp(void* dev) {
		return static_cast<rf60x*>(dev)->disconnect_udp();
	}

	result_8t get_sensor(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_sensor();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_analog_out(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_analog_out();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_AL_MODE get_AL_mode(void* dev) {
		result_AL_MODE tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_AL_mode();
		tempData.success = result;
		tempData.value = static_cast<AL_MODE_C>(value);

		return tempData;
	}

	result_AVERAGING_MODE get_averaging_mode(void* dev) {
		result_AVERAGING_MODE tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_averaging_mode();
		tempData.success = result;
		tempData.value = static_cast<AVERAGING_MODE_C>(value);

		return tempData;
	}

	result_ANALOG_OUTPUT_MODE get_analog_ouput_mode(void* dev) {
		result_ANALOG_OUTPUT_MODE tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_analog_ouput_mode();
		tempData.success = result;
		tempData.value = static_cast<ANALOG_OUTPUT_MODE_C>(value);

		return tempData;
	}

	result_SAMPLING_MODE get_sampling_mode(void* dev) {
		result_SAMPLING_MODE tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_sampling_mode();
		tempData.success = result;
		tempData.value = static_cast<SAMPLING_MODE_C>(value);

		return tempData;
	}

	result_8t get_network_address(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_network_address();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_baute_rate(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_baute_rate();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_number_of_averaged_values(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_number_of_averaged_values();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_sampling_period(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_sampling_period();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_maximum_integration_time(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_maximum_integration_time();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_begin_analog_range(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_begin_analog_range();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_end_analog_range(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_end_analog_range();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_time_lock_of_result(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_time_lock_of_result();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_zero_point(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_zero_point();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_CAN_interface_speed(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_CAN_interface_speed();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_16t get_standard_identifier(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_standard_identifier();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_32t get_extend_identifier(void* dev) {
		result_32t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_extend_identifier();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_CAN_interface_identifier(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_CAN_interface_identifier();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_CAN_interface(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_CAN_interface();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_char get_source_ip_address(void* dev) {
		result_char tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_source_ip_address();
		tempData.success = result;
		std::strcpy(tempData.value, value.c_str());
		tempData.value[value.length()] = '\0';

		return tempData;
	}

	result_char get_destination_ip_address(void* dev) {
		result_char tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_destination_ip_address();
		tempData.success = result;
		std::strcpy(tempData.value, value.c_str());
		tempData.value[value.length()] = '\0';

		return tempData;
	}

	result_char gateway_ip_address(void* dev) {
		result_char tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_gateway_ip_address();
		tempData.success = result;
		std::strcpy(tempData.value, value.c_str());
		tempData.value[value.length()] = '\0';

		return tempData;
	}

	result_char get_subnet_mask(void* dev) {
		result_char tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_subnet_mask();
		tempData.success = result;
		std::strcpy(tempData.value, value.c_str());
		tempData.value[value.length()] = '\0';

		return tempData;
	}

	result_16t get_number_of_measurements_in_the_packet(void* dev) {
		result_16t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_number_of_measurements_in_the_packet();
		tempData.success = result;
		tempData.value = value;

		return tempData;

	}

	result_8t get_ethernet_inteface(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_ethernet_inteface();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_autostart_of_measurement_stream(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_autostart_of_measurement_stream();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}

	result_8t get_protol_type(void* dev) {
		result_8t tempData;
		auto [result, value] = static_cast<rf60x*>(dev)->get_protol_type();
		tempData.success = result;
		tempData.value = value;

		return tempData;
	}




#ifdef __cplusplus
}
#endif


