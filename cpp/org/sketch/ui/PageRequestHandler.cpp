#include "org/sketch/ui/PageRequestHandler.h"

#include <string>
#include <iostream>

#include "Poco/StreamCopier.h"
#include "Poco/FileStream.h"

using Poco::FileInputStream;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::StreamCopier;
using std::cout;
using std::string;

namespace org {
namespace sketch {
namespace ui {

  void PageRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
    resp.setStatus(HTTPResponse::HTTP_OK);
    // cout << Poco::format("Received request %s", req.getURI()) << endl;
    string fileName;
    if (req.getURI() == "/") {
      resp.setContentType("text/html");
      fileName = "index.html";
    } else {
      resp.setContentType("text/css");
      fileName = req.getURI().substr(1);
    }
    FileInputStream input(fileName);
    StreamCopier::copyStream(input, resp.send());
  }

}}} // namespace
