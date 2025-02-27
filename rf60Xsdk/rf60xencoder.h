#ifndef RF60XENCODER_H
#define RF60XENCODER_H

#include "rf60Xsdk.h"
// Create enum for commands uart encoder
namespace SDK
{
  namespace RFENCODER
  {

    class API_EXPORT rf60xEncoder : public SDK::SCANNERS::RF60X::rf60x
    {
    public:
      rf60xEncoder() = default;
      ~rf60xEncoder() = default;

      /**
       * Sends a command to the encoder via UART.
       *
       * @param value The command to send.
       */
      bool send_command_encoder(COMMAND_UART_ENCODER value);

      /**
       * Gets the voltage reading from the encoder.
       *
       * @return The voltage reading as a float. Where the return value is
       * calculated Voltage (V) = Result voltage measurements /100.
       */
      float get_single_valtage_encoder();

      /**
       * Gets the encoder value.
       *
       * @return The encoder value as an unsigned 32-bit integer. Where are the
       * lower 16 bits {2 channels}/counter pulses {3 channels} (2) and high 16
       * bits/revolution counter (2)
       */
      uint32_t get_single_value_encoder();

      /**
       * Gets the stream of encoder values.
       *
       * @return The stream of encoder values as unsigned 32-bit integers.
       */
      uint32_t get_stream_value_encoder();

      /**
       * Gets the current operating mode of the encoder.
       *
       * @return A pair containing a boolean indicating success/failure and the
       * current operating mode as a uint8_t.
       * uint8_t can be one of the following values:
       *  0 – encoder 2 channels;
       *  1 – encoder 3 channels.
       */
      std::pair<bool, uint8_t> get_mode_encoder();

      /**
       * Gets the stream of voltage readings from the encoder.
       *
       * @param value Output parameter to receive the stream of voltage readings.
       */
      bool get_stream_valtage_encoder(float &value);

    private:
      bool getRawMeasure(char *buffer, size_t size);
    };

  } // namespace RFENCODER
} // namespace SDK

#endif // RF60XENCODER_H
