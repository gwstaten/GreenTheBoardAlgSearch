CXX := c++

SRC_DIR := src
OBJ_DIR := bin
BIN_DIR := .

EXE := $(BIN_DIR)/run
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CXXFLAGS := -g -Wall -Wextra -O3 -Iinclude -MMD -MP -std=c++17
LDLIBS   := -lm -pthread

ifeq ($(OS), Windows_NT)
	LDLIBS += -static-libstdc++ -static
endif

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	@$(CXX) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) -r $(EXE) $(OBJ_DIR)

-include $(OBJ:.o=.d)
