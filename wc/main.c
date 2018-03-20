#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wc.h"
#include "file.h"

#define DEBUG 0

#define FALSE 0
#define TRUE  1
#define ALL 1
#define PART 0

#define MAX_PATH 100


int
main(int argc, char **argv)
{
    
    /*i, j use for loop val, end use for end loop to reduce runtime*/
    int i, end, j = 0;
    /*array path to store file path, p visit command line*/
    char *path[MAX_PATH] , *p, *filename;
    /*buffer store .c file*/
    char *buffer;
    /*maintain a struct to store statistic info*/
    BasicInfo *info;
    /*process_type 0 represent single file*/
    int process_type;
    /*mask word list*/
    char **word_list;
    /*word_list path*/
    char *word_list_path;
    /*word buffer*/
    char *buf;
    /*state val to capture command line parameter*/
    int s_state;
    int a_state;


    /*initialize val and parse command line parameter*/
    word_list_path = path[0] = p = filename = NULL;
    process_type = PART;
    s_state = a_state = FALSE;
    
    for(i = 1; i < argc; ++i)
    {
        p = argv[i];

        /*����-sָ��*/
        if(strcmp(p, "-s") == 0)
            s_state = TRUE;

        /*����-aָ��*/
        if(strcmp(p, "-a") == 0)
            a_state = TRUE;

        /*��ȡ�ı���Ϣֱ������*/
        while(*++p != NULL)
            ;

        /*p�������񣬸���ĩβ��.c���ļ��ж���Ҫͳ�Ƶ��ĵ�·��*/
        if(strcmp(p - 2, ".c") == 0)
        {
            path[j++] = argv[i];
            end  = i;
        }

        /*p����4�񣬸���ĩβ��.txt���ļ��ж����ɵ��ĵ�·��, ͬʱ��׽�ļ�ǰ��-e����-o*/
        if(strcmp(p - 4, ".txt") == 0 && strcmp(argv[i - 1],"-e") == 0 )
        {
            word_list_path = argv[i];
        }

        if(strcmp(p - 4, ".txt") == 0 && argv[i + 1] == '\0')
        {
            /*���û��-o �׳��쳣*/
            if(strcmp(argv[i - 1], "-o") == 0)
                filename = argv[i];
            else
            {
                if(strcmp(argv[i - 1], "-e") != 0)
                {
                    printf("command line error.\n");
                    return EXIT_FAILURE;
                }

            }
        }
    }
    /*��ʼ��*/
    path[j] = '\0';
    /*j > 1 means user input *.c, so change process_type"*/
    if(j >= 1)
    {
		
        if(s_state == TRUE)
            process_type = ALL;
        else
            {
                printf("command111 line error.\n");
                return EXIT_FAILURE;
            }
    }


    if(word_list_path != NULL)
    {
        /*read word_list to buffer*/
        buf = readfile(word_list_path);
        /*process buffer and get a two-dimensional pointer*/
        word_list = processBuf(buf);
    }
    else
    {
        word_list = (char **)malloc(sizeof(char *));
        word_list[0] = '\0';
    }


    /*�������쳣*/
    if(path[0] == NULL)
    {
        printf("command line error.\n");
        return EXIT_FAILURE;
    }


    /*���������У�������ļ����ض���*/
    if (filename != NULL)
            freopen(filename, "w", stdout);


    /*�����ļ�*/
    j = 0;
  
      while(path[j] != '\0')
       {
            buffer = readfile(path[j]);
            info = CWL(buffer, word_list, a_state);
			for (i = 1; i < end; ++i)
			{
				if (strcmp(argv[i], "-c") == 0)
					printf("%s: �ַ���:%d\n", path[j], info->nc);
				if (strcmp(argv[i], "-w") == 0)
					printf("%s: ������:%d\n", path[j], info->nw);
				if (strcmp(argv[i], "-l") == 0)
					printf("%s: ����:%d\n", path[j], info->nl);
			}
            free(info);
            free(buffer);
            ++j;
            printStopList(word_list);
       }
    
	
    return EXIT_SUCCESS;
}
