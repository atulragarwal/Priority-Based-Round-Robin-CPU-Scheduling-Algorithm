#include<stdio.h>
#include<string.h>
#include<math.h>
int n;
void sort(int id[],int p[],int b[])
{
	int i,j;
	for(i=0;i<n;i++)
  {
		for(j=i+1;j<n;j++)
    {
    	if(p[i]>p[j])
      {
      	p[i]+=p[j];
        p[j]=p[i]-p[j];
        p[i]=p[i]-p[j];
      	id[i]+=id[j];
        id[j]=id[i]-id[j];
        id[i]=id[i]-id[j];
      	b[i]+=b[j];
        b[j]=b[i]-b[j];
        b[i]=b[i]-b[j];
      }
      if(p[i]==p[j])
      {
      	if(b[i]>b[j])
        {
        	p[i]+=p[j];
          	p[j]=p[i]-p[j];
          	p[i]=p[i]-p[j];
          	id[i]+=id[j];
          	id[j]=id[i]-id[j];
          	id[i]=id[i]-id[j];
          	b[i]+=b[j];
          	b[j]=b[i]-b[j];
          	b[i]=b[i]-b[j];
        }
    	}}}

}


void rr(int burst[],int tq,int p_id[])
{  
  int i,j,last[n],wait[n],tat[n],w=0,t=0,check[n];
  for(i=0;i<n;i++)
  {
  	last[i]=burst[i];
  	check[i]=0;
  }
  int time=0;
  while("true")
  {
  	int flag=0;
  	for(i=0;i<n;i++)
  	{
  		if((last[i]>0) && (check[i]==0))
  		{
  			flag=1;
 	    	if(last[i]>tq)
        	{
        		printf("\nProcess id:%d\n",p_id[i]);
        	    time+=tq;
        	    last[i]-=tq;
        	}
  			else
      		{
      			printf("\nProcess id:%d\n",p_id[i]);
        	  	time+=last[i];
        	  	wait[i]=time-burst[i];
        	  	w+=wait[i];
        	  	for(j=0;j<n;j++)
        	  	{
        	  		if((last[j]<=tq-last[i]) && (check[j]==0) && (j!=i))
        	  		{
        	  			printf("\nProcess id:%d\n",p_id[j]);
        	  			time+=last[j];
        	  			wait[j]=time-burst[j];
        	  			w+=wait[j];
        	  			last[j]=0;
        	  			check[j]=1;
				  	}
			  	}
			  	check[i]=1;
        	  	last[i]=0;
        	}
  		}
 	}
  	if(flag==0)
  	break;
  }
  for(i=0;i<n;i++)
  {
    tat[i]=burst[i]+wait[i];
    t+=tat[i];
  }
  printf("\nProcess ID\tBurst Time\tTAT\tWaiting Time\n");
  for(i=0;i<n;i++)
  {
  	printf("%d\t\t%d\t\t%d\t\t%d\n",p_id[i],burst[i],tat[i],wait[i]);
  }
  float avg_w=(float)w/n;
  float avg_t=(float)t/n;
  printf("\nThe Average Waiting Time is:%f\nThe Average TAT is:%f\n",avg_w,avg_t);
}


int main()
{
  int avg=0,i,t;
  printf("\nEnter Number Of Processes: ");
  scanf("%d",&n);
  int pid[n],bt[n],pri[n];
  for(i=0;i<n;i++)
  {
  	printf("\nEnter Process ID: ");
    scanf("%d",&pid[i]);
    printf("\nEnter Burst Time: ");
    scanf("%d",&bt[i]);
    avg+=bt[i];	
  }
  avg=floor(avg/n);
  t=avg;
  printf("\nTime Quantum:%d\n",t);
  for(i=0;i<n;i++)
  {
  	pri[i]=bt[i]%avg;
  }
  sort(pid,pri,bt);
  rr(bt,t,pid);
}
