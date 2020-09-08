#include <stdio.h>
#include <stdlib.h>

#define N 25

struct process
{
	int process_id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
    int remaining_time;
    int priority;
	int completion_time;
};

int n;
int queue[N];
int front = 0, rear = 0;
struct process pro[N],fcf[N];

struct process * create(){
	struct process temp;
    printf("Enter number of processes: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("\n");
		printf("Enter arrival time for process%d: ",i+1);
		scanf("%d",&pro[i].arrival_time);
		fcf[i].arrival_time=pro[i].arrival_time;
		printf("Enter burst time for process%d: ",i+1);
		scanf("%d",&pro[i].burst_time);
		fcf[i].burst_time=pro[i].burst_time;
		pro[i].process_id = i+1;
		fcf[i].process_id=pro[i].process_id;
	}
	
    return pro;
}

int fcfs(struct process proc[])
{
	int i,j,set=0;
	int service_time[n];
	service_time[0]=0;
	proc[0].waiting_time=0;
	struct process temp;

	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(proc[j].arrival_time > proc[j+1].arrival_time){
				temp=proc[j];
				proc[j]=proc[j+1];
				proc[j+1]=temp;
			}
		}
	}

	for(int i=0;i<n;i++){
		printf("\t%d",proc[i].process_id);
	}
    
	for(i=1;i<n;i++)
	{
		if((proc[i].arrival_time-(proc[i-1].arrival_time+proc[i-1].burst_time))>0){
			set+=proc[i].arrival_time-(proc[i-1].arrival_time+proc[i-1].burst_time);
		}
		service_time[i]=service_time[i-1]+proc[i-1].burst_time;
		// printf("%d %d ",service_time[i],set);
		proc[i].waiting_time = service_time[i]-proc[i].arrival_time+set;

		if(proc[i].waiting_time<0)
			proc[i].waiting_time=0;
	}

	for(i=0;i<n;i++)
	{
		proc[i].turn_around_time = proc[i].burst_time + proc[i].waiting_time;
	}
	printf("\n\n");
	printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n");
	int total_waiting_time=0,total_turn_around_time=0;
	for(i=0;i<n;i++)
	{
		total_waiting_time+=proc[i].waiting_time;
		total_turn_around_time+=proc[i].turn_around_time;

		int completion_time=proc[i].turn_around_time + proc[i].arrival_time;

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time,proc[i].turn_around_time,completion_time);
	}
	printf("Average waiting time: %f\n", (float)total_waiting_time/n);
	printf("Average turn around time: %f\n",(float)total_turn_around_time/n);
}

int sjfn(struct process pro[])
{
	int i=0,j=0;
	int bt=0,k=1,tat=0,sum=0,min,time=0,set=0;
	struct process temp,proc[n];
	if(pro[0].arrival_time!=0){
		set=pro[0].arrival_time;
	}

	for(int i=0;i<n;i++){
		proc[i]=pro[i];
	}

	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(proc[j].arrival_time > proc[j+1].arrival_time){
				temp=proc[j];
				proc[j]=proc[j+1];
				proc[j+1]=temp;
			}
		}
	}

	for(int i=0;i<n-1;i++)
    {
        min=i;
        if(time<proc[i].arrival_time)
            time=proc[i].arrival_time;
        for(int j=i+1;j<n;j++)
        {
            if(proc[j].arrival_time<=time&&proc[j].burst_time<proc[min].burst_time)
            {
                    min=j;
            }
        }
        if(min!=i)
        {
			temp=proc[min];
			proc[min]=proc[i];
			proc[i]=temp;
        }
        proc[i].completion_time=time+proc[i].burst_time;
        time=proc[i].completion_time;
    }
    proc[i].completion_time=time+proc[i].burst_time;
    time=proc[i].completion_time;
  
	proc[0].waiting_time=0;
	int wait_time_total=0;
	int turn_around_time_total=0;
	
	printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");

	for(i=0;i<n;i++)
    {
		proc[i].turn_around_time=(float)(proc[i].completion_time)-(float)(proc[i].arrival_time);
        turn_around_time_total+=(float)(proc[i].completion_time)-(float)(proc[i].arrival_time);
		proc[i].waiting_time=(float)(proc[i].turn_around_time)-(float)(proc[i].burst_time);
        wait_time_total+=proc[i].burst_time;
    }
	wait_time_total=turn_around_time_total-wait_time_total;
	for(i=0;i<n;i++)
	{

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time,proc[i].turn_around_time);
	}
	printf("Average waiting time: %f\n", (float)wait_time_total/n);
	printf("Average turn around time: %f\n",(float)turn_around_time_total/n);

}

void push(int process_id)
{
	queue[rear] = process_id;
	rear = (rear+1)%N;
}

