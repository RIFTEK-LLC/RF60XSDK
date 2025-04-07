#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

// #include "communicationinterface.h"
#include "asio.hpp"
#include "asio/placeholders.hpp"
#include "asio/ts/timer.hpp"
#include "rf60Xtypes.h"
#include <chrono>
#include <stdexcept>

/**
 * @brief timeout_exception - This class is responsible
 * for exception handling.
 */

class timeout_exception : public std::runtime_error {
public:
  timeout_exception(const std::string &arg) : runtime_error(arg) {}

  timeout_exception() = delete;
};

/**
 * @brief SerialManager - This class provides methods for
 * controlling the scanner via the serial port.
 */
class SerialManager {
public:
  SerialManager()
      :baud_rate(BAUR_RATE_UART::Baud9600), io(), port(io), timer(io), timeout(5000),
        socket(io), result(ReadResult::resultSuccess), bytesTransferred(0){}

  // CommunicationInterface interface
public:
  /**
   * Opens a serial device.
   * \param address serial device name, example "/dev/ttyS0" or "COM1"
   * \throws boost::system::system_error if cannot open the
   * serial device
   */

  bool open_serial_port(std::string devName);
  void close_serial_port();
  bool read_command(char *data, size_t size);
  bool write_command(char *data, size_t size);

  void set_timeout(const std::chrono::duration<int, std::milli> &t);
  void setBaud_rate(BAUR_RATE_UART newBaud_rate);
  void timeout_expired(const std::error_code &error);

  bool connect_udp(const std::string &hostAddress, uint32_t port);
  void disconnect_udp();

  bool get_measure_udp(char *data, size_t size);
  bool get_measure_udp_sync(char *data, size_t size);
  void clear_IO_buffer();
  /**
   * Possible outcome of a read. Set by callbacks, read from main code
   */
  enum ReadResult {
    resultInProgress,
    resultSuccess,
    resultError,
    resultTimeoutExpired
  };

  void read_completed(const std::error_code &error,
                      const size_t bytesTransferred);

private:
  BAUR_RATE_UART baud_rate;
  asio::io_service io;                            ///< Io service object
  asio::serial_port port;                         ///< Serial port object
  asio::high_resolution_timer timer;              ///< Timer for timeout
  std::chrono::duration<int, std::milli> timeout; ///< Read/write timeout
  asio::streambuf readData; ///< Holds eventual read but not consumed
  asio::ip::udp::socket socket;
  asio::ip::udp::endpoint endpoint;
  enum ReadResult result;  ///< Used by read with timeout
  size_t bytesTransferred; ///< Used by async read callback
  std::error_code error_code;
  //    ReadSetupParameters setupParameters; ///< Global because used in the OSX
  //    fix
};

#endif // SERIALMANAGER_H
