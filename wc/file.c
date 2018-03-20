#pragma warning(disable:4996)
#include "file.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define FILE_NUM    100
#define USELSEE_NUM 100
#define WORD_LEN 30


/*
**function:return the length of file
**parameter:file pointer
*/
static int
filelength(FILE *fp)
{
    int num;
    fseek(fp, 0, SEEK_END);
    num = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return num;
}


/*
**function:read file to buffer
**parameter:file path,relative or absolute path
*/
char *
readfile(char *path)
{
    FILE *fp;
    int len;
    char *buf;

    if((fp = fopen(path, "r")) == NULL)
    {
        printf("open file %s error.\n", path);
        exit(0);
    }


    len = filelength(fp);
    buf = (char *) malloc (len);
    fread(buf, sizeof(char), len, fp);
    fclose(fp);
    *(buf + len - 1) = '\0';
    return buf;
}



char **
processBuf(char *buf)
{
    char **word_list;
    int i;
    word_list = (char **) malloc(sizeof(char *) * USELSEE_NUM);
    for(i = 0; i < USELSEE_NUM; ++i)
        word_list[i] = (char *) malloc(sizeof(char) * WORD_LEN);


    i = 0;
    char seps[] = ",\t\n ";
    char *token;
    token = strtok(buf, seps);
    while(token != NULL )
    {
        strcpy(word_list[i++], token);
        token = strtok(NULL, seps);
    }
    word_list[--i] = '\0';

    return word_list;
}


