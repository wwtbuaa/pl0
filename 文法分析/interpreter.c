#include"interpreter.h"

char call_pro[100];
char call_procedure[10][100];
int call_num=0;
int str_num=0;
char print_str[100][100];

int interpreter()
{
	int i=0,n,temp=0,offset=0,j=0;
	ssymbol_table t;
	asyntax_code in;
	FILE *out=fopen("output.asm","w");
	printf("main:\n");
	fprintf(out,"main:\n");
	strcpy(call_pro,"main");
	n=return_num()*4;
	printf("addi $gp $sp 0\n");
	fprintf(out,"addi $gp $sp 0\n");
	printf("addi $sp $sp -%d\n",n);
	fprintf(out,"addi $sp $sp -%d\n",n);
	printf("addi $fp $sp 0\n");
	fprintf(out,"addi $fp $sp 0\n");
	add_offset();
	t=find("main");
	printf("addi $sp $sp -%d\n",t->offset_total);
	fprintf(out,"addi $sp $sp -%d\n",t->offset_total);
	in=return_code(j);
	while(strcmp(in.op,"end")!=0){
		j++;
		if(strcmp(in.op,"j")==0)
			inter_j(in,out);
		else if(strcmp(in.op,"label")==0)
			inter_label(in,out);
		else if(strcmp(in.op,"get")==0)
			inter_get(in,out);
		else if(strcmp(in.op,"getvar")==0)
			inter_gervar(in,out);
		else if(strcmp(in.op,"push")==0)
			inter_push(in,out);
		else if(strcmp(in.op,"pushvar")==0)
			inter_pushvar(in,out);
		else if(strcmp(in.op,"write")==0)
			inter_write(in,out);
		else if(strcmp(in.op,"add")==0)
			inter_add(in,out);
		else if(strcmp(in.op,"addi")==0)
			inter_addi(in,out);
		else if(strcmp(in.op,"muli")==0)
			inter_muli(in,out);
		else if(strcmp(in.op,"mul")==0)
			inter_mul(in,out);
		else if(strcmp(in.op,"div")==0)
			inter_div(in,out);
		else if(strcmp(in.op,"lw")==0)
			inter_lw(in,out);
		else if(strcmp(in.op,"sw")==0)
			inter_sw(in,out);
		else if(strcmp(in.op,"writestr")==0)
			inter_writestr(in,out);
		else if(strcmp(in.op,"read")==0)
			inter_read(in,out);
		else if(strcmp(in.op,"sub")==0)
			inter_sub(in,out);
		else if(strcmp(in.op,"bgez")==0)
			inter_bgez(in,out);
		else if(strcmp(in.op,"bgtz")==0)
			inter_bgtz(in,out);
		else if(strcmp(in.op,"bne")==0)
			inter_bne(in,out);
		else if(strcmp(in.op,"beq")==0)
			inter_beq(in,out);
		else if(strcmp(in.op,"enter")==0){
			strcpy(call_procedure[call_num++],call_pro);
			strcpy(call_pro,in.dest);
		}
		else if(strcmp(in.op,"jal")==0){
			printf("jal label%s\n",in.dest);
			fprintf(out,"jal label%s\n",in.dest);
		}
		else if(strcmp(in.op,"call")==0)
			inter_call(in,out);
		else if(strcmp(in.op,"getre")==0)
			inter_get_return(in,out);
		else if(strcmp(in.op,"ret")==0)
			inter_ret(in,out);
		else if(strcmp(in.op,"jr")==0){
			fprintf(out,"jr $ra\n");
			printf("jr $ra\n");
		}
		else if(strcmp(in.op,"exit")==0)
			inter_exit(in,out);
		else if(strcmp(in.op,"recover")==0){
			printf("addi $ra $s2 0\n");
			fprintf(out,"addi $ra $s2 0\n");
		}
		in=return_code(j);
	}
	fprintf(out,"jr $ra\n");
	printf("jr $ra\n");
	if(str_num!=0){
		fprintf(out,".data\n");
		printf(".data\n");
	}
	for(i=0;i<str_num;i++){
		fprintf(out,"str%d:.asciiz\"%s\"\n",i,print_str[i]);
		printf("str%d:.asciiz\"%s\"\n",i,print_str[i]);
	}
	return 0;
}

