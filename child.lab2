#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    char str[100];//считываемая строкa
    int len = 0;//длина строки
    char symb, l_symb = '\n';

    while(read(0, &symb, 1)){ // считывает по одному символу из строки

        str[len++] = symb;

        if(symb == '\n'){

            if(l_symb == '\n'){
                write(2, "2", 1);
                break;
            }

            if(l_symb == '.' || l_symb == ';'){
                write(2, "0", 1);
                write(1, &str[0], len);
            }
            else{
                write(2, "1", 1);
            }
            len = 0;
        }
        l_symb = symb;
    }
    return 0;
}
