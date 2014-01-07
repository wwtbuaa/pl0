#include"syntax.h"

int temp=0;
int label=0;
int label_number[100];
asyntax_code code[1000];
int code_number=0;
int call_number=0;
asyntax_code call_code[1000];

int return_code_num()
{
	return code_number;
}

asyntax_code return_code(int n)
{
	return code[n];
}

int return_num()
{
	return temp;
}

int syntax(sprogramme pprogramme,char *o)
{
	ssymbol_table table=new_table(o,-1,1);
	push(table);
	syntax_block(pprogramme->pblock,o);
	sprintf(code[code_number].op,"end");
	sprintf(code[code_number].dest,"\0");
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	pop();
	printf("end\n");
	return 0;
}

int syntax_block(sblock pblock,char *o)
{
	int label1;
	if(pblock->pconstdeclare!=NULL)
		syntax_constdeclare(pblock->pconstdeclare,o);
	if(pblock->pvardeclare!=NULL)
		syntax_vardeclare(pblock->pvardeclare,o);
	sprintf(code[code_number].op,"j");
	sprintf(code[code_number].dest,"%d",label);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("j label%d\n",label);
	label1=label;
	label++;
	if(pblock->ppflist!=NULL)
		syntax_pflist(pblock->ppflist,o);
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label1);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label1);
	syntax_complexstatement(pblock->pcomplexstatement,o);
	return 0;
}

int syntax_constdeclare(sconstdeclare pconstdeclare,char *o)
{
	syntax_constdefine(pconstdeclare->pconstdefine,o);
	if(pconstdeclare->pconstdeclare!=NULL)
		syntax_constdeclare(pconstdeclare->pconstdeclare,o);
	return 0;
}

int syntax_constdefine(sconstdefine pconstdefine,char *o)
{
	add_const(pconstdefine,o);
	if(pconstdefine->type){
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"%s:%s",o,pconstdefine->piden);
		sprintf(code[code_number].src1,"$0");
		sprintf(code[code_number].src2,"%d",pconstdefine->pchar);
		code_number++;
		printf("addi %s:%s $0 %d\n",o,pconstdefine->piden,pconstdefine->pchar);
	}
	else{
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"%s:%s",o,pconstdefine->piden);
		sprintf(code[code_number].src1,"$0");
		sprintf(code[code_number].src2,"%d",pconstdefine->pint);
		code_number++;
		printf("addi %s:%s $0 %d\n",o,pconstdefine->piden,pconstdefine->pint);
	}
	return 0;
}

int syntax_vardeclare(svardeclare pvardeclare,char *o)
{
	syntax_vardefine(pvardeclare->pvardefine,o);
	if(pvardeclare->pvardeclare!=NULL)
		syntax_vardeclare(pvardeclare->pvardeclare,o);
	return 0;
}

int syntax_vardefine(svardefine pvardefine,char *o)
{
	add_var(pvardefine,o);
	return 0;
}

int syntax_complexstatement(scomplexstatement pcomplexstatement,char *o)
{
	syntax_statementlist(pcomplexstatement->pstatementlist,o);
	return 0;
}

int syntax_statementlist(sstatementlist pstatementlist,char *o)
{
	syntax_statement(pstatementlist->pstatement,o);
	if(pstatementlist->pstatementlist!=NULL)
		syntax_statementlist(pstatementlist->pstatementlist,o);
	return 0;
}

int syntax_statement(sstatement pstatement,char *o)
{
	switch(pstatement->type){
	case 0:
		break;
	case 1:
		syntax_assignstatement(pstatement->passignstatement,o);
		break;
	case 2:
		syntax_conditionstatement(pstatement->pconditionstatement,o);
		break;
	case 3:
		syntax_whilestatement(pstatement->pwhilestatement,o);
		break;
	case 4:
		syntax_callprocedure(pstatement->pcallprocedure,o);
		break;
	case 5:
		syntax_complexstatement(pstatement->pcomplexstatement,o);
		break;
	case 6:
		syntax_readstatement(pstatement->preadstatement,o);
		break;
	case 7:
		syntax_writestatement(pstatement->pwritestatement,o);
		break;
	case 8:
		syntax_forstatement(pstatement->pforstatement,o);
		break;
	}
	return 0;
}