int inter_j(asyntax_code in,FILE *out)
{
	printf("j label%s\n",in.dest);
	fprintf(out,"j label%s\n",in.dest);
	return 0;
}

int inter_label(asyntax_code in,FILE *out)
{
	printf("label%s:\n",in.dest);
	fprintf(out,"label%s:\n",in.dest);
	return 0;
}

int inter_get(asyntax_code in,FILE *out)
{
	int i;
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	i=search_offset(s1,s2);
	printf("lw $t0 0($s0)\n");
	fprintf(out,"lw $t0 0($s0)\n");
	printf("addi $s0 $s0 4\n");
	fprintf(out,"addi $s0 $s0 4\n");
	printf("sw $t0 %d($sp)\n",i);
	fprintf(out,"sw $t0 %d($sp)\n",i);
	return 0;
}

int inter_gervar(asyntax_code in,FILE *out)
{
	int i;
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	i=search_offset(s1,s2);
	printf("lw $t0 0($s0)\n");
	fprintf(out,"lw $t0 0($s0)\n");
	printf("addi $s0 $s0 4\n");
	fprintf(out,"addi $s0 $s0 4\n");
	printf("sw $t0 %d($sp)\n",i);
	fprintf(out,"sw $t0 %d($sp)\n",i);
	return 0;
}

int inter_push(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("addi $s0 $s0 -4\n");
	printf("sw $t0 0($s0)\n");
	fprintf(out,"addi $s0 $s0 -4\n");
	fprintf(out,"sw $t0 0($s0)\n");
	return 0;
}

int inter_pushvar(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	int offset,i;
	ssymbol_table t;
	asymbol_entity e;
	split(in.dest,s1,s2);
	if(strcmp(s1,call_pro)==0){
		e=search_from_table(s2,find(call_pro));
		offset=search_offset(s1,s2);
		if(e.orvar==3){
			printf("lw $t0 %d($s3)\n",offset);
			fprintf(out,"lw $t0 %d($s3)\n",offset);
		}
		else{
			fprintf(out,"addi $t0 $s3 %d\n",offset);
			printf("addi $t0 $s3 %d\n",offset);
		}
	}
	else{
		t=find(call_pro);
		for(i=t->level-2;i>=0;i--){
			if(strcmp(t->stack[i]->name,s1)==0){
				e=search_from_table(s2,t->stack[i]);
				break;
			}
		}
		printf("lw $s1 -%d($s4)\n",4*(i+1));
		fprintf(out,"lw $s1 -%d($s4)\n",4*(i+1));
		offset=search_offset(s1,s2);
		if(e.orvar==3){
			printf("lw $t0 %d($s1)\n",offset);
			fprintf(out,"lw $t0 %d($s1)\n",offset);
		}
		else{
			printf("addi $t0 $s1 %d\n",offset);
			fprintf(out,"addi $t0 $s1 %d\n",offset);
		}
	}
	if(strcmp(in.src1,"\0")!=0){
		split(in.src1,s1,s2);
		printf("lw $t1 -%d($gp)\n",4*(atoi(s2)+1));
		printf("add $t0 $t0 $t1\n");
		fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s2)+1));
		fprintf(out,"add $t0 $t0 $t1\n");
	}
	printf("addi $s0 $s0 -4\n");
	printf("sw $t0 0($s0)\n");
	fprintf(out,"addi $s0 $s0 -4\n");
	fprintf(out,"sw $t0 0($s0)\n");
	return 0;
}

