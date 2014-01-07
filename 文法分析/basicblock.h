#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include"syntax.h"

typedef struct basicblock{
	int before[3];
	int follow[3];
}pbasicblock;

int basicblock();
#endif