int syntax_assignstatement(sassignstatement passignstatement,char *o)
{
	int temp1;
	asymbol_entity t=search(o,passignstatement->piden);
	switch(passignstatement->type){
	case 0:
		if(t.orvar==0)
			err(7,0,t.name);
		syntax_expression(passignstatement->pexpression,o);
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"%s:%s",search_table(o,passignstatement->piden)->name,passignstatement->piden);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"0");
		code_number++;
		printf("addi %s:%s gp:%d 0\n",search_table(o,passignstatement->piden)->name,passignstatement->piden,temp);
		temp++;
		break;
	case 1:
		if(t.orvar!=1)
			err(7,0,t.name);
		syntax_expression(passignstatement->pexpression,o);
		temp1=temp;
		temp++;
		syntax_expression(passignstatement->pnexpression,o);
		sprintf(code[code_number].op,"muli");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"4");
		code_number++;
		printf("muli gp:%d gp:%d 4\n",temp,temp);
		sprintf(code[code_number].op,"add");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,passignstatement->piden)->name,passignstatement->piden);
		sprintf(code[code_number].src2,"gp:%d",temp);
		code_number++;
		printf("add gp:%d %s:%s gp:%d\n",temp,search_table(o,passignstatement->piden)->name,passignstatement->piden,temp);
		sprintf(code[code_number].op,"sw");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp1);
		sprintf(code[code_number].src2,"0");
		code_number++;
		printf("sw gp:%d gp:%d 0\n",temp,temp1);
		temp++;
	}
	return 0;
}

int syntax_expression(sexpression pexpression,char *o)
{
	int temp1;
	stermlist ptermlist=pexpression->ptermlist;
	spluslist ppluslist=pexpression->ppluslist;
	syntax_term(ptermlist->pterm,o);
	temp1=temp;
	while(ptermlist->ptermlist!=NULL){
		temp++;
		ptermlist=ptermlist->ptermlist;
		syntax_term(ptermlist->pterm,o);
		if(ppluslist->pplus->type){
			sprintf(code[code_number].op,"add");
			sprintf(code[code_number].dest,"gp:%d",temp);
			sprintf(code[code_number].src1,"gp:%d",temp1);
			sprintf(code[code_number].src2,"gp:%d",temp);
			code_number++;
			printf("add gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		}
		else{
			sprintf(code[code_number].op,"sub");
			sprintf(code[code_number].dest,"gp:%d",temp);
			sprintf(code[code_number].src1,"gp:%d",temp1);
			sprintf(code[code_number].src2,"gp:%d",temp);
			code_number++;
			printf("sub gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		}
		temp1=temp;
		ppluslist=ppluslist->ppluslist;
	}
	if(pexpression->revert){
		sprintf(code[code_number].op,"subi");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"0");
		sprintf(code[code_number].src2,"gp:%d",temp);
		code_number++;
		printf("subi gp:%d 0 gp:%d\n",temp,temp);
	}
	return 0;
}

int syntax_term(sterm pterm,char *o)
{
	int temp1;
	sfactorlist pfactorlist=pterm->pfactorlist;
	smullist pmullist=pterm->pmullist;
	syntax_factor(pfactorlist->pfactor,o);
	temp1=temp;
	while(pfactorlist->pfactorlist!=NULL){
		temp++;
		pfactorlist=pfactorlist->pfactorlist;
		syntax_factor(pfactorlist->pfactor,o);
		if(pmullist->pmul->type){
			sprintf(code[code_number].op,"mul");
			sprintf(code[code_number].dest,"gp:%d",temp);
			sprintf(code[code_number].src1,"gp:%d",temp1);
			sprintf(code[code_number].src2,"gp:%d",temp);
			code_number++;
			printf("mul gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		}
		else{
			sprintf(code[code_number].op,"div");
			sprintf(code[code_number].dest,"gp:%d",temp);
			sprintf(code[code_number].src1,"gp:%d",temp1);
			sprintf(code[code_number].src2,"gp:%d",temp);
			code_number++;
			printf("div gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		}
		temp1=temp;
		pmullist=pmullist->pmullist;
	}
	return 0;
}

int syntax_factor(sfactor pfactor,char *o)
{
	asymbol_entity t;
	switch(pfactor->type){
	case 1:
		t=search(o,pfactor->piden);
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,pfactor->piden)->name,pfactor->piden);
		sprintf(code[code_number].src2,"0");
		code_number++;
		printf("addi gp:%d %s:%s 0\n",temp,search_table(o,pfactor->piden)->name,pfactor->piden);
		break;
	case 2:
		t=search(o,pfactor->piden);
		if(t.lenth==0)
			err(8,0,t.name);
		syntax_expression(pfactor->pexpression,o);
		sprintf(code[code_number].op,"muli");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"4");
		printf("muli gp:%d gp:%d 4\n",temp,temp);
		code_number++;
		sprintf(code[code_number].op,"add");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,pfactor->piden)->name,pfactor->piden);
		sprintf(code[code_number].src2,"gp:%d",temp);
		code_number++;
		printf("add gp:%d %s:%s gp:%d\n",temp,search_table(o,pfactor->piden)->name,pfactor->piden,temp);
		sprintf(code[code_number].op,"lw");
		sprintf(code[code_number].dest,"gp:%d",temp+1);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"0");
		code_number++;
		printf("lw gp:%d gp:%d 0\n",temp+1,temp);
		temp++;
		break;
	case 3:
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"$0");
		sprintf(code[code_number].src2,"%d",pfactor->pnumber);
		code_number++;
		printf("addi gp:%d $0 %d\n",temp,pfactor->pnumber);
		break;
	case 4:
		syntax_expression(pfactor->pexpression,o);
		break;
	case 5:
		syntax_callfunction(pfactor->pcallfunction,o);
		break;
	}
	return 0;
}

