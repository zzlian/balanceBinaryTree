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
	printf("����1������2���롢3���ҡ�4ɾ����㡢5�ϲ���6���ѡ�7��ӡƽ�������.\t-1��������.\n");
	printf("==================================================================================\n");
	printf("���������ѡ��");
    scanf("%d", &c);
    c0 = getchar();
    if(c0 != '\n') printf("�벻Ҫ������룬лл.\n");
	while(c != -1){
		switch(c){
			case 1:
				MakeAVL(T);
				if(s == OVERFLOW) printf("����ռ�ʧ�ܣ���\n");
				else printf("����ƽ��������ɹ�.\n");
				break;
			case 2:
				printf("������������ֵ��");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				s = InsertAVL(T, e, taller);
				if(OK == s) printf("�ɹ�����.\n");
				VisitAVL(T, 10);
				break;
			case 3:
				printf("������Ҫ���ҽ���ֵ��");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				p = SearchAVL(T, e);
				if(NULL == p) printf("��㲻���ڣ�����ʧ��!!\n");
				else printf("�����ڣ����ҳɹ�.\n");
				break;
			case 4:
				printf("������Ҫɾ������ֵ��");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				s = DeleteAVL(T, e, shorter);
				if(OK == s) printf("ɾ�����ɹ�.\n");
				else printf("��㲻���ڣ�ɾ��ʧ��!!\n");
				VisitAVL(T, 10);
				break;
			case 5:
				s = MergeAVL(T);
				if(ERROR == s) printf("�ϲ�ʧ�ܣ���\n");
				break;
			case 6:
			    t1 = t2 = NULL;
				printf("������Ҫ���ѵĽ���ֵ��");
				scanf("%d", &e);
				c0 = getchar();
                if(c0 != '\n') e = c0;
				DivideAVL(T, e, t1, t2);
                printf("............���Ѻ������t1............\n");
                if(NULL == t1) printf("                  ����\n\n");
                else VisitAVL(t1, 10);   // ��ӡ���Ѻ��������
                printf("............���Ѻ������t2............\n");
                if(NULL == t2) printf("                  ����\n");
                else VisitAVL(t2, 10);
				break;
			case 7:
				VisitAVL(T, 10);
				break;
			default:
				printf("ѡ����ڣ�����������!!\n\n");
		}
		printf("==================================================================================\n");
		printf("����1������2���롢3���ҡ�4ɾ����㡢5�ϲ���6���ѡ�7��ӡƽ�������.\t-1��������.\n");
		printf("==================================================================================\n");
		printf("���������ѡ��");
		scanf("%d", &c);
		c0 = getchar();
		if(c0 != '\n') c = c0;
	}
	return 0;
}
