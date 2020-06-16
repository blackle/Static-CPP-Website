#define UWS_HTTPRESPONSE_NO_WRITEMARK
#include "App.h"
#include "resources.h"
#include <iostream>

#define PORT 80

int main() {
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
		    res->end("404 Not Found");
		    return;
		  }

			auto resource = i->second;
			res->writeHeader("Content-type", resource.mimetype);
			res->writeHeader("ETag", resource.etag);
			//todo: hhnnggg chunk it
			res->end(std::string_view(resource.data, resource.length));

	}).listen(PORT, [](auto *token) {
	    if (token) {
		std::cout << "Listening on port " << PORT << std::endl;
	    }
	}).run();

	std::cout << "Failed to listen on port " << PORT << std::endl;
}