
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<wait.h>
#include<fcntl.h>  
int fp=0;
int  out=0;

int check_cd(int ar, char **arg)//cd
{
if(strcmp(arg[0],"cd")==0)
{
if(arg[1]!=NULL)
{
if(chdir(arg[1])==-1)
printf("invalid cmd.\n");
else
printf("directory changed.\n");
}
else
printf("invalid command.\n");
return 1;
}
return 0;
}

void run_cmd(char **arg)//run
{
int error = execvp(arg[0], arg);
if(error==-1)
{
if(strcmp(arg[0],"exit")==0)
{
exit(1);
}
exit(2);
}
}

void parse_arg(char *cmd)//parse
{
int     i = 0;
while(cmd[i++]!='\n');
cmd[i-1]='\0';
if((i-1)==0)
return;
	
char *sep=" ";
char *list=NULL;
char *wcmd = strdup(cmd);
list = strsep(&wcmd, sep);
int ar=0;
char **arg=NULL;
while(list!=NULL)
{
list = strsep(&wcmd, sep);
++ar;
}
arg = (char**)calloc(ar+1,sizeof(char*));
i=0;
list = strsep(&cmd, sep);
while(list!=NULL)
{
arg[i] = strdup(list);
i+=1;
list = strsep(&cmd, sep);
}
arg[i]=NULL;

check_redirect(&ar, arg);

if(check_cd(ar, arg)==1)
return;

int pid = fork();
if(pid==-1)
{
printf("unable to run command.\n");

}
else if(pid==0)
{

int j,index=0,flag=0;
		
char **carg = (char**)calloc(ar+1,sizeof(char*));
for(j=0;j<ar;j++)
{
carg[index++]=strdup(arg[j]);
if(strcmp(arg[j],"&")==0)
{
carg[index-1]=NULL;
index = 0;
flag = 1;
int cpid = fork();
if(cpid==0)
run_cmd(carg);
				
}
}
if(flag==1)
{
carg[index]=NULL;
index = 0;
flag = 1;
int cpid = fork();
if(cpid==0)
run_cmd(carg);
			
}
if(flag==1)
{
int stat=0;
waitpid(-1, &stat, 0);
if(stat==256)
exit(1);
}
if(flag==0)
{
run_cmd(arg);
			
}
}
else
{
int status=0;
wait(&status);
		
if(status==256)
exit(0);
else if(status==512)
{
char error_message[30] = "An error has occurred\n";
write(STDERR_FILENO, error_message, strlen(error_message));
}
}
if(fp!=0)
{
dup2(out,1);
dup2(out,2);
close(fp);
fp = 0;
}
}


void check_redirect(int *ar,char **arg)//redirect
{
int i;
for(i=0;i<(*ar);i++)
{
if(strcmp(arg[i],">")==0)
{
if(arg[i+1]!=NULL)
{
fp = open(arg[i+1], O_RDWR | O_CREAT, S_IRWXU);
if(fp!=0)
{
out = dup(1);
dup2(fp,1);
dup2(fp,2);
}
}
arg[i]=NULL;
*ar = i;
break;
}
}
}

int main(int argc,char **argv)//main
{
if(argc==1)
{
while(1)
{	
char *cmd=NULL;
size_t  len=0;
printf("wish> ");
getline(&cmd, &len, stdin);
parse_arg(cmd);
}
}
else
{
FILE *fp = fopen(argv[1],"r");
if(fp!=NULL)
{
fseek(fp, 0L, SEEK_END);
int file_len = ftell(fp)+1;
fseek(fp, 0L, SEEK_SET);
char *cmd = (char*)calloc(file_len, sizeof(char));
char ch;
int index = 0;
while((ch=fgetc(fp))!=EOF)
{
if(ch=='\n')
{
cmd[index]='\0';
index=0;
parse_arg(cmd);				
}
else
cmd[index++]=ch;
}
fclose(fp);
}
}
return 0;
}
