#include<stdio.h>
int a[101][101];
int n;
void Prim()
{
	int w[101]={0};
    int b[101];
	int i,j,t,time,tmin=0,p=1;
	for(i=1;i<=n;i++)
	{
		w[i]=a[1][i];
		b[i]=0;
	}
	b[1]=1;
	for(i=2;i<=n;i++)
	{
		t=1;
		time=10001;
		for(j=2;j<=n;j++)
		{
			if(!b[j]&&w[j]<time)
			{
				t=j;
			    time=w[j];
			}
		}
		tmin+=time;
		b[t]=1;
		for(j=2;j<=n;j++)
		{
			if(!b[j]&&w[j]>a[t][j])
				w[j]=a[t][j];
		}
		
	}
	for(i=1;i<=n;i++)
	{
		if(b[i]==0)
		{
			p=0;break;
		}
	}
	if(p==1) printf("%d\n",tmin);
}


int main()
{
    int i,j,m,t1,t2,t3;

	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			a[i][j]=10001;

    for(i=1;i<=m;i++)    
	{
		scanf("%d %d %d",&t1,&t2,&t3);   
		a[t2][t1]=a[t1][t2]=t3;
	}

	Prim();  
	return 0;
}

