#include"lex.h"
#include"error.h"

char type[][10]={"const","integer","char","var","array","of",
	"if","then","else","do","while","for","to","by","downto","procedure",
	"function","read","write","call","begin","end"};
char name[][10]={"CONSTTK","INTTK","CHARTK","VARTK","ARRAYTK","OFTK",
	"IFTK","THENTK","ELSETK","DOTK","WHILETK","FORTK","TOTK","BYTK","DOWNTOTK","PROCETK",
	"FUNCTK","READTK","WRITETK","CALLTK","BEGINTK","ENDTK"};
int number=22;
int line=1;

int isdigit(char c)
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}

int isalpha(char c)
{
	if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
		return 1;
	else
		return 0;
}

int ischar(char c)
{
	if(((c>=35)&&(c<=126))||(c==32)||(c==33))
		return 1;
	else
		return 0;
}

int lexical()
{
	char filein[100],str[100],c;
	int i=1,j=0,n=0,error=1;
	FILE *out=fopen("lexical.txt","w");
	printf("Please type in the name of the  file:");
	scanf("%s",filein);
	freopen(filein,"r",stdin);
	while(scanf("%c",&c)!=EOF){
		if(c==' ')
			continue;
		else if(c=='\n'){
			line++;
			continue;
		}
		if(isalpha(c)){
			str[j++]=c;
			while(scanf("%c",&c)!=EOF){
				if(isalpha(c)||isdigit(c))
					str[j++]=c;
				else{
					str[j]='\0';
					for(n=0;n<22;n++)
						if(strcmp(str,type[n])==0)
							break;
					if(n==22)
						fprintf(out,"%d %d IDEN %s\n",i,line,str);
					else
						fprintf(out,"%d %d %s %s\n",i,line,name[n],str);
					ungetc(c,stdin);
					j=0;
					i++;
					break;
				}
			}
			continue;
		}
		if(isdigit(c)){
			str[j++]=c;
			while(scanf("%c",&c)!=EOF){
				if(isdigit(c))
					str[j++]=c;
				else{
					str[j]='\0';
					fprintf(out,"%d %d INTCON %s\n",i,line,str);
					ungetc(c,stdin);
					j=0;
					i++;
					break;
				}
			}
			continue;
		}
		if(c=='+')
			fprintf(out,"%d %d PLUS +\n",i++,line);
		else if(c=='-')
			fprintf(out,"%d %d MINU -\n",i++,line);
		else if(c=='*')
			fprintf(out,"%d %d MULT *\n",i++,line);
		else if(c=='/')
			fprintf(out,"%d %d DIV /\n",i++,line);
		else if(c=='.')
			fprintf(out,"%d %d PERIOD .\n",i++,line);
		else if(c=='(')
			fprintf(out,"%d %d LPARENT (\n",i++,line);
		else if(c==')')
			fprintf(out,"%d %d RPARENT )\n",i++,line);
		else if(c=='[')
			fprintf(out,"%d %d LBRACK [\n",i++,line);
		else if(c==']')
			fprintf(out,"%d %d RBRACK ]\n",i++,line);
		else if(c=='{')
			fprintf(out,"%d %d LBRACE {\n",i++,line);
		else if(c=='}')
			fprintf(out,"%d %d RBRACE }\n",i++,line);
		else if(c==';')
			fprintf(out,"%d %d SEMICN ;\n",i++,line);
		else if(c==',')
			fprintf(out,"%d %d COMMA ,\n",i++,line);
		else if(c=='=')
			fprintf(out,"%d %d EQL =\n",i++,line);
		else if(c==':'){
			scanf("%c",&c);
			if(c=='='){
				fprintf(out,"%d %d ASSIGN :=\n", i++,line);
				continue;
			}
			else{
 				fprintf(out,"%d %d COLON :\n",i++,line);
				ungetc(c,stdin);
				continue;
			}
		}
		else if(c=='<'){
			scanf("%c",&c);
			if(c=='='){
				fprintf(out,"%d %d LEQ <=\n",i++,line);
				continue;
			}
			else if(c=='>'){
				fprintf(out,"%d %d NEQ <>\n",i++,line);
				continue;
			}
			else{
				fprintf(out,"%d %d LSS <\n",i++,line);
				ungetc(c,stdin);
				continue;
			}
		}
		else if(c=='>'){
			scanf("%c",&c);
			if(c=='='){
				fprintf(out,"%d %d GEQ >=\n",i++,line);
				continue;
			}
			else{
				fprintf(out,"%d %d GRE >\n",i++,line);
				ungetc(c,stdin);
				continue;
			}
		}
		else if(c=='\''){
			scanf("%c",&c);
			if((!isdigit(c))&&(!isalpha(c))){
				err(1,line,"\0");
				goto label;
			}
			str[0]=c;
			str[1]='\0';
			scanf("%c",&c);
			if(c!='\''){
				err(2,line,"\0");
				goto label;
			}
			fprintf(out,"%d %d CHARCON %s\n",i++,line,str);
		}
		else if(c=='"'){
			while(error=scanf("%c",&c)!=EOF){
				if((!ischar(c))&&(c!='"'))
					error=0;
				if(c!='"')
					str[j++]=c;
				else{
					str[j]='\0';
					j=0;
					break;
				}
			}
			if(error==0){
				err(3,line,"\0");
				goto label;
			}
			fprintf(out,"%d %d STRCON %s\n",i++,line,str);
		}
	}
label:
	fclose(stdin);
	fclose(out);
	return 0;
}