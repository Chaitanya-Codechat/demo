#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100 
typedef struct _job { 
int jobId; 
int startTime; 
int jobLength;
int remLength; 
} job;
typedef struct _heap { 
job list[MAX_SIZE]; 
int numJobs; 
}heap;
typedef struct _jobPair { 
int jobid_from; 
int jobid_to; 
} jobpair; 
void swap(heap* H,int i,int j)
{
  job temp;
  temp=H->list[i];
  H->list[i]=H->list[j];
  H->list[j]=temp;
}
void intiheap(heap* H)
{
  H->numJobs=0;
}
void insertjob(heap* H,job j)
{
  H->numJobs=H->numJobs+1;
  H->list[H->numJobs-1]=j;
  int i=H->numJobs-1;
  while(1)
    {
      int p=(i-1)/2;
      if(H->list[p].remLength>H->list[i].remLength)
  {
    swap(H,p,i);
    i=p;
  }
      else
  return;
    }
}
int extractmin(heap* H,job* j)
{
  *j=(H->list[0]);
  if(H->numJobs==0)
    return -1;
  H->list[0]=H->list[H->numJobs-1];
  int i=0;
  H->numJobs--;
  int n=H->numJobs;
  while(1)
    {
      int l=2*i+1;
      int r=2*i+2;
      int minidx;
      if(l>=n)
  return 0;
      if(r>=n)
  minidx=l;
      else
  {
    if(H->list[l].remLength>H->list[r].remLength)
      minidx=r;
    else
      minidx=l;
  }
      if(H->list[i].remLength>H->list[minidx].remLength)
    swap(H,i,minidx);
      else
  return 0;
    }
}
// normal decrease key of priority queue
void decreasekey(heap *H,int jid)
{
  //printf("%d\n",jid);
  //If the jobid is there in heap or not
  int temp=-1;
  for(int a=0;a<H->numJobs;a++)
  {
    if(H->list[a].jobId==jid)
      {
        temp=a;
        break;
      }
  }
  //if not in heap or started already return
  if(temp==-1)
    return;
  if(H->list[temp].remLength!=H->list[temp].jobLength)
    return;
  //DO the remaining job by taking jobid to the temp where we had 
  jid=temp;
  H->list[jid].remLength=(H->list[jid].remLength)/2;
  int i=jid;
  while(i!=jid)
    {
      int p=(i-1)/2;
      if(H->list[i].remLength>H->list[p].remLength)
  swap(H,i,p);
      else
  break;
      i=p;
    }
}
// Changes are just to see if the extracted has a pair 
void newscheduler(job joblist[],int n,jobpair pairlist[],int p)
{
  heap H;
  intiheap(&H);
  int puttinaheap=0;
  //Print 0 until 1 is put
  int i=0;
  int time=0;
  job temp;
  int j=0;
  float letsee=0;
  int *arr;
  arr=(int *)malloc(sizeof(int)*n);
  for(int a=0;a<n;a++)
    arr[a]=-1;
  while(j!=n)
    {
      if(H.numJobs==0&&time!=joblist[i].startTime)
  {
    printf("0 ");
  }
      else if(i<n&&time==joblist[i].startTime)
  {
    while(i<n&&time==joblist[i].startTime)
      {
        insertjob(&H,joblist[i]);
        i++;
      }
  }
      //SEE WHO HAS 0 REMLENGTH EXTRACT THEM
      if(H.list[0].remLength==0)
  {
    extractmin(&H,&temp);// Take the key which is extracted and check its pairs with others
    int la=0;
    for(;la<p;la++)
      {
        if(temp.jobId==pairlist[la].jobid_from)
    {
      break;
    }
      }
    // If la==p then none of the keys matches hence just j++
    if(la!=p)
      {
        // printf("here\n");
        decreasekey(&H,pairlist[la].jobid_to);
      }
    j++;
  }
      H.list[0].remLength--;
      if(H.numJobs>0)
  {
    //PRINT THOSE WHO HAVE LEAST REMLENGTH
    printf("%d ",H.list[0].jobId);
    if(arr[H.list[0].jobId-1]==-1)
      {
        arr[H.list[0].jobId-1]=time-H.list[0].startTime;
      }
  }
  time++;
    }
  printf("\n");
  for(int a=0;a<n;a++)
    {
      letsee=letsee+arr[a];
      //printf("%d\n",arr[a]);
    }
  printf("Average Turnaround Time is %f\n",(float)(letsee/n));
}
int main()
{
  int n;
  printf("Entre The number of Jobs: ");
  cin>>n;
  printf("Entre the jobs: \n");
  heap H;
  job listi[n];
  for(int i=0;i<n;i++)
    {
      cin>>listi[i].jobId>>listi[i].startTime>>listi[i].jobLength;
      listi[i].remLength=listi[i].jobLength;
    }
  for(int i=0;i<n;i++)
    {
      int idx;
      int min=10000;
      for(int j=i;j<n;j++)
  {
    if(listi[j].startTime<min)
      {
        min=listi[j].startTime;
        idx=j;
      }
    job temp;
    temp=listi[i];
    listi[i]=listi[idx];
    listi[idx]=temp;
  }
    }
  int p;
  cin>>p;
  jobpair pairlist[p];
  for(int a=0;a<p;a++)
    {
      cin>>pairlist[a].jobid_from;
      cin>>pairlist[a].jobid_to;
    }
  //for(int i=0;i<n;i++)
  //printf("%d %d %d\n",listi[i].jobId,listi[i].startTime,listi[i].jobLength);
  newscheduler(listi,n,pairlist,p);
  return 0;
}
  