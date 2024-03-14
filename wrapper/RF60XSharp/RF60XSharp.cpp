#include "pch.h"

#include "RF60XSharp.h"
void RF60XSharp::RF60X::bind_network_address(uint32_t value)
{
	m_rf60x->bind_network_address(value);
}

RFTYPES::uart_hello_rf60x_net_t RF60XSharp::RF60X::hello_msg_uart()
{
	RFTYPES::uart_hello_rf60x_net_t helloMsg;
	uart_hello_t tempHelloMsg = m_rf60x->hello_msg_uart();

	helloMsg.deviceMaxDistance = tempHelloMsg.deviceMaxDistance;
	helloMsg.deviceModificaton = tempHelloMsg.deviceModificaton;
	helloMsg.deviceRange = tempHelloMsg.deviceRange;
	helloMsg.deviceSerial = tempHelloMsg.deviceSerial;
	helloMsg.deviceType = tempHelloMsg.deviceType;
	return helloMsg;
}

void RF60XSharp::RF60X::set_wait_timer(UInt32 value)
{
	m_rf60x->set_wait_timer(std::chrono::milliseconds(value));
}

bool RF60XSharp::RF60X::set_sensor(uint8_t value)
{
	return m_rf60x->set_sensor(value);
}

bool RF60XSharp::RF60X::set_analog_out(uint8_t value)
{
	return m_rf60x->set_analog_out(value);
}

bool RF60XSharp::RF60X::set_AL_mode(RFTYPES::AL_MODE value)
{
	switch (value)
	{
	case RFTYPES::AL_MODE::OUT_OF_RANGE:
		return m_rf60x->set_AL_mode(AL_MODE::OUT_OF_RANGE);
	case RFTYPES::AL_MODE::SLAVE_MODE:
		return m_rf60x->set_AL_mode(AL_MODE::SLAVE_MODE);
	case RFTYPES::AL_MODE::HARDWARE_ZERO_SET:
		return m_rf60x->set_AL_mode(AL_MODE::HARDWARE_ZERO_SET);
	case RFTYPES::AL_MODE::LASER_SWITCH:
		return m_rf60x->set_AL_mode(AL_MODE::LASER_SWITCH);;
	case RFTYPES::AL_MODE::ENCODER_MODE:
		return m_rf60x->set_AL_mode(AL_MODE::ENCODER_MODE);
	case RFTYPES::AL_MODE::INPUT_MODE:
		return m_rf60x->set_AL_mode(AL_MODE::INPUT_MODE);
	case RFTYPES::AL_MODE::RESET_ETHERNET_COUNTER:
		return m_rf60x->set_AL_mode(AL_MODE::RESET_ETHERNET_COUNTER);
	case RFTYPES::AL_MODE::MASTER_MODE:
		return m_rf60x->set_AL_mode(AL_MODE::MASTER_MODE);
	default:
		break;
	}

	return false;
}

bool RF60XSharp::RF60X::set_averaging_mode(RFTYPES::AVERAGING_MODE value)
{
	switch (value)
	{
	case RFTYPES::AVERAGING_MODE::AVERAGING_OVER_RESULTS:
		return m_rf60x->set_averaging_mode(AVERAGING_MODE::AVERAGING_OVER_RESULTS);
	case RFTYPES::AVERAGING_MODE::TIME_AVERAGING:
		return m_rf60x->set_averaging_mode(AVERAGING_MODE::TIME_AVERAGING);
	default:
		break;
	}
	return false;
}

bool RF60XSharp::RF60X::set_analog_ouput_mode(RFTYPES::ANALOG_OUTPUT_MODE value)
{
	switch (value)
	{
	case RFTYPES::ANALOG_OUTPUT_MODE::WINDOW_MODE:
		return m_rf60x->set_analog_ouput_mode(ANALOG_OUTPUT_MODE::WINDOW_MODE);
	case RFTYPES::ANALOG_OUTPUT_MODE::FULL_RANGE:
		return m_rf60x->set_analog_ouput_mode(ANALOG_OUTPUT_MODE::FULL_RANGE);
	default:
		break;
	}
	return false;
}

bool RF60XSharp::RF60X::set_sampling_mode(RFTYPES::SAMPLING_MODE value)
{
	switch (value)
	{
	case RFTYPES::SAMPLING_MODE::TIME_SAMPLING:
		return m_rf60x->set_sampling_mode(SAMPLING_MODE::TIME_SAMPLING);
	case RFTYPES::SAMPLING_MODE::TRIGGER_SAMPLING:
		return m_rf60x->set_sampling_mode(SAMPLING_MODE::TRIGGER_SAMPLING);
	default:
		break;
	}
	return false;
}

bool RF60XSharp::RF60X::set_network_address(uint8_t value)
{
	return m_rf60x->set_network_address(value);
}

