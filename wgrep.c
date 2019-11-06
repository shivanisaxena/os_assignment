#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>



int main(int ar,char *arg[])
{
 
   size_t buffer=1024;
   if (ar==1)
	{
       printf("wgrep: searchterm [file ...]\n");
	return 1;
	}
	
char *b = (void *)malloc(buffer * sizeof(char));
	
   if(ar==2)
	{
	int l=0;
	while(-1 != getline(&b, &buffer,stdin))
    	{
        if(strstr(b,arg[1]))
            printf("%s", b);
	l++;
   	 }
   	 fflush(stdout);
	return 0;
	}
	
	

  int i=2;
for(i=2;i<ar;i++)
{
   FILE *fp;
	fp=fopen(arg[2],"r");
	if(fp==NULL)
	{
	printf("wgrep: cannot open file\n");
	return 1;
	}
 
   


    // read each line and print it to the screen
    int line_number = 0;
    while(-1 != getline(&b, &buffer, fp))
    {
        if(strstr(b,arg[1]))
            printf("%s", b);
	line_number++;
    }
    fflush(stdout);

    // make sure we close the file and clean up the buffer when we're
    fclose(fp);
    free(b);

    return 0;
             
  }        
   
}
