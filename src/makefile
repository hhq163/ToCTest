Target = MsgSystemTest


#######设置编译器######
CC = g++

######设置目录结构######
SRC_DIR = .
OBJ_DIR = .
LIBPATH=-L../lib 
VPATH = $(SRC_DIR)


######设置依赖关系######
vpath %.o $(OBJ_DIR) 
SOURCES = $(foreach path, $(VPATH), $(wildcard $(path)/*.cpp))
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

######设置库文件######
LIB = -lpthread  -lrt -ljson -lencrypt -liconv -lprotobuf

#设置头文件引用路径
#####################################################################
CINC = -I/usr/local/include -I/usr/include  -I../protocol -I../comm -I. -I../protocolbuffer

######设置编译选项######
CXXFLAGS = -Wall  -g   -O2
LDFLAGS = -Wl,-rpath,$(RUNLIBPATH)  -Wl,-rpath,/usr/local/lib
CXXFLAGS +=  $(CINC)


all:$(Target)
	@echo " "
	@echo -e "\033[32m>         [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\033[0m"
	@echo -e "\033[32m>         [              MsgSystemTest COMPILE SUCCEEDED !!!!!!             ]\033[0m"
	@echo -e "\033[32m>         [____________________________________________________________]\033[0m"
	@echo " "
	

$(Target):$(OBJECTS)
	$(CC) -o $@ $^ $(LIBPATH)
	
#$@ $^ $(LIB) $(LIBPATH)  $(LDFLAGS)
$(OBJECTS):%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $<  -o $(OBJ_DIR)/$@

install: 
	cp -f $(Target) ../../bin/msgsystem/$(Target)

.PHONY:clean
clean:
	rm -rf $(Target) $(OBJ_DIR)/*.o