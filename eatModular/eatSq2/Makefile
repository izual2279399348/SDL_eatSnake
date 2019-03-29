
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/eatSquares

SRC= main.c eatLogic.c eatDraw.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c eatLogic.h eatDraw.h gameStructures.h
eatDraw.o:  eatDraw.c eatDraw.h eatLogic.h gameStructures.h
eatLogic.o:  eatLogic.c eatLogic.h gameStructures.h 

