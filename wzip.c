#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char count[2000];
int main(int ar,char *arg[])
{

 	if(ar==1)
	{
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}


	
		
	
	int i,j=0;
	char ch;
	for(i=1;i<ar;++i)
	{
		FILE *fp = fopen(arg[i],"r");
		if(fp!=NULL)
		{
		while((ch=fgetc(fp))!=EOF)
			{
			count[j]=ch;
			j++;		
			}
		}
	}      
		int terms=j;
		count[j]='\0';
		for(i=0;i<terms;++i){
			int k=i,num;
			j = i;
			while(j<terms && count[j]==count[j+1])
				++j;

			num = (j-k+1);
			fwrite(&num, sizeof(int), 1, stdout);
			fwrite(&count[i], sizeof(char), 1, stdout);
			i=j;
		}
	
	
	return 0;
}
