#ifndef org_sketching_ui_PageRequestHandler
#define org_sketching_ui_PageRequestHandler

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"

namespace org {
namespace sketch {
namespace ui {

  class PageRequestHandler : public Poco::Net::HTTPRequestHandler {
   public:
    virtual void handleRequest(
        Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
  };

}}} // namespace

#endif