int syntax_condition(scondition pcondition,char *o)
{
	int temp1;
	syntax_expression(pcondition->pexpression1,o);
	temp1=temp;
	temp++;
	syntax_expression(pcondition->pexpression2,o);
	switch(pcondition->type){
	case 1:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp1);
		sprintf(code[code_number].src2,"gp:%d",temp);
		printf("sub gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		code_number++;
		sprintf(code[code_number].op,"bgez");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"1");
		sprintf(code[code_number].src2,"label%d",label);
		printf("bgez gp:%d 1 label%d\n",temp,label);
		code_number++;
		break;
	case 2:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp1);
		sprintf(code[code_number].src2,"gp:%d",temp);
		printf("sub gp:%d gp:%d gp:%d\n",temp,temp1,temp);
		code_number++;
		sprintf(code[code_number].op,"bgtz");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"0");
		sprintf(code[code_number].src2,"label%d",label);
		printf("bgtz gp:%d 0 label%d\n",temp,label);
		code_number++;
		break;
	case 3:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"gp:%d",temp1);
		printf("sub gp:%d gp:%d gp:%d\n",temp,temp,temp1);
		code_number++;
		sprintf(code[code_number].op,"bgez");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"1");
		sprintf(code[code_number].src2,"label%d",label);
		printf("bgez gp:%d 1 label%d\n",temp,label);
		code_number++;
		break;
	case 4:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"gp:%d",temp1);
		printf("sub gp:%d gp:%d gp:%d\n",temp,temp,temp1);
		code_number++;
		sprintf(code[code_number].op,"bgez");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"0");
		sprintf(code[code_number].src2,"label%d",label);
		printf("bgtz gp:%d 0 label%d\n",temp,label);
		code_number++;
		break;
	case 5:
		sprintf(code[code_number].op,"bne");
		sprintf(code[code_number].dest,"gp:%d",temp1);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"label%d",label);
		printf("bne gp:%d gp:%d label%d\n",temp1,temp,label);
		code_number++;
		break;
	case 6:
		sprintf(code[code_number].op,"beq");
		sprintf(code[code_number].dest,"gp:%d",temp1);
		sprintf(code[code_number].src1,"gp:%d",temp);
		sprintf(code[code_number].src2,"label%d",label);
		printf("beq gp:%d gp:%d label%d\n",temp1,temp,label);
		code_number++;
		break;
	}
	temp++;
	return 0;
}

