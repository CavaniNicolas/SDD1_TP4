# options
CFLAGS = -Wall -Wextra -g -MMD

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable
	@echo "Executer avec ./bin/executable filename"

# edition des liens
bin/executable: $(OBJ)
	@mkdir -p $(@D) #creer le dossier bin, s il n existe pas
	cc -o $@ $^

# genere les fichiers .o (dans build) a partir des fichiers .c (dans src) du meme nom
# compilation
build/%.o: src/%.c
	@mkdir -p $(@D) # creer le dossier build, s il n'existe pas
	cc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)