#ifndef WC_H_
#define WC_H_

typedef struct BasicInfo
{
    int nc;			//�ַ���
    int nw;			//������
    int nl;			//����
    int codeline;	//������
    int spaceline;	//����
    int commentline;//ע����
}BasicInfo;

BasicInfo *CWL(char *buf, char **word_list, int a_state);
void printStopList(char **word_list);

#endif // WC_H_