int syntax_conditionstatement(sconditionstatement pconditionstatement,char *o)
{
	int label1,label2;
	syntax_condition(pconditionstatement->pcondition,o);
	label1=label;
	label2=++label;
	label++;
	syntax_statement(pconditionstatement->pstatement1,o);
	if(pconditionstatement->type==0){
		sprintf(code[code_number].op,"label");
		sprintf(code[code_number].dest,"%d",label1);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("label%d:\n",label1);
		label++;
	}
	else if(pconditionstatement->type){
		sprintf(code[code_number].op,"j");
		sprintf(code[code_number].dest,"%d",label2);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("j label%d\n",label2);
		sprintf(code[code_number].op,"label");
		sprintf(code[code_number].dest,"%d",label1);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("label%d:\n",label1);
		syntax_statement(pconditionstatement->pstatement2,o);
		sprintf(code[code_number].op,"label");
		sprintf(code[code_number].dest,"%d",label2);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("label%d:\n",label2);
		label++;
	}
	return 0;
}

int syntax_whilestatement(swhilestatement pwhilestatement,char *o)
{
	int label1,label2;
	label1=label;
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label);
	label++;
	syntax_condition(pwhilestatement->pcondition,o);
	label2=label;
	label++;
	syntax_statement(pwhilestatement->pstatement,o);
	sprintf(code[code_number].op,"j");
	sprintf(code[code_number].dest,"%d",label1);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("j label%d\n",label1);
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label2);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label2);
	return 0;
}

int syntax_forstatement(sforstatement pforstatement,char *o)
{
	int temp1,temp2;
	int label1,label2;
	syntax_expression(pforstatement->pexpression2,o);
	temp2=temp;
	temp++;
	syntax_expression(pforstatement->pexpression1,o);
	sprintf(code[code_number].op,"addi");
	sprintf(code[code_number].dest,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
	sprintf(code[code_number].src1,"gp:%d",temp);
	sprintf(code[code_number].src2,"0");
	code_number++;
	printf("addi %s:%s gp:%d 0\n",search_table(o,pforstatement->piden)->name,pforstatement->piden,temp);
	temp1=temp;
	temp++;
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label);
	label1=label++;
	label2=label++;
	switch(pforstatement->type){
	case 0:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].src2,"gp:%d",temp2);
		code_number++;
		printf("sub gp:%d %s:%s gp:%d\n",temp,search_table(o,pforstatement->piden)->name,pforstatement->piden,temp2);
		sprintf(code[code_number].op,"bgtz");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"1");
		sprintf(code[code_number].src2,"label%d",label2);
		code_number++;
		printf("bgtz gp:%d 0 label%d\n",temp,label2);
		temp++;
		syntax_statement(pforstatement->pstatement,o);
		sprintf(code[code_number].op,"addi");
		sprintf(code[code_number].dest,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].src2,"1");
		code_number++;
		printf("addi %s:%s %s:%s 1\n",search_table(o,pforstatement->piden)->name,pforstatement->piden,search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].op,"j");
		sprintf(code[code_number].dest,"%d",label1);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("j label%d\n",label1);
		sprintf(code[code_number].op,"label");
		sprintf(code[code_number].dest,"%d",label2);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("label%d:",label2);
		label++;
		break;
	case 1:
		sprintf(code[code_number].op,"sub");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"gp:%d",temp2);
		sprintf(code[code_number].src2,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		code_number++;
		printf("sub gp:%d gp:%d %s:%s\n",temp,temp2,search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].op,"bgtz");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"1");
		sprintf(code[code_number].src2,"label%d",label2);
		code_number++;
		printf("bgtz gp:%d 0 label:%d\n",temp,label2);
		syntax_statement(pforstatement->pstatement,o);
		sprintf(code[code_number].op,"subi");
		sprintf(code[code_number].dest,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].src1,"%s:%s",search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].src2,"1");
		code_number++;
		printf("subi %s:%s %s:%s 1\n",search_table(o,pforstatement->piden)->name,pforstatement->piden,search_table(o,pforstatement->piden)->name,pforstatement->piden);
		sprintf(code[code_number].op,"j");
		sprintf(code[code_number].dest,"%d",label1);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("j label%d\n",label1);
		sprintf(code[code_number].op,"label");
		sprintf(code[code_number].dest,"%d",label2);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		printf("label%d:\n",label2);
		label++;
		break;
	}
	return 0;
}

