CC = gcc
CFLAGS = -Wall -g -Iinclude
TARGET = myshell

# src 폴더 안의 모든 .c 파일을 변수로 저장
SRCS = src/main.c src/parser.c src/process.c src/builtin.c
# .c 파일 이름들을 바탕으로 .o 파일 이름들 생성
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)