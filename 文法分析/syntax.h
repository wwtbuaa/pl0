#ifndef SYNTAX_H
#define SYNTAX_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"symbol.h"
#include"error.h"

typedef struct syntax_code{
	char op[100];
	char dest[100];
	char src1[100];
	char src2[100];
}asyntax_code;

int syntax(sprogramme pprogramme,char *o);
int syntax_block(sblock pblock,char *o);
int syntax_constdeclare(sconstdeclare pconstdeclare,char *o);
int syntax_constdefine(sconstdefine pconstdefine,char *o);
int syntax_vardeclare(svardeclare pvardeclare,char *o);
int syntax_vardefine(svardefine pvardefine,char *o);
int syntax_complexstatement(scomplexstatement pcomplexstatement,char *o);
int syntax_statementlist(sstatementlist pstatementlist,char *o);
int syntax_statement(sstatement pstatement,char *o);
int syntax_assignstatement(sassignstatement passignstatement,char *o);
int syntax_expression(sexpression pexpression,char *o);
int syntax_term(sterm pterm,char *o);
int syntax_factor(sfactor pfactor,char *o);
int syntax_condition(scondition pcondition,char *o);
int syntax_conditionstatement(sconditionstatement pconditionstatement,char *o);
int syntax_forstatement(sforstatement pforstatement,char *o);
int syntax_pflist(spflist ppflist,char *o);
int syntax_proceduredeclare(sproceduredeclare pprocedure,char *o);
int syntax_functiondeclare(sfunctiondeclare pfunction,char *o);
int syntax_procedure(sprocedure pprocedure,char *o);
int syntax_function(sfunction pfunction,char *o);
int syntax_virtualtable(svirtualtable pvirtualtable,char *o);
int syntax_whilestatement(swhilestatement pwhilestatement,char *o);
int syntax_callprocedure(scallprocedure pcallprocedure,char *o);
int syntax_realtable(srealtable prealtable,char *s,char *o,int *n);
int syntax_callfunction(scallfunction pcallfunction,char *o);
int syntax_writestatement(swritestatement pwritestatement,char *o);
int syntax_readstatement(sreadstatement preadstatement,char *o);
asyntax_code return_code(int n);
int return_num();
int return_code_num();

#endif