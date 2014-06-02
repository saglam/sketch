#include "org/sketch/ui/WebSocketHandler.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "org/modcpp/logging/Console.h"

namespace org {
namespace sketch {
namespace ui {
  using org::modcpp::logging::Console;
  using Poco::Net::HTTPResponse;
  using Poco::Net::HTTPServerRequest;
  using Poco::Net::HTTPServerResponse;
  using Poco::Net::WebSocket;
  using Poco::Net::WebSocketException;

  void WebSocketHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
  	try {
      WebSocket webSocket(request, response);
      int flags;
      int n;
      char buffer[1024];
      do {
        n = webSocket.receiveFrame(buffer, sizeof(buffer), flags);
        Console::info("Frame received %.*s\nsize = %d, flags = %d\n", n, buffer, n, flags);
        webSocket.sendFrame(buffer, n, flags);
        webSocket.sendFrame("hasan", 5, flags);
    	} while (n > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
      //webSocket.sendFrame("testtest", sizeof("testtest") + 1, 0);
      //webSocket.sendFrame("ddede", sizeof("ddede") + 1, 0);

    } catch (WebSocketException& exc) {
      switch (exc.code()) {
        case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
          response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
          // fallthrough
        case WebSocket::WS_ERR_NO_HANDSHAKE:
        case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
        case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
          response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
          response.setContentLength(0);
          response.send();
          break;
      }
    }
  }

}}} // namespace
