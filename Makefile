VERSION 	=_0.01
CXX			= g++
DEBUG 		= -g
CXXFLAGS	= -Wall -Wextra -Wpedantic
SOURCES	 	=$(wildcard ./code/Src/*.cpp)
INCLUDES  	= -I ./code/Inc
LIB_NAMES 	=
LIB_PATH 	= -lm
OBJ			=$(patsubst %.cpp, %.o, $(SOURCES))
TARGET		=stack

#links
$(TARGET):$(OBJ)
	@mkdir -p progect
	$(CXX) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o ./progect/$(TARGET)_$(VERSION)
	@rm -rf $(OBJ)
	
#compile
%.o: %.cpp
	$(CXX) $(INCLUDES) $(DEBUG) -c $(CXXFLAGS) $< -o $@

start: ./progect/$(TARGET)_$(VERSION)
	./progect/$(TARGET)_$(VERSION)

mem_test: ./progect/$(TARGET)_$(VERSION)
	valgrind ./progect/$(TARGET)_$(VERSION)

debug: ./progect/$(TARGET)_$(VERSION)
	gdb ./progect/$(TARGET)_$(VERSION)

create_f_sis:
	@mkdir -p ./code
	@mkdir -p ./code/Inc
	@mkdir -p ./code/Src

.PHONY:clear
clear:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output 
