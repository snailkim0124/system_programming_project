CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lncursesw

TARGET = farm_game
SRCS = src/main.c src/render.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)