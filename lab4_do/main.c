#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sys/mman.h"
pthread_mutex_t mutex;

int main() {
    char* str;
    printf("Enter the string:\n");
    str = calloc(100,sizeof(char));
    fgets (str, 100, stdin);
    char* input = mmap(NULL, sizeof(char)*strlen(str), PROT_WRITE|PROT_READ, MAP_SHARED|MAP_ANONYMOUS, 0, 0);

    for (int i = 0; i<strlen(str); i++){ //посимвольный ввод строки в массив "input"
        input[i] = str[i];
    }
    
    if(input == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
    }

    int child1 = fork();
        if (child1 == -1){
            char *wr = "fork 1 error\n";
            write(1,wr,strlen(wr));
            return -1;
        } 
        if (child1 == 0){
            pthread_mutex_lock(&mutex);
            int k = 0;
            while(k<strlen(input)) { //замена на верхние регистры
                if ((input[k] > 96) &&(input[k] < 123)) {
                    input[k] = input[k]-32;  
                }
                k++;
            }
            pthread_mutex_unlock(&mutex);
        }
        
        else {
            int child2=fork();

            if (child2 == -1) {
            char *wr2="child2 failed\n";
            write(1,wr2,strlen(wr2));
            return -1;
            } 
            if (child2 == 0) {
                pthread_mutex_lock(&mutex);
                int k = 0;
                while(k<strlen(input)){
                    if (input[k] == 32){
                        input[k] = 95;
                    }
                    k++;
                }
                pthread_mutex_unlock(&mutex);
            }

            if (child2 > 0)
            {   printf("%s", input);
                char d = munmap(input, 1);
                printf("%s", "\nmmap уничтожен\n");
                pthread_mutex_destroy(&mutex);
            }
        }
} 