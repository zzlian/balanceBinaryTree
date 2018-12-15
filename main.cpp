#include"operations_BBST.h"
#include<stdlib.h>

int main(){
	int c;
	char c0;
	BBSTree T = NULL;
	BBSTree p, t1, t2;
	ElemType e;
	Status s, taller=FALSE, shorter=FALSE;
	printf("==================================================================================\n");
	printf("输入1创建、2插入、3查找、4删除结点、5合并、6分裂、7打印平衡二叉树.\t-1结束操作.\n");
	printf("==================================================================================\n");
	printf("请输入你的选择：");
    scanf("%d", &c);
    c0 = getchar();
    if(c0 != '\n') printf("请不要随便输入，谢谢.\n");
	while(c != -1){
		switch(c){
			case 1:
				MakeAVL(T);
				if(s == OVERFLOW) printf("申请空间失败！！\n");
				else printf("创建平衡二叉树成功.\n");
				break;
			case 2:
				printf("请输入插入结点的值：");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				s = InsertAVL(T, e, taller);
				if(OK == s) printf("成功插入.\n");
				VisitAVL(T, 10);
				break;
			case 3:
				printf("请输入要查找结点额值：");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				p = SearchAVL(T, e);
				if(NULL == p) printf("结点不存在，查找失败!!\n");
				else printf("结点存在，查找成功.\n");
				break;
			case 4:
				printf("请输入要删除结点的值：");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				s = DeleteAVL(T, e, shorter);
				if(OK == s) printf("删除结点成功.\n");
				else printf("结点不存在，删除失败!!\n");
				VisitAVL(T, 10);
				break;
			case 5:
				s = MergeAVL(T);
				if(ERROR == s) printf("合并失败！！\n");
				break;
			case 6:
			    t1 = t2 = NULL;
				printf("请输入要分裂的结点的值：");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				DivideAVL(T, e, t1, t2);
                printf("............分裂后的子树t1............\n");
                if(NULL == t1) printf("                  空树\n\n");
                else VisitAVL(t1, 10);   // 打印分裂后的左子树
                printf("............分裂后的子树t2............\n");
                if(NULL == t2) printf("                  空树\n");
                else VisitAVL(t2, 10);
				break;
			case 7:
				VisitAVL(T, 10);
				break;
			default:
				printf("选项不存在，请重新输入!!\n\n");
		}
		printf("==================================================================================\n");
		printf("输入1创建、2插入、3查找、4删除结点、5合并、6分裂、7打印平衡二叉树.\t-1结束操作.\n");
		printf("==================================================================================\n");
		printf("请输入你的选择：");
		scanf("%d", &c);
		c0 = getchar();
		if(c0 != '\n') c = c0;
	}
	return 0;
}
