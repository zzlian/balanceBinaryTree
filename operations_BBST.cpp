#include"operations_BBST.h"

// 右旋调整
void R_Rotate(BBSTree &p){
	BBSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

// 右旋调整
void L_Rotate(BBSTree &p){
	BBSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

// 对最小失衡子树进行左平衡处理
void LeftBalance(BBSTree &T){
	BBSTree lc, rd;
	lc = T->lchild;
	switch(lc->bf){	// 依据失衡类型进行相应的处理
		case LH:    // 失衡类型为LL型，右旋处理
			T->bf = lc->bf = EH; R_Rotate(T); break; // 调节后等高
		case RH:    // 失衡类型为LR型，双旋处理
			rd = lc->rchild;
			switch(rd->bf){	// 依据不同情况对相应结点的平衡因子进相应的调整
				case LH: T->bf = RH; lc->bf = EH; break;
				case EH: T->bf = lc->bf = EH; break;
				case RH: T->bf = EH; lc->bf = LH; break;
			}
			rd->bf = EH;
			L_Rotate(T->lchild); // 左旋调整
			R_Rotate(T);	     // 右旋调整
			break;
	}
}

// 对最小失衡子树进行右平衡处理
void RightBalance(BBSTree &T){
	BBSTree rc, ld;
	rc = T->rchild;
	switch(rc->bf){	// 依据失衡类型进行相应的处理
		case RH:    // 失衡类型为RR，左旋处理
			T->bf = rc->bf = EH; L_Rotate(T); break;
		case LH:    // 失衡类型为RL型，双旋处理
			ld = rc->lchild;
			switch(ld->bf){	// 对相应结点的平衡因子进行调整
				case LH: T->bf = EH; rc->bf = RH; break;
				case EH: T->bf = rc->bf = EH; break;
				case RH: T->bf = LH; rc->bf = EH; break;
			}
			ld->bf = EH;
			R_Rotate(T->rchild); // 右旋调整
			L_Rotate(T);	     // 左旋调整
			break;
	}
}


// 平衡二叉树的插入操作
Status InsertAVL(BBSTree &T, ElemType e, Status &taller){
	if(NULL == T){	// 树为空，树长高
		T = (BBSTree)malloc(sizeof(BBSTNode));
		if(NULL == T){
			printf("申请空间失败！！\n");
			return FALSE;
		}
		T->data = e; T->bf = EH; T->lchild = T->rchild = NULL;
		taller = TRUE;
	}
	else if(e == T->data){	// 结点已存在，插入失败
		printf("结点已存在！！\n");
		return FALSE;
	}
	else if(e < T->data){	// 在左子树进行插入
		if(FALSE == InsertAVL(T->lchild, e, taller)) return FALSE;// 结点已存在
		if(TRUE == taller){ // 插入成功，树长高
			switch(T->bf){	// 平衡因子调整
				case LH: LeftBalance(T); taller = FALSE; break; // 原左高，插入后失衡，进行左失衡处理，高度不变
				case EH: T->bf = LH; taller = TRUE; break;      // 原等高，插入后左高，高度加1
				case RH: T->bf = EH; taller = FALSE; break;     // 原右高，插入后等高，高度不变
			}
		}
	}
	else{	// 在右子树进行插入
		if(FALSE == InsertAVL(T->rchild, e, taller)) return FALSE;// 结点已存在
		if(TRUE == taller){ // 插入成功，树长高
			switch(T->bf){	// 平衡因子调整
				case LH: T->bf = EH; taller = FALSE; break;     // 原左高，插入后等高，高度不变
				case EH: T->bf = RH; taller = TRUE; break;      // 原等高，插入后右高，高度加1
				case RH: RightBalance(T); taller = FALSE; break;// 原右高，插入后失衡，进行右平衡处理，高度不变
			}
		}
	}
	return TRUE;
}


// 创建平衡二叉树
Status MakeAVL(BBSTree &T){
	ElemType e;
	char c;
	BBSTree p;
	Status s, taller = FALSE;
	T = NULL;
	printf("请输入一个整数作为新结点的值，输入-1表示结束：");
	scanf("%d", &e);
	c = getchar();
	if(c != '\n') e = c;
	while(e != -1){ // 开始创建平衡二叉树
		InsertAVL(T, e, taller);
		printf("请输入一个整数作为新结点的值，输入-1表示结束：");
		scanf("%d", &e);
		c = getchar();
        if(c != '\n') e = c;
	}
	return OK;
}


// 在平衡二叉树中查找相应结点
BBSTree SearchAVL(BBSTree T, ElemType e){
	if(NULL == T) return NULL;   // 结点不存在
	if(e == T->data) return T;   // 结点存在
	if(e < T->data) return SearchAVL(T->lchild, e); // 在左子树递归查找
	return SearchAVL(T->rchild, e); // 在右子树递归查找
}


// 在平衡二叉树中进行结点的删除
Status DeleteAVL(BBSTree &T, ElemType e, Status &shorter){
	if(NULL == T){	// 结点不存在，删除失败
		printf("不存在要删除的结点！！\n");
		return ERROR;
	}
	if(e < T->data){ // 在左子树进行删除
		if(ERROR == DeleteAVL(T->lchild, e, shorter)) return ERROR;// 结点不存在
		if(TRUE == shorter){ // 高度有变，平衡因子调整
			if(T->bf == LH) T->bf = EH; // 原左高，删后等高，高度减1
			else if(T->bf == EH){       // 原等高，删后右高，高度不变
				T->bf = RH;
				shorter = FALSE;
			}
			else RightBalance(T);       // 原右高，删后失衡，进行右失衡处理，高度减1
		}
	}
	else if(e > T->data){ // 在右子树进行删除
		if(ERROR == DeleteAVL(T->rchild, e, shorter)) return ERROR;// 结点不存在
		if(TRUE == shorter){	// 高度有变，进行平衡因子调整
			if(T->bf == RH) T->bf = EH; // 原右高，删后等高，高度减1
			else if(T->bf == EH){       // 原等高，删后左高，高度不变
				T->bf = LH;
				shorter = FALSE;
			}
			else LeftBalance(T);        // 原左高，删后失衡，进行左失衡处理，高度减1
		}
	}
	else{
		BBSTree p = T;
		if(NULL == T->rchild){ // 被删结点右子树不存在
			T = T->lchild;     // 以左子树代替被删结点
			free(p);
			shorter = TRUE;    // 高度减1
		}
		else if(NULL == T->lchild){ // 被删结点左子树不存在
			T = T->rchild;          // 以右子树代替被删结点
			free(p);
			shorter = TRUE;	        // 高度减1
		}
		else{	// 被删结点左、右子树均存在
			Delete(T, T->lchild, shorter);// 以左子树上的最大结点代替被删结点
			if(TRUE == shorter){	// 高度有变，平衡因子调整
				if(T->bf == LH) T->bf = EH; // 原左高，删后等高，高度减1
				else if(T->bf == EH){	    // 原等高，删后右高，高度不变
					T->bf = RH;
					shorter = FALSE;
				}
				else RightBalance(T);       // 原右高，删后失衡，右失衡处理，高度减1
			}
		}
	}
	return OK;
}

// 进行结点的删除
void Delete(BBSTree p, BBSTree &r, Status &shorter){
	if(NULL == r->rchild){	 // 满足时r结点为被删结点左子树的最大结点
		p->data = r->data;   // 以所寻结点代替被删结点
		p = r;
		r = r->lchild;
		free(p);
		shorter = TRUE;      // 高度减1
	}
	else{
		Delete(p, r->rchild, shorter);	// 递归寻找
		if(TRUE == shorter){	// 高度有变，平衡因子调整
			if(r->bf == RH) r->bf = EH; // 原右高，删后等高，高度减1
			else if(r->bf == EH){       // 原等高，删后左，高度不变
				r->bf = LH;
				shorter = FALSE;
			}
			else LeftBalance(r);        // 原左高，删后失衡，左平衡处理，高度减1
		}
	}
}


// 合并两棵平衡二叉树，并将合并结果保存在T中
Status MergeAVL(BBSTree &T){
	BBSTree t1, t2;
	Status s;
	printf(".............创建要合并的平衡二叉树............\n");
	s = MakeAVL(t1);    // 创建要合并的第一棵平衡二叉树
	if(OK == s) printf("创建成功.\n");
	else return ERROR;
	printf(".............创建要合并的第二棵平衡二叉树..............\n");
	s = MakeAVL(t2);    // 创建要合并的第二棵平衡二叉树
	if(OK == s) printf("创建成功.\n");
	else return ERROR;

	if(NULL == t1) T = t2;      // t1为空树，则合并结果为t2
	else if(NULL == t2) T = t1; // t2为空树，则合并结果为t1
	else{                       // t1、t2均不为空树，
		Merge(t1, t2);          // 进行合并，将t2合并到t1中
		T = t1;
	}
	printf("...............合并结果...............\n");
	VisitAVL(T, 10);            // 显示合并后的平衡二叉树
	return OK;
}

// 将t2合并到t1中
void Merge(BBSTree &t1, BBSTree t2){
	if(NULL != t2){
		Status taller = FALSE;
		InsertAVL(t1, t2->data, taller);// 将t2中的结点插入到t1中
		Merge(t1, t2->lchild);          // 遍历左子树
		Merge(t1, t2->rchild);          // 遍历右子树
	}
}


// 根据指定结点分裂二叉树
void DivideAVL(BBSTree T, ElemType e, BBSTree &t1, BBSTree &t2){
    Status taller = FALSE;
    if(NULL == T) return;
	if(e >= T->data)  InsertAVL(t1, T->data, taller);     // 将结点插入t1中
	else if(e < T->data)  InsertAVL(t2, T->data, taller); // 将结点插入t2中
	DivideAVL(T->lchild, e, t1, t2);    // 在左子树上递归分裂
	DivideAVL(T->rchild, e, t1, t2);    // 在右子树上递归分裂
}


// 凹入表形式打印平衡二叉树
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
