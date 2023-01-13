#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sys/mman.h"
pthread_mutex_t mutex;

int main() 
{

    char* filename;
    printf("Enter out file name:\n");
    filename = calloc(100,sizeof(char));
    fgets (filename, 100, stdin);

    FILE* out_file = fopen(filename,"w");

    char* str;
    printf("\nEnter the string:\n");
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

        if (child1 == -1)
        {
            char *wr = "fork 1 error\n";
            write(1,wr,strlen(wr));
            return -1;
        } 
        if (child1 == 0)
        {
            pthread_mutex_lock(&mutex);
            //printf("%s", "\nYou are in the child 1 procces. Mutex is locked.\n");

            int last_c_of_input = sizeof(char)*strlen(input)-2; 

                if((input[last_c_of_input] == '.') || (input[last_c_of_input] == ';'))
                {
                    fputs(input,out_file);
                    printf("\nGreat line! Successfully written to out file!\n\n");
                }
        
            pthread_mutex_unlock(&mutex);
        }
        
        else 
        {
            int child2=fork();

            if (child2 == -1) {
            char *wr2="child2 failed\n";
            write(1,wr2,strlen(wr2));
            return -1;
            } 

            if (child2 == 0) 
            {
                pthread_mutex_lock(&mutex);
                //printf("%s", "\nYou are in the child 2 procces. Mutex is locked.\n");

                int last_c_of_input = sizeof(char)*strlen(input)-2;

                if((input[last_c_of_input] != '.') && (input[last_c_of_input] != ';'))  
                {
                    printf("\n+++invalid line+++\n");
                }

                pthread_mutex_unlock(&mutex);
            }

            if (child2 > 0)
            {   
                char d = munmap(input, 1);
                //printf("%s", "\nmmap уничтожен\n");
                pthread_mutex_destroy(&mutex);
            }
        }
} 
