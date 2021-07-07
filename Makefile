.PHONY : all clean_all clean
CC=g++
CPPFLAGS=-std=c++11 -g -Werror -pedantic-errors -Wredundant-decls \
			-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual \
			-Wconversion -Wctor-dtor-privacy -Wduplicated-branches \
			-Wduplicated-cond -Wextra-semi -Wfloat-equal -Wlogical-op \
			-Wnon-virtual-dtor -Woverloaded-virtual -Wsign-conversion -Wsign-promo
OMNI_HOME=/opt
INCLUDES=-I$(OMNI_HOME)/include
LIBS=-lomniORB4 -lomnithread -lomniDynamic4
SERVER_SOURCES=$(wildcard ./Server/*.cpp)
CLIENT_SOURCES=$(wildcard ./Client/*.cpp)
SERVER_OBJECTS=$(SERVER_SOURCES:.cpp=.o)
CLIENT_OBJECTS=$(CLIENT_SOURCES:.cpp=.o)
SERVER_RUN=ServerRun
CLIENT_RUN=ClientRun

all: $(SERVER_RUN) $(CLIENT_RUN)

$(SERVER_RUN): DataSK.o $(SERVER_OBJECTS)
	$(CC) -g -o $(SERVER_RUN) -L$(OMNI_HOME)/lib DataSK.o $(SERVER_OBJECTS) $(LIBS)

$(SERVER_OBJECTS): DataSK.o $(SERVER_SOURCES)
	$(foreach src,$(SERVER_SOURCES),$(CC) $(CPPFLAGS) -c $(src) -o $(src:.cpp=.o) &&) true

$(CLIENT_RUN): DataSK.o $(CLIENT_OBJECTS)
	$(CC) -g -o $(CLIENT_RUN) -L$(OMNI_HOME)/lib DataSK.o $(CLIENT_OBJECTS) $(LIBS)

$(CLIENT_OBJECTS): DataSK.o $(CLIENT_SOURCES)
	$(foreach src,$(CLIENT_SOURCES),$(CC) $(CPPFLAGS) -c $(src) -o $(src:.cpp=.o) &&) true

DataSK.o: DataSK.cc Data.hh
	$(CC) -c DataSK.cc

DataSK.cc Data.hh: Data.idl
	omniidl -bcxx Data.idl

clean_all: clean
	rm -f ./$(SERVER_RUN)
	rm -f ./$(CLIENT_RUN)

clean:
	rm -f ./*.o
	rm -f ./*.hh
	rm -f ./*SK.cc
	rm -f ./Server/*.o
	rm -f ./Client/*.o
