#include<stdio.h>
#include<string.h>
#define inf 0x7fffffff

void error()
{
	printf("Input error!\n");
}

int main(int argc,char* args[])
{
	int sum=-inf,a[2000][2000],b[2000],s[2000],h,l,i=0,j=0,k=0,t,y,m;
	int HEXT=0,VEXT=0;
	FILE* p;
	char x;
	char filename[256];
	memset(b,0,sizeof(b));

	for(i=1;i<argc;i++)
	{
		if(strcmp(args[i],"/h")==0)HEXT=1;
		if(strcmp(args[i],"/v")==0)VEXT=1;
		if(args[i][0]!='/')
			memcpy(filename, args[i], strlen(args[i])+1);
	}
	p=fopen("filename","r");
	fscanf(p,"%d%c",&h,&x);
	fscanf(p,"%d%c",&l,&x);
	for(i=0;i<h;i++)
	{
		for(j=0;j<l;j++)
			if(!(fscanf(p,"%d",&a[i][j])))
			{
				error();
				return 0;
			}
	}
	for(i=0;i<2*h-1;i++)
		for(j=0;j<2*l-1;j++)
			a[i][j]=a[i%h][j%l];

	for(i=0;i<h;i++)
	{
		if(!HEXT)
		{
			for(y=i;y<h;y++)
			{
				for(j=0;j<2*l-1;j++)
				{
					for(k=0;k<=y;k++)
						b[j]+=a[k][j];
				}
				if(!VEXT)
				{
					s[0]=b[0];
					for(t=1;t<l;t++)
						s[t]=(s[t-1]>0)?(s[t-1]+b[t]):b[t];
					for(t=0;t<l;t++)
						if(sum<s[t])sum=s[t];
					memset(b,0,sizeof(b));
				}
				else
				{
					for(m=0;m<l;m++)
					{
						s[m]=b[m];
						for(t=m+1;t<m+l;t++)
							s[t]=(s[t-1]>0)?(s[t-1]+b[t]):b[t];
						for(t=m;t<m+l;t++)
							if(sum<s[t])sum=s[t];
						memset(b,0,sizeof(b));
					}
				}
			}
		}
		else
		{
			for(y=i;y<i+h;y++)
			{
				for(j=0;j<2*l-1;j++)
				{
					for(k=0;k<=y;k++)
						b[j]+=a[k][j];
				}
				if(!VEXT)
				{
					s[0]=b[0];
					for(t=1;t<l;t++)
						s[t]=(s[t-1]>0)?(s[t-1]+b[t]):b[t];
					for(t=0;t<l;t++)
						if(sum<s[t])sum=s[t];
					memset(b,0,sizeof(b));
				}
				else
				{
					for(m=0;m<l;m++)
					{
						s[m]=b[m];
						for(t=m+1;t<m+l;t++)
							s[t]=(s[t-1]>0)?(s[t-1]+b[t]):b[t];
						for(t=m;t<m+l;t++)
							if(sum<s[t])sum=s[t];
						memset(b,0,sizeof(b));
					}
				}
			}
		}
	}

	fclose(p);
	printf("sum=%d\n",sum);
	return 0;
}