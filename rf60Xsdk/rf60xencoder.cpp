#include "rf60xencoder.h"

bool SDK::RFENCODER::rf60xEncoder::send_command_encoder(COMMAND_UART_ENCODER value)
{
    constexpr char MASK_NETWORK_ADDRESS = 0xFF;
    constexpr char MASK_VALUE = 0x0F;
    constexpr char MASK_BIT_7 = 0x80;

    char ucBuffer[2]{};

    ucBuffer[0] = static_cast<char>(m_NetworkAddress & MASK_NETWORK_ADDRESS);
    ucBuffer[1] = MASK_BIT_7 | (static_cast<char>(value) & MASK_VALUE);

    return request_custom_command(ucBuffer, 2);
}


bool SDK::RFENCODER::rf60xEncoder::get_stream_valtage_encoder(float &value)
{
    uart_stream_measure_t tempValue;

    if(!get_measure_uart(&tempValue, PROTOCOL_MEASURE_UART::UART_STREAM_MEASURE_T))
    {
            return false;
    }

    uint16_t convertedValue;
    std::memcpy(&convertedValue, &tempValue.value, sizeof(uint16_t));
    value=static_cast<float>(convertedValue/100.0);

    return true;

}

float SDK::RFENCODER::rf60xEncoder::get_single_valtage_encoder()
{
    uart_stream_measure_t tempValue;

    if(!get_single_measure(&tempValue)){
        return 0;
    }

    uint16_t convertedValue;
    std::memcpy(&convertedValue, &tempValue.value, sizeof(uint16_t));

    return static_cast<float>(convertedValue/100.0);
}

uint32_t SDK::RFENCODER::rf60xEncoder::get_single_value_encoder()
{
    if (!send_command_encoder(COMMAND_UART_ENCODER::GET_VALUE_ENCODER)) {
        return false;
    }

    char bufferArray[4];
    if(!get_raw_measure_uart(bufferArray,sizeof(uint32_t))) return 0;

    uint32_t result = (static_cast<uint32_t>(bufferArray[0]) << 24) |
                      (static_cast<uint32_t>(bufferArray[1]) << 16) |
                      (static_cast<uint32_t>(bufferArray[2]) << 8) |
                      static_cast<uint32_t>(bufferArray[3]);


    return result;

}

uint32_t SDK::RFENCODER::rf60xEncoder::get_stream_value_encoder()
{
    char bufferArray[4];
    if(!get_raw_measure_uart(bufferArray,sizeof(uint32_t))) return 0;

    uint32_t result = (static_cast<uint32_t>(bufferArray[0]) << 24) |
                      (static_cast<uint32_t>(bufferArray[1]) << 16) |
                      (static_cast<uint32_t>(bufferArray[2]) << 8) |
                      static_cast<uint32_t>(bufferArray[3]);


    return result;
}
