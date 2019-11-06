#include<stdio.h>
#include<stdlib.h>
int main(int ar,char *arg[])
{
	char c;
       int i;
    	for(i=1;i<ar;i++)
{
	FILE *fp,*ch;
	fp=fopen(arg[i],"r");
	if(fp==NULL)
	{
	printf("wcat: cannot open file\n");
	return 1;
	}
	ch=fp;
	while((c=fgetc(ch))!=EOF)
	{
	printf("%c",c);
	
	}

	fclose(fp);
}
	return 0;
}
 	