int pop()
{
	if(front == rear)
		return -1;

	int return_position = queue[front];
	front = (front +1)%N;
	return return_position;
}

int rr(struct process pro[])
{
	struct process proc[n];
	float wait_time_total = 0.0, tat = 0.0;
	int time_quantum;

	for(int i=0;i<n;i++){
		proc[i]=pro[i];
	}

	for(int i=0; i<n; i++)
	{
		proc[i].remaining_time = proc[i].burst_time;
	}
	printf("Enter time quantum: ");
	scanf("%d",&time_quantum);

	int time=0; 
	int processes_left=n;   
	int position=-1; 		
	int local_time=0; 

	for(int j=0; j<n; j++)
		if(proc[j].arrival_time == time)
			push(j);

	while(processes_left)
	{
		if(local_time == 0) 
		{
			if(position != -1)
				push(position);

			position = pop();
		}

		for(int i=0; i<n; i++)
		{
			if(proc[i].arrival_time > time)
				continue;
			if(i==position)
				continue;
			if(proc[i].remaining_time == 0)
				continue;

			proc[i].waiting_time++;
			proc[i].turn_around_time++;
		}

		if(position != -1)
		{
			proc[position].remaining_time--;
			proc[position].turn_around_time++;
			
			if(proc[position].remaining_time == 0)
			{
				processes_left--;
				local_time = -1;
				position = -1;
			}
		}
		else
			local_time = -1; 

		time++;
		local_time = (local_time +1)%time_quantum;
		for(int j=0; j<n; j++)
			if(proc[j].arrival_time == time)	
				push(j);
	}

	printf("\n");

	printf("Process\t\tArrival Time\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", proc[i].process_id, proc[i].arrival_time);
		printf("%d\t\t%d\t\t%d\n", proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);

		tat += proc[i].turn_around_time;
		wait_time_total += proc[i].waiting_time;
	}

	tat = tat/(1.0*n);
	wait_time_total = wait_time_total/(1.0*n);

	printf("\nAverage waiting time     : %f",wait_time_total);
	printf("\nAverage turn around time : %f\n", tat);
	
}

int prion(struct process pro[])
{

	int i,j,o;
	int bt=0,k=1,tat=0,sum=0,min,mini;
	struct process temp,proc[n];
	printf("Do you want to add new(1) or continue with the same ");
	scanf("%d",&o);
	if(o==1){
		create();
	}

	for(int i=0;i<n;i++){
		proc[i]=pro[i];
	}

	for(i=0;i<n;i++){
		printf("Enter priority for process%d: ",i+1);
		scanf("%d",&proc[i].priority);
		proc[i].process_id = i+1;
	}

	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(proc[j].arrival_time > proc[j+1].arrival_time){
				temp=proc[j];
				proc[j]=proc[j+1];
				proc[j+1]=temp;
			}
		}
	}

	for(i=0;i<n;i++)
	{
		bt+=proc[i].burst_time;
		min = proc[k].burst_time;
		mini = proc[k].priority;
		for(j=k;j<n;j++)
		{
			if(bt>=proc[j].arrival_time && proc[j].priority<mini)
			{
				temp=proc[k];
				proc[k]=proc[j];
				proc[j]=temp;
			}
		}
		k++;
	}
	proc[0].waiting_time=0;
	int wait_time_total=0;
	int turn_around_time_total=0;
	for(i=1;i<n;i++)
	{
		sum+=proc[i-1].burst_time;
		proc[i].waiting_time = sum-proc[i].arrival_time;
		wait_time_total += proc[i].waiting_time;
	}
	for(i=0;i<n;i++)
	{
		tat+=proc[i].burst_time;
		proc[i].turn_around_time = tat - proc[i].arrival_time;
		turn_around_time_total+=proc[i].turn_around_time;
	}
	printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");

	for(i=0;i<n;i++)
	{

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time,proc[i].turn_around_time);
	}
	printf("Average waiting time: %f\n", (float)wait_time_total/n);
	printf("Average turn around time: %f\n",(float)turn_around_time_total/n);

}

void menu(struct process pro[]){
    int o=0;
    printf("Choose from the list to do \n\t 1.FCFS \n\t 2.SJF \n\t 3.RR \n\t 4.PRIORITY \n\t 5.CREATE NEW\n");
    scanf("%d",&o);
    switch(o){
        case 1 : fcfs(fcf);
                 menu(pro);
                 break;
        case 2 : sjfn(pro);
                 menu(pro);
                 break;
        case 3 : rr(pro);
                 menu(pro);
                 break;
        case 4 : prion(pro);
                 menu(pro);
                 break;
        case 5 : create();
		 		 menu(pro);
                 break;
        default : printf("Enter a valid option ");

    }
}

void main(){
    menu(create());
}
