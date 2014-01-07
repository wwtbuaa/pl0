#include"basicblock.h"

typedef struct dag{
	int op; //0 +,1 -,2 *,3 /
	int left;
	int right;
}bdag,*pdag;