bool RF60XSharp::RF60X::set_baute_rate(uint8_t value)
{
	return m_rf60x->set_baute_rate(value);
}

bool RF60XSharp::RF60X::set_number_of_averaged_values(uint8_t value)
{
	return m_rf60x->set_number_of_averaged_values(value);
}

bool RF60XSharp::RF60X::set_sampling_period(uint16_t value)
{
	return m_rf60x->set_sampling_period(value);
}

bool RF60XSharp::RF60X::set_maximum_integration_time(uint16_t value)
{
	return m_rf60x->set_maximum_integration_time(value);
}

bool RF60XSharp::RF60X::set_begin_analog_range(uint16_t value)
{
	return m_rf60x->set_begin_analog_range(value);
}

bool RF60XSharp::RF60X::set_end_analog_range(uint16_t value)
{
	return m_rf60x->set_end_analog_range(value);
}

bool RF60XSharp::RF60X::set_time_lock_of_result(uint8_t value)
{
	return m_rf60x->set_time_lock_of_result(value);
}

bool RF60XSharp::RF60X::set_zero_point(uint16_t value)
{
	return m_rf60x->set_zero_point(value);
}

bool RF60XSharp::RF60X::set_CAN_interface_speed(uint8_t value)
{
	return m_rf60x->set_CAN_interface_speed(value);
}

bool RF60XSharp::RF60X::set_standard_identifier(uint16_t value)
{
	return m_rf60x->set_standard_identifier(value);
}

bool RF60XSharp::RF60X::set_extend_identifier(uint32_t value)
{
	return m_rf60x->set_extend_identifier(value);
}

bool RF60XSharp::RF60X::set_CAN_interface_identifier(uint8_t value)
{
	return m_rf60x->set_CAN_interface_identifier(value);
}

bool RF60XSharp::RF60X::set_CAN_interface(uint8_t value)
{
	return m_rf60x->set_CAN_interface(value);
}

bool RF60XSharp::RF60X::set_destination_ip_address(std::string value)
{
	return m_rf60x->set_destination_ip_address(value);
}

bool RF60XSharp::RF60X::set_gateway_ip_address(std::string value)
{
	return m_rf60x->set_gateway_ip_address(value);
}

bool RF60XSharp::RF60X::set_subnet_mask(std::string value)
{
	return m_rf60x->set_subnet_mask(value);
}

bool RF60XSharp::RF60X::set_source_ip_address(std::string value)
{
	return m_rf60x->set_source_ip_address(value);
}

bool RF60XSharp::RF60X::set_number_of_measurements_in_the_packet(uint16_t value)
{
	return m_rf60x->set_number_of_measurements_in_the_packet(value);
}

bool RF60XSharp::RF60X::set_ethernet_inteface(uint8_t value)
{
	return m_rf60x->set_ethernet_inteface(value);
}

bool RF60XSharp::RF60X::set_autostart_of_measurement_stream(uint8_t value)
{
	return m_rf60x->set_autostart_of_measurement_stream(value);
}

bool RF60XSharp::RF60X::set_protol_type(uint8_t value)
{
	return m_rf60x->set_protol_type(value);
}

bool RF60XSharp::RF60X::open_serial_port(String^ comPortName, uint32_t baudRate)
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(comPortName)).ToPointer();
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return m_rf60x->open_serial_port(chars, baudRate);
}

void RF60XSharp::RF60X::close_serial_port()
{
	m_rf60x->close_serial_port();
}


bool RF60XSharp::RF60X::get_raw_measure_uart(array<char>^ bufferArray)
{
	bufferArray->Clear;
	pin_ptr<char> pBuffer = &bufferArray[0];

	return m_rf60x->get_raw_measure_uart(pBuffer, bufferArray->Length);
}

bool RF60XSharp::RF60X::get_single_measure(RFTYPES::uart_stream_measure_net_t% measure)
{
	uart_stream_measure_t tempMeasure;

	bool result = m_rf60x->get_single_measure(&tempMeasure);
	if (!result) {
		return false;
	}

	measure.value = tempMeasure.count;
	measure.status = tempMeasure.status;
	measure.count = tempMeasure.count;
	measure.reserverd = tempMeasure.reserverd;

	return true;
}

