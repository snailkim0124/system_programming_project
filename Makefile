CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lncursesw -lm

TARGET = farm_game
SRCS = src/main.c src/render.c src/player.c src/save.c src/crop.c src/system.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

reset:
	rm -f save.dat