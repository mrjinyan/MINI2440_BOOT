//N��Ա����
#include <stdio.h>
#include <malloc.h>
typedef unsigned int uint; 
typedef struct salary{
	uint sal;
	uint fre; 
	struct salary* next;
}Node; 
/*
�Ƚϲ��� 
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
		//��������
		//printf("there are 1\n"); 
		cur = &head;	
		//�ҵ����ϵĵط� 
		//printf("%d\n",cur->sal); 
		//printf("%p\n",cur->next); 
		//printf("%d",((cur->next)!=NULL));
		while(((cur->sal)!=(sala[i]))&&((cur->next)!=NULL)){
			cur = cur->next;
			//printf("there are 3\n"); 
		}
			//printf("there are 2\n"); 
		//�����ȣ�˵���ҵ��� ,����Ƶ�� 
		if(cur->sal == sala[i]){
			cur->fre++; 
		} 
		//�������ȣ��϶����ҵ�����ˣ����ӽڵ� 
		else{
			cur->next = malloc(sizeof(Node));
			cur->next->fre = 1;
			cur->next->next = NULL;
			cur->next->sal = sala[i]; 
			node_cnt++; //ÿ����һ���ڵ�������һ������ 
		}
		i++; 
	}//while i<num 
	printf("there are %d nodes\n",node_cnt);
	//���Ա�������ÿ�ҵ�һ�����ľͼ�¼�ڲᣬ���ң�ɾ�����ýڵ㣬ͬʱ���ܹ���֤���ֵ�˳��
	uint (*S)[2] = (uint(*)[2])malloc(sizeof(uint)*node_cnt*2);//���ݼ�¼�Ľڵ�����������Ӧ��С����
	cur  = head.next;
	Node* pro = &head;
	Node* max_pro = pro;//���ֵ��ǰ��ָ�� 
	Node* max_cur = cur;//���ֵ�ڵ㣻 
	uint  max_value = cur->fre;
	uint record_cnt = 0;
	while(record_cnt<node_cnt){//ֱ��ɾ�������нڵ� 
	
		while(cur!=NULL){//����������β��ʹ��cur��cur->next���бȽ��ǲ�ͬ�ģ�������Ҫ�ڳ������ٽ����ж� 
		if(cur->fre>max_value){//�����ǰ��Ƶ��ֵ�������ֵ����Ҫ��¼������Ϣ 
			max_pro = pro;
			max_cur = cur;
			max_value = cur->fre;
		}
		pro = cur;
		cur = cur->next; 
		}
	//�Լ�¼�Ľڵ����һ���Ĳ������ֳ��������,���������Ա�����ͳһ 
	max_pro->next = max_cur->next;//��������
	S[record_cnt][0] = max_cur->fre;
	S[record_cnt][1] = max_cur->sal;
		//printf("the fre is%d\n",max_cur->sal);
		free(max_cur);//�ͷ���Ӧ�ڵ� 
		//���±�����Ҫ����Щ�������³�ʼ�� 
		
		pro = &head;
		max_pro = pro;
		cur = pro->next;
		//printf("the 1\n");
		max_cur=cur;
		//printf("the 2\n");
		if(max_cur!=NULL) 
		max_value = max_cur->fre;//�����ʱmax_curΪNULL������ͻᷢ������ 
		//printf("the 3\n");
		//printf("record cnt is%d\n",record_cnt);
		record_cnt++; 
	}//while������������ҳ����ֵ
	uint* result = malloc(sizeof(uint)*num); 
	i = 0;
	uint j=0;//ԭ�ȷŵ�λ�ô����ˡ� 
	for(;record_cnt>0;record_cnt--){
		
		while(S[i][0]--){
			result[j] = S[i][1];
			j++;
		}
		i++; 
	}
	return result; 
}//sort���� 
