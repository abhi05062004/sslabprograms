#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
char label[20],opcode[20],operand[20],code[20];
int length,start,locctr;
FILE *fp1,*fp2,*fp3,*fp4;
fp1=fopen("input.dat","r");
fp2=fopen("symtab.dat","w");
fp3=fopen("output.dat","w");
fp4=fopen("optab.dat","r");
fscanf(fp1,"%s%s%s",label,opcode,operand);
if(strcmp(opcode,"START")==0)
{
start=atoi(operand);
locctr=start;
fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
else
locctr=0;
while(strcmp(opcode,"END")!=0)
{
fprintf(fp3,"%d\t",locctr);
if(strcmp(label,"**")!=0)
{
fprintf(fp2,"%s\t%d\n",label,locctr);
}
rewind(fp4);
fscanf(fp4,"%s",code);
while(strcmp(code,"END")!=0)
{
if(strcmp(opcode,code)==0)
{
locctr+=3;
break;
}
fscanf(fp4,"%s",code);
}
if(strcmp(opcode,"WORD")==0)
locctr+=3;
else if(strcmp(opcode,"RESW")==0)
locctr+=(3*(atoi(operand)));
else if(strcmp(opcode,"RESB")==0)
locctr+=atoi(operand);
else if(strcmp(opcode,"BYTE")==0)
locctr+=strlen(operand)-3;
fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
length=locctr-start;
printf("\n length is :%d\n",length);
fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);
}