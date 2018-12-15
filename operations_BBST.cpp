#include"operations_BBST.h"

// ��������
void R_Rotate(BBSTree &p){
	BBSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

// ��������
void L_Rotate(BBSTree &p){
	BBSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

// ����Сʧ������������ƽ�⴦��
void LeftBalance(BBSTree &T){
	BBSTree lc, rd;
	lc = T->lchild;
	switch(lc->bf){	// ����ʧ�����ͽ�����Ӧ�Ĵ���
		case LH:    // ʧ������ΪLL�ͣ���������
			T->bf = lc->bf = EH; R_Rotate(T); break; // ���ں�ȸ�
		case RH:    // ʧ������ΪLR�ͣ�˫������
			rd = lc->rchild;
			switch(rd->bf){	// ���ݲ�ͬ�������Ӧ����ƽ�����ӽ���Ӧ�ĵ���
				case LH: T->bf = RH; lc->bf = EH; break;
				case EH: T->bf = lc->bf = EH; break;
				case RH: T->bf = EH; lc->bf = LH; break;
			}
			rd->bf = EH;
			L_Rotate(T->lchild); // ��������
			R_Rotate(T);	     // ��������
			break;
	}
}

// ����Сʧ������������ƽ�⴦��
void RightBalance(BBSTree &T){
	BBSTree rc, ld;
	rc = T->rchild;
	switch(rc->bf){	// ����ʧ�����ͽ�����Ӧ�Ĵ���
		case RH:    // ʧ������ΪRR����������
			T->bf = rc->bf = EH; L_Rotate(T); break;
		case LH:    // ʧ������ΪRL�ͣ�˫������
			ld = rc->lchild;
			switch(ld->bf){	// ����Ӧ����ƽ�����ӽ��е���
				case LH: T->bf = EH; rc->bf = RH; break;
				case EH: T->bf = rc->bf = EH; break;
				case RH: T->bf = LH; rc->bf = EH; break;
			}
			ld->bf = EH;
			R_Rotate(T->rchild); // ��������
			L_Rotate(T);	     // ��������
			break;
	}
}


// ƽ��������Ĳ������
Status InsertAVL(BBSTree &T, ElemType e, Status &taller){
	if(NULL == T){	// ��Ϊ�գ�������
		T = (BBSTree)malloc(sizeof(BBSTNode));
		if(NULL == T){
			printf("����ռ�ʧ�ܣ���\n");
			return FALSE;
		}
		T->data = e; T->bf = EH; T->lchild = T->rchild = NULL;
		taller = TRUE;
	}
	else if(e == T->data){	// ����Ѵ��ڣ�����ʧ��
		printf("����Ѵ��ڣ���\n");
		return FALSE;
	}
	else if(e < T->data){	// �����������в���
		if(FALSE == InsertAVL(T->lchild, e, taller)) return FALSE;// ����Ѵ���
		if(TRUE == taller){ // ����ɹ���������
			switch(T->bf){	// ƽ�����ӵ���
				case LH: LeftBalance(T); taller = FALSE; break; // ԭ��ߣ������ʧ�⣬������ʧ�⴦���߶Ȳ���
				case EH: T->bf = LH; taller = TRUE; break;      // ԭ�ȸߣ��������ߣ��߶ȼ�1
				case RH: T->bf = EH; taller = FALSE; break;     // ԭ�Ҹߣ������ȸߣ��߶Ȳ���
			}
		}
	}
	else{	// �����������в���
		if(FALSE == InsertAVL(T->rchild, e, taller)) return FALSE;// ����Ѵ���
		if(TRUE == taller){ // ����ɹ���������
			switch(T->bf){	// ƽ�����ӵ���
				case LH: T->bf = EH; taller = FALSE; break;     // ԭ��ߣ������ȸߣ��߶Ȳ���
				case EH: T->bf = RH; taller = TRUE; break;      // ԭ�ȸߣ�������Ҹߣ��߶ȼ�1
				case RH: RightBalance(T); taller = FALSE; break;// ԭ�Ҹߣ������ʧ�⣬������ƽ�⴦���߶Ȳ���
			}
		}
	}
	return TRUE;
}


// ����ƽ�������
Status MakeAVL(BBSTree &T){
	ElemType e;
	char c;
	BBSTree p;
	Status s, taller = FALSE;
	T = NULL;
	printf("������һ��������Ϊ�½���ֵ������-1��ʾ������");
	scanf("%d", &e);
	c = getchar();
	if(c != '\n') e = c;
	while(e != -1){ // ��ʼ����ƽ�������
		InsertAVL(T, e, taller);
		printf("������һ��������Ϊ�½���ֵ������-1��ʾ������");
		scanf("%d", &e);
		c = getchar();
        if(c != '\n') e = c;
	}
	return OK;
}


// ��ƽ��������в�����Ӧ���
BBSTree SearchAVL(BBSTree T, ElemType e){
	if(NULL == T) return NULL;   // ��㲻����
	if(e == T->data) return T;   // ������
	if(e < T->data) return SearchAVL(T->lchild, e); // ���������ݹ����
	return SearchAVL(T->rchild, e); // ���������ݹ����
}


// ��ƽ��������н��н���ɾ��
Status DeleteAVL(BBSTree &T, ElemType e, Status &shorter){
	if(NULL == T){	// ��㲻���ڣ�ɾ��ʧ��
		printf("������Ҫɾ���Ľ�㣡��\n");
		return ERROR;
	}
	if(e < T->data){ // ������������ɾ��
		if(ERROR == DeleteAVL(T->lchild, e, shorter)) return ERROR;// ��㲻����
		if(TRUE == shorter){ // �߶��б䣬ƽ�����ӵ���
			if(T->bf == LH) T->bf = EH; // ԭ��ߣ�ɾ��ȸߣ��߶ȼ�1
			else if(T->bf == EH){       // ԭ�ȸߣ�ɾ���Ҹߣ��߶Ȳ���
				T->bf = RH;
				shorter = FALSE;
			}
			else RightBalance(T);       // ԭ�Ҹߣ�ɾ��ʧ�⣬������ʧ�⴦���߶ȼ�1
		}
	}
	else if(e > T->data){ // ������������ɾ��
		if(ERROR == DeleteAVL(T->rchild, e, shorter)) return ERROR;// ��㲻����
		if(TRUE == shorter){	// �߶��б䣬����ƽ�����ӵ���
			if(T->bf == RH) T->bf = EH; // ԭ�Ҹߣ�ɾ��ȸߣ��߶ȼ�1
			else if(T->bf == EH){       // ԭ�ȸߣ�ɾ����ߣ��߶Ȳ���
				T->bf = LH;
				shorter = FALSE;
			}
			else LeftBalance(T);        // ԭ��ߣ�ɾ��ʧ�⣬������ʧ�⴦���߶ȼ�1
		}
	}
	else{
		BBSTree p = T;
		if(NULL == T->rchild){ // ��ɾ���������������
			T = T->lchild;     // �����������汻ɾ���
			free(p);
			shorter = TRUE;    // �߶ȼ�1
		}
		else if(NULL == T->lchild){ // ��ɾ���������������
			T = T->rchild;          // �����������汻ɾ���
			free(p);
			shorter = TRUE;	        // �߶ȼ�1
		}
		else{	// ��ɾ�����������������
			Delete(T, T->lchild, shorter);// ���������ϵ��������汻ɾ���
			if(TRUE == shorter){	// �߶��б䣬ƽ�����ӵ���
				if(T->bf == LH) T->bf = EH; // ԭ��ߣ�ɾ��ȸߣ��߶ȼ�1
				else if(T->bf == EH){	    // ԭ�ȸߣ�ɾ���Ҹߣ��߶Ȳ���
					T->bf = RH;
					shorter = FALSE;
				}
				else RightBalance(T);       // ԭ�Ҹߣ�ɾ��ʧ�⣬��ʧ�⴦���߶ȼ�1
			}
		}
	}
	return OK;
}

// ���н���ɾ��
void Delete(BBSTree p, BBSTree &r, Status &shorter){
	if(NULL == r->rchild){	 // ����ʱr���Ϊ��ɾ����������������
		p->data = r->data;   // ����Ѱ�����汻ɾ���
		p = r;
		r = r->lchild;
		free(p);
		shorter = TRUE;      // �߶ȼ�1
	}
	else{
		Delete(p, r->rchild, shorter);	// �ݹ�Ѱ��
		if(TRUE == shorter){	// �߶��б䣬ƽ�����ӵ���
			if(r->bf == RH) r->bf = EH; // ԭ�Ҹߣ�ɾ��ȸߣ��߶ȼ�1
			else if(r->bf == EH){       // ԭ�ȸߣ�ɾ���󣬸߶Ȳ���
				r->bf = LH;
				shorter = FALSE;
			}
			else LeftBalance(r);        // ԭ��ߣ�ɾ��ʧ�⣬��ƽ�⴦���߶ȼ�1
		}
	}
}


// �ϲ�����ƽ��������������ϲ����������T��
Status MergeAVL(BBSTree &T){
	BBSTree t1, t2;
	Status s;
	printf(".............����Ҫ�ϲ���ƽ�������............\n");
	s = MakeAVL(t1);    // ����Ҫ�ϲ��ĵ�һ��ƽ�������
	if(OK == s) printf("�����ɹ�.\n");
	else return ERROR;
	printf(".............����Ҫ�ϲ��ĵڶ���ƽ�������..............\n");
	s = MakeAVL(t2);    // ����Ҫ�ϲ��ĵڶ���ƽ�������
	if(OK == s) printf("�����ɹ�.\n");
	else return ERROR;

	if(NULL == t1) T = t2;      // t1Ϊ��������ϲ����Ϊt2
	else if(NULL == t2) T = t1; // t2Ϊ��������ϲ����Ϊt1
	else{                       // t1��t2����Ϊ������
		Merge(t1, t2);          // ���кϲ�����t2�ϲ���t1��
		T = t1;
	}
	printf("...............�ϲ����...............\n");
	VisitAVL(T, 10);            // ��ʾ�ϲ����ƽ�������
	return OK;
}

// ��t2�ϲ���t1��
void Merge(BBSTree &t1, BBSTree t2){
	if(NULL != t2){
		Status taller = FALSE;
		InsertAVL(t1, t2->data, taller);// ��t2�еĽ����뵽t1��
		Merge(t1, t2->lchild);          // ����������
		Merge(t1, t2->rchild);          // ����������
	}
}


// ����ָ�������Ѷ�����
void DivideAVL(BBSTree T, ElemType e, BBSTree &t1, BBSTree &t2){
    Status taller = FALSE;
    if(NULL == T) return;
	if(e >= T->data)  InsertAVL(t1, T->data, taller);     // ��������t1��
	else if(e < T->data)  InsertAVL(t2, T->data, taller); // ��������t2��
	DivideAVL(T->lchild, e, t1, t2);    // ���������ϵݹ����
	DivideAVL(T->rchild, e, t1, t2);    // ���������ϵݹ����
}


// �������ʽ��ӡƽ�������
void VisitAVL(BBSTree T, int t){
	int i;
	if(NULL != T){
		VisitAVL(T->rchild, t+5);
		for(i=0; i<t; i++){
			printf(" ");
		}
		printf("%d(%d)\n", T->data, T->bf);
		VisitAVL(T->lchild, t+5);
	}
}
