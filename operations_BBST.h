#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define LH +1   // ���
#define EH 0    // �ȸ�
#define RH -1   // �Ҹ�

typedef int Status;   // ״̬����
typedef int ElemType; // ���Ԫ������

typedef struct BBSTNode // �������
{
	ElemType data;
	struct BBSTNode *lchild, *rchild;
	int bf;
}BBSTNode, *BBSTree;

void R_Rotate(BBSTree &p);     // ������������
void L_Rotate(BBSTree &p);     // ������������
void LeftBalance(BBSTree &T);  // ������ƽ�⴦��
void RightBalance(BBSTree &T); // ������ƽ�⴦��
Status InsertAVL(BBSTree &T, ElemType e, Status &taller); // �������뵽ƽ���������
Status MakeAVL(BBSTree &T);    // ����ƽ�������
BBSTree SearchAVL(BBSTree T, ElemType e); // ��ƽ��������в��ҽ��
Status DeleteAVL(BBSTree &T, ElemType e, Status &shorter);// ��ƽ���������ɾ�����
void Delete(BBSTree p, BBSTree &r, Status &shorter);      // ���ɾ������
void VisitAVL(BBSTree T, int t);// ������ӡ������
Status MergeAVL(BBSTree &T);    // �ϲ�ƽ�������
void Merge(BBSTree &t1, BBSTree t2);    // ���кϲ�����
void DivideAVL(BBSTree T, ElemType e, BBSTree &t1, BBSTree &t2);// ����ƽ�������
