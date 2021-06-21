CC	= gcc
OBJ_DIR = ../obj
BIN_DIR = ../bin
SRC_DIR = .
INCDIR	= headers
CFLAGS	= -Wall -I$(INCDIR)

TARGET	= $(BIN_DIR)/framework
OBJS	= $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/infgath.o \
	  $(OBJ_DIR)/exploits.o \
	  $(OBJ_DIR)/lists.o \
	  $(OBJ_DIR)/utils.o \
	  $(OBJ_DIR)/display.o
	

$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)*.d

clean :
	@rm -r $(OBJ_DIR) $(BIN_DIR) 
