#define UWS_HTTPRESPONSE_NO_WRITEMARK
#include "App.h"
#include "resources.h"
#include <iostream>
#include <cstdlib>

int main() {
	const char* portstring = std::getenv("PORT");
	if (portstring == nullptr) {
		portstring = "8080";
	}
	int port = atoi(portstring);
	//resource list is generated on construction of this class
	Resources resources;

	uWS::App().get("/*", [&resources](auto *res, auto *req) {
			auto path = req->getUrl();

			std::string modified; //path is a string_view, so to modify it we need a temporary string that remains in scope.
			if (path.back() == '/') {
				modified = std::string(path) + "index.html";
				path = modified;
			}
			path = path.substr(1, path.length()); //remove the / at the start of the path

			auto i = resources.map.find(path);
			if (i == resources.map.end()) {
				res->writeStatus("404 Not Found");
				i = resources.map.find("404.html");
			}

			auto resource = i->second;

			auto client_etag = req->getHeader("if-none-match");
			if (client_etag == resource.etag) {
				res->writeStatus("304 Not Modified");
				res->end();
				return;
			}

			res->writeHeader("Content-type", resource.mimetype);
			res->writeHeader("ETag", resource.etag);
			//todo: hhnnggg chunk it
			res->end(std::string_view(resource.data, resource.length));

	}).listen(port, [port](auto *token) {
	    if (token) {
		std::cout << "Listening on port " << port << std::endl;
	    }
	}).run();

	std::cout << "Failed to listen on port " << port << std::endl;
}