#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct directory
{
    char dname[10],fname[10][10];
    int fcnt;
};


int one(){
    struct directory dir;
    int i,ch=0;
    char f[30];
    dir.fcnt = 0;
    printf("\nEnter name of directory ");
    scanf("%s", dir.dname);

	while(1)
	{
		printf("\nMenu \n\t1. Create Directory\n\t2. Create File\n\t3. Delete File\n\t4. Search File\n\t5. Display\n\t6. Exit\nEnter your choice ");
        	scanf("%d",&ch);
		switch(ch)
		{
			case 1: one();
				break;

			case 2: printf("\nEnter the name of the file ");
				scanf("%s",dir.fname[dir.fcnt]);
				dir.fcnt++;
				break;

			case 3: printf("\nEnter the name of the file ");
				scanf("%s",f);
				for(i=0;i<dir.fcnt;i++)
				{
					if(strcmp(f, dir.fname[i])==0)
					{
						printf("File %s is deleted ",f);
						strcpy(dir.fname[i],dir.fname[dir.fcnt-1]);
						break;
					}
				}

				if(i==dir.fcnt)
					printf("File %s not found",f);
				else
					dir.fcnt--;
				break;

			case 4: printf("\nEnter the name of the file ");
				scanf("%s",f);
				for(i=0;i<dir.fcnt;i++)
				{
					if(strcmp(f, dir.fname[i])==0)
					{
						printf("File %s is found ", f);
						break;
					}
				}
				if(i==dir.fcnt)
					printf("File %s not found",f);
				break;

			case 5: if(dir.fcnt==0)
				printf("\nDirectory Empty");
				else
				{
					printf("\nThe Files are ");
					for(i=0;i<dir.fcnt;i++)
						printf("\t%s",dir.fname[i]);
				}
				break;

			default: printf("Exiting....");
                     return 0;
		}
	}
}

int two()
{
    struct directory dir[10];
    int i,ch=0,dcnt,k,flag;
    char f[30], d[30];
    dcnt=0;

    while(1)
    {
        printf("\nMenu \n\t1. Create Directory\n\t2. Create File\n\t3. Delete File\n\t4. Search File\n\t5. Display\n\t6. Exit\nEnter your choice ");
        scanf("%d",&ch);
    switch(ch)
    {
        case 1: printf("\nEnter name of directory ");
                scanf("%s", d);
                for(i=0;i<dcnt;i++)
                    if(strcmp(d,dir[i].dname)==0)
                    {
                        printf("Directory already exixts...");
                        goto jump;
                    }
                    strcpy(dir[dcnt].dname,d);
                    dir[dcnt].fcnt=0;
                    dcnt++;
                    printf("Directory created");
                    goto jump;
                    jump : break;

        case 2: printf("\nEnter name of the directory ");
                scanf("%s",d);
                for(i=0;i<dcnt;i++)
                    if(strcmp(d,dir[i].dname)==0)
                    {
                        printf("Enter name of the file ");
                        scanf("%s",dir[i].fname[dir[i].fcnt]);
                        dir[i].fcnt++;
                        printf("File created");
                        break;
                    }
                if(i==dcnt)
                    printf("Directory %s not found",d);
                break;

        case 3: printf("\nEnter name of the directory ");
                scanf("%s",d);
                for(i=0;i<dcnt;i++)
                {
                    if(strcmp(d,dir[i].dname)==0)
                    {
                        printf("Enter name of the file ");
                        scanf("%s",f);
                        for(k=0;k<dir[i].fcnt;k++)
                        {
                            if(strcmp(f, dir[i].fname[k])==0)
                            {
                                printf("File %s is deleted ",f);
                                dir[i].fcnt--;
                                strcpy(dir[i].fname[k],dir[i].fname[dir[i].fcnt]);
                                goto jmp;
                            }
                        }

                    printf("File %s not found",f);
                    goto jmp;
                }
                }

                printf("Directory %s not found",d);
                jmp : break;

        case 4: printf("\nEnter name of the directory ");
                scanf("%s",d);
                for(i=0;i<dcnt;i++)
                {
                    if(strcmp(d,dir[i].dname)==0)
                    {
                        printf("Enter the name of the file ");
                        scanf("%s",f);
                        for(k=0;k<dir[i].fcnt;k++)
                        {
                            if(strcmp(f, dir[i].fname[k])==0)
                            {
                                printf("File %s is found ",f);
                                goto jmp1;
                            }
                        }
                        printf("File %s not found",f);
                        goto jmp1;
                    }
                }
                printf("Directory %s not found",d);
                jmp1: break;
        case 5: if(dcnt==0)
                    printf("\nNo Directory's ");
                else
                {
                    printf("\nDirectory\tFiles");
                    for(i=0;i<dcnt;i++)
                    {
                        printf("\n%s\t\t",dir[i].dname);
                        for(k=0;k<dir[i].fcnt;k++)
                        printf("\t%s",dir[i].fname[k]);
                    }
                }
                break;
        default: printf("Exiting....");
                 return 0;
    }
}
}

void list(){
    int o=0;
    printf("Choose from the list to do \n\t 1.Single \n\t 2.Two \n");
    scanf("%d",&o);
    switch(o){
        case 1 : one();
                 list();
                 break;
        case 2 : two();
                 list();
                 break;
        default: printf("\nEnter a valid option");
                 list();
    }
                 
}

void main(){
    list();
}
