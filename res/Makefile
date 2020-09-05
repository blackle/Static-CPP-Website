FILES := $(wildcard public/*)
OBJECTS := $(FILES:public/%=build/%.o)

resources.a : $(OBJECTS) resources.o
	ar cr $@ $^

resources.o : resources.cpp resources.h
	g++ -c $< -o $@ -std=c++17

resources.cpp : $(FILES) $(OBJECTS) generate_resources.py
	./generate_resources.py $(FILES)

build/%.o : public/% autodetect-arch
	objcopy -I binary -O ${FORMAT} -B ${ARCH} \
		--rename-section .data=.rodata,alloc,load,readonly,data,contents \
		$< $@

detect: detect.cpp
	g++ -o detect detect.cpp

.PHONY: autodetect-arch
autodetect-arch: detect
	$(eval FORMAT=$(shell objdump -f ./detect | grep -oP 'file format \K.*'))
	$(eval ARCH=$(shell objdump -f ./detect | grep -oP 'architecture: \K[^,]*'))
