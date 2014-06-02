#ifndef org_sketch_ui_UiServer
#define org_sketch_ui_UiServer

#include "Poco/Net/HTTPServer.h"

namespace org {
namespace sketch {

// For forward declaration
namespace entity { class SketchProgress; }

namespace ui {
  class UiServer {
   public:
    UiServer(const org::sketch::entity::SketchProgress &progress, int port = 8080);
    ~UiServer();

   private:
    const org::sketch::entity::SketchProgress &progress;
    Poco::Net::HTTPServer httpServer;
  };

}}} // namespace

#endif
