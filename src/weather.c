#include "weather.h"

int check_weather(char* weather) {
    // 날씨 체크
    if(strstr(weather, "Rain") != NULL || strstr(weather, "Drizzle") != NULL || strstr(weather, "Shower") != NULL) {
        return 2;
    }
    else if(strstr(weather, "Cloud") != NULL || strstr(weather, "Overcast") != NULL) {
        return 1;
    }
    else {
        printf("맑음\n");
        return 0;
    }
}

void weather_is_what(int *out_weather, int *out_wind, int *out_temp) {
    // 대구 날씨 api 받아오기
    int server_fd;
    struct sockaddr_in server_addr;
   
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("소켓 실패!");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80); // HTTP
    server_addr.sin_addr.s_addr = inet_addr("5.9.243.187"); // wttr.in 날씨 api

    if(connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("연결 실패!");
        close(server_fd);
        return;
    }

    char *req = "GET /Daegu?format=%C_%w_%t HTTP/1.1\r\nHost: wttr.in\r\nConnection: close\r\n\r\n";
    write(server_fd, req, strlen(req));

    char buffer[BUF_SIZE];
    int bytes = read(server_fd, buffer, BUF_SIZE - 1);
    if(bytes > 0) {
        buffer[bytes] = '\0';
        // printf("req : %s\n", buffer);
        // 파싱
        char *req2 = strstr(buffer, "\r\n\r\n");

        // 검사하기
        if(req2 != NULL) {
            req2 += 4;
            req2[strcspn(req2, "\r\n")] = '\0';
            char *weather = strtok(req2, "_");;
            char *wind = strtok(NULL, "_");
            char *temp = strtok(NULL, "_");

            if(weather != NULL && wind != NULL && temp != NULL) {
                *out_weather = check_weather(weather);
            
                // 숫자만 뽑기
                for(int i = 0; wind[i] != '\0'; i++) {
                    if(isdigit(wind[i])) {
                        *out_wind = atoi(&wind[i]);
                        break;
                    }
                }

                for(int i = 0; temp[i] != '\0'; i++) {
                    if(isdigit(temp[i]) || temp[i] == '+' || temp[i] == '-') {
                        *out_temp = atoi(&temp[i]);
                        break;
                    }
                }
                
                // printf("weather: %d, wind: %d, temp: %d\n", *out_weather, *out_wind, *out_temp);
            }
        }
    }

    close(server_fd);

    return;
}