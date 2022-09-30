#include<stdio.h>
#include<math.h>
int time_q(int b[],int num)
{
    int tq=0;
    int count=0,i;
    for(i=0;i<num;i++)
    {
    	if(b[i]>0)
    	{
            tq+=b[i];
            count++;
    }}
    if(count>0)
    {
    tq=tq/count;
}
    return tq;
}
void sort(int id[],int wt[],int b[],int a[],int nom,int fl[],int ob[],int com_t[])
{
	int i,j;
	int number=nom;
	for(i=0;i<number;i++)
    {
		for(j=i+1;j<number;j++)
        {
            if(wt[i]>wt[j])
            {
              	a[i]+=a[j];
                a[j]=a[i]-a[j];
                a[i]=a[i]-a[j];
              	id[i]+=id[j];
                id[j]=id[i]-id[j];
                id[i]=id[i]-id[j];
              	b[i]+=b[j];
                b[j]=b[i]-b[j];
                b[i]=b[i]-b[j];
                ob[i]+=ob[j];
                ob[j]=ob[i]-ob[j];
                ob[i]=ob[i]-ob[j];
                wt[i]+=wt[j];
                wt[j]=wt[i]-wt[j];
                wt[i]=wt[i]-wt[j];
                fl[i]+=fl[j];
                fl[j]=fl[i]-fl[j];
                fl[i]=fl[i]-fl[j];
                com_t[i]+=com_t[j];
                com_t[j]=com_t[i]-com_t[j];
                com_t[i]=com_t[i]-com_t[j];
            }
            else if(wt[i]==wt[j])
            {
          	    if(id[i]>id[j])
                {
                    a[i]+=a[j];
                    a[j]=a[i]-a[j];	
                    a[i]=a[i]-a[j];
                    id[i]+=id[j];
                    id[j]=id[i]-id[j];
                    id[i]=id[i]-id[j];
                    b[i]+=b[j];
                    b[j]=b[i]-b[j];
                    b[i]=b[i]-b[j];
                    wt[i]+=wt[j];
                    wt[j]=wt[i]-wt[j];
                    wt[i]=wt[i]-wt[j];
                    fl[i]+=fl[j];
                	fl[j]=fl[i]-fl[j];
                	fl[i]=fl[i]-fl[j];
                	ob[i]+=ob[j];
                	ob[j]=ob[i]-ob[j];
                	ob[i]=ob[i]-ob[j];
                	com_t[i]+=com_t[j];
                	com_t[j]=com_t[i]-com_t[j];
                	com_t[i]=com_t[i]-com_t[j];
                }
            }
        }
    }

}

void rr(int no,int burst[],int time_quantum,int arr[],int w[],int p_id[],int fla[], int obt[])
{
    int i,j,time=time_quantum,bur[no],p[no],art[no],weight[no],num=0,obur[no],ct[no],tat[no],wt[no];
    float avg_tat=0.0,avg_wt=0.0;
    for(i=0;i<no;i++)
    {
        if(arr[i]<=time && fla[i]==0)
        {
           bur[i]=burst[i];
           obur[i]=obt[i];
           p[i]=p_id[i];
           weight[i]=w[i];
           art[i]=arr[i];
           fla[i]=1;
           ct[i]=0;
           num++;
        }
        else
        break;
    }
    time_quantum=time_q(bur,num);
    sort(p,weight,bur,art,num,fla,obur,ct);
    int counter=0,temp=0,la,solve=0;
	int k;
	while(counter<no)
	{
		for(k=0;k<num;k++)
		{
			
    		if((bur[k]<=time_quantum) && (bur[k]>0)) 
			{	
				
				counter++;
				time=time+bur[k]; 
		    	bur[k]=0;
		    	ct[k]=time;
			}
			else if(bur[k]>0) 
			{
				time=time+time_quantum;
				int l;
				for(l=0;l<num;l++)
				{
					if((bur[l]<=time_quantum-bur[k]) && (ct[l]==0) && (l!=k))
					{	
						counter++;
						time=time+bur[l]; 
		    			bur[l]=0;
		    			ct[l]=time;
					}
				}
		   		bur[k]=bur[k]-time_quantum; 
		   		
			}
		}
		int check=num;
		for(j=num;j<no;j++)
		{
			
			if((arr[j]<=time) && (fla[j]==0))
			{
		    	bur[j]=burst[j];
		    	obur[j]=obt[j];
		    	p[j]=p_id[j];
		    	weight[j]=w[j];
		    	art[j]=arr[j];
		    	fla[j]=1;
		    	ct[j]=0;
		    	check++;
			}
			else
			break;
		}
		num=check;
		time_quantum=time_q(bur,num);
    	sort(p,weight,bur,art,num,fla,obur,ct);
	}
	printf("\nPID\tBT\tCOMP TIME\tTAT\tWAIT TIME\n");
	for(i=0;i<no;i++)
	{
		tat[i]=ct[i]-art[i];
		wt[i]=tat[i]-obur[i];
		avg_tat+=tat[i];
		avg_wt+=wt[i];
		printf("P[%d]\t|\t%d\t|\t%d|\t%d|\t%d\n",p[i],obur[i],ct[i],tat[i],wt[i]);
	}
	avg_tat=avg_tat/no;
	avg_wt=avg_wt/no;
	printf("\nThe Average TAT: %f\n",avg_tat);
	printf("\nThe Average WT: %f\n",avg_wt);
}

int main()
{
    int n;
    printf("\nEnter Number Of Processes: ");
    scanf("%d",&n);
    int pid[n],bt[n],at[n],pri[n],tc,flag[n],i;
    int wt_fac[n],og_burst[n];
    printf("\nEnter First Arrival First!!!\n");
    for(i=0;i<n;i++)
    {
        printf("\nEnter Process ID: ");
        scanf("%d",&pid[i]);
        printf("\nEnter Burst Time: ");
        scanf("%d",&bt[i]);
        og_burst[i]=bt[i];
        printf("\nEnter Arrival Time: ");
        scanf("%d",&at[i]);
        flag[i]=0;
        wt_fac[i]=bt[i];
    }
    tc=at[0];
    int ti_q=tc;
    rr(n,bt,ti_q,at,wt_fac,pid,flag,og_burst);
    return 0;
}
