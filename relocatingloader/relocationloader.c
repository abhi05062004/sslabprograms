#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
	char add[10],length[10],input[10],binary[12],bitmask[12],relocbit;
	int start,len,i,address,opcode,addr,actualadd;
	FILE *inp,*out;
	printf("\nENTER THE ACTUAL STARTING ADDRESS: ");/*start address 4000 in this code*/
	scanf("%d",&start);
	start=start-1000;
	inp = fopen("relocatinginput.dat","r");
	out = fopen("relocatingoutput.dat","w");
	
	fscanf(inp,"%s",input);
	
	while(strcmp(input,"E")!=0){
		if(strcmp(input,"H")==0){
			fscanf(inp,"%s",add);	
			fscanf(inp,"%s",length);
			fscanf(inp,"%s",input);
			}
		else if(strcmp(input,"T")==0)
		{
			fscanf(inp,"%d",&address);
			fscanf(inp,"%s",bitmask);
			address+=start;
			len = strlen(bitmask);
			for(i=0;i<len;i++){
			
				fscanf(inp,"%d",&opcode);
				fscanf(inp,"%d",&addr);
				relocbit = bitmask[i];
				
				if(relocbit=='0'){
					actualadd = addr;
					}
				else{
					actualadd = addr+start;
				}
				fprintf(out,"%d\t%d%d\n",address,opcode,actualadd);
				address+=3;
		}
				fscanf(inp,"%s",input);
		}
		}
		fclose(inp);
		fclose(out);
		printf("\nFINISHED\n");
		}
