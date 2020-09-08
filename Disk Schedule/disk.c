#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct request
{
	int rno;
	bool vis;
};


void fcfs(){
    int i,n,initial_head;
	printf("Enter the number of requests: ");
	scanf("%d",&n);
	int request[n];
	printf("Enter the requests: ");
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&request[i]);
	}
	printf("Enter initial position of R/W head: ");
	scanf("%d",&initial_head);
	int seek_time=0;
	printf("%d  ",initial_head );
	for(i=0;i<n;i++)
	{
		if(i == n-1)
			printf("%d\n", request[i] );
		else
			printf("%d  ", request[i] );
		seek_time += abs(request[i] - initial_head);
		initial_head = request[i];
	}
	printf("Seek Time: %d\n", seek_time);
}

void scan(){
    int i,n,initial_head,limit,j,dir;
	printf("Enter the number of requests: ");
	scanf("%d",&n);
	struct request req[n];
	printf("Enter the requests: ");
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&req[i].rno);
		req[i].vis = false;
	}
	printf("Enter initial position of R/W head: ");
	scanf("%d",&initial_head);

	printf("Enter the direction \n\t1.Right\n\t2.Left: ");
	scanf("%d",&dir);

    limit = req[0].rno;
	printf("Enter the cylinder size: ");
	scanf("%d",&limit);

	//scanf("%d",&dir);
	int seek_time=0;
	printf("%d  ",initial_head );
	if(dir == 1)
	{
		for(i=initial_head;i<limit;i++)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("%d  ", limit);
		seek_time += abs(limit-1 - initial_head);
		initial_head = limit-1;
		for(i=initial_head;i>=0;i--)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		// seek_time += abs(initial_head - 0);
		printf("0 \n");
	}
	else if(dir == 2)
	{
		for(i=initial_head;i>=0;i--)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("%d  ", 0);
		seek_time += abs(0 - initial_head);
		initial_head = 0;
		for(i=initial_head;i<limit;i++)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		seek_time += abs(limit - initial_head );
		printf("%d \n", limit);
		
	}
	printf("\nSeek Time: %d\n", seek_time);
}

void cscan(){
    int i,n,initial_head,limit,j,dir;
	printf("Enter the number of requests: ");
	scanf("%d",&n);
	struct request req[n];
	printf("Enter the requests: ");
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&req[i].rno);
		req[i].vis = false;
	}
	printf("Enter initial position of R/W head: ");
	scanf("%d",&initial_head);

	printf("Enter the direction \n\t1.Right\n\t2.Left: ");
	scanf("%d",&dir);

	printf("Enter the cylinder size: ");
	scanf("%d",&limit);

	//scanf("%d",&dir);
	int seek_time=0;
	printf("%d  ",initial_head );
	int cp_initial_head = initial_head;
	if(dir == 1)
	{
		for(i=initial_head;i<limit;i++)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("%d  ", limit-1);
		seek_time += abs(limit-1 - initial_head);
		seek_time += limit-1;
		printf("%d  ", 0 );
		initial_head = 0;
		for(i=0;i<cp_initial_head;i++)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("\n");
	}
	else if(dir == 2)
	{
		for(i=initial_head;i>=0;i--)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("%d  %d ", 0 , limit-1);
		seek_time += abs(initial_head - 0);
		seek_time += limit-1;
		initial_head = limit-1;
		for(i=limit;i>cp_initial_head;i--)
		{
			for(j=0;j<n;j++)
			{
				if(req[j].rno == i && req[j].vis == false)
				{
					printf("%d  ", req[j].rno);
					req[j].vis = true;
					seek_time += abs(req[j].rno - initial_head);
					initial_head = req[j].rno;
				}
			}
		}
		printf("\n");
	}
	printf("Seek Time: %d\n", seek_time);
}

void menu(){
    int o=0;
    printf("\nChoose from the list to do \n\t 1.FCFS \n\t 2.SCAN \n\t 3.C-SCAN \n");
    scanf("%d",&o);
    switch(o){
        case 1 : fcfs();
                 menu();
                 break;
        case 2 : scan();
                 menu();
                 break;
        case 3 : cscan();
                 menu();
                 break;
        default: printf("Enter a valid option \n");
                 menu();

    }
}

void main(){
    menu();
}
