#include <stdio.h>
#include <stdbool.h>

int pointer;
int faults ,hits;
void print(int fs,int frame[])
{
	int i;
	for(i=0;i<fs;i++)
	{
		if(frame[i]==-1)
			printf("- ");
		else
			printf("%d ",frame[i]);
	}

	printf("\n");
}

int lru(int element_length, int elements[], int page_no ,int fs,int frame[], int start)
{
	int pos = -1, farthest = start, i;
	for(i=0;i<fs;i++)
	{
		int j;
		for(j=start-1;j>=0;j--)
		{
			if(frame[i]==elements[j])
			{
				if(j<farthest)
				{
					farthest=j;
					pos=i;
				}
				break;
			}
		}
		if(j==page_no)
			return i;
	}
	if(pos == -1)
		return 0;
	else
		return pos;
}

int optimal(int element_length, int elements[], int page_no ,int fs,int frame[], int start)
{
	int pos = -1, farthest = start, i;
	for(i=0;i<fs;i++)
	{
		int j;
		for(j=start;j<element_length;j++)
		{
			if(frame[i]==elements[j])
			{
				if(j>farthest)
				{
					farthest=j;
					pos=i;
				}
				break;
			}
		}
		if(j==page_no)
			return i;
	}
	if(pos == -1)
		return 0;
	else
		return pos;
}

void add_element(int fs,int frame[], int element, int pos,int element_length, int elements[], int ch)
{
	int i;
	bool allocated=false;
	for(i=0;i<fs;i++)
	{
		
		if(frame[i]==element)
		{
			printf("  Hit for %d | ", element);
			hits++;
			allocated = true;
			break;
		}
		else if(frame[i]==-1)
		{
			frame[i] = element;
			printf("Fault for %d | ", element);
			faults++;
			allocated = true;
			break;
		}
	}
    if(allocated == false&&ch==0){
		    faults++;
		    printf("Fault for %d | ", element);
		    frame[pointer] = element;
		    pointer = (pointer+1)%fs;
	}else if(allocated==false&&ch==1){
		    int j = lru(element_length,elements,pos,fs,frame,pos+1);
		    frame[j] = element;
		    printf("Fault for %d | ", element);
		    faults++;	
	}else if (allocated==false&&ch==2){
		    int j = optimal(element_length,elements,pos,fs,frame,pos+1);
		    frame[j] = element;
		    printf("Fault for %d | ", element);
		    faults++;	
	}
    print(fs, frame);
}

int insert(int op)
{
	int fs,i,no;
	printf("Enter frame size: ");
	scanf("%d",&fs);
	int frame[fs];
	for(i=0;i<fs;i++)
	{
		frame[i] = -1;
	}

	print(fs,frame);
	
	printf("Enter the number of elements: ");
	scanf("%d",&no);
	int element[no];
	
	for(i=0;i<no;i++)
	{
		scanf("%d",&element[i]);
		add_element(fs,frame,element[i],i,no,element,op);
	}
	printf("\nNumber of faults: %d \nNumber of hits: %d\n",faults,hits );
}

void menu(){
    int o=0;
    printf("\nChoose from the list to do \n\t 1.FIFO \n\t 2.LRU \n\t 3.OPTIMAL\n");
    scanf("%d",&o);
    switch(o){
        case 1 : insert(0);
                 menu();
                 break;
        case 2 : insert(1);
                 menu();
                 break;
        case 3 : insert(2);
                 menu();
                 break;
        default: printf("Enter a valid option \n");
                 menu();

    }
}

void main(){
    menu();
}
