##work in progress
##these are variables 
CC=g++
## not needed
CC__= -std=c++11
OBJS = main.o And.o Command.o Or.o Semi.o

##errors flag
CC_FLAGS=-Wall -Werror -ansi -pedantic
##probably want to make all files have the same suffix
MKDIR = mkdir -p
OUT_DIR = bin


rshell: $(OBJS) $(OUT_DIR)/rshell

all: $(OBJS) $(OUT_DIR)/rshell
	
	$(CC) $(CC_FLAGS) $(OBJS) -o all

$(OUT_DIR)/rshell: $(OBJS)
	$(CC) -o $@ $(OBJS)
	
main.o: main.cpp And.cpp Command.cpp Or.cpp Semi.cpp Base.h
	$(MKDIR) $(OUT_DIR)
	$(CC) $(CC_FLAGS) -c main.cpp

And.o: And.h And.cpp Base.h
	$(CC) $(CC_FLAGS) -c And.cpp
	
Command.o: Command.cpp Command.h Base.h
	$(CC) $(CC_FLAGS) -c Command.cpp
	
Or.o: Or.cpp Or.h Base.h
	$(CC) $(CC_FLAGS) -c Or.cpp
	
Semi.o: Semi.cpp Semi.h Base.h
	$(CC) $(CC_FLAGS) -c Semi.cpp

clean:
	rm $(OUT_DIR)/rshell
	rm -f *.o *~ all *~ rshell
	rmdir $(OUT_DIR)
	