int syntax_pflist(spflist ppflist,char *o)
{
	if(ppflist->ppf->type)
		syntax_functiondeclare(ppflist->ppf->pfunctiondeclare,o);
	else 
		syntax_proceduredeclare(ppflist->ppf->pproceduredeclare,o);
	if(ppflist->ppflist!=NULL)
		syntax_pflist(ppflist->ppflist,o);
	return 0;
}

int syntax_proceduredeclare(sproceduredeclare pproceduredeclare,char *o)
{
	syntax_procedure(pproceduredeclare->pprocedure,o);
	syntax_block(pproceduredeclare->pblock,pproceduredeclare->pprocedure->piden);
	sprintf(code[code_number].op,"exit");
	sprintf(code[code_number].dest,"\0");
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("exit\n");
	sprintf(code[code_number].op,"jr");
	sprintf(code[code_number].dest,"$ra");
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("jr $ra\n");
	pop();
	return 0;
}

int syntax_functiondeclare(sfunctiondeclare pfunctiondeclare,char *o)
{
	syntax_function(pfunctiondeclare->pfunction,o);
	syntax_block(pfunctiondeclare->pblock,pfunctiondeclare->pfunction->piden);
	sprintf(code[code_number].op,"addi");
	sprintf(code[code_number].dest,"gp:%d",temp);
	sprintf(code[code_number].src1,"%s:%s",pfunctiondeclare->pfunction->piden,pfunctiondeclare->pfunction->piden);
	strcpy(code[code_number].src2,"0");
	code_number++;
	printf("addi gp:%d %s:%s 0\n",temp,pfunctiondeclare->pfunction->piden,pfunctiondeclare->pfunction->piden);
	sprintf(code[code_number].op,"ret");
	sprintf(code[code_number].dest,"gp:%d",temp);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("ret gp:%d\n",temp);
	temp++;
	sprintf(code[code_number].op,"exit");
	sprintf(code[code_number].dest,"\0");
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("exit\n");
	sprintf(code[code_number].op,"jr");
	sprintf(code[code_number].dest,"$ra");
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("jr $ra\n");
	pop();
	return 0;
}

int syntax_function(sfunction pfunction,char *o)
{
	ssymbol_table table=new_table(pfunction->piden,label,pfunction->level);
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label);
	sprintf(code[code_number].op,"enter");
	sprintf(code[code_number].dest,"%s",pfunction->piden);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("enter %s\n",pfunction->piden);
	push(table);
	label++;
	if(pfunction->type)
		syntax_virtualtable(pfunction->pvirtualtable,pfunction->piden);
	add_function(pfunction,o);
	add_return(pfunction->piden,pfunction->piden);
	return 0;
}

