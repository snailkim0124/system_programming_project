#ifndef WEATHER_H
#define WEATHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#define BUF_SIZE 4096

void weather_is_what(char *out_weather, int *out_wind, int *out_temp);
int check_weather(char* weather);

#endif