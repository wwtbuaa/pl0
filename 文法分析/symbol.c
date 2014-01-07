#include"symbol.h"

int sym_top=0;
ssymbol_table sym_head=NULL,sym_stack[10];

int check(ssymbol_table table,char s[])
{
	int i;
	for(i=0;i<table->n;i++)
		if(strcmp(s,table->s[i].name)==0)
			return 0;
	return 1;
}

asymbol_entity search(char o[],char s[])
{
	int i,j;
	ssymbol_table t;
	for(j=sym_top-1;j>=0;j--){
		t=sym_stack[j];
		for(i=0;i<t->n;i++)
			if(strcmp(s,t->s[i].name)==0)
				return t->s[i];
	}
	err(6,0,s);
}

ssymbol_table search_table(char o[],char s[])
{
	int i,j;
	ssymbol_table t;
	for(j=sym_top-1;j>=0;j--){
		t=sym_stack[j];
		for(i=0;i<t->n;i++)
			if(strcmp(s,t->s[i].name)==0)
				return t;
	}
	err(6,0,s);
}

int link(ssymbol_table table)
{
	if(sym_head==NULL)
		sym_head=table;
	else{
		table->next=sym_head->next;
		sym_head->next=table;
	}
	return 0;
}

ssymbol_table find(char s[])
{
	ssymbol_table t=sym_head;
	while((t!=NULL)&&(strcmp(s,t->name)!=0))
		t=t->next;
	if(t==NULL)
		err(4,0,s);
	return t;
}

asymbol_entity search_from_table(char s[],ssymbol_table t)
{
	int i;
	for(i=0;i<t->n;i++)
		if(strcmp(t->s[i].name,s)==0)
			return t->s[i];
}

ssymbol_table new_table(char s[],int value,int level)
{
	ssymbol_table t=(ssymbol_table)malloc(sizeof(asymbol_table));
	int i;
	strcpy(t->name,s);
	t->value=value;
	t->level=level;
	t->n=0;
	t->para_number=0;
	t->next=NULL;
	t->lev=sym_top-1;
	for(i=0;i<sym_top;i++)
		t->stack[i]=sym_stack[i];
	link(t);
	return t;
}

int add_const(sconstdefine pconstdefine,char s[])
{
	ssymbol_table table=find(s);
	if(check(table,pconstdefine->piden)==0)
		err(5,0,pconstdefine->piden);
	table->s[table->n].lenth=0;
	table->s[table->n].offset=0;
	strcpy(table->s[table->n].name,pconstdefine->piden);
	table->s[table->n].orvar=0;
	table->s[table->n].type=pconstdefine->type;
	if(pconstdefine->type)
		table->s[table->n].value=pconstdefine->pchar;
	else
		table->s[table->n].value=pconstdefine->pint;
	table->n++;
	return 0;
}

int add_var(svardefine pvardefine,char s[])
{
	int i;
	for(i=0;i<pvardefine->num;i++)
		add_var_demo(pvardefine->piden[i],pvardefine->type,pvardefine->lenth,s);
	return 0;
}

int add_var_demo(char sl[],int type,int lenth,char s[])
{
	ssymbol_table table=find(s);
	if(check(table,sl)==0)
		err(5,0,sl);
	table->s[table->n].lenth=lenth;
	table->s[table->n].offset=0;
	table->s[table->n].type=type;
	table->s[table->n].orvar=1;
	strcpy(table->s[table->n].name,sl);
	table->n++;
	return  0;
}

int add_para(svirtuallist pvirtuallist,char s[])
{
	int i;
	ssymbol_table table=find(s);
	table->s[table->n].offset=0;
	for(i=0;i<pvirtuallist->num;i++){
		if(check(table,pvirtuallist->piden[i])==0)
			err(5,0,pvirtuallist->piden[i]);
		table->s[table->n].lenth=0;
		table->s[table->n].type=pvirtuallist->type;
		if(pvirtuallist->var)
			table->s[table->n].orvar=3;
		else
			table->s[table->n].orvar=2;
		strcpy(table->s[table->n].name,pvirtuallist->piden[i]);
		table->n++;
		table->para_number++;
	}
	return 0;
}

int push(ssymbol_table table)
{
	sym_stack[sym_top++]=table;
	return 0;
}

int pop()
{
	sym_top--;
	return 0;
}

int add_procedure(sprocedure pprocedure,char s[])
{
	ssymbol_table table=find(s);
	if(check(table,pprocedure->piden)==0)
		err(5,0,pprocedure->piden);
	table->s[table->n].lenth=0;
	table->s[table->n].offset=0;
	strcpy(table->s[table->n].name,pprocedure->piden);
	table->s[table->n].orvar=5;
	table->s[table->n].type=0;
	table->n++;
	return 0;
}

int add_function(sfunction pfunction,char s[])
{
	ssymbol_table table=find(s);
	if(check(table,pfunction->piden)==0)
		err(5,0,pfunction->piden);
	table->s[table->n].lenth=0;
	table->s[table->n].offset=0;
	strcpy(table->s[table->n].name,pfunction->piden);
	table->s[table->n].orvar=4;
	table->s[table->n].type=pfunction->type;
	table->n++;
	return 0;
}

ssymbol_table return_head()
{
	return sym_head;
}

int search_offset(char o[],char s[])
{
	ssymbol_table t=find(o);
	int i;
	for(i=0;i<t->n;i++)
		if(strcmp(t->s[i].name,s)==0)
			return t->s[i].offset;
	return -1;
}

int add_return(char sl[],char s[])
{
	ssymbol_table table=find(s);
	table->s[table->n].lenth=0;
	table->s[table->n].offset=0;
	strcpy(table->s[table->n].name,sl);
	table->s[table->n].orvar=6;
	table->s[table->n].type=0;
	table->n++;
	return 0;
}