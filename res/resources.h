#pragma once
#include <string>
#include <unordered_map>

struct Resource {
	std::string mimetype;
	size_t length;
	const char* data;
};

class Resources {
public:
	Resources();
	const std::unordered_map<std::string, Resource> map;
};