int syntax_procedure(sprocedure pprocedure,char *o)
{
	ssymbol_table table=new_table(pprocedure->piden,label,pprocedure->level);
	sprintf(code[code_number].op,"label");
	sprintf(code[code_number].dest,"%d",label);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("label%d:\n",label);
	sprintf(code[code_number].op,"enter");
	sprintf(code[code_number].dest,"%s",pprocedure->piden);
	strcpy(code[code_number].src1,"\0");
	strcpy(code[code_number].src2,"\0");
	code_number++;
	printf("enter %s\n",pprocedure->piden);
	add_procedure(pprocedure,o);
	push(table);
	label++;
	if(pprocedure->type)
		syntax_virtualtable(pprocedure->pvirtualtable,pprocedure->piden);
	return 0;
}

int syntax_virtualtable(svirtualtable pvirtualtable,char *o)
{
	int i;
	add_para(pvirtualtable->pvirtuallist,o);
	for(i=0;i<pvirtualtable->pvirtuallist->num;i++){
		if(pvirtualtable->pvirtuallist->var)
			sprintf(code[code_number].op,"getvar");
		else
			sprintf(code[code_number].op,"get");
		sprintf(code[code_number].dest,"%s:%s",o,pvirtualtable->pvirtuallist->piden[i]);
		strcpy(code[code_number].src1,"\0");
		strcpy(code[code_number].src2,"\0");
		code_number++;
		if(pvirtualtable->pvirtuallist->var)
			printf("getvar %s:%s\n",o,pvirtualtable->pvirtuallist->piden[i]);
		else
			printf("get %s:%s\n",o,pvirtualtable->pvirtuallist->piden[i]);
	}
	if(pvirtualtable->pvirtualtable)
		syntax_virtualtable(pvirtualtable->pvirtualtable,o);
	return 0;
}

int syntax_callprocedure(scallprocedure pcallprocedure,char *o)
{
	int n=0,i;
	call_number=0;
	if(pcallprocedure->prealtable!=NULL)
		syntax_realtable(pcallprocedure->prealtable,pcallprocedure->piden,o,&n);
	sprintf(code[code_number].op,"call");
	sprintf(code[code_number].dest,"%s",pcallprocedure->piden);
	sprintf(code[code_number].src1,"%s",o);
	sprintf(code[code_number].src2,"\0",o);
	code_number++;
	printf("call %s %s\n",pcallprocedure->piden,o);
	for(i=0;i<call_number;i++){
		sprintf(code[code_number].op,call_code[i].op);
		sprintf(code[code_number].dest,"%s",call_code[i].dest);
		sprintf(code[code_number].src1,"%s",call_code[i].src1);
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("%s %s %s\n",call_code[i].op,call_code[i].dest,call_code[i].src1);
	}
	sprintf(code[code_number].op,"jal");
	sprintf(code[code_number].dest,"%d",find(pcallprocedure->piden)->value);
	sprintf(code[code_number].src1,"\0");
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("jal label%d\n",find(pcallprocedure->piden)->value);
	sprintf(code[code_number].op,"recover");
	sprintf(code[code_number].dest,"\0");
	sprintf(code[code_number].src1,"\0");
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("recover\n");
	return 0;
}

int syntax_callfunction(scallfunction pcallfunction,char *o)
{
	int n=0,i;
	call_number=0;
	if(pcallfunction->prealtable!=NULL)
		syntax_realtable(pcallfunction->prealtable,pcallfunction->piden,o,&n);
	sprintf(code[code_number].op,"call");
	sprintf(code[code_number].dest,"%s",pcallfunction->piden);
	sprintf(code[code_number].src1,"%s",o);
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("call %s %s\n",pcallfunction->piden,o);
	for(i=0;i<call_number;i++){
		sprintf(code[code_number].op,call_code[i].op);
		sprintf(code[code_number].dest,"%s",call_code[i].dest);
		sprintf(code[code_number].src1,"%s",call_code[i].src1);
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("%s %s %s\n",call_code[i].op,call_code[i].dest,call_code[i].src1);
	}
	sprintf(code[code_number].op,"jal");
	sprintf(code[code_number].dest,"%d",find(pcallfunction->piden)->value);
	sprintf(code[code_number].src1,"\0");
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("jal label%d\n",find(pcallfunction->piden)->value);
	sprintf(code[code_number].op,"recover");
	sprintf(code[code_number].dest,"\0");
	sprintf(code[code_number].src1,"\0");
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("recover\n");
	sprintf(code[code_number].op,"getre");
	sprintf(code[code_number].dest,"gp:%d",temp);
	sprintf(code[code_number].src1,"\0");
	sprintf(code[code_number].src2,"\0");
	code_number++;
	printf("getre gp:%d\n",temp);
	return 0;
}

