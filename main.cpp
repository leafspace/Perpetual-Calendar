#include <ctime>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
#define PCOX 50
#define PCOY 150
#define WEIT 70
#define HEIT 50
#define INFX 565
#define INFY 90
#define WEII 125
#define HEII 50
typedef struct
{
	char year[6];
	char month[10];
	char day[3];
	char week[10];
	char time[10];
}DAY;
typedef struct
{
	int year;
	int month;
	int day;
	int week;
}DAY_NUM;
int month[2][12]={31,28,31,30,31,30,31,31,30,31,30,31,
	              31,29,31,30,31,30,31,31,30,31,30,31
	};
char WEEK[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
char MONTH[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
void analysis(void);
void drawinfo(void);
void writetips(void);
void drawchoose(void);
void runcalendar(void);
void runchoose(char c);
void drawcalendar(void);
void cleancalendar(void);
void drawcalendarBG(void);
int leap_year(int year);
int count_week(int y,int c,int m,int d);
DAY TO_day;
DAY_NUM CO_day,today;
void main()
{
	while(1)
		runcalendar();
	
	getch();
	closegraph();
}
void drawcalendarBG(void)
{
	int i;
	setcolor(RGB(255,0,0));
	setfont(60,30,"黑体");
	outtextxy(30,30,"Perpetual Calendar");

	setcolor(RGB(140,140,140));
	rectangle(50,150,540,500);
	for(i=0;i<6;i++){
		line(50,200+i*HEIT,540,200+i*HEIT);
		line(120+i*WEIT,150,120+i*WEIT,500);
	}
	
	setfillcolor(RGB(54,197,233));
	for(i=0;i<7;i++)
		fillrectangle(50+i*WEIT,150,120+i*WEIT,200);

	setcolor(RGB(255,255,0));
	setfont(30,15,"黑体");
	outtextxy(70,160,"日");
	outtextxy(140,160,"一");
	outtextxy(210,160,"二");
	outtextxy(280,160,"三");
	outtextxy(350,160,"四");
	outtextxy(420,160,"五");
	outtextxy(490,160,"六");

	setcolor(RGB(140,140,140));
	rectangle(INFX,INFY,690,390);

	for(i=0;i<5;i++)
		line(INFX,INFY+(i+1)*HEII,INFX+WEII,INFY+(i+1)*HEII);

	setfillcolor(RGB(54,197,233));
	fillrectangle(INFX,INFY,INFX+WEII,INFY+HEII);
	setcolor(RGB(255,255,0));
	setfont(30,15,"黑体");
	outtextxy(INFX+25,INFY+10,"Today");

	setcolor(RGB(255,10,10));
	setfillcolor(RGB(255,10,10));
	fillrectangle(INFX+10,INFY+HEII*6+10,INFX+20,INFY+HEII*6+20);

	setcolor(RGB(50,245,55));
	setfillcolor(RGB(50,245,55));
	fillrectangle(INFX+10,INFY+HEII*6+30,INFX+20,INFY+HEII*6+40);

	setcolor(RGB(45,45,250));
	setfillcolor(RGB(45,45,250));
	fillrectangle(INFX+10,INFY+HEII*6+50,INFX+20,INFY+HEII*6+60);

	setcolor(RGB(140,140,140));
	setfont(10,7,"");
	outtextxy(INFX+30,INFY+HEII*6+10,"YOU CHOOSE");
	outtextxy(INFX+30,INFY+HEII*6+30,"TODAY");
	outtextxy(INFX+30,INFY+HEII*6+50,"GENERAL");
}
void drawinfo(void)
{
	int i;
	char str[25]={0};
	char tt[10]={0};
	time_t t;
    t=time(&t);
	sprintf(str,"%s",ctime(&t));

	sprintf(tt,"%s",&str[20]);
	tt[4]=0;
	strcpy(TO_day.year,tt);
	for(i=0;i<12;i++)
		if(MONTH[i][0]==str[4]&&MONTH[i][1]==str[5]&&MONTH[i][2]==str[6]){
			strcpy(TO_day.month,MONTH[i]);
			break;
		}
	TO_day.day[0]=str[8];
	TO_day.day[1]=str[9];
	TO_day.day[2]=0;
	for(i=0;i<7;i++)
		if(WEEK[i][0]==str[0]&&WEEK[i][1]==str[1]&&WEEK[i][2]==str[2]){
			strcpy(TO_day.week,WEEK[i]);
			break;
		}
	sprintf(tt,"%s",&str[11]);
	tt[8]=0;
	strcpy(TO_day.time,tt);
	setcolor(RGB(247,47,187));
	setfont(20,10,"宋体");
	outtextxy(INFX+43,INFY+HEII+15,TO_day.year);
	outtextxy(INFX+17,INFY+HEII*2+15,TO_day.month);
	outtextxy(INFX+53,INFY+HEII*3+15,TO_day.day);
	outtextxy(INFX+17,INFY+HEII*4+15,TO_day.week);
	outtextxy(INFX+23,INFY+HEII*5+15,TO_day.time);
}

void analysis(void)
{
	int i;
	today.year=(TO_day.year[0]-'0')*1000+(TO_day.year[1]-'0')*100+(TO_day.year[2]-'0')*10+(TO_day.year[3]-'0');
	for(i=0;i<12;i++)
		if(!strcmp(TO_day.month,MONTH[i])){
			today.month=i+1;
			break;
		}
	today.day=(TO_day.day[0]-'0')*10+(TO_day.day[1]-'0');
	today.week=count_week(today.year%100,today.year/100,today.month,today.day);
	CO_day=today;
	CO_day.day=1;
	CO_day.week=count_week(CO_day.year%100,CO_day.year/100,CO_day.month,CO_day.day);
}
int count_week(int y,int c,int m,int d)
{
	int w;
	if(m<3){
		m=12+m;
		y--;
	}
	w=(y+y/4+c/4-2*c+(26*(m+1)/10)+d-1)%7;
	if(w<0)
		w=w+7;
	return w;
}
void drawcalendar(void)
{
	int i;
	int num;
	int x,y;
	DAY_NUM T_day;
	T_day=CO_day;
	T_day.day=1;
	x=T_day.week=count_week(T_day.year%100,T_day.year/100,T_day.month,T_day.day);
	y=1;
	num=month[leap_year(T_day.year)][T_day.month-1];
	setfont(40,20,"");
	for(i=0;i<num;i++,T_day.day++){
		if(T_day.year==CO_day.year&&T_day.month==CO_day.month&&T_day.day==CO_day.day)
			setfillcolor(RGB(255,40,40));
		else if(T_day.year==today.year&&T_day.month==today.month&&T_day.day==today.day)
			     setfillcolor(RGB(50,245,55));
		     else
				 setfillcolor(RGB(45,45,250));
		setcolor(RGB(140,140,140));
		fillrectangle(PCOX+x*WEIT,PCOY+y*HEIT,PCOX+x*WEIT+WEIT,PCOY+y*HEIT+HEIT);
		char str[3]={0};
		sprintf(str,"%02d",i+1);
		setcolor(RGB(255,255,255));
		outtextxy(PCOX+x*WEIT+15,PCOY+y*HEIT+5,str);
		x++;
		if(x%7==0){
			y++;
			x=0;
		}
	}
}
int leap_year(int year)
{
	if(year%4==0&&year%100!=0||year%400==0)
		return 1;
	else
		return 0;
}
void runchoose(char c)
{
	switch(c)
			{
			    case 72 : CO_day.day-=7; break;
				case 80 : CO_day.day+=7; break;
				case 75 : CO_day.day-=1; break;
				case 77 : CO_day.day+=1; break;
			}
	if(CO_day.day<=0){
		CO_day.month--;
		if(CO_day.month<=0){
			CO_day.year--;
			CO_day.month=12;
		}
		CO_day.day=month[leap_year(CO_day.year)][CO_day.month-1];
	}
	if(CO_day.day>month[leap_year(CO_day.year)][CO_day.month-1]){
		CO_day.month++;
		if(CO_day.month>12){
			CO_day.year++;
			CO_day.month=1;
		}
		CO_day.day=1;
	}
}
void drawchoose(void)
{
	char str[50]={0};
	setcolor(RGB(140,140,140));
	setfillcolor(RGB(140,140,140));
	bar3d(130,100,510,140,5,1);
	setcolor(RGB(175,230,65));
	sprintf(str,"YOU CHOOSE DAY IS : %04d年%02d月%02d日",CO_day.year,CO_day.month,CO_day.day);
	setfont(20,10,"");
	outtextxy(150,110,str);
}
void cleancalendar(void)
{
	int i;
	setcolor(RGB(140,140,140));
	setfillcolor(RGB(0,0,0));
	fillrectangle(50,200,540,500);
	for(i=0;i<6;i++){
		line(50,200+i*HEIT,540,200+i*HEIT);
		line(120+i*WEIT,150,120+i*WEIT,500);
	}
}
void writetips(void)
{
	closegraph();
	char str[1000]={0};
	FILE *fp;
	if((fp=fopen("Diary.txt","a+"))==NULL){
		printf("File open error !\n");
		exit(-1);
	}
	fseek(fp,0,2);
	{
		char str[25]={0};
		sprintf(str,"%02d年%02d月%02d日",CO_day.year,CO_day.month,CO_day.day);
		puts(str);
		fprintf(fp,"%s\n",str);
	}
	gets(str);
	fprintf(fp,"%s\n",str);
	fclose(fp);
	runcalendar();
}
void runcalendar(void)
{
	initgraph(720,530);
	drawcalendarBG();
	drawinfo();
	analysis();
	drawchoose();
	drawcalendar();
	while(1){
		if(kbhit())
		{
			char c;
			c=getch();
			if(c==27)
				exit(0);
			if(c==13)
				writetips();
			cleancalendar();
			runchoose(c);
			drawchoose();
			drawcalendar();
		}
		drawinfo();
	}
}