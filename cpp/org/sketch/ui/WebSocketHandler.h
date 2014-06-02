#ifndef org_sketching_ui_WebSocketHandler
#define org_sketching_ui_WebSocketHandler

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"

namespace org {
namespace sketch {

// For forward declaration
namespace entity { class SketchProgress; }

namespace ui {
  using org::sketch::entity::SketchProgress;

  class WebSocketHandler : public Poco::Net::HTTPRequestHandler {
   public:
    WebSocketHandler(const SketchProgress &progress) : progress(progress) {}

    virtual void handleRequest(
        Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

   private:
    const SketchProgress &progress; 
  };

}}} // namespace

#endif
