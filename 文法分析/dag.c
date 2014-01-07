#include"dag.h"

int dag_n,dag_sn;
bdag dag_list[100];
char dag_stack[100][10];
int dag_stack_n[100];

int find_opretor(int op,int left,int right)
{
	int i;
	for(i=0;i<=dag_n;i++){
		if((op==dag_list[i].op)&&(left==dag_list[i].left)&&(right==dag_list[i].right))
			return i;
	}
	return -1;
}

int find_string(char s[])
{
	int i;
	for(i=0;i<=dag_sn;i++){
		if(strcmp(s,dag_stack[i])==0)
			return i;
	}
	return -1;
}