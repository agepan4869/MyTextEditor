#include <stdio.h>

void file_print(char *filename);

int main(int argc,char *argv[]){
    int i;
    printf("\e[2J\e[1;1H");     // ターミナルでclearするのと同じ処理
    if(argc == 2)
        file_print(argv[1]);
    return 0;
}

void file_print(char *filename){
    FILE *fp;
    char str[2];
    if((fp = fopen(filename,"r")) == NULL){
        printf("file not found \n");
        return;
    }
    while(fgets(str,2,fp))
        printf("%s",str);
    fclose(fp);
    return;
}
