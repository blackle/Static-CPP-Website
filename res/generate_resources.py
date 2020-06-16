#!/usr/bin/env python3
import sys
import mimetypes
import uuid

def symbol_prefix_for_file(filename):
	return "_binary_" + filename.replace("/", "_").replace(".", "_")

def start_symbol_for_file(filename):
	return symbol_prefix_for_file(filename) + "_start"

def end_symbol_for_file(filename):
	return symbol_prefix_for_file(filename) + "_end"

def main():
	files = sys.argv[1:]
	f = open('resources.cpp', 'w')
	f.write('#include "resources.h"\n\n')

	for file in files:
		f.write('extern const char {start};\n'.format(start = start_symbol_for_file(file)))
		f.write('extern const char {end};\n'.format(end = end_symbol_for_file(file)))

	f.write('\n')
	f.write('Resources::Resources() : map{\n')

	for file in files:
		path = file[len("public/"):]
		mimetype, encoding = mimetypes.guess_type(path)
		symbol = start_symbol_for_file(file)
		f.write('{{"{path}", {{"{mimetype}", "{etag}", std::string_view(&{start}, (size_t) (&{end} - &{start})) }} }},\n'.format( \
			path=path, \
			mimetype=mimetype + "; charset=UTF-8", \
			etag=str(uuid.uuid4()), \
			start=start_symbol_for_file(file), \
			end=end_symbol_for_file(file) \
		))

	f.write('} { }\n')
	f.close()

if __name__ == "__main__":
	main()