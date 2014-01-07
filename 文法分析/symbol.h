#ifndef SYMBOL_H
#define SYMBOL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"parse.h"
#include"error.h"

typedef struct symbol_entity *ssymbol_entity,asymbol_entity;
typedef struct symbol_table *ssymbol_table,asymbol_table;

typedef struct symbol_entity{
	char name[100];
	int type;//type=0 int,type=1 char
	int value;
	int orvar;//1 var,0 const,2 para,3 varpara,4 function,5 procedure,6 return value
	int lenth;
	int offset;
};

typedef struct symbol_table{
	int n;
	int value;
	int level;
	int para_number;
	int offset_total;
	char name[100];
	asymbol_entity s[100];
	ssymbol_table next;
	int lev;
	ssymbol_table stack[10]; 
};

int link(ssymbol_table table);
int push(ssymbol_table table);
int pop();
int check(ssymbol_table table,char s[]);
asymbol_entity search(char o[],char s[]);
ssymbol_table new_table(char s[],int value,int level);
ssymbol_table search_table(char o,char s[]);
asymbol_entity search_from_table(char s[],ssymbol_table t);
ssymbol_table find(char s[]);
int add_const(sconstdefine pconstdefine,char s[]);
int add_var(svardefine pvardefine,char s[]);
int add_var_demo(char sl[],int type,int lenth,char s[]);
int add_para(svirtuallist pvirtuallist,char s[]);
int add_procedure(sprocedure pprocedure,char s[]);
int add_function(sfunction pfunction,char s[]);
int add_return(char sl[],char s[]);
ssymbol_table return_head();
int search_offset(char o[],char s[]);

#endif