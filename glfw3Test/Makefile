SOURCES := main.cpp \
./src/gl/rgGLProgram.cpp


PROGRAM := glfw3Test 
CXX := clang++ 
LDFLAGS := -L/usr/lib/gcc/x86_64-linux-gnu/4.8 -L/usr/lib/nvidia-331-updates
LDFLAGS += -L../external/linux/glfw-3.1/src
LDFLAGS +=  -lGL -lGLU -lglut -lGLEW -O3 -lserial -lpthread -lglfw3
CXXFLAGS := -I include
CXXFLAGS += -I /usr/include -I /usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/c++/4.8
CXXFLAGS += -I ../external/linux/glfw-3.1/include
CXXFLAGS += -std=c++11 -Wall -O3 -mfpmath=sse -msse4.1
CXXFLAGS += -fpermissive
OBJECTS := $(SOURCES:.cpp=.o)

BIN := bin

build: $(BIN)/$(PROGRAM)

all: clean run

run: $(BIN)/$(PROGRAM)
	./$(BIN)/$(PROGRAM) $(PARAMS)

$(OBJECTS): 
	@mkdir -p $(BIN)
	@echo "Compiling: $(subst .o,.cpp, $@) -> $(addprefix $(BIN)/, $(notdir $@))"
	@$(CXX) -c $(subst .o,.cpp, $@) -o $(addprefix $(BIN)/,$(notdir $@)) $(CXXFLAGS)

$(BIN)/$(PROGRAM): $(OBJECTS)
	@mkdir -p $(BIN)
	@echo "Linking: $(addprefix $(BIN)/, $(notdir $^)) -> $@"
	@$(CXX) $(addprefix $(BIN)/, $(notdir $^)) -o $@ $(CXXFLAGS) $(LDFLAGS)
clean: 
	@rm -f *.o $(BIN)/$(PROGRAM)