int inter_write(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("addi $v0 $0 1\n");
	fprintf(out,"addi $v0 $0 1\n");
	printf("lw $a0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $a0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("syscall\n");
	fprintf(out,"syscall\n");
	return 0;
}

int inter_writestr(asyntax_code in,FILE *out)
{
	printf("addi $v0 $0 4\n");
	printf("la $a0 str%d\n",str_num);
	printf("syscall\n");
	fprintf(out,"addi $v0 $0 4\n");
	fprintf(out,"la $a0 str%d\n",str_num);
	fprintf(out,"syscall\n");
	strcpy(print_str[str_num++],in.dest);
	return 0;
}

int inter_read(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	int i,offset;
	ssymbol_table t;
	asymbol_entity e;
	printf("addi $v0 $0 5\n");
	printf("syscall\n");
	fprintf(out,"addi $v0 $0 5\n");
	fprintf(out,"syscall\n");
	split(in.dest,s1,s2);
	if(strcmp(s1,call_pro)==0){
		e=search_from_table(s2,find(call_pro));
		if(e.orvar==0)
			while(1)
				;
		fprintf(out,"addi $s1 $sp 0\n");
		printf("addi $s1 $sp 0\n");
	}else{
		t=find(call_pro);
		for(i=t->lev-1;i>=0;i--){
			if(strcmp(t->stack[i]->name,s1)==0){
				e=search_from_table(s2,t->stack[i]);
				if(e.orvar==0)
					while(1)
						;
				fprintf(out,"lw $s1 -%d($fp)\n",4*(i+1));
				printf("lw $s1 -%d($fp)\n",4*(i+1));
			}
		}
	}
	offset=search_offset(s1,s2);
	fprintf(out,"sw $v0 %d($s1)\n",offset);
	printf("sw $v0 %d($s1)\n",offset);
	return 0;
}

int inter_addi(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	int offset,sp_change=0,i;
	int n;
	ssymbol_table t;
	asymbol_entity e;
	if(strcmp(in.src1,"$0")==0){
		fprintf(out,"addi $t1 $0 0\n");
		printf("addi $t1 $0 0\n");
	}
	else{
		split(in.src1,s1,s2);
		if(strcmp(s1,"gp")==0){
			fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s2)+1));
			printf("lw $t1 -%d($gp)\n",4*(atoi(s2)+1));
		}
		else{
			if(strcmp(s1,call_pro)==0){
				e=search_from_table(s2,find(call_pro));
				if(e.orvar==3){
					offset=search_offset(s1,s2);
					fprintf(out,"lw $t1 %d($sp)\n",offset);
					printf("lw $t1 %d($sp)\n",offset);
					fprintf(out,"lw $t1 0($t1)\n");
					printf("lw $t1 0($t1)\n");
				}
				else if(e.lenth>0){
					offset=search_offset(s1,s2);
					fprintf(out,"addi $t1 $sp %d\n",offset);
					printf("addi $t1 $sp %d\n",offset);
				}
				else{
					offset=search_offset(s1,s2);
					fprintf(out,"lw $t1 %d($sp)\n",offset);
					printf("lw $t1 %d($sp)\n",offset);
				}
			}
			else{
				t=find(call_pro);
				for(i=t->level-2;i>=0;i--){
					if(strcmp(t->stack[i]->name,s1)==0){
						e=search_from_table(s2,t->stack[i]);
						break;
					}
				}
				fprintf(out,"lw $s1 -%d($fp)\n",4*(i+1));
				printf("lw $s1 -%d($fp)\n",4*(i+1));
				offset=search_offset(s1,s2);
				if(e.orvar==3){
					fprintf(out,"lw $t1 %d($s1)\n",offset);
					printf("lw $t1 %d($s1)\n",offset);
					fprintf(out,"lw $t1 0($t1)\n",offset);
					printf("lw $t1 0($t1)\n",offset);
				}		
				else if(e.lenth>0){
					fprintf(out,"addi $t1 $s1 %d\n",offset);
					printf("lw $t1 $s1 %d\n",offset);
				}
				else{
					fprintf(out,"lw $t1 %d($s1)\n",offset);
					printf("lw $t1 %d($s1)\n",offset);
				}
			}
		}
	}
	fprintf(out,"addi $t0 $t1 %d\n",atoi(in.src2));
	printf("addi $t0 $t1 %d\n",atoi(in.src2));
	split(in.dest,s3,s4);
	if(strcmp(s3,"gp")==0){
		fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s4)+1));
		printf("sw $t0 -%d($gp)\n",4*(atoi(s4)+1));
	}
	else{
		if(strcmp(s3,call_pro)==0){
			e=search_from_table(s4,find(call_pro));
			offset=search_offset(s3,s4);
			if(e.orvar==3){
				fprintf(out,"lw $t3 %d($sp)\n",offset);
				printf("lw $t3 %d($sp)\n",offset);
				fprintf(out,"sw $t0 0($t3)\n",offset);
				printf("sw $t0 0($t3)\n",offset);
			}
			else{
				fprintf(out,"sw $t0 %d($sp)\n",offset);
				printf("sw $t0 %d($sp)\n",offset);
			}
		}
		else{
			t=find(call_pro);
			for(i=t->level-2;i>=0;i--){
				if(strcmp(t->stack[i]->name,s1)==0){
					e=search_from_table(s4,t->stack[i]);
					break;
				}
			}
			fprintf(out,"lw $s1 -%d($fp)\n",4*(i+1));
			printf("lw $s1 -%d($fp)\n",4*(i+1));
			offset=search_offset(s3,s4);
			if(e.orvar==3){
				printf("lw $t3 %d($s1)\n",offset);
				fprintf(out,"lw $t3 %d($s1)\n",offset);
				printf("sw $t0 0($t3)\n");
				fprintf(out,"sw $t0 0($t3)\n");
			}
			else{
				fprintf(out,"sw $t0 %d($s1)\n",offset);
				printf("sw $t0 %d($s1)\n",offset);
			}
		}
	}
}

