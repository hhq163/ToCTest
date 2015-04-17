all:
	make  -C encryptlib
	make install -C encryptlib
	make -C msgsystem
	
install:
	make install -C msgsystem
	
clean:
	make clean -C msgsystem
	make clean -C encryptlib
	rm -rf comm/*.o




