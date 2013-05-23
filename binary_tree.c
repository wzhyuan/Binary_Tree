#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#define NUMBER 10
/*定义二叉树节点结构体，包括序号，节点值，左右孩子指针*/
typedef struct{
		int seq;
		double dvalue;
		struct BINARY_NODE * right;
		struct BINARY_NODE * left;
}BINARY_NODE;
/*定义按照序号大小排序的结构体*/
typedef struct{
		int seq;
		double dvalue;
}BINARY_ORDER_NODE;

int g_Order = 1;
double RandomList[NUMBER] = { 0 };
BINARY_ORDER_NODE BinaryList[NUMBER] = { 0 };

/*对二叉树进行插入节点操作，并按照插入位置记录相应序号到节点中*/
int insert_node(BINARY_NODE *present,double insert_value ,int PesentSeq)
{
	/*如果待插入的数据比当前节点大，则放在右孩子中*/
	if( insert_value > present->dvalue )
	{
		/*如果右孩子中没有数据，则插入，计算序号，并返回*/
		if( present->right == NULL )
		{
			BINARY_NODE * P_TEMP = NULL ;
			P_TEMP = (BINARY_NODE*) malloc(sizeof( BINARY_NODE));
			P_TEMP->dvalue = insert_value;
			P_TEMP->right = NULL;
			P_TEMP->left  = NULL;
			P_TEMP->seq  = PesentSeq*2+1;
			present->right = P_TEMP;
			/*将已插入节点的值和序号放在数组中，为后面按照序号排序做准备*/
			BinaryList[g_Order].seq = P_TEMP->seq;
			BinaryList[g_Order].dvalue = insert_value;
			g_Order++;
			
			return 0;
		}
		/*如果右孩子中有数据，则以右孩子为根结点，递归调用本身，寻找插入位置*/
		else if( present->right != NULL )
		{
			PesentSeq = PesentSeq*2+1;
			insert_node(  present->right,insert_value,PesentSeq);
		}
	}
	/*如果待插入的数据比当前节点小，则放在左孩子中*/
	else if( insert_value < present->dvalue )
	{
		/*如果左孩子中没有数据，则插入，计算序号，并返回*/
		if( present->left == NULL )
		{
			BINARY_NODE *P_TEMP = NULL ;
			P_TEMP = (BINARY_NODE*) malloc(sizeof( BINARY_NODE));
			P_TEMP->dvalue = insert_value;
			P_TEMP->right = NULL;
			P_TEMP->left  = NULL;
			P_TEMP->seq  = PesentSeq*2;
			present->left = P_TEMP;
			
			BinaryList[g_Order].seq = P_TEMP->seq;
			BinaryList[g_Order].dvalue = insert_value;
			g_Order++;
			return 0;
		}
		/*如果左孩子中有数据，则以左孩子为根结点，递归调用本身，寻找插入位置*/
		else if( present->left != NULL )
		{
			PesentSeq = PesentSeq*2;
			insert_node(  present->left,insert_value,PesentSeq);
		}
	}
}



int main()
{
	int iLoop   =  0;
	int jLoop   =  0;
	int iseq    =  1;
	double dmin =  0;
	BINARY_NODE *P_HEAD = NULL ;
	/* set the seed */
	srand ((unsigned)time(NULL));
	srand(100);
	for (iLoop = 0;iLoop < NUMBER;iLoop++)
	{			
			RandomList[iLoop]=20.0*rand()/RAND_MAX;
			printf("%d    %lf \n",iLoop,RandomList[iLoop]);		
	}
	
    /*申请内存存放根结点*/
	P_HEAD = (BINARY_NODE*) malloc(sizeof(BINARY_NODE));
	P_HEAD->dvalue = RandomList[0];
	P_HEAD->right = NULL;
	P_HEAD->left  = NULL;
	P_HEAD->seq = 1;
    BinaryList[0].dvalue = RandomList[0];
	BinaryList[0].seq = 1;
	
	/*从第二个开始，依次插入生成的随机数到二叉树中*/
	for(iLoop = 1;iLoop < NUMBER;iLoop++)
	{
		 insert_node( P_HEAD ,RandomList[iLoop],1 );
	}
	
	
	/*采用冒泡法按序号大小进行排序，为最终输出做准备*/
	for(jLoop = 0;jLoop<NUMBER-1;jLoop++)
	{
		
		for(iLoop = 0;iLoop < NUMBER-1;iLoop++)
		{
			
			if( BinaryList[iLoop].seq > BinaryList[iLoop+1].seq )
			{
				iseq = BinaryList[iLoop+1].seq;
				dmin  = BinaryList[iLoop+1].dvalue;
				BinaryList[iLoop+1].seq    = BinaryList[iLoop].seq;
				BinaryList[iLoop+1].dvalue = BinaryList[iLoop].dvalue;
				BinaryList[iLoop].seq    = iseq;
				BinaryList[iLoop].dvalue = dmin;
			}
			
		}
	}
	/*排序后按序号大小依次输出*/
   	for(iLoop = 0;iLoop < NUMBER;iLoop++)
	{
		if(BinaryList[iLoop].seq  != 0)
		printf("%d  %lf\n",BinaryList[iLoop].seq,BinaryList[iLoop].dvalue);
	}
	
	
	return 0;

}