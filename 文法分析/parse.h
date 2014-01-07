#ifndef PARSE_H
#define PARSE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct programme *sprogramme,aprogramme;
typedef struct block *sblock,ablock;
typedef struct constdeclare *sconstdeclare,aconstdeclare;
typedef struct constdefine *sconstdefine,aconstdefine;
typedef struct vardefine *svardefine,avardefine;
typedef struct vardeclare *svardeclare,avardeclare;
typedef struct proceduredeclare *sproceduredeclare,aproceduredeclare;
typedef struct functiondeclare *sfunctiondeclare,afunctiondeclare;
typedef struct procedure *sprocedure,aprocedure;
typedef struct function *sfunction,afunction;
typedef struct virtuallist *svirtuallist,avirtuallist;
typedef struct virtualtable *svirtualtable,avirtualtable;
typedef struct statement *sstatement,astatement;
typedef struct complexstatement *scomplexstatement,acomplexstatement;
typedef struct pflist *spflist,apflist;
typedef struct pf *spf,apf;
typedef struct statementlist *sstatementlist,astatementlist;
typedef struct statement *sstatement,astatement;
typedef struct assignstatement *sassignstatement,aassignstatement;
typedef struct conditionstatement *sconditionstatement,aconditionstatement;
typedef struct whilestatement *swhilestatement,awhilestatement;
typedef struct forstatement *sforstatement,aforstatement;
typedef struct callprocedure *scallprocedure,acallprocedure;
typedef struct readstatement *sreadstatement,areadstatement;
typedef struct writestatement *swritestatement,awritestatement;
typedef struct expression *sexpression,aexpression;
typedef struct term *sterm,aterm;
typedef struct termlist *stermlist,atermlist;
typedef struct plus *splus,aplus;
typedef struct pluslist *spluslist,apluslist;
typedef struct factor *sfactor,afactor;
typedef struct multi *smulti,amulti;
typedef struct factorlist *sfactorlist,afactorlist;
typedef struct mullist *smullist,amullist;
typedef struct realtable *srealtable,arealtable;
typedef struct condition *scondition,acondition;
typedef struct callfunction *scallfunction,acallfunction;

sprogramme parse();
sprogramme dprogramme();
sblock dblock();
sconstdeclare dconstdeclare();
sconstdefine dconstdefine();
svardeclare dvardeclare();
svardefine dvardefine();
sproceduredeclare dproceduredeclare();
sfunctiondeclare dfunctiondeclare();
sprocedure dprocedure();
sfunction dfunction();
spflist dpflist();
scomplexstatement dcomplexstatement();
sstatementlist dstatementlist();
sstatement dstatement();
sassignstatement dassignstatement(char *sl,sexpression sd);
sexpression dexpression();
sterm dterm();
sfactor dfactor();
spf dpf();
svirtuallist dvirtuallist();
svirtualtable dvirtualtable();
sconditionstatement dconditionstatement();
scondition dcondition();
swhilestatement dwhilestatement();
sforstatement dforstatement();
scallprocedure dcallprocedure(char *sl);
scallfunction dcallfunction(char *sl);
srealtable drealtable();
sreadstatement dreadstatement();
swritestatement dwritestatement();

typedef struct programme{
	sblock pblock;
};

typedef struct block{
	sconstdeclare pconstdeclare;
	svardeclare pvardeclare;
	spflist ppflist;
	scomplexstatement pcomplexstatement;
};

typedef struct constdeclare{
	sconstdefine pconstdefine;
	sconstdeclare pconstdeclare;
};

typedef struct vardeclare{
	svardefine pvardefine;
	svardeclare pvardeclare;
};

typedef struct pflist{
	spf ppf;
	spflist ppflist;
};

typedef struct pf{
	int type;//type=0 procedure, type=1 function
	sproceduredeclare pproceduredeclare;
	sfunctiondeclare pfunctiondeclare;
}
;
typedef struct constdefine{
	char piden[10];
	int type;//type=0 int;type=1 char
	int pint;
	char pchar;
};

typedef struct vardefine{
	char piden[10][10];
	int type;
	int lenth;
	int num;
};

typedef struct complexstatement{
	sstatementlist pstatementlist;
};

typedef struct statementlist{
	sstatement pstatement;
	sstatementlist pstatementlist;
};

typedef struct statement{
	int type;
	sassignstatement passignstatement;//type=1
	sconditionstatement pconditionstatement;//type=2
	swhilestatement pwhilestatement;//type=3
	scallprocedure pcallprocedure;//type=4
	scomplexstatement pcomplexstatement;//type=5
	sreadstatement preadstatement;//type=6;
	swritestatement pwritestatement;//type=7
	sforstatement pforstatement;//type=8
};

typedef struct assignstatement{
	int type;//type=0 no array,type=1 array
	char piden[10];
	sexpression pnexpression;
	sexpression pexpression;
};

typedef struct conditionstatement{
	int type;//0 no else, 1 else
	scondition pcondition;
	sstatement pstatement1;
	sstatement pstatement2;
};

typedef struct whilestatement{
	scondition pcondition;
	sstatement pstatement;
};

typedef struct expression{
	int revert;
	stermlist ptermlist;
	spluslist ppluslist; //+ 1,- 0
};

typedef struct termlist{
	sterm pterm;
	stermlist ptermlist;
};

typedef struct term{
	sfactorlist pfactorlist;
	smullist pmullist;//* 1,/ 0
};

typedef struct pluslist{
	splus pplus;
	spluslist ppluslist;
};

typedef struct plus{
	int type;
};

typedef struct factorlist{
	sfactor pfactor;
	sfactorlist pfactorlist;
};

typedef struct factor{
	int type;
	char piden[10];
	sexpression pexpression;
	scallfunction pcallfunction;
	int pnumber;
};

typedef struct mullist{
	smulti pmul;
	smullist pmullist;
};

typedef struct multi{
	int type;
};

typedef struct proceduredeclare{
	sprocedure pprocedure;
	sblock pblock;
};

typedef struct functiondeclare{
	sfunction pfunction;
	sblock pblock;
};

typedef struct procedure{
	int type;//type=0 no;type=1 yes
	char piden[10];
	int level;
	svirtualtable pvirtualtable;
};

typedef struct virtualtable{
	svirtuallist pvirtuallist;
	svirtualtable pvirtualtable;
};

typedef struct virtuallist{
	int num;
	int type;
	int var;
	char piden[10][10];
};

typedef struct function{
	int type;
	int orchar;//int 0,char 1
	char piden[10];
	int level;
	svirtualtable pvirtualtable;
};

typedef struct condition{
	int type;//< 1,<= 2,> 3,>= 4,= 5,<> 6
	sexpression pexpression1;
	sexpression pexpression2;
};

typedef struct forstatement{
	char piden[10];
	sexpression pexpression1;
	sexpression pexpression2;
	sstatement pstatement;
	int type;//0 to,1 downto
};

typedef struct callprocedure{
	char piden[10];
	srealtable prealtable;
};

typedef struct realtable{
	sexpression pexpression;
	srealtable prealtable;
};

typedef struct readstatement{
	int num;
	char piden[10][10];
};

typedef struct writestatement{
	int type;
	sexpression pexpression;
	char pstring[100];
};

typedef struct callfunction{
	char piden[10];
	srealtable prealtable;
};

#endif