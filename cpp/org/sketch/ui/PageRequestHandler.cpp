#include "org/sketch/ui/PageRequestHandler.h"

#include <algorithm>
#include <iostream>
#include <string>

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

  static bool stringEndsWith(const string& text, const string &pattern) {
    return text.length() >= pattern.length() &&
        std::equal(text.crend(), text.crend() + pattern.length(), pattern.cbegin());
  }

  void PageRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
    resp.setStatus(HTTPResponse::HTTP_OK);
    // cout << Poco::format("Received request %s", req.getURI()) << endl;
    string fileName = req.getURI() == "/" ? "index.html" : (req.getURI().substr(1));
    
    if (stringEndsWith(req.getURI(), ".html")) {
      resp.setContentType("text/html");      
    } else if (stringEndsWith(req.getURI(), ".css")) {
      resp.setContentType("text/css");
    } else if (stringEndsWith(req.getURI(), ".js")) {
      resp.setContentType("application/javascript");
    } else if (stringEndsWith(req.getURI(), ".woff")) {
      resp.setContentType("font/woff");
    }
    FileInputStream input(fileName);
    StreamCopier::copyStream(input, resp.send());
  }

}}} // namespace
