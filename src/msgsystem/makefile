include ../Makefile.in

Target = msg_system_svr
CXXFLAGS += -D__MSGSYS_SVR__ $(CINC)

all:$(Target)

$(Target):$(PROTOCOL_OBJ) $(OBJECTS)
	$(CC) -o $@ $^ $(LIB) $(LIBPATH)  $(LDFLAGS)

$(OBJECTS):%.o:%.cpp
	$(CC) -c $(CXXFLAGS)  $<  -o $(OBJ_DIR)/$@

$(PROTOCOL_OBJ):%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

install: 
	cp -f $(Target) ../../bin/msgsystem/$(Target)

.PHONY:clean
clean:
	rm -rf $(Target) $(OBJ_DIR)/*.o $(PROTOCOL_DIR)/*.o