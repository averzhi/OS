#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    write(1, "enter output file name\n", 24);

    char* out_file = (char*)malloc(100 * sizeof(char)); //путь на название файла
	int nleng = read(0, out_file, 100); //считали имя файла
	out_file[nleng - 1] = 0;
    int fd_out = open(out_file, O_WRONLY|O_APPEND);

    write(1, "print str OR print nothing and push enter to stop\n", 38);

    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    int id = fork(); // 

    if(id > 0){
        close(fd1[0]);
        close(fd2[1]);

        char symb, ans;
        do{
            while(read(0, &symb, 1)){
                write(fd1[1], &symb, 1);
                if(symb == '\n'){
                    break;
                }
            }
            read(fd2[0], &ans, 1);
            if(ans == '1'){
                write(1, "+++invalid line+++\n", 20);
            }
        }
        while(ans != '2');

        close(fd1[1]);
        close(fd2[0]);
    }
    else if(id == 0){
        close(fd1[1]);
        close(fd2[0]);

        dup2(fd1[0], 0);

        dup2(fd_out, 1);

        dup2(fd2[1], 2);

        execl("./prog_child.out", "prog_child.out", NULL);

        close(fd1[0]);
        close(fd2[1]);
    }
    else{
        _exit(-1);
    }
    
    return 0;
}
