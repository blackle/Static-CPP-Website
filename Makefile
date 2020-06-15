HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.cpp)
PROJECT := server

CXXFLAGS += -g -Wall -Werror -Wextra -O1 -flto -std=c++17 -lpthread -isystem uWebSockets/src -isystem uWebSockets/uSockets/src
LDFLAGS += uWebSockets/uSockets/*.o -lz -lssl -lcrypto -fuse-ld=gold

all : $(PROJECT) $(TEST_PROJECT)

$(PROJECT) : $(HEADERS) $(SOURCES) Makefile uSockets
	g++ -o $(PROJECT) $(SOURCES) $(CXXFLAGS) $(LDFLAGS)

uSockets : 
	$(MAKE) -C uWebSockets/uSockets WITH_OPENSSL=1
