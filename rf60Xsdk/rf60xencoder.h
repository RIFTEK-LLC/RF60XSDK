#ifndef RF60XENCODER_H
#define RF60XENCODER_H

#include "rf60Xsdk.h"
// Create enum for commands uart encoder
namespace SDK {
namespace RFENCODER {

class API_EXPORT rf60xEncoder : public SDK::SCANNERS::RF60X::rf60x
{
public:
    rf60xEncoder()=default;
    ~rf60xEncoder()=default;
    bool send_command_encoder(COMMAND_UART_ENCODER value);
    float get_single_valtage_encoder();
    uint32_t get_single_value_encoder();
    uint32_t get_stream_value_encoder();
    std::pair<bool,uint8_t>  get_mode_encoder();
    bool  get_stream_valtage_encoder(float &value);

};

} // namespace RFENCODER
} // namespace SDK

#endif // RF60XENCODER_H