//bool RF60XSharp::RF60X::get_single_measure(RFTYPES::uart_stream_advanced_measure_net_t% measure)
//{
//	uart_stream_advanced_measure_t tempMeasure;
//
//	bool result = m_rf60x->get_single_measure(&tempMeasure);
//	if (!result) {
//		return false;
//	}
//
//	measure.cnt = tempMeasure.cnt;
//	measure.dir = tempMeasure.dir;
//	measure.status = tempMeasure.status;
//	measure.value = tempMeasure.value;
//
//	return true;
//}
//
//bool RF60XSharp::RF60X::get_single_measure(RFTYPES::uart_stream_modified_measure_net_t% measure)
//{
//	uart_stream_modified_measure_t tempMeasure;
//
//	bool result = m_rf60x->get_single_measure(&tempMeasure);
//	if (!result) {
//		return false;
//	}
//
//	measure.cnt = tempMeasure.cnt;
//	measure.cnt_stream = tempMeasure.cnt_stream;
//	measure.dir = tempMeasure.dir;
//	measure.status = tempMeasure.status;
//	measure.value = tempMeasure.value;
//
//	return true;
//}
//
//bool RF60XSharp::RF60X::get_single_measure(RFTYPES::uart_result_with_encoder_net_t% measure)
//{
//	uart_result_with_encoder_t tempMeasure;
//
//	bool result = m_rf60x->get_single_measure(&tempMeasure);
//	if (!result) {
//		return false;
//	}
//
//	measure.encoderValue = tempMeasure.encoderValue;
//	measure.measure = tempMeasure.measure;
//	measure.rotationMarks = tempMeasure.rotationMarks;
//
//	return true;
//}

bool RF60XSharp::RF60X::send_command(RFTYPES::COMMAND_UART value)
{
	switch (value)
	{
	case RFTYPES::COMMAND_UART::WRITEPARAM:
		return m_rf60x->send_command(COMMAND_UART::WRITEPARAM);
	case RFTYPES::COMMAND_UART::SAVETOFLASH:
		return m_rf60x->send_command(COMMAND_UART::SAVETOFLASH);
	case RFTYPES::COMMAND_UART::RESTORE_FROM_FLASH:
		return m_rf60x->send_command(COMMAND_UART::RESTORE_FROM_FLASH);
	case RFTYPES::COMMAND_UART::GETRESULT:
		return m_rf60x->send_command(COMMAND_UART::GETRESULT);
	case RFTYPES::COMMAND_UART::START_STREAM:
		return m_rf60x->send_command(COMMAND_UART::START_STREAM);
	case RFTYPES::COMMAND_UART::START_STREAM_ADVANCED:
		return m_rf60x->send_command(COMMAND_UART::START_STREAM_ADVANCED);;
	case RFTYPES::COMMAND_UART::START_STREAM_MODIFIED:
		return m_rf60x->send_command(COMMAND_UART::START_STREAM_MODIFIED);
	case RFTYPES::COMMAND_UART::STOP_STREAM:
		return m_rf60x->send_command(COMMAND_UART::STOP_STREAM);
	default:
		break;
	}
	return false;
}

bool RF60XSharp::RF60X::read_custom_command(uint8_t command, uint8_t size, List<char>^ ref)
{
	std::vector<char> tempBuffer;


	if (!m_rf60x->read_custom_command(command, size, tempBuffer)) return false;


	for (uint32_t i = 0; i < tempBuffer.size(); ++i) {
		ref->Add(tempBuffer.at(i));
	}

	return true;
}

bool RF60XSharp::RF60X::get_measure_uart(RFTYPES::uart_stream_measure_net_t% measure)
{
	uart_stream_measure_t tempMeasure;

	bool result = m_rf60x->get_measure_uart(&tempMeasure, PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T);
	if (!result) {
		return false;
	}

	measure.value = tempMeasure.value;
	measure.status = tempMeasure.status;
	measure.count = tempMeasure.count;
	measure.reserverd = tempMeasure.reserverd;

	return true;
}

bool RF60XSharp::RF60X::get_measure_uart(RFTYPES::uart_stream_advanced_measure_net_t% measure)
{
	uart_stream_advanced_measure_t tempMeasure;

	bool result = m_rf60x->get_measure_uart(&tempMeasure, PROTOCOL_MEASURE_UART::UART_STREAM_ADVANCED_MEASURE_T);
	if (!result) {
		return false;
	}

	measure.cnt = tempMeasure.cnt;
	measure.dir = tempMeasure.dir;
	measure.status = tempMeasure.status;
	measure.value = tempMeasure.value;

	return true;
}

bool RF60XSharp::RF60X::get_measure_uart(RFTYPES::uart_stream_modified_measure_net_t% measure)
{
	uart_stream_modified_measure_t tempMeasure;

	bool result = m_rf60x->get_measure_uart(&tempMeasure, PROTOCOL_MEASURE_UART::UART_STREAM_MODIFIED_MEASURE_T);
	if (!result) {
		return false;
	}

	measure.cnt = tempMeasure.cnt;
	measure.cnt_stream = tempMeasure.cnt_stream;
	measure.dir = tempMeasure.dir;
	measure.status = tempMeasure.status;
	measure.value = tempMeasure.value;

	return true;
}

