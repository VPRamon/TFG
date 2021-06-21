CC	= gcc
OBJ_DIR = ../../obj
BIN_DIR = ../../bin
SRC_DIR = .
INCDIR	= ../../src/headers
CFLAGS	= -Wall -I$(INCDIR)

TARGET	= $(BIN_DIR)/fuzzer
OBJS	= $(OBJ_DIR)/fuzzer.o \
	  $(OBJ_DIR)/lists.o
	

$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -pthread

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)*.d

clean :
	@rm -r $(OBJ_DIR) $(BIN_DIR) 
