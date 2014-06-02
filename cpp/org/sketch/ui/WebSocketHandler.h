#ifndef org_sketching_ui_WebSocketHandler
#define org_sketching_ui_WebSocketHandler

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"

namespace org {
namespace sketch {
namespace ui {

  class WebSocketHandler : public Poco::Net::HTTPRequestHandler {
   public:
    virtual void handleRequest(
        Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
  };

}}} // namespace

#endif
