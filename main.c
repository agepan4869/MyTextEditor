#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUFFER_SIZE 100

struct termios CookedMode;
struct termios RawMode;

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
    string *head = malloc(sizeof(string));
    head->prev = NULL;
    head->next = NULL;
    if(argc != 2)
        printf("error: invalid argument\n");
    else{
        file_read(argv[1],head);
        string *current = head;

        int input_key;
        tcgetattr(STDIN_FILENO,&CookedMode);
        cfmakeraw(&RawMode);

        tcsetattr(STDIN_FILENO,0,&RawMode);

        // normal
//        printf("\e[31m\e[47m");     // color
        while(current){
            printf("\e[2J\e[H");        // clear
            printf("%s",current->str);

            input_key = getchar();
            if(input_key == 110){
                // 110 = n
                current = current->next;
            }
            if(input_key == 112){
                // 112 = p
                current = current->prev;
            }
            if(input_key == 101){
                // 101 = e
                printf("\e[2J\e[H");        // clear
                printf("\e[39m\e[49m\n");     // reset
                break;
            }
        }
        tcsetattr(STDIN_FILENO,0,&CookedMode);
//        printf("\e[39m\e[49m\n");     // reset
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
