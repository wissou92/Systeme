NOM=SeaOfDevs
LIB_DIR=./lib
INCL_DIR=./lib/include

all: compile

run:
	./$(NOM) input.sod

compile:
	cd $(LIB_DIR) && $(MAKE)
	gcc -o $(NOM) -I$(INCL_DIR) $(NOM).c -L$(LIB_DIR) -lnm

.PHONY: clean mrproper

clean:
	rm -rf $(NOM)

mrproper: clean
	rm -rf $(LIB_DIR)/*.o
	rm -rf $(LIB_DIR)/libnm.a
