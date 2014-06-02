#include "org/sketch/ui/WebSocketHandler.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"

namespace org {
namespace sketch {
namespace ui {
  using Poco::Net::HTTPResponse;
  using Poco::Net::HTTPServerRequest;
  using Poco::Net::HTTPServerResponse;
  using Poco::Net::WebSocket;
  using Poco::Net::WebSocketException;

  void WebSocketHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
  	try {
      WebSocket webSocket(request, response);
      webSocket.sendFrame("test", sizeof("test"), 0);
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
