#pragma warning(disable:4996)
#include "wc.h"
#include <ctype.h>      //for isalpha
#include <stdlib.h>     //for malloc
#include <string.h>
#include <stdio.h>

#define IN  1           //in word
#define OUT 0           //out word

#define PRECODE 1
#define CODE 2
#define SPACE_LINE 3
#define PRECOMMENT 4
#define COMMENT 5

#define NOT 0
#define YES 1

#define USELSEE_NUM 100
#define WORD_LEN 30

#define MAX_LINE 1000
#define MAX_LINE_LEN 100

#define SPACE  ' ' == c || '\n' == c || '\t' == c ||\
                ',' == c || ';' == c || ')' == c || \
                '(' == c || '{' == c || '}' == c



static int *word_num;


/*
**function:compare checked word with word_list,
**********according result add corresponding word_num
**parameter:checked word and the word_list
*/
static void compare(char **word_list, char *word)
{
    int i = 0;
    while(word_list[i] != '\0')
    {
        if(strcmp(word_list[i], word) == 0)
        {
            word_num[i] += 1;
        }
        i += 1;
    }
    word_num[i] = -1;
}


/*
**function: count char, word, line
**parameter: .c file buffer, mask word list
**return value: statistics result
*/
BasicInfo *CWL(char *buf, char **word_list, int a_state)
{

    /*状态变量*/
    BasicInfo *info = (BasicInfo *)malloc(sizeof(BasicInfo));
    int state,extra_state=NOT;
    char c;
    char tmp[WORD_LEN];
    int i,extra_space;
    char *p,*extra_p;   /*buf copy*/



    /*初始化变量*/
    info->nc = info->nl = info->nw = 0;
    state = OUT;
	extra_state = NOT;
    tmp[0] = '\0';
    word_num = (int *) malloc(sizeof(int ) * USELSEE_NUM);
    memset(word_num, 0, sizeof(int) * USELSEE_NUM);
    extra_p = p = buf;



  
    for(i = 0; (c = *buf++) != '\0'&&c>=-1&&c<=255; )
    {
        ++info->nc;

        if('\n' == c)
            ++info->nl;

		if (' ' == c || '\n' == c || '\t' == c || ',' == c || ';' == c || ')' == c || '(' == c || '{' == c || '}' == c)
        {
            state = OUT;
            tmp[i] = '\0';
            compare(word_list, tmp);
            i = 0;
        }

        if(isalpha(c) && OUT == state)
        {
            state = IN;
            ++info->nw;
        }

        if(isalpha(c) && IN == state)
        {
            tmp[i++] = c;
        }
    }
    /*最后一行没有'\n'*/
    ++info->nl;




    /*following count codeline, spaceline, commentline*/
    char seps[] = "\n";
    char *token;
    char **line;
    int influence = NOT;
    line = (char **)malloc(sizeof(char *) * MAX_LINE);
    for(i = 0; i < MAX_LINE; ++i)
        line[i] = (char *) malloc(sizeof(char) * MAX_LINE_LEN);

    i = 0;
    token = strtok(p, seps);
	
	
    while(token != NULL)
    {
        strcpy(line[i++], token);
        token = strtok(NULL, seps);
    }
    line[i] = '\0';
    /*process each line, determine the line type*/
    i = 0;
    int line_type;
    
    info->codeline = info->commentline = info->spaceline = 0;
    /*these are ugly code, time limited*/
	while (line[i] != '\0')
    {
        p = line[i];
        line_type = SPACE_LINE;
        while((c = *p++) != '\0'&&c >= -1 && c <= 255)
        {

			if (influence == YES  && strstr(line[i], "*/") != NULL)
            {
                influence = NOT;
				if (*(strstr(line[i], "*/") + 2) == '\0')
                {
                    line_type = COMMENT;
                    break;
                }

            }

            if (line_type == SPACE_LINE && isspace(c))
                continue;

            if (line_type == SPACE_LINE && '/' == c)
            {
                line_type = PRECOMMENT;
                continue;
            }

            if (line_type == PRECOMMENT && '/' == c)
            {
                line_type = COMMENT;
                continue;
            }

            if (line_type == PRECOMMENT && '*' == c)
            {
                line_type = COMMENT;
                influence = YES;
                continue;
            }
            if (line_type == COMMENT && isprint(c))
                continue;
            if (line_type == SPACE_LINE && !isspace(c) && c != '/')
            {
                line_type = PRECODE;
                continue;
            }

            if (line_type == PRECODE && !isspace(c) && c != '/')
            {
                line_type = CODE;
                continue;
            }

            if (line_type == PRECODE && '/' == c)
            {
                line_type = PRECOMMENT;
                continue;
            }
            if (line_type == PRECOMMENT && !isspace(c) && c != '*' && c != '/')
            {
                line_type = CODE;
                continue;
            }

            if (line_type == PRECODE && isspace(c))
                continue;

            if (influence == YES && line_type == CODE)
            {
                line_type = COMMENT;
                continue;
            }

        }

        if(line_type == PRECODE || line_type == PRECOMMENT)
            line_type = SPACE_LINE;
		if (line_type == CODE) 
			++info->codeline;
		else if ((line_type == SPACE_LINE) )
			++info->spaceline;
		else                                        
		++info->commentline;

        ++i;
    }
    
    if(a_state )
        printf("代码行/空行/注释行:%d/%d/%d\n", info->codeline, info->commentline, info->spaceline);

    i = 0;
    while(word_num[i] != -1)
    {
        info->nw -= word_num[i];
        ++i;
    }
    return info;
}

/*
**function: print mask word num
*/
void
printStopList(char **word_list)
{

    int i = 0;
    while(word_list[i] != '\0')
    {
         printf("%s, num :%d\n", word_list[i], word_num[i]);
         i += 1;
    }
}

