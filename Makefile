CC = clang

CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)

SRC = main.c board.c moves.c render.c
OBJ = $(SRC:.c=.o)

TARGET = chess

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *.o chess

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
