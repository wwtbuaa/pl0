#include"interpreter.h"
#include"basicblock.h"

int main()
{
	sprogramme result=parse();
	syntax(result,"main");
	printf("\n\n");
	interpreter();
	return 0;
}