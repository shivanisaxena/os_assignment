#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>



int main(int ar,char *arg[])
{
 
   
   if (ar==1)
	{
       printf("wunzip: file1 [file2 ...]\n");
	return 1;
	}
	

 
   int i=2;
for(i=1;i<ar;i++)
{
   FILE *fp;
	fp=fopen(arg[i],"r");
	if(fp!=NULL)
	{
	int val;
	char ch;
	int j;
	while( (fread(&val, sizeof(int), 1, fp)==1) && (fread(&ch, sizeof(char), 1, fp)==1) )
	{
	for(j=0;j<val;j++)
		printf("%c",ch);
	}
	}
 
   


    

    
    fclose(fp);
}
    

    return 0;
             
  }        
