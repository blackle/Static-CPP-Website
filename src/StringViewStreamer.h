#pragma once
#include <string_view>
#include <memory>
#include "HttpResponseInterface.h"
#include "App.h"

class StringViewStreamer {
public:
	StringViewStreamer(const std::string_view& str, size_t total_size, std::shared_ptr<HttpResponseInterface> res);
	bool operator()(int offset);
private:
	const std::string_view m_str;
	const size_t m_total_size;
	std::shared_ptr<HttpResponseInterface> m_res;
};