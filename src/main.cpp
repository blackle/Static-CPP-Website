#include "App.h"
#include "resources.h"
#include <iostream>

#define PORT 4873

int main() {
	Resources resources;

	uWS::App().get("/*", [&resources](auto *res, auto *req) {
			(void) res;
			(void) req;
			auto path = req->getUrl();
			std::string modified;
			if (path.back() == '/') {
				modified = std::string(path) + "index.html";
				path = modified;
			}
			path = path.substr(1, path.length());
			auto i = resources.map.find(path);
			if (i != resources.map.end()) {
				auto resource = i->second;
				res->writeHeader("Content-type", resource.mimetype);
				res->writeHeader("ETag", resource.etag);
				//todo: hhnnggg chunk it
				res->end(std::string_view(resource.data, resource.length));
			} else {
				res->writeStatus("404 Not Found");
		    res->end("404 Not Found");
			}
	}).listen(PORT, [](auto *token) {
	    if (token) {
		std::cout << "Listening on port " << PORT << std::endl;
	    }
	}).run();

	std::cout << "Failed to listen on port " << PORT << std::endl;
}