int syntax_realtable(srealtable prealtable,char *s,char *o,int *n)
{
	int temp1,k;
	(*n)++;
	k=*n;
	if(prealtable->prealtable!=NULL)
		syntax_realtable(prealtable->prealtable,s,o,n);
	if(find(s)->s[k-1].orvar==3){
		if(prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->type==1){
			sprintf(call_code[call_number].op,"pushvar");
			sprintf(call_code[call_number].dest,"%s:%s",search_table(o,prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->piden)->name,prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->piden);
			sprintf(call_code[call_number].src1,"\0");
			sprintf(call_code[call_number].src2,"\0");
			call_number++;
		}
		else if(prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->type==2){
			syntax_expression(prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->pexpression,o);
			temp1=temp++;
			sprintf(code[code_number].op,"muli");
			sprintf(code[code_number].dest,"gp:%d",temp1);
			sprintf(code[code_number].src1,"gp:%d",temp1);
			sprintf(code[code_number].src2,"4");
			code_number++;
			printf("muli gp:%d gp:%d 4\n",temp1,temp1);
			sprintf(call_code[call_number].op,"pushvar");
			sprintf(call_code[call_number].dest,"%s:%s",search_table(o,prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->piden)->name,prealtable->pexpression->ptermlist->pterm->pfactorlist->pfactor->piden);
			sprintf(call_code[call_number].src1,"gp:%d",temp1);
			sprintf(call_code[call_number].src2,"\0");
			call_number++;
		}
		else{
			while(1)
				;
		}
	}
	else if(find(s)->s[k-1].orvar==2){
		syntax_expression(prealtable->pexpression,o);
		temp1=temp++;
		sprintf(call_code[call_number].op,"push");
		sprintf(call_code[call_number].dest,"gp:%d",temp1);
		sprintf(call_code[call_number].src1,"\0");
		sprintf(call_code[call_number].src2,"\0");
		call_number++;
	}
	else 
		err(10,0,find(s)->s[k-1].name);
	return 0;
}

int syntax_writestatement(swritestatement pwritestatement,char *o)
{
	switch(pwritestatement->type){
	case 1:
		sprintf(code[code_number].op,"writestr");
		sprintf(code[code_number].dest,"%s",pwritestatement->pstring);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("writestr %s\n",pwritestatement->pstring);
		syntax_expression(pwritestatement->pexpression,o);
		sprintf(code[code_number].op,"write");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("write gp:%d\n",temp);
		temp++;
		break;
	case 2:
		sprintf(code[code_number].op,"writestr");
		sprintf(code[code_number].dest,"%s",pwritestatement->pstring);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("writestr %s\n",pwritestatement->pstring);
		break;
	case 3:
		syntax_expression(pwritestatement->pexpression,o);
		sprintf(code[code_number].op,"write");
		sprintf(code[code_number].dest,"gp:%d",temp);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("write gp:%d\n",temp);
		temp++;
		break;
	}
}

int syntax_readstatement(sreadstatement preadstatement,char *o)
{
	int i;
	for(i=0;i<preadstatement->num;i++){
		sprintf(code[code_number].op,"read");
		sprintf(code[code_number].dest,"%s:%s",search_table(o,preadstatement->piden[i])->name,preadstatement->piden[i]);
		sprintf(code[code_number].src1,"\0");
		sprintf(code[code_number].src2,"\0");
		code_number++;
		printf("read %s:%s\n",search_table(o,preadstatement->piden[i])->name,preadstatement->piden[i]);
	}
	return 0;
}