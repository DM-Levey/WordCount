#ifndef WC_H_
#define WC_H_

typedef struct BasicInfo
{
    int nc;			//字符数
    int nw;			//单词数
    int nl;			//行数
    int codeline;	//代码行
    int spaceline;	//空行
    int commentline;//注释行
}BasicInfo;

BasicInfo *CWL(char *buf, char **word_list, int a_state);
void printStopList(char **word_list);

#endif // WC_H_
