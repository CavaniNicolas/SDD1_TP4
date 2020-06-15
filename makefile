#options
CFLAGS = -Wall -Wextra -g -MMD

SRC = $(wildcard src/*.c)# $(wildcard src/pilefile/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable
	@echo "Executer avec ./bin/executable"

#édition des liens
bin/executable: $(OBJ)
	@mkdir -p $(@D) #créer le dossier bin, s'il n'existe pas
	cc -o $@ $^

#génère les fichiers .o (dans build) à partir des fichiers .c (dans src) du même nom
#compilation
build/%.o: src/%.c
	@mkdir -p $(@D) #créer le dossier build, s'il n'existe pas
	cc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)