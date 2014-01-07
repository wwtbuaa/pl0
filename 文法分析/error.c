#include"error.h"

int err(int n,int l,char s[]){
	switch(n){
	case 1:
		printf("There is nochar in the charcon! %d \n ",l);
		break;
	case 2:
		printf("There is more than one char in the charcon! %d \n",l);
		break;
	case 3:
		printf("The string has not been completed! %d \n",l);
		break;
	case 4:
		printf("Could not find the symbol table! %s\n",s);
		break;
	case 5:
		printf("The variable has been defined! %s\n",s);
		break;
	case 6:
		printf("The variable could not been found! %s\n",s);
		break;
	case 7:
		printf("A const is assigned! %s\n",s);
		break;
	case 8:
		printf("The variable is not an array %s!\n",s);
		break;
	case 9:
		printf("The number of parameters is not right!\n");
		break;
	case 10:
		printf("The parameter is not a varible! %s\n",s);
		break;
	case 11:
		printf("The string is not a identity! %d %s\n",l,s);
		break;
	case 12:
		printf("There is not a colon! %d\n",l);
		break;
	case 13:
		printf("This is not a right type! %d\n",l);
		break;
	case 14:
		printf("There needs a rparent! %d\n",l);
		break;
	case 15:
		printf("There needs a semicn! %d\n",l);
		break;
	case 16:
		printf("There needs a period! %d\n",l);
		break;
	case 17:
		printf("There needs a begin! %d\n",l);
		break;
	case 18:
		printf("There needs a =! %d\n",l);
		break;
	case 19:
		printf("This variable is not a integer! %d %s\n",l,s);
		break;
	case 20:
		printf("There needs a chartk or vartk! %d\n",l);
		break;
	case 21:
		printf("There needs a lbrack! %d\n",l);
		break;
	case 22:
		printf("There needs a rbrack! %d\n",l);
		break;
	case 23:
		printf("There needs a if! %d\n",l);
		break;
	case 24:
		printf("There needs a end! %d\n",l);
		break;
	case 25:
		printf("There needs a then! %d\n",l);
		break;
	case 26:
		printf("There needs a do! %d\n",l);
		break;
	case 27:
		printf("There needs a assign! %d\n",l);
		break;
	case 28:
		printf("There needs a to!%d\n",l);
		break;
	case 29:
		printf("There needs a lparent!%d\n",l);
	}
	while(1)
		;
	return 0;
}