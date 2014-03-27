CC=g++
Cflags=-c -MD
LDflags=

Input=main.cpp
ObjDir=obj
BinDir=bin
Output=EchoClient

Objects=$(addprefix $(ObjDir)/,$(Input:%.cpp=%.cpp.o))

all: $(BinDir)/$(Output)
	$(BinDir)/$(Output)
    
$(BinDir)/$(Output): $(Objects)
	g++ -o $(BinDir)/$(Output) $(Objects) $(LDflags)

obj/%.cpp.o: %.cpp
	g++ $(Cflags) -o $@ $<

-include $(ObjDir)/*.d

.IGNORE: clean
clean:
	rm $(ObjDir)/*
	rm $(BinDir)/$(Output)

