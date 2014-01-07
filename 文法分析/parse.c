#include"lex.h"
#include"parse.h"
#include"error.h"

int n;
int parse_line;
char s[10];
char v[100];
int level=1;

svirtuallist dvirtuallist()
{
	int i=0;
	svirtuallist t=(svirtuallist)malloc(sizeof(avirtuallist));
	t->var=0;
	if(strcmp(s,"VARTK")==0){
		t->var=1;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden[i++],v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	while(strcmp(s,"COMMA")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"IDEN")!=0){
			err(11,parse_line,v);
		}
		strcpy(t->piden[i++],v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	if(strcmp(s,"COLON")!=0){
		err(12,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"INTTK")==0)
		t->type=0;
	else if(strcmp(s,"CHARTK")==0)
		t->type=1;
	else{
		err(13,parse_line,"\0");
	}
	t->num=i;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

svirtualtable dvirtualtable()
{
	svirtualtable t=(svirtualtable)malloc(sizeof(avirtualtable)),p,q;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pvirtuallist=dvirtuallist();
	t->pvirtualtable=NULL;
	p=t;
	while(strcmp(s,"SEMICN")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		q=(svirtualtable)malloc(sizeof(avirtualtable));
		p->pvirtualtable=q;
		q->pvirtuallist=dvirtuallist();
		q->pvirtualtable=NULL;
		p=q;
	}
	if(strcmp(s,"RPARENT")!=0){
		err(14,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sfunction dfunction()
{
	sfunction t=(sfunction)malloc(sizeof(afunction));
	t->type=0;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden,v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"LPARENT")==0){
		t->type=1;
		t->pvirtualtable=dvirtualtable();
	}
	else
		t->pvirtualtable=NULL;
	if(strcmp(s,"COLON")!=0){
		err(12,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"INTTK")==0)
		t->orchar=0;
	else if(strcmp(s,"CHARTK")==0)
		t->orchar=1;
	else{
		err(13,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	t->level=level;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sprocedure dprocedure()
{
	sprocedure t=(sprocedure)malloc(sizeof(aprocedure));
	t->type=0;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden,v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"LPARENT")==0){
		t->type=1;
		t->pvirtualtable=dvirtualtable();
	}
	else
		t->pvirtualtable=NULL;
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	t->level=level;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sproceduredeclare dproceduredeclare()
{
	sproceduredeclare t=(sproceduredeclare)malloc(sizeof(aproceduredeclare));
	level++;
	t->pprocedure=dprocedure();
	t->pblock=dblock();
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	level--;
	return t;
}

sfunctiondeclare dfunctiondeclare()
{
	sfunctiondeclare t=(sfunctiondeclare)malloc(sizeof(afunctiondeclare));
	level++;
	t->pfunction=dfunction();
	t->pblock=dblock();
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	level--;
	return t;
}

sprogramme dprogramme()
{
	sprogramme t=(sprogramme)malloc(sizeof(aprogramme));
	t->pblock=dblock();
	if(strcmp(s,"PERIOD")!=0)
		err(16,parse_line,"\0");
	return t;
}

sblock dblock()
{
	sblock t=(sblock)malloc(sizeof(ablock));
	if(strcmp(s,"CONSTTK")==0)
		t->pconstdeclare=dconstdeclare();
	else
		t->pconstdeclare=NULL;
	if(strcmp(s,"VARTK")==0)
		t->pvardeclare=dvardeclare();
	else
		t->pvardeclare=NULL;
	if((strcmp(s,"PROCETK")==0)||(strcmp(s,"FUNCTK")==0))
		t->ppflist=dpflist();
	else 
		t->ppflist=NULL;
	if(strcmp(s,"BEGINTK")==0)
		t->pcomplexstatement=dcomplexstatement();
	else {
		err(17,parse_line,"\0");
		t->pcomplexstatement=NULL;
	}
	return t;
}

spf dpf()
{
	spf t=(spf)malloc(sizeof(apf));
	if(strcmp(s,"PROCETK")==0){
		t->type=0;
		t->pproceduredeclare=dproceduredeclare();
		t->pfunctiondeclare=NULL;
	}
	else if(strcmp(s,"FUNCTK")==0){
		t->type=1;
		t->pproceduredeclare=NULL;
		t->pfunctiondeclare=dfunctiondeclare();
	}
	return t;
}

spflist dpflist()
{
	spflist t=(spflist)malloc(sizeof(apflist)),p,q;
	t->ppf=dpf();
	t->ppflist=NULL;
	p=t;
	while((strcmp(s,"PROCETK")==0)||(strcmp(s,"FUNCTK")==0)){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		q=(spflist)malloc(sizeof(apflist));
		p->ppflist=q;
		q->ppf=dpf();
		q->ppflist=NULL;
		p=q;
	}
	return t;
}

sconstdeclare dconstdeclare()
{
	sconstdeclare t,p,q;
	t=(sconstdeclare)malloc(sizeof(aconstdeclare));
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pconstdefine=dconstdefine();
	t->pconstdeclare=NULL;
	p=t;
	while(strcmp(s,"COMMA")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		q=(sconstdeclare)malloc(sizeof(aconstdeclare));
		p->pconstdeclare=q;
		q->pconstdefine=dconstdefine();
		q->pconstdeclare=NULL;
		p=q;
	}
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sconstdefine dconstdefine()
{
	char sl[100];
	sconstdefine t=(sconstdefine)malloc(sizeof(aconstdefine));
	strcpy(sl,v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"EQL")!=0){
		err(18,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"CHARCON")==0){
		strcpy(t->piden,sl);
		t->type=1;
		t->pint=0;
		t->pchar=v[0];
	}
	else if(strcmp(s,"PLUS")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"INTCON")!=0){
			err(19,parse_line,v);
		}
		strcpy(t->piden,sl);
		t->type=0;
		t->pchar=0;
		t->pint=atoi(v);
	}
	else if(strcmp(s,"INTCON")==0){
		strcpy(t->piden,sl);
		t->type=0;
		t->pchar=0;
		t->pint=atoi(v);
	}
	else if(strcmp(s,"MINUS")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"INTCON")!=0){
			err(19,parse_line,v);
		}
		strcpy(t->piden,sl);
		t->type=0;
		t->pchar=0;
		t->pint=-atoi(v);
	}
	else{
		err(20,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

svardeclare dvardeclare()
{
	svardeclare t,p,q;
	t=(svardeclare)malloc(sizeof(avardeclare));
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pvardefine=dvardefine();
	t->pvardeclare=NULL;
	p=t;
	if(strcmp(s,"SEMICN")!=0){
		err(15,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	while(strcmp(s,"IDEN")==0){
		q=(svardeclare)malloc(sizeof(avardeclare));
		p->pvardeclare=q;
		q->pvardefine=dvardefine();
		q->pvardeclare=NULL;
		p=q;
		if(strcmp(s,"SEMICN")==0){
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
			continue;
		}
		else{
			err(15,parse_line,"\0");
		}
	}
	return t;
}

svardefine dvardefine()
{
	int i=0;
	svardefine t=(svardefine)malloc(sizeof(avardefine));
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden[i++],v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	while(strcmp(s,"COMMA")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"IDEN")!=0){
			err(11,parse_line,v);
		}
		strcpy(t->piden[i++],v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	t->num=i;
	if(strcmp(s,"COLON")!=0){
		err(12,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"ARRAYTK")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"LBRACK")!=0){
			err(21,parse_line,"\0");
		}
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"INTCON")!=0){
			err(19,parse_line,v);
		}
		t->lenth=atoi(v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"RBRACK")!=0){
			err(22,parse_line,"\0");
		}
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"OFTK")!=0){
			err(23,parse_line,"\0");
		}
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"INTTK")==0)
			t->type=0;
		else if(strcmp(s,"CHARTK")==0)
			t->type=1;
		else{
			err(20,parse_line,"\0");
		}
	}
	else if(strcmp(s,"INTTK")==0){
		t->type=0;
		t->lenth=0;
	}
	else if(strcmp(s,"CHARTK")==0){
		t->type=1;
		t->lenth=0;
	}
	else{
		err(20,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

scomplexstatement dcomplexstatement()
{
	scomplexstatement t=(scomplexstatement)malloc(sizeof(acomplexstatement));
	if(strcmp(s,"BEGINTK")!=0){
		err(17,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pstatementlist=dstatementlist();
	if(strcmp(s,"ENDTK")!=0){
		err(24,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sassignstatement dassignstatement(char *sl,sexpression sd)
{
	sassignstatement t=(sassignstatement)malloc(sizeof(aassignstatement));
	strcpy(t->piden,sl);
	t->type=0;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pnexpression=sd;
	if(sd!=NULL)
		t->type=1;
	t->pexpression=dexpression();
	return t;
}

sexpression dexpression()
{
	sexpression t=(sexpression)malloc(sizeof(aexpression));
	stermlist a=(stermlist)malloc(sizeof(atermlist)),p=NULL;
	spluslist b=NULL,q=NULL,c=NULL;
	splus x=NULL;
	t->revert=0;
	if(strcmp(s,"MINU")==0){
		t->revert=1;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	else if(strcmp(s,"PLUS")==0)
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	a->pterm=dterm();
	a->ptermlist=NULL;
	p=a;
	if((strcmp(s,"MINU")==0)||(strcmp(s,"PLUS")==0)){
		b=(spluslist)malloc(sizeof(apluslist));
		q=b;
		x=(splus)malloc(sizeof(aplus));
		if(strcmp(s,"MINU")==0)
			x->type=0;
		if(strcmp(s,"PLUS")==0)
			x->type=1;
		q->pplus=x;
		q->ppluslist=NULL;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		p->ptermlist=(stermlist)malloc(sizeof(atermlist));
		p=p->ptermlist;
		p->pterm=dterm();
		p->ptermlist=NULL;
	}
	while((strcmp(s,"MINU")==0)||(strcmp(s,"PLUS")==0)){
		x=(splus)malloc(sizeof(aplus));
		if(strcmp(s,"MINU")==0)
			x->type=0;
		if(strcmp(s,"PLUS")==0)
			x->type=1;
		c=(spluslist)malloc(sizeof(apluslist));
		c->pplus=x;
		c->ppluslist=NULL;
		q->ppluslist=c;
		q=q->ppluslist;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		p->ptermlist=(stermlist)malloc(sizeof(atermlist));
		p=p->ptermlist;
		p->pterm=dterm();
		p->ptermlist=NULL;
	}
	t->ptermlist=a;
	t->ppluslist=b;
	return t;
}

sterm dterm()
{
	sterm t=(sterm)malloc(sizeof(aterm));
	sfactorlist a=(sfactorlist)malloc(sizeof(afactorlist)),p=NULL;
	smullist b=NULL,q=NULL,c=NULL;
	smulti x=NULL;
	a->pfactor=dfactor();
	a->pfactorlist=NULL;
	p=a;
	if((strcmp(s,"MULT")==0)||(strcmp(s,"DIV")==0)){
		b=(smullist)malloc(sizeof(amullist));
		q=b;
		x=(smulti)malloc(sizeof(amulti));
		if(strcmp(s,"DIV")==0)
			x->type=0;
		if(strcmp(s,"MULT")==0)
			x->type=1;
		q->pmul=x;
		q->pmullist=NULL;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		p->pfactorlist=(sfactorlist)malloc(sizeof(afactorlist));
		p=p->pfactorlist;
		p->pfactor=dfactor();
		p->pfactorlist=NULL;
	}
	while((strcmp(s,"MULT")==0)||(strcmp(s,"DIV")==0)){
		x=(smulti)malloc(sizeof(amulti));
		if(strcmp(s,"DIV")==0)
			x->type=0;
		if(strcmp(s,"MULT")==0)
			x->type=1;
		c=(smullist)malloc(sizeof(amullist));
		c->pmul=x;
		c->pmullist=NULL;
		q->pmullist=c;
		q=q->pmullist;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		p->pfactorlist=(sfactorlist)malloc(sizeof(afactorlist));
		p=p->pfactorlist;
		p->pfactor=dfactor();
		p->pfactorlist=NULL;
	}
	t->pfactorlist=a;
	t->pmullist=b;
	return t;
}

sconditionstatement dconditionstatement()
{
	sconditionstatement t=(sconditionstatement)malloc(sizeof(aconditionstatement));
	t->pstatement1=NULL;
	t->pstatement2=NULL;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pcondition=dcondition();
	t->type=0;
	if(strcmp(s,"THENTK")!=0){
		err(25,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pstatement1=dstatement();
	if(strcmp(s,"ELSETK")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		t->pstatement2=dstatement();
		t->type=1;
	}
	return t;
}

scondition dcondition()
{
	scondition t=(scondition)malloc(sizeof(acondition));
	t->pexpression1=dexpression();
	if(strcmp(s,"LSS")==0)
		t->type=1;
	else if(strcmp(s,"LEQ")==0)
		t->type=2;
	else if(strcmp(s,"GRE")==0)
		t->type=3;
	else if(strcmp(s,"GEQ")==0)
		t->type=4;
	else if(strcmp(s,"EQL")==0)
		t->type=5;
	else if(strcmp(s,"NEQ")==0)
		t->type=6;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pexpression2=dexpression();
	return t;
}

swhilestatement dwhilestatement()
{
	swhilestatement t=(swhilestatement)malloc(sizeof(awhilestatement));
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pcondition=dcondition();
	if(strcmp(s,"DOTK")!=0){
		err(26,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pstatement=dstatement();
	return t;
}

sforstatement dforstatement()
{
	sforstatement t=(sforstatement)malloc(sizeof(aforstatement));
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden,v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"ASSIGN")!=0){
		err(27,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pexpression1=dexpression();
	if((strcmp(s,"TOTK")!=0)&&(strcmp(s,"DOWNTK")!=0)){
		err(28,parse_line,"\0");
	}
	if(strcmp(s,"TOTK")==0)
		t->type=0;
	else
		t->type=1;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pexpression2=dexpression();
	if(strcmp(s,"DOTK")!=0){
		err(26,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pstatement=dstatement();
	return t;
}

srealtable drealtable()
{
	srealtable t=(srealtable)malloc(sizeof(arealtable)),p=NULL,q=NULL;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->pexpression=dexpression();
	t->prealtable=NULL;
	p=t;
	while(strcmp(s,"COMMA")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		q=(srealtable)malloc(sizeof(arealtable));
		p->prealtable=q;
		q->pexpression=dexpression();
		q->prealtable=NULL;
		p=q;
	}
	if(strcmp(s,"RPARENT")!=0){
		err(14,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

scallprocedure dcallprocedure(char *sl)
{
	scallprocedure t=(scallprocedure)malloc(sizeof(acallprocedure));
	strcpy(t->piden,sl);
	if(strcmp(s,"LPARENT")==0)
		t->prealtable=drealtable();
	else
		t->prealtable=NULL;
	return t;
}

sreadstatement dreadstatement()
{
	int i=0;
	sreadstatement t=(sreadstatement)malloc(sizeof(areadstatement));
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"LPARENT")!=0){
		err(29,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"IDEN")!=0){
		err(11,parse_line,v);
	}
	strcpy(t->piden[i++],v);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	while(strcmp(s,"COMMA")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"IDEN")!=0){
			err(11,parse_line,v);
		}
		strcpy(t->piden[i++],v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	if(strcmp(s,"RPARENT")!=0){
		err(14,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	t->num=i;
	return t;
}

swritestatement dwritestatement()
{
	swritestatement t=(swritestatement)malloc(sizeof(awritestatement));
	t->type=0;
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	if(strcmp(s,"LPARENT")!=0){
		err(29,parse_line,"\0");
	}
	scanf("%d",&n);
	scanf("%d",&parse_line);
	scanf("%s",&s);
	scanf("%c",&v);
	gets(v);
	if(strcmp(s,"STRCON")==0){
		t->type=2;
		strcpy(t->pstring,v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	    if(strcmp(s,"COMMA")==0){
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
			t->type=1;
			t->pexpression=dexpression();
		}
	}
	else{
		t->type=3;
		t->pexpression=dexpression();
	}
	if(strcmp(s,"RPARENT")!=0){
		err(14,parse_line,"\0");
	}
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	return t;
}

sstatement dstatement()
{
	char sl[100],sr[100];
	sstatement t=(sstatement)malloc(sizeof(astatement));
	sexpression sd=NULL;
	t->type=0;
	t->passignstatement=NULL;
	t->pconditionstatement=NULL;
	t->pcomplexstatement=NULL;
	t->pforstatement=NULL;
	t->preadstatement=NULL;
	t->pwhilestatement=NULL;
	t->pcallprocedure=NULL;
	t->pwritestatement=NULL;
	if(strcmp(s,"IDEN")==0){
		strcpy(sl,s);
		strcpy(sr,v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"ASSIGN")==0){
			t->type=1;
			t->passignstatement=dassignstatement(sr,NULL);
		}
		else if(strcmp(s,"LBRACK")==0){
			t->type=1;
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
			sd=dexpression();
			if(strcmp(s,"RBRACK")!=0){
				err(22,parse_line,"\0");
			}
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
			t->passignstatement=dassignstatement(sr,sd);
		}
		else{
			t->type=4;
			t->pcallprocedure=dcallprocedure(sr);
		}
	}
	else if(strcmp(s,"IFTK")==0){
		t->type=2;
		t->pconditionstatement=dconditionstatement();
	}
	else if(strcmp(s,"WHILETK")==0){
		t->type=3;
		t->pwhilestatement=dwhilestatement();
	}
	else if(strcmp(s,"BEGINTK")==0){
		t->type=5;
		t->pcomplexstatement=dcomplexstatement();
	}
	else if(strcmp(s,"READTK")==0){
		t->type=6;
		t->preadstatement=dreadstatement();
	}
	else if(strcmp(s,"WRITETK")==0){
		t->type=7;
		t->pwritestatement=dwritestatement();
	}
	else if(strcmp(s,"FORTK")==0){
		t->type=8;
		t->pforstatement=dforstatement();
	}
	return t;
}

sstatementlist dstatementlist()
{
	sstatementlist t=(sstatementlist)malloc(sizeof(astatementlist)),p,q;
	t->pstatement=dstatement();
	t->pstatementlist=NULL;
	p=t;
	while(strcmp(s,"SEMICN")==0){
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		q=(sstatementlist)malloc(sizeof(astatement));
		p->pstatementlist=q;
		q->pstatement=dstatement();
		q->pstatementlist=NULL;
		p=q;
	}
	return t;
}

scallfunction dcallfunction(char *sl)
{
	scallfunction t=(scallfunction)malloc(sizeof(acallfunction));
	strcpy(t->piden,sl);
	t->prealtable=drealtable();
	return t;
}

sfactor dfactor()
{
	char sl[100];
	sfactor t=(sfactor)malloc(sizeof(afactor));
	t->pexpression=NULL;
	t->pcallfunction=NULL;
	if(strcmp(s,"LPARENT")==0){
		t->type=4;
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		t->pexpression=dexpression();
		if(strcmp(s,"RPARENT")!=0){
			err(14,parse_line,"\0");
		}
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	else if(strcmp(s,"INTCON")==0){
		t->type=3;
		t->pnumber=atoi(v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	}
	else if(strcmp(s,"IDEN")==0){
		strcpy(sl,v);
		scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		if(strcmp(s,"LBRACK")==0){
			t->type=2;
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
			strcpy(t->piden,sl);
			t->pexpression=dexpression();
			if(strcmp(s,"RBRACK")!=0){
				err(22,parse_line,"\0");
			}
			scanf("%d%d%s%s",&n,&parse_line,&s,&v);
		}
		else if(strcmp(s,"LPARENT")==0){
			t->type=5;
			t->pcallfunction=dcallfunction(sl);
		}
		else{
			t->type=1;
			strcpy(t->piden,sl);
		}
	}
	else
		err(11,parse_line,v);
	return t;
}

sprogramme parse()
{
	sprogramme result;
	lexical();
	freopen("lexical.txt","r",stdin);
	scanf("%d%d%s%s",&n,&parse_line,&s,&v);
	result=dprogramme();
	return result;
}