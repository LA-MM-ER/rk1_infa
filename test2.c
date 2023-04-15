#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int main() {
    int time_lim;
    scanf("%d",&time_lim);
    //system ("chcp 65001");
    system("cls");
    int str_ctr = 1, i, j;

    FILE *fptr; //указатель на структуру типа FILE
    char name[] = "text.txt";
    fptr = fopen(name, "r"); //поток

    char c;
    while((c = fgetc(fptr)) != EOF) {
        if (c == '\n')
            str_ctr++;
    }
    fclose(fptr);//на этом моменте закончили подсчет строк

    char **str_arr = (char **) malloc(str_ctr * sizeof(char *)); //массив указателей на строки

    char buffer[100];
    fptr = fopen(name, "r"); //открыли файл заново, чтобы считывать строки с начала
    for (i = 0; i < str_ctr; i++) {
        fgets(buffer, 100, fptr);
        str_arr[i] = (char *) malloc(strlen(buffer));
        strcpy(str_arr[i], buffer);
    }
    fclose(fptr);

    for (i = 0; i < str_ctr; i++) { //вывод массива строк
        printf("%s", str_arr[i]);
    }
    double start = clock() / CLOCKS_PER_SEC;
    double now = start;
        printf("\033[1;1f"); //смещение на x,у координаты (вертикаль, горизонталь)
        while (time_lim - now + start > 0) {
            while(kbhit()) {
                for (i = 0; i < str_ctr; ++i) {
                    for (j = 0; str_arr[i][j] != '\0'; j++) {
                        while (!kbhit());
                        c = getch();
                        printf("\033[%d;%df", i + 1, j + 1);
                        if (str_arr[i][j] == c) {
                            printf("\x1b[32m%c\x1b[0m", str_arr[i][j]);
                        } else {
                            printf("\x1b[31m%c\x1b[0m", str_arr[i][j]);
                        }

                    }
                }
            }
            now = clock() / CLOCKS_PER_SEC;
        }
    free(str_arr);
    return 0;
}