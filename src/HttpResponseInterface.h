#pragma once
#include <memory>
#include "App.h"

//so I don't have to fuck with the templates
class HttpResponseInterface {
public:
	virtual std::pair<bool, bool> tryEnd(std::string_view data, int totalSize = 0) = 0;
};

template <bool SSL>
class HttpResponseFacade  : public HttpResponseInterface {
public:
	HttpResponseFacade(uWS::HttpResponse<SSL>* res) : m_res(res) {}

	virtual std::pair<bool, bool> tryEnd(std::string_view data, int totalSize = 0) {
		return m_res->tryEnd(data, totalSize);
	};

private:
	uWS::HttpResponse<SSL>* m_res;
};

template <bool SSL>
std::shared_ptr<HttpResponseInterface> responseToFacade(uWS::HttpResponse<SSL>* res) {
	return std::make_shared<HttpResponseFacade<SSL>>(res);
}
