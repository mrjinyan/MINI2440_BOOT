//N名员工，
#include <stdio.h>
#include <malloc.h>
typedef unsigned int uint; 
typedef struct salary{
	uint sal;
	uint fre; 
	struct salary* next;
}Node; 
/*
比较插入 
*/
uint* sort(uint num,uint* sala);
int main(void){
	uint* p;
	uint i=0;
	uint s[6] = {10,20,20,30,30,30};
	p = sort(6,s);
	while(i<6){
		printf("%d\n",p[i]); i++;
	} 
	return 0;
}
uint* sort(uint num,uint* sala){
	uint i=0;
	Node head;
	uint node_cnt;
	Node* cur;
	head.next = NULL;
	node_cnt = 0;
	
	while(i<num){
		//遍历链表
		//printf("there are 1\n"); 
		cur = &head;	
		//找到符合的地方 
		//printf("%d\n",cur->sal); 
		//printf("%p\n",cur->next); 
		//printf("%d",((cur->next)!=NULL));
		while(((cur->sal)!=(sala[i]))&&((cur->next)!=NULL)){
			cur = cur->next;
			//printf("there are 3\n"); 
		}
			//printf("there are 2\n"); 
		//如果相等，说明找到了 ,增加频次 
		if(cur->sal == sala[i]){
			cur->fre++; 
		} 
		//如果不相等，肯定是找到最后了，增加节点 
		else{
			cur->next = malloc(sizeof(Node));
			cur->next->fre = 1;
			cur->next->next = NULL;
			cur->next->sal = sala[i]; 
			node_cnt++; //每创建一个节点则增加一个记数 
		}
		i++; 
	}//while i<num 
	printf("there are %d nodes\n",node_cnt);
	//可以遍历链表，每找到一个最大的就记录在册，并且，删除掉该节点，同时还能够保证出现的顺序
	uint (*S)[2] = (uint(*)[2])malloc(sizeof(uint)*node_cnt*2);//根据记录的节点数量申请相应大小数组
	cur  = head.next;
	Node* pro = &head;
	Node* max_pro = pro;//最大值的前驱指针 
	Node* max_cur = cur;//最大值节点； 
	uint  max_value = cur->fre;
	uint record_cnt = 0;
	while(record_cnt<node_cnt){//直到删除完所有节点 
	
		while(cur!=NULL){//遍历到链表尾，使用cur和cur->next进行比较是不同的，后者需要在出来后再进行判断 
		if(cur->fre>max_value){//如果当前的频率值大于最大值，需要记录最大的信息 
			max_pro = pro;
			max_cur = cur;
			max_value = cur->fre;
		}
		pro = cur;
		cur = cur->next; 
		}
	//对记录的节点进行一定的操作，分成若干情况,不过都可以被下面统一 
	max_pro->next = max_cur->next;//建立连接
	S[record_cnt][0] = max_cur->fre;
	S[record_cnt][1] = max_cur->sal;
		//printf("the fre is%d\n",max_cur->sal);
		free(max_cur);//释放相应节点 
		//重新遍历需要将这些变量重新初始化 
		
		pro = &head;
		max_pro = pro;
		cur = pro->next;
		//printf("the 1\n");
		max_cur=cur;
		//printf("the 2\n");
		if(max_cur!=NULL) 
		max_value = max_cur->fre;//如果此时max_cur为NULL，这里就会发生错误。 
		//printf("the 3\n");
		//printf("record cnt is%d\n",record_cnt);
		record_cnt++; 
	}//while遍历多次链表找出最大值
	uint* result = malloc(sizeof(uint)*num); 
	i = 0;
	uint j=0;//原先放的位置错误了。 
	for(;record_cnt>0;record_cnt--){
		
		while(S[i][0]--){
			result[j] = S[i][1];
			j++;
		}
		i++; 
	}
	return result; 
}//sort函数 
