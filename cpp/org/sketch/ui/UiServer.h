#ifndef org_sketch_ui_UiServer
#define org_sketch_ui_UiServer

#include "Poco/Net/HTTPServer.h"

namespace org {
namespace sketch {
namespace ui {

  class UiServer {
   public:
    UiServer(int port = 8080);
    ~UiServer();

   private:
    Poco::Net::HTTPServer httpServer;
  };

}}} // namespace

#endif
