# CSCI 3081W S24
# - Abdelrahman 2024

# This Makefile is responsible for compiling all the back end code for the project

CXX = g++
CXXFLAGS = -std=c++23 -g -Wl,-rpath,$(DEP_DIR)/lib
ROOT_DIR = ..
DEP_DIR = $(ROOT_DIR)/dependencies
LIBDIRS = -L$(DEP_DIR)/lib

# need to use different version based on libssl
WEBSOCKET_VERSION_MAJOR = $(shell pkg-config --modversion libssl | cut -d '.' -f 1)
ifeq "$(WEBSOCKET_VERSION_MAJOR)" "3"
	WEBSOCKETS = websockets22
else
	WEBSOCKETS = websockets20
endif

BUILD_DIR = $(ROOT_DIR)/build
HEADERS_ALL = $(shell find include -name '*.h' -exec dirname {} \;) # finds all folders of .h files in include folder
HEADERS = $(sort ${HEADERS_ALL}) # sort to remove duplicates from headers list
INCLUDES = -I$(DEP_DIR)/include -Isrc/routing $(foreach d, $(HEADERS), -I$d)
SOURCES = $(shell find src -name '*.cc') # finds all .cc files in src folder
OBJFILES = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cc=.o)) # replace .cc with .o for all .cc files to get names for all object files
LIBS = -l$(WEBSOCKETS) -lssl -lcrypto -lz -lpthread

TRANSITE_EXE = $(BUILD_DIR)/bin/transit_service

# compiles all .cc files into .o
$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# compiles final exe by combining all object files
$(TRANSITE_EXE): $(OBJFILES)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LIBDIRS) $^ $(LIBS) -o $@
