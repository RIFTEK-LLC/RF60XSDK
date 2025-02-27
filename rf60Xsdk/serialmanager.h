#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

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

class timeout_exception : public std::runtime_error
{
public:
  timeout_exception(const std::string &arg) : runtime_error(arg) {}

  timeout_exception() = default;
};

/**
 * @brief SerialManager - This class provides methods for
 * controlling the scanner via the serial port.
 */
class SerialManager
{
public:
  SerialManager()
      : baud_rate(BAUR_RATE_UART::Baud9600), io(), port(io), timer(io), timeout(5000),
        socket(io), result(ReadResult::resultSuccess), bytesTransferred(0) {}

  SerialManager(const SerialManager &) = delete;
  SerialManager &operator=(const SerialManager &) = delete;
  // CommunicationInterface interface
public:

  /**
   * Opens a serial port device.
   * @param devName The name of the serial device to open, e.g. "/dev/ttyS0" or "COM1".
   * @return true if the serial port was opened successfully, false otherwise.
   * @throws boost::system::system_error if the serial port cannot be opened.
   */
  bool open_serial_port(std::string devName);
  
  /**
   * Closes the open serial port.
   */
  void close_serial_port();
  
  /**
   * Reads a command from the serial port.
   * @param data Pointer to a buffer to store the read data.
   * @param size The size of the buffer.
   * @return true if the read was successful, false otherwise.
   */
  bool read_command(char *data, size_t size);
  
  /**
   * Writes a command to the serial port.
   * @param data Pointer to the data to write.
   * @param size The size of the data to write.
   * @return true if the write was successful, false otherwise.
   */
  bool write_command(char *data, size_t size);
  
  /**
   * Sets the read/write timeout for the serial port.
   * @param t The new timeout duration.
   */
  void set_timeout(const std::chrono::duration<int, std::milli> &t);
  
  /**
   * Sets the baud rate for the serial port.
   * @param newBaud_rate The new baud rate to use.
   */
  void setBaud_rate(BAUR_RATE_UART newBaud_rate);
  
  /**
   * Callback function called when a timeout expires.
   * @param error The error code associated with the timeout.
   */
  void timeout_expired(const std::error_code &error);
  
  /**
   * Connects to a UDP server.
   * @param hostAddress The IP address of the UDP server.
   * @param port The port number of the UDP server.
   * @return true if the connection was successful, false otherwise.
   */
  bool connect_udp(const std::string &hostAddress, uint32_t port);
  
  /**
   * Disconnects from the UDP server.
   */
  void disconnect_udp();
  
  /**
   * Retrieves a measurement from the UDP server.
   * @param data Pointer to a buffer to store the measurement data.
   * @param size The size of the buffer.
   * @return true if the measurement was retrieved successfully, false otherwise.
   */
  bool get_measure_udp(char *data, size_t size);
  
  /**
   * Clears the I/O buffer.
   */
  void clear_IO_buffer();

  /**
   * Possible outcome of a read. Set by callbacks, read from main code
   */
  enum ReadResult
  {
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
  asio::streambuf readData;                       ///< Holds eventual read but not consumed
  asio::ip::udp::socket socket;
  asio::ip::udp::endpoint endpoint;
  enum ReadResult result;  ///< Used by read with timeout
  size_t bytesTransferred; ///< Used by async read callback
  std::error_code error_code;
  uint32_t udpDataCounter = 0;
  //    ReadSetupParameters setupParameters; ///< Global because used in the OSX
  //    fix
};

#endif // SERIALMANAGER_H
