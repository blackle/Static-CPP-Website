HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.cpp)
PROJECT := server

CXXFLAGS += -g -Wall -Werror -Wextra -O1 -flto -std=c++17 -lpthread -isystem uWebSockets/src -isystem uWebSockets/uSockets/src -Ires
LDFLAGS += uWebSockets/uSockets/*.o -lz -lssl -lcrypto -fuse-ld=gold

all : $(PROJECT) $(TEST_PROJECT)

$(PROJECT) : $(HEADERS) $(SOURCES) Makefile uSockets resources
	g++ -o $(PROJECT) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) res/resources.a

resources :
	$(MAKE) -C res

uSockets : 
	$(MAKE) -C uWebSockets/uSockets WITH_OPENSSL=1
