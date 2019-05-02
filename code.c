#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<math.h>
#include<windows.h>

#define MAX 100

int c=0;
char ip[MAX];
char op[MAX];
char var_array[100];
char var[100][100];
char fx[100];
char meaning[10][100];
char meaning_fx[100];
int cycles,time;

//STACH USING LINKED LIST


struct node     //user defined data structure
{
    char data;
    struct node *next;         //pointer to next node
};

struct node *l1=NULL;        //first node


void insert(char x)
{
    if(l1==NULL)
    {
        l1=(struct node *)malloc(sizeof(struct node));              //creating a node of same size as defined
        l1->data=x;
        l1->next=NULL;
    }
    else
    {
        struct node *p;
        p=(struct node *)malloc(sizeof(struct node));
        p->data=x;
        p->next=l1;
        l1=p;
    }
}


char delet()         //to delete 
{
    char c;
    struct node *p;
    if (l1==NULL)
    {
        printf("");
    }
    else
    {
        c=l1->data;
        p=l1->next;
        free (l1);
        l1=p;
    }
    return c;
}


void display(struct node *start)
{
    {
        struct node *p;
        p=start;
        if(p==NULL)
            printf("");
        else
        {
            while(p!=NULL)
            {
                printf("%c->",p->data);
                p=p->next;
            }
            printf("");
        }
    }
}


int prior(char s, char c)
{
    if ((c=='^' && s=='+') || s=='-' || s=='@' || s=='*')
        return 1;
    else if(c=='*' || c=='@')
    {
        if(s=='+' || s=='-')
            return 1;
        else
            return 0;
    }
    else if(c=='+' || c=='-')
        return 0;
  return -1;
}


