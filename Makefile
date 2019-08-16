#通用makefile
#文件目录
BIN_DIR=./bin
OBJ_DIR=./obj
SRC_DIR=./source
INC_DIR=./include 
LIB_PATH=./lib

SRC=$(wildcard $(SRC_DIR)/*.cpp )  #源文件
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

#目标文件名
TARGET=$(BIN_DIR)/glog
INSTALL_PATH ?= .

#修改编译器
ARCH ?= 
CC=$(ARCH)gcc
CPP=$(ARCH)g++
AR=$(ARCH)ar
STRIP=$(ARCH)strip

CFLAGS += -Wall
CFLAGS += $(foreach dir,$(INC_DIR),-I$(dir))
ifeq ($(debug), yes)
CFLAGS += -DDEBUG_LOG
endif


#加载库文件
LDFLAGS += -L$(LIB_PATH)
LDFLAGS += -lpthread -lglog


all:$(TARGET)
$(TARGET): $(OBJS)
	@$(CPP) $(OBJS) -o $@ $(LDFLAGS)
	@echo "  "$(CPP) $(notdir $(OBJS)) "-o" $(notdir $@) $(CFLAGS) $(LDFLAGS)
	@$(STRIP) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CPP) $(CFLAGS) -c $< -o $@
	@echo "  "$(CPP) $(CFLAGS) "-c" $(notdir $<) "-o" $(notdir $@) 

print:
	@echo $(SRC)
	@echo $(OBJS)
	@echo $(LDFLAGS)

	
clean:
	-rm $(TARGET)
	-rm $(OBJS) $(LIB_TARGET)

