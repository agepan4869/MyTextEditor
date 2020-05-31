#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2

typedef struct _string{
    char str[BUFFER_SIZE];
    struct _string *prev;
    struct _string *next;
}string;

void file_read(char *filename,string *head);

/* ****************************
 *      main
 * ****************************/
int main(int argc,char *argv[]){
    printf("\e[2J\e[1;1H");     // ターミナルでclearするのと同じ処理
    string *head = malloc(sizeof(string));
    head->prev = NULL;
    head->next = NULL;
    if(argc != 2)
        printf("error: invalid argument");
    else{
        file_read(argv[1],head);
        string *current = head;

        // normal
        printf("\e[31m\e[47m");     // color
        while(current->next){
            printf("%s",current->str);
            current = current->next;
        }
        printf("%s",current->str);
        printf("\e[39m\e[49m");     // reset
/*
        // reverse
        printf("\e[31m\e[47m");     // color
        while(current->prev){
            printf("%c",current->str[1]);
            printf("%c",current->str[0]);
            current = current->prev;
        }
        printf("%c",current->str[1]);
        printf("%c",current->str[0]);
        printf("\e[39m\e[49m");     // reset
*/
    }
    return EXIT_SUCCESS;
}

/* ****************************
 *      insert
 * ****************************/
string *insert(string *from){
    string *to = malloc(sizeof(string));
    if(from->next){
        from->next->prev = to;
        to->next = from->next;
    }else
        to->next = NULL;
    if(from)
        from->next = to;
    to->prev = from;
    return to;
}

/* ****************************
 *      file_read
 * ****************************/
void file_read(char *filename,string *head){
    FILE *fp;
    char buf[BUFFER_SIZE];

    if((fp = fopen(filename,"r")) == NULL){
        printf("file not found \n");
        return;
    }
    string *current = head;
    while(fgets(buf,sizeof(buf),fp)){
        strcpy(current->str,buf);
        insert(current);
        current = current->next;        
    }
    fclose(fp);
    return;
}