void cnvrt(char s[], int n)
{
    int i,j;
    for(i=0,j=0;i<n;i++)
    {

        if ((s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'))
        {
            op[j]=s[i];
            j++;
        }
        else if(s[i]=='(')
        {
            insert(s[i]);
        }
        else if (s[i]=='+' || s[i]=='@' || s[i]=='-' || s[i]=='*' || s[i]=='^')
        {

            if( l1==NULL)
                insert(s[i]);
            else if(l1->data=='(')
                insert(s[i]);
            else if(prior(l1->data, s[i] )!=1)
                insert(s[i]);
            else
            {
                op[j]=delet();
                j++;
                insert(s[i]);
            }
        }
        else if(s[i]==')')
        {
            while(l1!=NULL && l1->data!='(')
            {
                op[j]=delet();
                j++;
            }
            delet();
        }
    }
    while(l1!=NULL)
    {
        op[j]=delet();
        j++;
    }
}


int count0( char * ip,int i)
{
	int p;
	for (p=0;p<i;p++)
	{
		if(ip[i]==ip[p])
		return 0;

	}

	return 1;
}


int no_of_variables(char * ip,char * var_array)
{
	int i,count=0;
	for(i=0;ip[i]!='\0';i++)
	{
		if((((ip[i]>='A'&& ip[i]<='Z')||(ip[i]>='a'&& ip[i]<='z'))&&(count0(ip,i))))
		{
			var_array[count]=ip[i];
			count++;
		}
	}
	return count;
}


int *ttable(int varc)
{
     int t=pow(2,varc);
     char bit='1';
     int j=0;
     int i=0;
     for(i=0;i<varc;i++)
     {
             for (j=0;j<t;j++)
             {
                 if(j%(int)pow(2,varc-i-1)==0)
                 {
                     bit=(bit=='1'?'0':'1');
                 }
                 var[i][j]=bit;
             }
     }
}


int *ttabledisplay(int varc)
{
     int t=pow(2,varc);
     int i,j;
   for(j=0;j<pow(2,varc);j++)
     {
         for (i=0;i<varc;i++)
            {
                printf("%c\t",var[i][j]);
            }
    printf("\t%c",fx[j]);
    printf("\n");
     }
    printf("\n\n");
}

int eval(char * op,int variables,char * var_array)	
{
	char ch;
	int c,l,j,a,b,i=0,k=0;
	char temparray[50],op1,op2;
	for(c=0;c<pow(2,variables);c++)
	{
		strcpy(temparray,op);
		for(a=0;a<variables;a++)
	{
		for(b=0;temparray[b]!='\0';b++)
		{
			if(var_array[a]==temparray[b])
			{
				temparray[b]=var[a][c];
			}
		}
	}

	for(l=1;temparray[l]!='\0';l++)
	{
		if(temparray[l]=='\'')
			if(temparray[l-1]=='0')
				temparray[l-1]='1';
			else
				temparray[l-1]='0';
	}
	i=0;
	while( (ch=temparray[i++]) != '\0')
 	{
 		if(ch=='0'||ch=='1')
		{	insert(ch);
		}
		else if(ch=='\'')
			continue;
  		else
  		{
	   		op2=delet();
	   		op1=delet();
	   			switch(ch)
   				{
   					case '+':
                        if(op1=='1' || op2=='1' ) insert('1');
                        else insert('0');
                        break;
                    case '^':
                        if(op1=='0') insert('1');
                        else if(op1=='1') insert('0');
                        break;
			   		case '*':
                        if( op1=='0' || op2=='0' ) insert('0');
                        else insert('1');
                        break;
                    case '@':
                        if(op1=='0' && op2=='0') insert('0');
                        else if(op1=='0'&& op2=='1') insert('1');
                        else if(op1=='1'&& op2=='0') insert('1');
                        else if(op1=='1'&& op2=='1') insert('0');
                        break;
					case '\'':
						break;

   				}
  		}
 	}
 	fx[c] = l1->data;
	}
}


void graphdisplay(int varc,char *var_array)
{
	int i,j,o,n,d,freq;
	printf("Enter Clock Time for Simulation Graph (in multiples of 50 ms) : ");
	scanf("%d",&time);
	printf("Enter the number of cycles : ");
	scanf("%d",&cycles);

	int t=pow(2,varc);
	printf("\n");
	for(i=0;i<varc;i++)
    {
        printf("%c\t",var_array[i]);

        for(t=0;t<cycles;t++)
        {

            for(j=0;j<pow(2,varc);j++)
            {

                for(o=0;o<time/50;o++)
                {
                    if(var[i][j]=='1')
                        printf("-");
                    else
                        printf("_");
                }
            }
        }
    printf("\n\n");
	}
	printf("Fx\t");
	for(t=0;t<cycles;t++)
	{

        for(j=0;j<pow(2,varc);j++)
        {
            for(n=0;n<time/50;n++)
            {
       			if(fx[j]=='1')
       				printf("-");
				else
			    	printf("_");
            }
        }
	}

	printf("\n\nTime\t");

	for(d=0;d<time*cycles;d=d+time)
    {
        printf("%d",d);
        for(i=0;i<pow(2,varc);i++)
        {
            for(n=0;n<(time/50);n++)
            {
                printf(" ");
            }
        }

    }
}

void graphdisplay_out(int varc,char *var_array)
{

	int i,j,o,n,d;
	int t=pow(2,varc);
	FILE *fp;
	fp=fopen("Graph.txt","w");                                          //File handeling Functions

	fprintf(fp,"\n");
	fprintf(fp,"\nGRAPH FOR THE LOGIC EXPRESSION : ");
	for(i=0;i<strlen(ip);i++)
    {
        fprintf(fp,"%c ",ip[i]);
    }
    fprintf(fp,"\n\n");
	  for(i=0;i<varc;i++)
    {
        fprintf(fp,"%c\t",var_array[i]);

        for(t=0;t<cycles;t++)
        {

            for(j=0;j<pow(2,varc);j++)
            {

                for(o=0;o<time/50;o++)
                {
                    if(var[i][j]=='1')
                        fprintf(fp,"-");
                    else
                        fprintf(fp,"_");
                }
            }
        }
    fprintf(fp,"\n\n");
	}
	fprintf(fp,"Fx\t");
	for(t=0;t<cycles;t++)
	{

        for(j=0;j<pow(2,varc);j++)
        {
            for(n=0;n<time/50;n++)
            {
       			if(fx[j]=='1')
       				fprintf(fp,"-");
				else
			    	fprintf(fp,"_");
            }
        }
	}

	fprintf(fp,"\n\nTime\t");

	for(d=0;d<time*cycles;d=d+time)
    {
        fprintf(fp,"%d",d);
        for(i=0;i<pow(2,varc);i++)
        {
            for(n=0;n<(time/50);n++)
            {
                fprintf(fp," ");
            }
        }
    }
	fclose(fp);
	printf("\n\nTHE GRAPH FILE HAS BEEN SAVED TO YOUR LOCAL DIRECTORY...PLZZ SAVE IT FOR USING NEXT TIME \n\n");

}


void success_cases(int varc)
{
    printf("SUCCESS CASES\n\n");
    int t=pow(2,varc);
    int i,j;
    for(i=0;i<varc;i++)
    {
        printf("%c\t",var_array[i]);
	}
	printf("\n");
    for(j=0;j<pow(2,varc);j++)
     {
         if(fx[j]=='0')
         {
             continue;
         }
         else
         {
             for (i=0;i<varc;i++)
            {
                printf("%c\t",var[i][j]);
            }
         }
    printf("\n");
     }
    printf("\n\n");
}

void meaning_of_variables(char *var_array,int variables)
{
    int i=0;
    char mean[100];
    fgets(mean, 100, stdin);

    for(i=0;i<variables;i++)
    {
        printf("Enter the meaning of variable \t %c \n",var_array[i]);
        gets(mean);
        strcpy(meaning[i],mean);
        printf("\n%s\n",meaning[i]);
    }
    printf("Enter the meaning of variable \t Fx \n");
    gets(mean);
    strcpy(meaning_fx,mean);
    printf("\n%s\n",meaning_fx);
}


void final_saying(char * ip,int n,int variables)
{
    int i,j;
    printf("\t\tTHE FINAL SAYING IS : \n\n");
    printf("%s if ",meaning_fx);
    for(i=0;i<n;i++)
    {
        if(ip[i]=='+')
        {
            printf("Or ");
            continue;
        }
        else if(ip[i]=='*')
        {
            printf("And ");
            continue;
        }
        else
        {
            for(j=0;j<variables;j++)
            {
                if(ip[i]==var_array[j])
                {
                    printf("%s ",meaning[j]);
                }
            }
        }
    }
    printf("\n");
}

void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}


int main()
{
    int i,n,meaning_c;
    while(1)
    {
        printf("\tLOGIC EQUATION SIMULATION SOFTWARE\n");
        printf(" ENTER THE BOOLEAN EXPRESSION TO BE EVALUATED : \n");
    scanf("%s",ip);
    n=strlen(ip);

    cnvrt(ip,n);

    int variables=no_of_variables(ip,var_array);

    printf("\n\nNo of variables used are : %d\n",variables);
    printf("\nTHE VARIABLES USED ARE : ");
    for(i=0;i<variables;i++)
    {
        printf("%c\t",var_array[i]);
    }
    printf("\n\nPLZZ PRESS 1 TO SOLVE LOGICAL STATEMENT PROBLEM OR 0 TO SOLVE NORMAL EQUATION : ");
    scanf("%d",&meaning_c);
    if(meaning_c==1)
    {
        printf("\n\n");
        meaning_of_variables(var_array,variables);
    }

    ttable(variables);

    printf("\n\nTHE FUNCTION USED BY COMPUTER FOR EVALUATION IS : ");
    for(i=0;i<n;i++)
    {
        printf("%c",op[i]);
    }
    printf("\n\n");

    eval(op,variables,var_array);  
    printf("\n\nTRUTH TABLE\n\n");
    for(i=0;i<variables;i++)
    {
          printf("%c\t",var_array[i]);
    }
    printf(":\tFx\n");

    ttabledisplay(variables);

    printf("\n\n");

    graphdisplay(variables,var_array);

    graphdisplay_out(variables,var_array);

    printf("\n\n");

    success_cases(variables);

    if(meaning_c==1)
    final_saying(ip,n,variables);
    printf("\n\nTO EXIT PRESS 0 OR 1 TO CONTINUE :\n");
    int exit_status;
    scanf("%d",&exit_status);
    if(exit_status==0)
        exit(0);
    printf("PLEASE SAVE YOUR DATA BEFORE PROCEEDING AHEAD\n\n");
    l1=NULL;
    system("cls");
    }
    return 0;
}
