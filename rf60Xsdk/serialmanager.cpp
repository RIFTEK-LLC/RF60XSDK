#include "serialmanager.h"

bool SerialManager::open_serial_port(std::string devName) {

  if (port.is_open())
    return false;
  port.open(devName);
  port.set_option(
      asio::serial_port_base::baud_rate(static_cast<uint32_t>(baud_rate)));
  port.set_option(
      asio::serial_port_base::parity(asio::serial_port_base::parity::even));
  port.set_option(asio::serial_port_base::character_size(8));
  /*port.set_option(asio::serial_port_base::flow_control(
      asio::serial_port_base::flow_control::none));*/
  port.set_option(asio::serial_port_base::stop_bits(
      asio::serial_port_base::stop_bits::one));
  return true;
}

void SerialManager::close_serial_port() {
  if (port.is_open() == false)
    return;
  port.close();
}

bool SerialManager::read_command(char *data, size_t size) {

  io.reset();

  asio::async_read(port, asio::buffer(data, size),
                   std::bind(&SerialManager::read_completed, this,
                             std::placeholders::_1, std::placeholders::_2));

  // For this code to work, there should always be a timeout, so the
  // request for no timeout is translated into a very long timeout

  if (timeout != std::chrono::seconds(0)) {
    timer.expires_from_now(timeout);
  } else {
    timer.expires_from_now(asio::chrono::hours(100000));
  }

  timer.async_wait(
      std::bind(&SerialManager::timeout_expired, this, std::placeholders::_1));

  result = resultInProgress;
  bytesTransferred = 0;
  for (;;) {
    io.run_one();
    switch (result) {
    case resultSuccess:
      timer.cancel();
      return true;
    case resultTimeoutExpired:
      // port.cancel();
      throw(timeout_exception("Timeout expired"));
    case resultError:
      timer.cancel();
      port.cancel();
      throw(std::system_error(std::error_code(), "Error while reading"));
      // if resultInProgress remain in the loop
    case resultInProgress:
      break;
    }
  }
}
void SerialManager::timeout_expired(const std::error_code &error) {
  if (!error && result == resultInProgress) {
    result = resultTimeoutExpired;
  }
}

bool SerialManager::connect_udp(const std::string &hostAddress, uint32_t port) {
  asio::error_code ec;

  using asio::ip::udp;

  udp::resolver resolver(io);
  udp::endpoint endpoint(asio::ip::address::from_string(hostAddress), port);

  try {
    socket.open(endpoint.protocol());
    socket.bind(endpoint, ec);
  } catch (std::exception &e) {

    std::cout << e.what() << std::endl;
  }

  if (ec) {
    return false;
  }

  return true;
}

void SerialManager::disconnect_udp() { socket.close(); }

bool SerialManager::get_measure_udp(char *data, size_t size) {
  try {
      if (size < 2) {
          throw std::invalid_argument("Buffer size must be at least 2 bytes");
      }

      std::atomic<bool> dataReceived{false};
      asio::error_code ec;

      io.restart();

      if (timeout != std::chrono::seconds(0)) {
          timer.expires_from_now(timeout);
      } else {
          timer.cancel();
      }

      auto handleTimeout = [&](const asio::error_code &error) {
          if (!error && !dataReceived.load(std::memory_order_acquire)) {
              std::cout << "Timeout expired." << std::endl;
              socket.cancel(ec);
              if (ec) std::cerr << "Cancel error: " << ec.message() << std::endl;
          }
      };

      socket.async_receive(asio::buffer(data, size),
          [&](const asio::error_code &error, size_t bytesReceived) {
              if (!error && bytesReceived > 0) {
                  if (bytesReceived >= 2) {
                      const auto first = static_cast<unsigned char>(data[0]);
                      const auto second = static_cast<unsigned char>(data[1]);
                      if (first == 0xFF && second == 0x7F) {
                          std::cout << "Invalid data received: FF 7F" << std::endl;
                          dataReceived.store(false, std::memory_order_release);
                          timer.cancel();
                          return;
                      }
                  }
                  dataReceived.store(true, std::memory_order_release);
              }
              timer.cancel();
          });

      timer.async_wait(handleTimeout);

      if (timeout != std::chrono::seconds(0)) {
          io.run_for(timeout);
      } else {
          io.run();
      }

      return dataReceived.load(std::memory_order_acquire);
  } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return false;
  }
}

void SerialManager::clear_IO_buffer()
{

#ifdef __linux__
    tcflush(port.lowest_layer().native_handle(), TCIOFLUSH);
#elif _WIN32
    PurgeComm(port.native_handle(), PURGE_TXCLEAR);
    PurgeComm(port.native_handle(), PURGE_RXCLEAR);
#else

#endif



}


void SerialManager::read_completed(const std::error_code &error,
                                   const size_t bytesTransferred) {
  if (!error) {
    result = resultSuccess;
    this->bytesTransferred = bytesTransferred;
    return;
  }

  // In case a asynchronous operation is cancelled due to a timeout,
  // each OS seems to have its way to react.
#ifdef _WIN32
  if (error.value() == 995)
    return; // Windows spits out error 995
#elif defined(__APPLE__)
  if (error.value() == 45) {
    // Bug on OS X, it might be necessary to repeat the setup
    // http://osdir.com/ml/lib.boost.asio.user/2008-08/msg00004.html
    performReadSetup(setupParameters);
    return;
  }
#else // Linux
  if (error.value() == 125)
    return; // Linux outputs error 125
#endif

  result = resultError;
}

bool SerialManager::write_command(char *data, size_t size) {
  size_t countByte = asio::write(port, asio::buffer(data, size));
  if (countByte != size) {
    return false;
  }

  return true;
}

void SerialManager::set_timeout(
    const std::chrono::duration<int, std::milli> &t) {
  timeout = t;
}

void SerialManager::setBaud_rate(BAUR_RATE_UART newBaud_rate) {
  baud_rate = newBaud_rate;
}
