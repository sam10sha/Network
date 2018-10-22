# Command options
CFLAGS      = g++ -ansi -Wall -std=c++11
LFLAGS      = -c

# Directories
SRC_DIR     = src/Sources
HEAD_DIR    = src/Headers
OBJ_DIR     = obj
BIN_DIR     = bin

# Source files
DRIVER_CPP  = $(SRC_DIR)/driver.cpp
SERVER_CPP  = $(SRC_DIR)/server.cpp

# Object files
DRIVER_OBJ  = $(OBJ_DIR)/driver.o
SERVER_OBJ  = $(OBJ_DIR)/server.o

# Executables
SERVER      = $(BIN_DIR)/server


# Directories
$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@


server: $(SERVER)

# Binaries
$(SERVER): $(DRIVER_OBJ) $(SERVER_OBJ) | $(BIN_DIR)
	$(CFLAGS) $^ -o $@


# Object files
$(DRIVER_OBJ): $(DRIVER_CPP) | $(OBJ_DIR)
	$(CFLAGS) $(LFLAGS) -I $(HEAD_DIR) $^ -o $@

$(SERVER_OBJ): $(SERVER_CPP) | $(OBJ_DIR)
	$(CFLAGS) $(LFLAGS) -I $(HEAD_DIR) $^ -o $@


# Clean
clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*