int inter_add(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100],s5[100],s6[100];
	int offset,i;
	ssymbol_table t;
	asymbol_entity e;
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	split(in.src2,s5,s6);	
	if(strcmp(s3,"gp")==0){
		printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
		fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	}
	else{
		if(strcmp(s3,call_pro)==0){
			e=search_from_table(s4,find(call_pro));
			if(e.orvar==3){
				offset=search_offset(s3,s4);
				printf("lw $t1 %d($sp)\n",offset);
				printf("lw $t1 0($t1)\n");
				fprintf(out,"lw $t1 %d($sp)\n",offset);
				fprintf(out,"lw $t1 0($t1)\n");
			}
			else if(e.lenth>0){
				offset=search_offset(s3,s4);
				fprintf(out,"addi $t1 $sp %d\n",offset);
				printf("addi $t1 $sp %d\n",offset);
			}
			else{
				offset=search_offset(s3,s4);
				fprintf(out,"lw $t1 %d($sp)\n",offset);
				printf("lw $t1 %d($sp)\n",offset);
			}
		}
		else{
			t=find(call_pro);
			for(i=t->level-2;i>=0;i--){
				if(strcmp(t->stack[i]->name,s3)==0){
					e=search_from_table(s4,t->stack[i]);
					break;
				}
			}
			printf("lw $s1 -%d($fp)\n",4*(i+1));
			fprintf(out,"lw $s1 -%d($fp)\n",4*(i+1));
			offset=search_offset(s3,s4);
			if(e.orvar==3){
				fprintf(out,"lw $t1 %d($s1)\n",offset);
				printf("lw $t1 %d($s1)\n",offset);
				fprintf(out,"lw $t1 0($t1)\n",offset);
				printf("lw $t1 0($t1)\n",offset);
			}		
			else if(e.lenth>0){
				fprintf(out,"addi $t1 $s1 %d\n",offset);
				printf("lw $t1 $s1 %d\n",offset);
			}
			else{
				fprintf(out,"lw $t1 %d($s1)\n",offset);
				printf("lw $t1 %d($s1)\n",offset);
			}
		}
	}
	fprintf(out,"lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	printf("lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	printf("add $t0 $t1 $t2\n");
	fprintf(out,"add $t0 $t1 $t2\n");
	fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_lw(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s4)+1));
	printf("lw $t0 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t1 %d($t0)\n",atoi(in.src2));
	printf("lw $t1 %d($t0)\n",atoi(in.src2));
	printf("sw $t1 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"sw $t1 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_sw(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("sw $t1 %d($t0)\n",atoi(in.src2));
	fprintf(out,"sw $t1 %d($t0)\n",atoi(in.src2));
	return 0;
}

int inter_muli(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("addi $t2 $0 %d\n",atoi(in.src2));
	printf("mul $t0 $t1 $t2\n");
	printf("sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"addi $t2 $0 %d\n",atoi(in.src2));
	fprintf(out,"mul $t0 $t1 $t2\n");
	fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_mul(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100],s5[100],s6[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	split(in.src2,s5,s6);
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	printf("mul $t0 $t1 $t2\n");
	printf("sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	fprintf(out,"mul $t0 $t1 $t2\n");
	fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_div(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100],s5[100],s6[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	split(in.src2,s5,s6);
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	printf("div $t0 $t1 $t2\n");
	printf("sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	fprintf(out,"div $t0 $t1 $t2\n");
	fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int split(char s[],char s1[],char s2[])
{
	int i=0,j;
	while(s[i]!=':')
		i++;
	for(j=0;j<i;j++)
		s1[j]=s[j];
	s1[j]='\0';
	for(j=0;s[i+j+1]!='\0';j++)
		s2[j]=s[i+j+1];
	s2[j]='\0';
	return 0;
}

int add_offset()
{
	int i,offset;
	ssymbol_table t;
	t=return_head();
	while(t!=NULL){
		offset=0;
		for(i=t->n-1;i>=0;i--){
			if((t->s[i].lenth==0)&&(t->s[i].orvar!=5)){
				t->s[i].offset=offset;
				offset+=4;
			}
			else{
				t->s[i].offset=offset;
				offset+=4*(t->s[i].lenth);
			}
		}
		t->offset_total=offset;
		t=t->next;
	}
	return 0;
}

int inter_sub(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100],s5[100],s6[100];
	int i,offset;
	ssymbol_table t;
	asymbol_entity e;
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	split(in.src2,s5,s6);
	if(strcmp(s3,"gp")==0){
		printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
		fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	}
	else{
		if(strcmp(s3,call_pro)==0){
			e=search_from_table(s4,find(call_pro));
			if(e.orvar==3){
				offset=search_offset(s3,s4);
				printf("lw $t1 %d($sp)\n",offset);
				printf("lw $t1 0($t1)\n");
				fprintf(out,"lw $t1 %d($sp)\n",offset);
				fprintf(out,"lw $t1 0($t1)\n");
			}
			else{
				offset=search_offset(s3,s4);
				fprintf(out,"lw $t1 %d($sp)\n",offset);
				printf("lw $t1 %d($sp)\n",offset);
			}
		}
		else{
			t=find(call_pro);
			for(i=t->level-2;i>=0;i--){
				if(strcmp(t->stack[i]->name,s3)==0){
					e=search_from_table(s4,t->stack[i]);
					break;
				}
			}
			printf("lw $s1 -%d($fp)\n",4*(i+1));
			fprintf(out,"lw $s1 -%d($fp)\n",4*(i+1));
			offset=search_offset(s3,s4);
			if(e.orvar==3){
				fprintf(out,"lw $t1 %d($s1)\n",offset);
				printf("lw $t1 %d($s1)\n",offset);
				fprintf(out,"lw $t1 0($t1)\n",offset);
				printf("lw $t1 0($t1)\n",offset);
			}		
			else{
				fprintf(out,"lw $t1 %d($s1)\n",offset);
				printf("lw $t1 %d($s1)\n",offset);
			}
		}
	}
	printf("lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	fprintf(out,"lw $t2 -%d($gp)\n",4*(atoi(s6)+1));
	printf("sub $t0 $t1 $t2\n");
	fprintf(out,"sub $t0 $t1 $t2\n");
	printf("sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"sw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_bgez(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("bgez $t0 %s\n",in.src2);
	fprintf(out,"bgez $t0 %s\n",in.src2);
	return 0;
}

int inter_bgtz(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("bgtz $t0 %s\n",in.src2);
	fprintf(out,"bgtz $t0 %s\n",in.src2);
	return 0;
}

int inter_beq(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("beq $t0 $t1 %s\n",in.src2);
	fprintf(out,"beq $t0 $t1 %s\n",in.src2);
}

int inter_bne(asyntax_code in,FILE *out)
{
	char s1[100],s2[100],s3[100],s4[100];
	split(in.dest,s1,s2);
	split(in.src1,s3,s4);
	printf("lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $t0 -%d($gp)\n",4*(atoi(s2)+1));
	printf("lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	fprintf(out,"lw $t1 -%d($gp)\n",4*(atoi(s4)+1));
	printf("bne $t0 $t1 %s\n",in.src2);
	fprintf(out,"bne $t0 $t1 %s\n",in.src2);
}

int inter_call(asyntax_code in,FILE *out)
{
	ssymbol_table t=find(in.dest);
	ssymbol_table t1=find(in.src1);
	int l1,l2;
	int offset,i,j;
	l1=t->level;
	l2=t1->level;
	printf("addi $s3 $sp 0\n");
	fprintf(out,"addi $s3 $sp 0\n");
	printf("addi $s4 $fp 0\n");
	fprintf(out,"addi $s4 $fp 0\n");
	for(i=0;i<return_num();i++){
		printf("lw $t0 -%d($gp)\n",4*(i+1));
		printf("sw $t0 -%d($sp)\n",4*(i+1));
		fprintf(out,"lw $t0 -%d($gp)\n",4*(i+1));
		fprintf(out,"sw $t0 -%d($sp)\n",4*(i+1));
	}
	if(l1==l2+1){
		for(i=0;i<l2-1;i++){
			printf("lw $t0 -%d($fp)\n",4*(i+1));
			fprintf(out,"lw $t0 -%d($fp)\n",4*(i+1));
			printf("sw $t0 -%d($sp)\n",4*(i+1)+4*return_num());
			fprintf(out,"sw $t0 -%d($sp)\n",4*(i+1)+4*return_num());
		}
		printf("sw $sp -%d($sp)\n",4*(i+1)+4*return_num());
		fprintf(out,"sw $sp -%d($sp)\n",4*(i+1)+4*return_num());
		i++;
	}
	else{
		for(i=0;i<l1-1;i++){
			printf("lw $t0 -%d($fp)\n",4*(i+1));
			fprintf(out,"lw $t0 -%d($fp)\n",4*(i+1));
			printf("sw $t0 -%d($sp)\n",4*(i+1)+4*return_num());
			fprintf(out,"sw $t0 -%d($sp)\n",4*(i+1)+4*return_num());
		}
	}
	printf("sw $sp -%d($sp)\n",4*(i+1)+4*return_num());
	fprintf(out,"sw $sp -%d($sp)\n",4*(i+1)+4*return_num());
	i++;
	printf("sw $ra -%d($sp)\n",4*(i+1)+4*return_num());
	fprintf(out,"sw $ra -%d($sp)\n",4*(i+1)+4*return_num());
	i++;
	printf("sw $gp -%d($sp)\n",4*(i+1)+4*return_num());
	fprintf(out,"sw $gp -%d($sp)\n",4*(i+1)+4*return_num());
	i++;
	printf("sw $fp -%d($sp)\n",4*(i+1)+4*return_num());
	fprintf(out,"sw $fp -%d($sp)\n",4*(i+1)+4*return_num());
	i++;
	printf("addi $gp $sp 0\n");
	fprintf(out,"addi $gp $sp 0\n");
	printf("addi $sp $sp -%d\n",4*return_num());
	fprintf(out,"addi $sp $sp -%d\n",4*return_num());
	offset=4*i+t->offset_total;
	printf("addi $fp $sp 0\n");
	fprintf(out,"addi $fp $sp 0\n");
	printf("addi $sp $sp -%d\n",offset);
	fprintf(out,"addi $sp $sp -%d\n",offset);
	printf("addi $s0 $sp 0\n");
	fprintf(out,"addi $s0 $sp 0\n");
	return 0;
}

int inter_get_return(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("sw $v0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"sw $v0 -%d($gp)\n",4*(atoi(s2)+1));
}

int inter_ret(asyntax_code in,FILE *out)
{
	char s1[100],s2[100];
	split(in.dest,s1,s2);
	printf("lw $v0 -%d($gp)\n",4*(atoi(s2)+1));
	fprintf(out,"lw $v0 -%d($gp)\n",4*(atoi(s2)+1));
	return 0;
}

int inter_exit(asyntax_code in,FILE *out)
{
	int i;
	ssymbol_table t=find(call_pro);
	for(i=0;i<return_num();i++){
		printf("lw $t0 -%d($gp)\n",4*(i+1));
		printf("sw $t0 %d($fp)\n",4*(return_num()-i-1));
		fprintf(out,"lw $t0 -%d($gp)\n",4*(i+1));
		fprintf(out,"sw $t0 %d($fp)\n",4*(return_num()-i-1));
	}
	printf("lw $sp -%d($fp)\n",4*(t->level));
	printf("lw $s2 -%d($fp)\n",4*(t->level+1));
	printf("lw $gp -%d($fp)\n",4*(t->level+2));
	printf("lw $fp -%d($fp)\n",4*(t->level+3));
	fprintf(out,"lw $sp -%d($fp)\n",4*(t->level));
	fprintf(out,"lw $s2 -%d($fp)\n",4*(t->level+1));
	fprintf(out,"lw $gp -%d($fp)\n",4*(t->level+2));
	fprintf(out,"lw $fp -%d($fp)\n",4*(t->level+3));
	strcpy(call_pro,call_procedure[--call_num]);
	return 0;
}