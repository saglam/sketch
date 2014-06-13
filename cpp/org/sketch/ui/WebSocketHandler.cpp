#include "org/sketch/ui/WebSocketHandler.h"

#include <iostream>

#include "org/sketch/entity/SketchProgress.h"
#include "org/sketch/ui/ProgressSerializer.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Thread.h"

namespace org {
namespace sketch {
namespace ui {
  using org::modcpp::string::String;
  using org::sketch::entity::SketchProgress;
  using Poco::Net::HTTPResponse;
  using Poco::Net::HTTPServerRequest;
  using Poco::Net::HTTPServerResponse;
  using Poco::Net::WebSocket;
  using Poco::Net::WebSocketException;

  void WebSocketHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
    try {
      WebSocket webSocket(request, response);
      ProgressSerializer serializer(progress);
      int sentBytes;
      do {
        String message = serializer.getTopK(30);
        sentBytes = webSocket.sendFrame(message.begin(), message.length(), 129);
        std::cout << "Sent: " << message << "\n";
        Poco::Thread::sleep(100);
      } while (!progress.isDone());
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
        default:
          break;
      }
    }
  }

}}} // namespace
