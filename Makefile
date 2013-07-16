EXE = jvm
SOURCES = jvm.c frame_stack.c loader.c linker.c initializer.c opcode.c
OBJECTS := $(SOURCES:%.c=%.o)
CFLAGS = -Wall -std=c99 -pedantic -lm
CC = gcc

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 

clean:
	$(RM) $(EXE) $(OBJECTS) *~
	$(RM) -r .depend

valgrind:
	valgrind $(EXE)

zip: clean
	zip dream_team_jvm.zip *

.PHONY: clean valgrind zip

###########
# necessário para descobrir automaticamente as dependências de cada arquivo fonte
depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend

include .depend
###########
