#include "org/sketch/ui/UiServer.h"

#include "org/sketch/ui/PageRequestHandler.h"
#include "org/sketch/ui/WebSocketHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/ServerSocket.h"

namespace org {
namespace sketch {
namespace ui {
  using org::sketch::entity::SketchProgress;
  using Poco::Net::HTTPRequestHandler;
  using Poco::Net::HTTPRequestHandlerFactory;
  using Poco::Net::HTTPServer;
  using Poco::Net::HTTPServerParams;
  using Poco::Net::HTTPServerRequest;
  using Poco::Net::ServerSocket;

  class UiServerRequestHandlerFactory : public HTTPRequestHandlerFactory {
   public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &request) {
      if (request.getURI() == "/ws")
        return new WebSocketHandler;
      else
        return new PageRequestHandler;
    }
  };

  UiServer::UiServer(const SketchProgress &progress, int port) : progress(progress),
      httpServer(new UiServerRequestHandlerFactory, ServerSocket(port), new HTTPServerParams) {
    httpServer.start();    
  }
  
  UiServer::~UiServer() {
    httpServer.stop();
  }

}}} // namespace