bool RF60XSharp::RF60X::get_measure_uart(RFTYPES::uart_result_with_encoder_net_t% measure)
{
	uart_result_with_encoder_t tempMeasure;

	bool result = m_rf60x->get_measure_uart(&tempMeasure, PROTOCOL_MEASURE_UART::UART_RESULT_WITH_ENCODER_T);
	if (!result) {
		return false;
	}

	measure.encoderValue = tempMeasure.encoderValue;
	measure.measure = tempMeasure.measure;
	measure.rotationMarks = tempMeasure.rotationMarks;

	return true;
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_sensor()
{
	auto value = m_rf60x->get_sensor();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_analog_out()
{
	auto value = m_rf60x->get_analog_out();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_AL_mode()
{
	auto value = m_rf60x->get_AL_mode();

	return gcnew System::Tuple<bool, Byte>(value.first, static_cast<uint8_t>(value.second));
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_averaging_mode()
{
	auto value = m_rf60x->get_averaging_mode();

	return gcnew System::Tuple<bool, Byte>(value.first, static_cast<uint8_t>(value.second));
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_analog_ouput_mode()
{
	auto value = m_rf60x->get_analog_ouput_mode();

	return gcnew System::Tuple<bool, Byte>(value.first, static_cast<uint8_t>(value.second));
}

Tuple<bool, Byte>^ RF60XSharp::RF60X::get_sampling_mode()
{
	auto value = m_rf60x->get_sampling_mode();

	return gcnew System::Tuple<bool, Byte>(value.first, static_cast<uint8_t>(value.second));
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_network_address()
{
	auto value = m_rf60x->get_network_address();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_baute_rate()
{
	auto value = m_rf60x->get_baute_rate();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_number_of_averaged_values()
{
	auto value = m_rf60x->get_number_of_averaged_values();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_sampling_period()
{
	auto value = m_rf60x->get_sampling_period();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_maximum_integration_time()
{
	auto value = m_rf60x->get_maximum_integration_time();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_begin_analog_range()
{
	auto value = m_rf60x->get_begin_analog_range();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_end_analog_range()
{
	auto value = m_rf60x->get_end_analog_range();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_time_lock_of_result()
{
	auto value = m_rf60x->get_time_lock_of_result();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_zero_point()
{
	auto value = m_rf60x->get_zero_point();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_CAN_interface_speed()
{
	auto value = m_rf60x->get_CAN_interface_speed();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_standard_identifier()
{
	auto value = m_rf60x->get_standard_identifier();

	return gcnew System::Tuple<bool, UInt16>(value.first, value.second);
}

Tuple<bool, uint32_t>^ RF60XSharp::RF60X::get_extend_identifier()
{
	auto value = m_rf60x->get_extend_identifier();

	return gcnew System::Tuple<bool, UInt32>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_CAN_interface_identifier()
{
	auto value = m_rf60x->get_CAN_interface_identifier();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_CAN_interface()
{
	auto value = m_rf60x->get_CAN_interface();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

String^ RF60XSharp::RF60X::get_source_ip_address()
{
	String^ tempString;
	auto value = m_rf60x->get_source_ip_address();
	if (!value.first) {
		return tempString = "Empty";
	}
	return tempString = msclr::interop::marshal_as<String^>(value.second);
}

String^ RF60XSharp::RF60X::destination_ip_address()
{
	String^ tempString;
	auto value = m_rf60x->destination_ip_address();
	if (!value.first) {
		return tempString = "Empty";
	}

	return tempString = msclr::interop::marshal_as<String^>(value.second);
}

String^ RF60XSharp::RF60X::gateway_ip_address()
{
	String^ tempString;
	auto value = m_rf60x->gateway_ip_address();
	if (!value.first) {
		return tempString = "Empty";
	}

	return tempString = msclr::interop::marshal_as<String^>(value.second);
}

String^ RF60XSharp::RF60X::subnet_mask()
{
	String^ tempString;
	auto value = m_rf60x->subnet_mask();
	if (!value.first) {
		return tempString = "Empty";
	}

	return tempString = msclr::interop::marshal_as<String^>(value.second);
}

Tuple<bool, uint16_t>^ RF60XSharp::RF60X::get_number_of_measurements_in_the_packet()
{
	auto value = m_rf60x->get_number_of_measurements_in_the_packet();

	return gcnew System::Tuple<bool, UINT16>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_ethernet_inteface()
{
	auto value = m_rf60x->get_ethernet_inteface();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_autostart_of_measurement_stream()
{
	auto value = m_rf60x->get_autostart_of_measurement_stream();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

Tuple<bool, uint8_t>^ RF60XSharp::RF60X::get_protol_type()
{
	auto value = m_rf60x->get_protol_type();

	return gcnew System::Tuple<bool, Byte>(value.first, value.second);
}

