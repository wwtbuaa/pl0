#ifndef INTER_H
#define INTER_H

#include<stdio.h>
#include<string.h>
#include"syntax.h"

int interpreter();
int inter_j(asyntax_code in,FILE *out);
int inter_label(asyntax_code in,FILE *out);
int inter_get(asyntax_code in,FILE *out);
int inter_push(asyntax_code in,FILE *out);
int add_offset();
int split(char s[],char s1[],char s2[]);
int inter_write(asyntax_code in,FILE *out);
int inter_add(asyntax_code in,FILE *out);
int inter_addi(asyntax_code in,FILE *out);
int inter_muli(asyntax_code in,FILE *out);
int inter_writestr(asyntax_code in,FILE *out);
int inter_read(asyntax_code in,FILE *out);
int inter_lw(asyntax_code in,FILE *out);
int inter_sw(asyntax_code in,FILE *out);
int inter_sub(asyntax_code in,FILE *out);
int inter_bgez(asyntax_code in,FILE *out);
int inter_bgtz(asyntax_code in,FILE *out);
int inter_beq(asyntax_code in,FILE *out);
int inter_bne(asyntax_code in,FILE *out);
int inter_call(asyntax_code in,FILE *out);
int inter_get_return(asyntax_code in,FILE *out);
int inter_mul(asyntax_code in,FILE *out);
int inter_ret(asyntax_code in,FILE *out);
int inter_exit(asyntax_code in,FILE *out);
int inter_popst(asyntax_code in,FILE *out);
int inter_pushst(asyntax_code in,FILE *out);
int inter_div(asyntax_code in,FILE *out);

//$s0 is used for passing parameters; 
//$s1 is used for finding the address;
//$s2 is used for return address;
//$s3 is used for last $sp;
//$s4 is used for last $fp;
//$t0,$t1,$t2,$t3 is used for computing;
#endif