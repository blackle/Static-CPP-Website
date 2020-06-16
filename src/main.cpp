#include "App.h"
#include "resources.h"
#include <iostream>
/* Note that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support */

int main() {
	Resources res;
	auto i = res.map.find("index.html");
	if (i != res.map.end()) {
		auto resource = i->second;
		std::cout << "mimetype: " << resource.mimetype << std::endl;
	}
	/* Overly simple hello world app */
	uWS::App().get("/*", [](auto *res, auto *req) {
			(void) res;
			(void) req;
	    res->end("Hello world!");
	}).listen(3000, [](auto *token) {
	    if (token) {
		std::cout << "Listening on port " << 3000 << std::endl;
	    }
	}).run();

	std::cout << "Failed to listen on port 3000" << std::endl;
}