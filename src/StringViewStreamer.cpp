#include "StringViewStreamer.h"

#define CHUNK_SIZE 100000

StringViewStreamer::StringViewStreamer(const std::string_view& str, size_t total_size, std::shared_ptr<HttpResponseInterface> res)
	: m_str(str)
	, m_total_size(total_size)
	, m_res(res)
{}

bool StringViewStreamer::operator()(int offset)
{
	while (true) {
		if (static_cast<unsigned>(offset) >= m_str.length()) {
			return true; //we hit the end of the string, which means we wrote everything
		}
		auto chunk = m_str.substr(offset, CHUNK_SIZE);
		if (!m_res->tryEnd(chunk, m_total_size).first) {
			return false; //failed, meaning we need to keep writing
		}
		offset += CHUNK_SIZE;
	}
}