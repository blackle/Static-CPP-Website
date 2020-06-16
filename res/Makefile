FILES := $(wildcard public/*)
OBJECTS := $(FILES:public/%=build/%.o)
#todo: autodetect this for cross compilation
FORMAT := elf64-x86-64
ARCH := i386:x86-64

resources.a : $(OBJECTS) resources.o
	ar cr $@ $^

resources.o : resources.cpp resources.h
	g++ -c $< -o $@ -std=c++17

resources.cpp : $(FILES) $(OBJECTS) generate_resources.py
	./generate_resources.py $(FILES)

build/%.o : public/%
	objcopy -I binary -O $(FORMAT) -B $(ARCH) \
		--rename-section .data=.rodata,alloc,load,readonly,data,contents \
		$< $@