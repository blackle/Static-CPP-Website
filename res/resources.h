#pragma once
#include <string_view>
#include <unordered_map>

struct Resource {
	std::string_view mimetype;
	std::string_view etag;
	size_t length;
	const char* data;
};

class Resources {
public:
	Resources();
	const std::unordered_map<std::string_view, Resource> map;
};