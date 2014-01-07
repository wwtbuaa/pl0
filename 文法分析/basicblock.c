#include"basicblock.h"

pbasicblock bblock[1000];
int middle[2000];
int ifentry[2000];

int jump(char s[])
{
	if(strcmp(s,"j")==0)
		return 1;
	if(strcmp(s,"bne")==0)
		return 1;
	if(strcmp(s,"beq")==0)
		return 1;
	if(strcmp(s,"bgez")==0)
		return 1;
	if(strcmp(s,"bgtz")==0)
		return 1;
	return 0;
}

int basicblock()
{
	int i,n,block_now=0;
	asyntax_code s;
	n=return_code_num();
	printf("%d\n",n);
	for(i=0;i<n;i++){
		s=return_code(i);
		if(jump(s.op)==0){
			middle[i]=block_now;
			block_now++;
			ifentry[i+1]=1;
		}
		else if(strcmp(s.op,"label")==0){
			middle[i]=++block_now;
			ifentry[i]=1;
		}
		else{
			middle[i]=block_now;
		}
	}
}