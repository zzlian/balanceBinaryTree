#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define LH +1   // 左高
#define EH 0    // 等高
#define RH -1   // 右高

typedef int Status;   // 状态类型
typedef int ElemType; // 结点元素类型

typedef struct BBSTNode // 结点类型
{
	ElemType data;
	struct BBSTNode *lchild, *rchild;
	int bf;
}BBSTNode, *BBSTree;

void R_Rotate(BBSTree &p);     // 进行右旋调整
void L_Rotate(BBSTree &p);     // 进行左旋调整
void LeftBalance(BBSTree &T);  // 进行左平衡处理
void RightBalance(BBSTree &T); // 进行右平衡处理
Status InsertAVL(BBSTree &T, ElemType e, Status &taller); // 将结点插入到平衡二叉树中
Status MakeAVL(BBSTree &T);    // 创建平衡二叉树
BBSTree SearchAVL(BBSTree T, ElemType e); // 在平衡二叉树中查找结点
Status DeleteAVL(BBSTree &T, ElemType e, Status &shorter);// 在平衡二叉树中删除结点
void Delete(BBSTree p, BBSTree &r, Status &shorter);      // 结点删除操作
void VisitAVL(BBSTree T, int t);// 凹入表打印二叉树
Status MergeAVL(BBSTree &T);    // 合并平衡二叉树
void Merge(BBSTree &t1, BBSTree t2);    // 进行合并操作
void DivideAVL(BBSTree T, ElemType e, BBSTree &t1, BBSTree &t2);// 分裂平衡二叉树
