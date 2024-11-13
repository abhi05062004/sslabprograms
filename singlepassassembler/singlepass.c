
{
strcpy(symtbl[j].sym,table[i].label);
symtbl[j].val=locctr;
symtbl[j].f=0;j++;
}
}
fscanf(fp2,"%s%s",code,mnemcode);

while(strcmp(code,"END")!=0)
{
if(strcmp(table[i].opcode,code)==0)
{
strcpy(table[i].mnemonic,mnemcode);
locctr+=3;
for(x=1;x<=j;x++)
{
flag=0;
if(strcmp(table[i].operand,symtbl[x].sym)==0)
{
flag=1;
if(symtbl[x].f==0)
table[i].loc=symtbl[x].val;
break;
}
}
if(flag!=1)
{
strcpy(symtbl[j].sym,table[i].operand);
symtbl[j].f=1;
symtbl[j].ref=i;j++;
}
}
fscanf(fp2,"%s%s",code,mnemcode);
   }
   rewind(fp2);
   
   
   if(strcmp(table[i].opcode,"WORD")==0)
   {
    locctr+=3;
    strcpy(table[i].mnemonic,"\0");
    table[i].loc=atoi(table[i].operand);
   }
   else if(strcmp(table[i].opcode,"RESW")==0)
   {
    locctr+=(3*(atoi(table[i].operand)));
    strcpy(table[i].mnemonic,"\0");
    table[i].loc=atoi("\0");
    }
else if(strcmp(table[i].opcode,"RESB")==0)
{
locctr+=(atoi(table[i].operand));
    strcpy(table[i].mnemonic,"\0");
    table[i].loc=atoi("\0");
}
else if(strcmp(table[i].opcode,"BYTE")==0)
{
++locctr;
if((table[i].operand[0]=='c') ||  (table[i].operand[0]=='x'))
table[i].loc=(int)table[i].operand[2];
else
table[i].loc=locctr;
}
i++;
fscanf(fp1,"%s%s%s",table[i].label,table[i].opcode,table[i].operand);
}
for(x=1;x<=i;x++)
fprintf(fp3,"%s\t%s\t%s\t%s%d\n",table[x].label,table[x].opcode,table[x].operand,table[x].mnemonic,table[x].loc);
for(x=1;x<j;x++)
printf("%s\t%d\n",symtbl[x].sym,symtbl[x].val);
}   
