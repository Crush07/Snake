#include<iostream>
#include<time.h>
#include<conio.h>
#include<graphics.h>
int t=100;
char a[5];
char botton=72;
int nofood=0;
int nosleep=0;
int score=0;
int eat=0;
int g_map[19][19]=
{
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};
void food();
void g_print();
void move();
void snake(int*pmax,int*pi,int*pj);
void main()
{
	initgraph(680,608);
	outtextxy(630,20,"得分");
	food();	
	g_print();
	while(1)
	{
			move();
			outtextxy(630,70,"得分");
		MOUSEMSG m;
		m=GetMouseMsg();
		while(m.mkLButton!=1)
		{
			m=GetMouseMsg();
		}
	}
}
void food()
{

	int x,y;
	while(1)
	{
		srand((unsigned)time(0));
		y=rand()%17+1;
		srand((unsigned)time(0));
		x=rand()%17+1;
		if(g_map[y][x]==0) break;
	}
	g_map[y][x]=1;
}
void g_print()
{
	IMAGE m;
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<19;j++)
		{
			if(g_map[i][j]==0)
			{
				loadimage(&m,"0.jpg",24,24);
				putimage(j*24,i*24,&m);
			}
			else if(g_map[i][j]==1)
			{
				loadimage(&m,"1.jpg",24,24);
				putimage(j*24,i*24,&m);
			}
			else if(g_map[i][j]==2)
			{
				loadimage(&m,"2.jpg",24,24);
				putimage(j*24,i*24,&m);
			}
			else if(g_map[i][j]>2)
			{
				loadimage(&m,"3.jpg",24,24);
				putimage(j*24,i*24,&m);
			}
		}
	}
	sprintf(a, "%d", score);
	outtextxy(630,40,a);
}
void move()
{
	int i,j;
	int pi,pj;
	int max=2;
	int pmax;
	g_print();
while(1)
{
	switch(botton)
	{
	case 72://上
		while(1)
		{
			if(clock()%t==0||nosleep==1)
			{
				for(int i=0;i<19;i++)
				{
					for(int j=0;j<19;j++)
					{
						if(g_map[i][j]==1) nofood=1;
					}
				}
				if(nofood==0) food();	
				max=2;
				for(i=0;i<19;i++)
				{
					for(j=0;j<19;j++)
					{
						if(g_map[i][j]>max)
						{
							max=g_map[i][j];
							pi=i;
							pj=j;
						}
					}
				}
				for(i=0;i<19;i++)
				{
					if(g_map[1][i]==max) return;
				}
				if(g_map[pi-1][pj]==max-1)
				{
					botton=80;
					break;
				}
				if(g_map[pi-1][pj]<max-1&&g_map[pi-1][pj]>2) return;
				if(g_map[pi-1][pj]==1)
				{
					g_map[pi-1][pj]=max+1;
					score++;
					g_print();
					nofood=0;
					botton=72;
					break;
				}
					g_map[pi-1][pj]=max;
					snake(&max,&pi,&pj);
					nosleep=0;
				g_print();
			}	
			else if((clock()%t!=0)&&kbhit())
			{
				if(kbhit())
				{
					g_print();
					botton=getch();
					if(botton!=80&&botton!=77&&botton!=75) botton=72;
					else
					nosleep=1;
					break;
				}
			}
		}
		break;
	case 80://下
		while(1)
		{
			if(clock()%t==0||nosleep==1)
			{
				for(int i=0;i<19;i++)
				{
					for(int j=0;j<19;j++)
					{
						if(g_map[i][j]==1) nofood=1;
					}
				}
				if(nofood==0) food();	
				max=2;
				for(i=0;i<19;i++)
				{
					for(j=0;j<19;j++)
					{
						if(g_map[i][j]>max)
						{
							max=g_map[i][j];
							pi=i;
							pj=j;
						}
					}
				}
				for(i=0;i<19;i++)
				{
					if(g_map[17][i]==max) return;
				}
				if(g_map[pi+1][pj]==max-1)
				{
					botton=72;
					break;
				}
				if(g_map[pi+1][pj]<max-1&&g_map[pi+1][pj]>2) return;
				if(g_map[pi+1][pj]==1)
				{
					g_map[pi+1][pj]=max+1;
					score++;
					g_print();
					nofood=0;
					botton=80;
					break;
				}
					g_map[pi+1][pj]=max;
					snake(&max,&pi,&pj);
					nosleep=0;
				g_print();
			}
			else if((clock()%t!=0)&&kbhit())
			{
				if(kbhit())
				{
					g_print();
					botton=getch();
					if(botton!=72&&botton!=77&&botton!=75) botton=80;
					else
					nosleep=1;
					break;
				}
			}
		}
		break;
	case 75://左
		while(1)
		{
			if(clock()%t==0||nosleep==1)
			{
				for(int i=0;i<19;i++)
				{
					for(int j=0;j<19;j++)
					{
						if(g_map[i][j]==1) nofood=1;
					}
				}
				if(nofood==0) food();	
				max=2;
				for(i=0;i<19;i++)
				{
					for(j=0;j<19;j++)
					{
						if(g_map[i][j]>max)
						{
							max=g_map[i][j];
							pi=i;
							pj=j;
						}
					}
				}
				for(i=0;i<19;i++)
				{
					if(g_map[i][1]==max) return;
				}
				if(g_map[pi][pj-1]==max-1)
				{
					botton=77;
					break;
				}
				if(g_map[pi][pj-1]<max-1&&g_map[pi][pj-1]>2) return;
				if(g_map[pi][pj-1]==1)
				{
					g_map[pi][pj-1]=max+1;
					score++;
					g_print();
					nofood=0;
					botton=75;
					break;
				}
					g_map[pi][pj-1]=max;
					snake(&max,&pi,&pj);
					nosleep=0;
				g_print();	
			}
			else if((clock()%t!=0)&&kbhit())
			{
				if(kbhit())
				{
					g_print();
					botton=getch();
					if(botton!=80&&botton!=77&&botton!=72) botton=75;
					else
					nosleep=1;
					break;
				}
			}
		}
		break;
	case 77://右
		while(1)
		{
			if(clock()%t==0||nosleep==1)
			{
				for(int i=0;i<19;i++)
				{
					for(int j=0;j<19;j++)
					{
						if(g_map[i][j]==1) nofood=1;
					}
				}
				if(nofood==0) food();	
				max=2;
				for(i=0;i<19;i++)
				{
					for(j=0;j<19;j++)
					{
						if(g_map[i][j]>max)
						{
							max=g_map[i][j];
							pi=i;
							pj=j;
						}
					}
				}
				for(i=0;i<19;i++)
				{
					if(g_map[i][17]==max) return;
				}
				if(g_map[pi][pj+1]==max-1)
				{
					botton=75;
					break;
				}
				if(g_map[pi][pj+1]<max-1&&g_map[pi][pj+1]>2) return;
				if(g_map[pi][pj+1]==1)
				{
					g_map[pi][pj+1]=max+1;
					score++;
					g_print();
					nofood=0;
					botton=77;
					break;
				}
					g_map[pi][pj+1]=max;
					snake(&max,&pi,&pj);
					nosleep=0;
				g_print();			
			}
			else if((clock()%t!=0)&&kbhit())
			{
				if(kbhit())
				{
					g_print();
					botton=getch();
					if(botton!=80&&botton!=72&&botton!=75) botton=77;
					else
					nosleep=1;
					break;
				}
			}
		}
		break;
	}
}
}
void snake(int*max,int*pi,int*pj)
{
	int pmax=*max;
	while(pmax-1>2)
	{
		for(int i=0;i<19;i++)
		{
			for(int j=0;j<19;j++)
			{
				if(g_map[i][j]==pmax-1)
				{
					g_map[*pi][*pj]=g_map[i][j];
					*pi=i;
					*pj=j;
					pmax--;
					if(pmax==3) break;
				}
			}
			if(pmax==3) break;
		}
	}
	g_map[*pi][*pj]=0;
}