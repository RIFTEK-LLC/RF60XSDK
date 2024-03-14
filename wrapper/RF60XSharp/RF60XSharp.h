#pragma once

using namespace SDK::SCANNERS::RF60X;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace  System::Collections::Generic;

namespace RFTYPES {

	[StructLayout(LayoutKind::Sequential, Pack = 1)]
		public value struct uart_hello_rf60x_net_t
	{
		Byte  deviceType;
		Byte  deviceModificaton;
		UInt16 deviceSerial;
		UInt16 deviceMaxDistance;
		UInt16 deviceRange;
	};

	public enum  class AL_MODE
	{
		OUT_OF_RANGE = 0b00000000,
		SLAVE_MODE = 0b00000100,
		HARDWARE_ZERO_SET = 0b00001000,
		LASER_SWITCH = 0b00001100,
		ENCODER_MODE = 0b01000000,
		INPUT_MODE = 0b01000100,
		RESET_ETHERNET_COUNTER = 0b01101000,
		MASTER_MODE = 0b01001100
	};


	public enum class COMMAND_UART {
		WRITEPARAM = 0x03,
		RESTORE_FROM_FLASH = 0x04,
		GETRESULT = 0x06,
		START_STREAM = 0x07,
		STOP_STREAM = 0x08,
		START_STREAM_ADVANCED = 0x0C,
		START_STREAM_MODIFIED = 0x0D,
		SAVETOFLASH = 0xF4
	};


	public enum class AVERAGING_MODE {
		AVERAGING_OVER_RESULTS =
		0b00000000, // averaging over a number of results (by default);
		TIME_AVERAGING = 0b00100000 // time averaging (5 ms)
	};

	public enum class ANALOG_OUTPUT_MODE {
		WINDOW_MODE = 0b00000000, // window mode (by default)
		FULL_RANGE = 0b00000010   // full range
	};

	public enum class SAMPLING_MODE {
		TIME_SAMPLING = 0b00000000,   // time sampling (by default)
		TRIGGER_SAMPLING = 0b00000001 // trigger sampling
	};


	[StructLayout(LayoutKind::Sequential, Pack = 1)]
		public value struct uart_stream_measure_net_t
	{
		UInt16 value;
		Byte count;
		Byte status;
		Byte reserverd;
	};

	[StructLayout(LayoutKind::Sequential, Pack = 1)]
		public value struct uart_stream_advanced_measure_net_t
	{
		UInt16 value;
		Byte status;
		Byte dir;
		Byte cnt;
	};

	[StructLayout(LayoutKind::Sequential, Pack = 1)]
		public value struct uart_stream_modified_measure_net_t
	{
		UInt16 value;
		Byte status;
		Byte dir;
		Byte cnt;
		UInt16 cnt_stream;;
	};

	[StructLayout(LayoutKind::Sequential, Pack = 1)]
		public value struct uart_result_with_encoder_net_t
	{
		UInt16 measure;
		UInt16 rotationMarks;
		UInt16 encoderValue;
	};

}

namespace RF60XSharp {
	public ref class RF60X
	{

	public:
		RF60X() {

			m_rf60x = new rf60x();

		}

		~RF60X() {
			delete m_rf60x;
		}

		void bind_network_address(uint32_t value);
		RFTYPES::uart_hello_rf60x_net_t hello_msg_uart();
		void set_wait_timer(UInt32 value);
		bool set_sensor(uint8_t value);
		bool set_analog_out(uint8_t value);
		bool set_AL_mode(RFTYPES::AL_MODE value);
		bool set_averaging_mode(RFTYPES::AVERAGING_MODE value);
		bool set_analog_ouput_mode(RFTYPES::ANALOG_OUTPUT_MODE value);
		bool set_sampling_mode(RFTYPES::SAMPLING_MODE value);
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
		bool open_serial_port(String^ comPortName, uint32_t baudRate);
		void close_serial_port();
		bool get_raw_measure_uart(array<char>^ bufferArray);
		bool get_single_measure(RFTYPES::uart_stream_measure_net_t% measure);
		//bool get_single_measure(RFTYPES::uart_stream_advanced_measure_net_t% measure);
		//bool get_single_measure(RFTYPES::uart_stream_modified_measure_net_t% measure);
		//bool get_single_measure(RFTYPES::uart_result_with_encoder_net_t% measure);
		bool send_command(RFTYPES::COMMAND_UART value);
		bool read_custom_command(uint8_t command, uint8_t size,
			List<char>^ ref);
		//bool request_custom_command(char* data, uint8_t size);
		bool get_measure_uart(RFTYPES::uart_stream_measure_net_t% measure);
		bool get_measure_uart(RFTYPES::uart_stream_advanced_measure_net_t% measure);
		bool get_measure_uart(RFTYPES::uart_stream_modified_measure_net_t% measure);
		bool get_measure_uart(RFTYPES::uart_result_with_encoder_net_t% measure);
		Tuple<bool, Byte>^ get_sensor();

		Tuple<bool, Byte>^ get_analog_out();

		Tuple<bool, Byte>^ get_AL_mode();

		Tuple<bool, Byte>^ get_averaging_mode();

		Tuple<bool, Byte>^ get_analog_ouput_mode();

		Tuple<bool, Byte>^ get_sampling_mode();

		Tuple<bool, uint8_t>^ get_network_address();

		Tuple<bool, uint8_t>^ get_baute_rate();

		Tuple<bool, uint8_t>^ get_number_of_averaged_values();

		Tuple<bool, uint16_t>^ get_sampling_period();

		Tuple<bool, uint16_t>^ get_maximum_integration_time();

		Tuple <bool, uint16_t>^ get_begin_analog_range();

		Tuple<bool, uint16_t>^ get_end_analog_range();

		Tuple<bool, uint8_t>^ get_time_lock_of_result();

		Tuple<bool, uint16_t>^ get_zero_point();

		Tuple<bool, uint8_t>^ get_CAN_interface_speed();

		Tuple<bool, uint16_t>^ get_standard_identifier();

		Tuple<bool, uint32_t>^ get_extend_identifier();

		Tuple<bool, uint8_t>^ get_CAN_interface_identifier();

		Tuple<bool, uint8_t>^ get_CAN_interface();

		String^ get_source_ip_address();

		String^ destination_ip_address();

		String^ gateway_ip_address();

		String^  subnet_mask();

		Tuple<bool, uint16_t>^ get_number_of_measurements_in_the_packet();

		Tuple<bool, uint8_t>^ get_ethernet_inteface();

		Tuple<bool, uint8_t>^ get_autostart_of_measurement_stream();

		Tuple<bool, uint8_t>^ get_protol_type();
		//bool connect_udp(const std::string& hostAddress, uint32_t port);
		//void disconnect_udp();
		//bool get_measure_udp();
		//bool get_measure_udp_binocular();


	internal:
		rf60x* m_rf60x;

	};

}
