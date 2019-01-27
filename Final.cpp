#include<stdio.h>
#include<fstream.h>
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>

/***********************************************************************

				---------
				S.N.A.K.E
				---------

				Made By :
				=======

				TEAM X
				######

				Members :
				=======
				Samriddh Singh a.k.a Cyborg
				Ashish Gupta a.k.a Mr.X


				Compiled Using :
				--------------
				Borland Turbo C++ 3.0 Compiler.

************************************************************************/

struct Player
{
  char PlayerName[20];
  long SCORE;
} P;

struct Snake
{
  int x,y;
  Snake *nxt,*prv;
} X, *head=NULL, *tail=NULL, *temp;

// Function List
void CheckExisting(void);
void HighScoreMaker(void);
void Login(void);
void IntroScr(void);
void DevBy(void);
void blink(int,int,int,int);
void Presents(void);
void SnakeLogo(void);
void Draw(void);
void Selector(void);
void CycleUp(void);
void CycleDown(void);
void BeginGame(void);
void AddNode(int,int);
void DestroySnake(void);
int  PlayerDown(void);
void PopulateSnake(void);
int  HighScoreLoad(void);
void GenLevel(void);
void MakeFood(void);
void MoveRight(void);
void MoveUp(void);
void DrawSC(void);
void CycleUpSC(void);
void CycleDownSC(void);
void HighLight(int);
void SCSelector(void);
void MoveDown(void);
void MoveLeft(void);
void Update(void);
char Eat(void);
void CleanFood(void);
void Score(void);
int  MakeScore(char[],long);
void DifLevel(void);
void PlaySound(void);
void LivesLeft(void);
char CollideS(void);
char Collide(void);
void GameOver(void);
void PlaySound2(void);
void SaveGame(void);
void ResetStats(void);
void ContactUs(void);

fstream file;
int fclr=4, sclr=15, dvar=20, foodx=-1, foody=-1;
int GameNo=0;
char on='x', ch=0;                       // *Variable List BEGIN
int nx1=220, nx2=420, ny1=120, ny2=180;  //
int sx1=245, sx2=400, sy1=190, sy2=250;  //
int ex1=272, ex2=370, ey1=260, ey2=320;  // Draw();
int counter=0, overcount=0;              //
char ScoreVar[10];

char Top1[15], Top2[20], Top3[20], Top4[20], Top5[20], Top6[20]; //*Variable List END.
int tops1=0, tops2=0, tops3=0, tops4=0, tops5=0, tops6=0;
char tops1ar[10], tops2ar[10], tops3ar[10], tops4ar[10], tops5ar[10], tops6ar[10];

int onSC=0, SC=0, counterSC=0;
int tri1[8]={320, 15, 610, 100, 29, 100, 320, 15};
int tri2[8]={610, 340, 320, 425, 29, 340, 610, 340};

char sbody[]={char(233),'\0'};

int main()
{
  P.SCORE=0;
  strcpy(P.PlayerName,"Anonymous");

  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");

  IntroScr();
  DevBy();
  Presents();
  SnakeLogo();
  Draw();

  return 0;
}

void CheckExisting(void)
{
  Player Z;
  ifstream fileX;
  ofstream fileY;
  
  fileY.open("temp.dat",ios::binary);
  fileY.close();
  
  fileY.open("temp.dat",ios::binary|ios::app);
  
  fileX.open("Scores.dat",ios::binary);
  fileX.seekg(0,ios::end);
  long eofx=fileX.tellg() - sizeof(Player);
  fileX.seekg(0);
  
  while(fileX.tellg()<=eofx)
  {
    fileX.read((char *)&Z , sizeof(Player));
    if(strcmp(P.PlayerName,Z.PlayerName)==0) fileX.read((char *)&Z , sizeof(Player));
    else
      fileY.write((char *)&Z,sizeof(Player));
  }
  fileX.close();
  fileY.close();
  remove("Scores.dat");
  rename("temp.dat" , "Scores.dat");
}

void PopulateSnake(void)
{
  head=&X;
  tail=&X;
  X.x=400;
  X.y=280;
  for(int i=0;i<=10;i++)
    AddNode(400+i,280);
}

void MoveRight(void)
{

  for(;;)
  {

    setcolor(2);
    outtextxy(360,22,ScoreVar);
    if(head->x>=615){GameOver();}
    head->x=head->x+5;
    Update();
    setcolor(sclr);
    outtextxy(head->x,head->y,sbody);
    delay(dvar);
    setcolor(0);
    outtextxy(tail->x,tail->y,sbody);
    if(CollideS()=='y'|| Collide()=='y'){GameOver();}
    if (Eat()=='y'){Score();CleanFood();MakeFood();}

    while (kbhit())
    {
      char ch=getch();
      if(ch=='q') {SaveGame();Draw();}
      if(ch==0)  ch=getch();
      if(ch==72) MoveUp();
      if(ch==80) MoveDown();
    }
  }
}

void MoveUp(void)
{

  for(;;)
  {

    setcolor(2);
    outtextxy(360,22,ScoreVar);
    if(head->y<=60){GameOver();}
    head->y = head->y -5;
    Update();
    setcolor(sclr);
    outtextxy(head->x,head->y,sbody);
    delay(dvar);
    setcolor(0);
    outtextxy(tail->x,tail->y,sbody);

    if (Eat()=='y') {Score();CleanFood();MakeFood(); }
    if(CollideS()=='y'|| Collide()=='y'){GameOver();}

    if (kbhit())
    {
      char ch=getch();
      if(ch=='q') {SaveGame();Draw();}
      if(ch==0) ch=getch();
      if(ch==75) MoveLeft();
      if(ch==77) MoveRight();
    }
  }
}

void MoveDown(void)
{

  for(;;)
  {

    setcolor(2);
    outtextxy(360,22,ScoreVar);
    if(head->y>=452){GameOver();}
    head->y = head->y +5;
    Update();
    setcolor(sclr);
    outtextxy(head->x,head->y,sbody);
    delay(dvar);
    setcolor(0);
    outtextxy(tail->x,tail->y,sbody);
    if (Eat()=='y') {Score();CleanFood();MakeFood();}

    if(CollideS()=='y'|| Collide()=='y'){GameOver();}

    if (kbhit())
    {
      char ch=getch();
      if(ch=='q') {SaveGame();Draw();}
      if(ch==0) ch=getch();
      if(ch==75) MoveLeft();
      if(ch==77) MoveRight();
    }
  }
}

void MoveLeft(void)
{

  for(;;)
  {

    setcolor(2);
    outtextxy(360,22,ScoreVar);
    if(head->x<=21){GameOver();}
    head->x = head->x -5;
    Update();
    setcolor(sclr);
    outtextxy(head->x,head->y,sbody);

    setcolor(0);
    outtextxy(tail->x,tail->y,sbody);

    if(CollideS()=='y'|| Collide()=='y'){GameOver();}

    if (Eat()=='y') {Score();CleanFood();MakeFood();}
    delay(dvar);
    if (kbhit())
    {
      char ch=getch();
      if(ch=='q') {SaveGame();Draw();}
      if(ch==0)  ch=getch();
      if(ch==72) MoveUp();
      if(ch==80) MoveDown();

    }
  }
}

void MakeFood(void)
{
  randomize();
  fclr=rand()%15;
  while(fclr==0)
  {
    randomize();
    fclr=rand()%15;
  }
  foodx=rand()%500,foody=rand()%400;
  if(foodx<=25 || foodx>=615) foodx=150;
  if(foodx<=322 && foodx>=308) foodx=150;
  if(foody<=65 || foody>=455) foody=200;
  setcolor(fclr);
  circle(foodx,foody,2);
  setfillstyle(SOLID_FILL,fclr);
  floodfill(foodx,foody,fclr);
}

void Update(void)

{
  Snake *sort=tail;

  for(;;)
  {
    sort->x=sort->prv->x;
    sort->y=sort->prv->y;
    sort=sort->prv;
    if(sort==head) break;
  }
  setcolor(0);
  outtextxy(tail->x,tail->y,sbody);
}



void AddNode(int a,int b)
{
  temp=new Snake;
  temp->x=a;
  temp->y=b;
  temp->prv=tail;
  tail->nxt=temp;
  tail=temp;
  tail->nxt=NULL;
}

void CleanFood(void)
{
  setcolor(0);
  circle(foodx,foody,2);
  setfillstyle(SOLID_FILL,0);
  floodfill(foodx,foody,0);
  setcolor(2);
}

char CollideS(void)
{
  Snake *temp=head->nxt->nxt;

  while(temp->nxt!=NULL)
  {
    if (temp->y==head->y)
    {
      if (temp->x==head->x)
	return 'y';
    }
    temp=temp->nxt;
  }

  return 'n';
}

void EatSound(void)
{
  for (int i=0;i<100;i++)
  {
    sound(9*i);
    delay(1);
  }
  nosound();
}

char Eat(void)
{
  if ((head->x>=foodx-6 && head->x<=foodx+6) && (head->y>=foody-6 && head->y<=foody+6))
  {
    sclr=fclr;
    EatSound();
    AddNode(tail->x,tail->y);
    AddNode(tail->x,tail->y);
    AddNode(tail->x,tail->y);
    AddNode(tail->x,tail->y);
    AddNode(tail->x,tail->y);
    return 'y';
  }
  else
    return 'n';
}

void IntroScr(void)
{
  cleardevice();
  int b,i,j;
  setbkcolor(0);
  randomize();
  setfillstyle(11,1);
  for( i = 0 ; i<180;i++)
  {
    delay(10);
    line(315,225,315+i,225);
    setcolor(0);
    pieslice(315,225,0,360,i);
  }

  for( i = 0 ; i<250 ;i++)
  {
    delay(3);
    setfillstyle(11,4);
    bar(100+i, 120+i, 250+i, 100+i);
    setcolor(4);
    rectangle(102+i, 95+i, 250+i, 100+i);
  }

  setcolor(0);

  for(  i = 0 , j=2; i<295&&j<280 ;i++,j++)
  {
    setcolor(0);
    setfillstyle(6,4);
    delay(3);
    pieslice(161+i,380-i,1,360,6);
  }

  setcolor(15);
  rectangle(125,365,225,385);
  rectangle(390,95,490,115);
  setcolor(15);
  rectangle(123,363,227,387);
  rectangle(388,93,492,117);

  for(int sy=365;sy<=385;sy++)
  {
    delay(15);
    for(int sx=125;sx<=225;sx++)
      putpixel(sx,sy,4);
  }

  for(sy=95;sy<=115;sy++)
  {
    delay(15);
    for(int sx=390;sx<=490;sx++)
      putpixel(sx,sy,4);
  }

  setcolor(0);
  delay(200);

  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 7);
  delay(300);
  outtextxy(177, 195,"G.A.M.E.S");
  delay(300);
  setcolor(8);
  outtextxy(178, 195,"G.A.M.E.S");
  delay(300);
  setcolor(0);
  outtextxy(176, 195,"G.A.M.E.S");
  delay(300);
  setcolor(7);
  outtextxy(180, 195,"G.A.M.E.S");
  delay(300);
  setcolor(7);
  outtextxy(181, 195,"G.A.M.E.S");
  delay(300);
  setcolor(8);
  outtextxy(175, 195,"G.A.M.E.S");


  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 7);
  delay(300);
  outtextxy(177, 195,"G.A.M.E.S");
  delay(300);
  setcolor(8);
  outtextxy(178, 195,"G.A.M.E.S");
  delay(300);
  setcolor(0);
  outtextxy(176, 195,"G.A.M.E.S");
  delay(300);
  setcolor(7);
  outtextxy(180, 195,"G.A.M.E.S");
  delay(300);
  setcolor(8);
  outtextxy(181, 195,"G.A.M.E.S");
  delay(300);
  setcolor(8);
  outtextxy(175, 195,"G.A.M.E.S");
  int c=0;
  delay(500);

  for(;;)
  {
    for(i=1;i<7;i++)
    {
      setcolor(random(8));
      circle(315,225,190+i);
    }
    c++;
    if(c==40) break;
  }
}


int HighScoreLoad(void)
{
  cleardevice();
  setbkcolor(0);
  setfillstyle(8,4);
  int r=0,clr=0,k=0;

  for(int i=240;i>200;i--)
  {
    clr=0;
    if(i>220) clr=4;

    setcolor(clr);
    delay(20);
    circle(320,240,i);
  }

  for( i=170;i>=0;i--)
  {
    while(kbhit())
    {
      char ch=getch();
      if(ch=='q') {return 0;}
    }


    for(float i2=0;i2<6.28;i2=i2+0.1)
    {
      sound(80*i);
      k=i%50;

      setcolor(k);

      if(i==180) r=8;
      if(i==150) r=9;
      if(i==130) r=10;
      if(i==110) r=15;

      setfillstyle(1,i%15);
      pieslice(320+(i*cos(i2)),240+(i*sin(i2)),0,360,r);
    }

    nosound();
  }

  clr=1;

  for(i=200;i>180;i--)
  {
    setcolor(i%2);
    delay(30);
    circle(320,240,i);
  }


  delay(1000);

  setfillstyle(3,4);
  settextstyle(TRIPLEX_FONT,0,9);
  for(int x=0;x<640;x++)
  {

    delay(10);
    setcolor(0);
    line(x,200,x,280);
    setcolor(3);
    if(x==160)  outtextxy(50,180,"H");
    if(x==210) outtextxy(125,180,"I");
    if(x==260) outtextxy(155,180,"G");
    if(x==310) outtextxy(215,180,"H");
    if(x==360) outtextxy(305,180,"S");
    if(x==410) outtextxy(355,180,"C");
    if(x==460) outtextxy(405,180,"O");
    if(x==510) outtextxy(455,180,"R");
    if(x==560) outtextxy(505,180,"E");
    if(x==610) outtextxy(555,180,"S");

  }
  delay(2000);
}




void Presents(void) //.....PRESENTS.....//
{
  cleardevice();
  delay(1000);
  settextstyle(GOTHIC_FONT,0,7);

  setcolor(6);
  outtextxy(175,180,"Presents");
  delay(300);
  outtextxy(400,180,".");
  delay(300);
  outtextxy(415,180,".");
  delay(300);
  outtextxy(430,180,".");
  delay(100);
  setcolor(1);

  for(int i=640;i>200;i--)
  {
    delay(3);
    putpixel(i,250,1);
    if(i<=435)putpixel(i+205,250,0);
  }
  delay(150);

  for(i=640;i>195;i--)
  {
    delay(3);
    putpixel(i,254,4);
    if(i<=426)putpixel(i+214,254,0);
  }
  delay(100);

  for(i=640;i>185;i--)
  {
    delay(3);
    putpixel(i,258,GREEN);
    if(i<=411)putpixel(i+229,258,0);
  }


}

void SnakeLogo(void)
{
  cleardevice();
  char ch='A';int cvar=0;
  char z[2];
  setcolor(4);
  settextstyle(GOTHIC_FONT,HORIZ_DIR,10);

  int sc=0,nc=0,ac=0,kc=0,ec=0;
  randomize();
  cvar=rand()%15;
  for(int i=0;i<200;i++)
  {

    char s[2];char n[2];char a[2];char k[2];char e[2];
    if(ch+4>'Z') ch='A';
    s[0]=ch;n[0]=ch+1;a[0]=ch+1+1;k[0]=ch+1+1+1;e[0]=ch+1+1+1+1;
    s[1]='\0';n[1]='\0';a[1]='\0';k[1]='\0';e[1]='\0';

    if(ch%10!=0)
      setcolor(ch%10);
    else
      setcolor(1);

    if(sc>10+cvar) outtextxy(90,100,"S");
    else
    {
      outtextxy(90,100,s);
      sc++;
      delay(3);
    }
    if(nc>30+cvar) outtextxy(195,100,"N");
    else
    {
      outtextxy(195,100,n);
      nc++;
      delay(3);
    }

    if(ac>50+cvar) outtextxy(295,100,"A");
    else
    {
      outtextxy(295,100,a);
      ac++;
      delay(3);
    }

    if(kc>70+cvar) outtextxy(390,100,"K");
    else
    {
      outtextxy(390,100,k);
      kc++;
      delay(3);
    }

    if(ec>90+cvar) {outtextxy(495,100,"E");delay(3000);break;}
    {
      outtextxy(495,100,e);
      ec++;
      delay(3);
    }

    setcolor(0);
    outtextxy(90,100,s);
    outtextxy(195,100,n);
    outtextxy(295,100,a);
    outtextxy(390,100,k);
    outtextxy(495,100,e);
    delay(100);

    ch=ch+1;

  }
  setcolor(7);
  outtextxy(90,100,"S");
  outtextxy(195,100,"N");
  outtextxy(295,100,"A");
  outtextxy(390,100,"K");
  outtextxy(495,100,"E");
  delay(1500);
}

char Collide(void)
{
  if(head->x>=310 && head->x<=321)
  {
    for(int rj=40;rj<460;rj=rj+50)
    {
      for(int c=0;c<3;c++)
      {
	if(head->y>=rj-c+1 && head->y<=rj+c+3)
	{
	  return 'y';
	}
      }
    }
  }

  return 'n';
}

void Draw(void)
{
  cleardevice();
  setbkcolor(0);
  setcolor(1);
  int poly[]={100,45,260,85,380,85,540,45,500,235,540,425,380,375,260,375,100,425,140,235,100,45};

  int poly2[]={100,20,100,40,260,80,380,80,540,40,540,20,100,20};

  settextstyle(TRIPLEX_FONT,0,5);
  delay(1000);
  setcolor(CYAN);
  outtextxy(250,22,"SNAKE");
  setcolor(BLUE);
  drawpoly(11,poly);
  drawpoly(7,poly2);
  setcolor(WHITE);
  settextstyle(4,0,4);
  outtextxy(230,130,"NEW GAME");
  outtextxy(260,200,"SCORES");
  outtextxy(280,270,"QUIT");
  delay(1000);
  for(int i=10;i<=15;i++)
  {
    setfillstyle(i,4);
    delay(50);
    floodfill(10,10,1);
  }
  Selector();
}


void Selector(void)
{

  for(;;)
  {
    while(kbhit())
    {
      char ch=getch();

      if(ch==13)
      {
	if(on=='n') BeginGame();
	if(on=='s')
	{
	  HighScoreMaker();
	  if(GameNo==0) {HighScoreLoad();GameNo++;}
	  DrawSC();
	  SCSelector();
	}
	if(on=='e')
	{
	  cleardevice();
	  ContactUs();
	  exit(0);
	}
      }

      if(ch==0)
      {
	ch=getch();
	if(ch==72)CycleUp();
	if(ch==80)CycleDown();
      }
    }
  }
}


void CycleUp(void)
{

  if(counter==0)
  {
    counter=1;
    on='s';
  }

  if(on=='n')
  {
    setcolor(0);
    rectangle(nx1,ny1,nx2,ny2);

    setcolor(GREEN);
    rectangle(ex1,ey1,ex2,ey2);
    on='e';
    Selector();
  }

  if(on=='s')
  {
    setcolor(0);
    rectangle(sx1,sy1,sx2,sy2);

    setcolor(YELLOW);
    rectangle(nx1,ny1,nx2,ny2);

    on='n';
    Selector();
  }

  if(on=='e')
  {
    setcolor(0);
    rectangle(ex1,ey1,ex2,ey2);

    setcolor(LIGHTRED);
    rectangle(sx1,sy1,sx2,sy2);
    on='s';
    Selector();
  }


}

void CycleDown(void)
{
  if(counter==0)
  {
    counter=1;
    on='e';
  }


  if(on=='n')
  {
    setcolor(0);
    rectangle(nx1,ny1,nx2,ny2);

    setcolor(BLUE);
    rectangle(sx1,sy1,sx2,sy2);
    on='s';
    Selector();
  }

  if(on=='s')
  {
    setcolor(0);
    rectangle(sx1,sy1,sx2,sy2);

    setcolor(WHITE);
    rectangle(ex1,ey1,ex2,ey2);

    on='e';
    Selector();
  }

  if(on=='e')
  {
    setcolor(0);
    rectangle(ex1,ey1,ex2,ey2);

    setcolor(RED);
    rectangle(nx1,ny1,nx2,ny2);
    on='n';
    Selector();
  }


}

void BeginGame(void)
{
  ResetStats();
  cleardevice();
  Login();
  if(strcmp(P.PlayerName,"")==0) strcpy(P.PlayerName,"Anonymous");
  CheckExisting();
  PopulateSnake();
  GenLevel();
  MakeFood();
  MoveLeft();
}

void ResetStats(void)
{
  fclr=4,sclr=15,dvar=20,foodx=-1,foody=-1;
  counterSC=0;counter=0;

  P.SCORE=-10;
  Score();
  strcpy(P.PlayerName,"Anonymous");
  counter=0,overcount=0;
//namex=225,namey=200;
  DifLevel();
}

void DevBy(void)
{
  cleardevice();
  int x=70;
  blink(220,130,3,200);
  settextstyle(TRIPLEX_FONT,0,4);
  setcolor(GREEN);
  outtextxy(224,100,"D");
  delay(x);
  outtextxy(244,100,"E");
  delay(x);
  outtextxy(264,100,"V");
  delay(x);
  outtextxy(284,100,"E");
  delay(x);
  outtextxy(304,100,"L");
  delay(x);
  outtextxy(324,100,"O");
  delay(x);
  outtextxy(344,100,"P");
  delay(x);
  outtextxy(364,100,"E");
  delay(x);
  outtextxy(384,100,"D");

  blink(400,130,2,200);
  blink(275,210,5,180);

  setcolor(GREEN);
  delay(x);
  outtextxy(280,180,"B");
  delay(x);
  outtextxy(300,180,"Y");
  blink(314,210,5,180);

  x=200;
  setcolor(RED);
  settextstyle(TRIPLEX_FONT,0,7);
  outtextxy(215,300,"T");
  delay(x);
  outtextxy(250,300,"E");
  delay(x);
  outtextxy(285,300,"A");
  delay(x);
  outtextxy(320,300,"M");
  delay(x);

  for(int i=220;i<=430;i++)
  {
//putpixel(i,375,BLUE);
    putpixel(i,370,BLUE);
    putpixel(i,373,BLUE);
//putpixel(i,382,BLUE);
    delay(6);
  }
  setcolor(WHITE);
  for(i=0;i<3;i++)
  {
    line(420+i,305,360+i,405);
    line(380+i,315,420+i,365);
  }

  delay(1000);
}

void blink(int i,int j,int n,int t)
{
  for(int c=0;c<n;c++)
  {
    setcolor(GREEN);
    sound(800);
    line(i,j,i+20,j);
    line(i,j+1,i+20,j+1);
    delay(t);
    nosound();
    setcolor(BLACK);
    line(i,j,i+20,j);
    line(i,j+1,i+20,j+1);
    delay(t);
  }
}

int MakeScore(char Arr[],long x)
{
  long z=x;int num=0;
  z=x;

  if(x==0)
  {
    strcpy(Arr,"000");
    return 0;
  }

  while(z!=0)
  {
    z=z/10;
    num++;
  }

  int i=0;

  if(x<100 && x>0)
  {
    i=-1;
    Arr[0]='0';
  }

  Arr[num-i]='\0';

  z=x;

  while(z!=0)
  {       i++;
    switch(z%10)
    {
    case 0: Arr[num-i]=char(48);break;
    case 1: Arr[num-i]=char(49);break;
    case 2: Arr[num-i]=char(50);break;
    case 3: Arr[num-i]=char(51);break;
    case 4: Arr[num-i]=char(52);break;
    case 5: Arr[num-i]=char(53);break;
    case 6: Arr[num-i]=char(54);break;
    case 7: Arr[num-i]=char(55);break;
    case 8: Arr[num-i]=char(56);break;
    case 9: Arr[num-i]=char(57);break;
    }

    z=z/10;
  }

  return 0;
}

void Score(void)
{
  P.SCORE=P.SCORE+10;

  if((P.SCORE!=0) && (P.SCORE%100==0)) {
    dvar=dvar-2;
    DifLevel();
  }

  setcolor(0);
  outtextxy(360,22,ScoreVar);
  MakeScore(ScoreVar,P.SCORE);
}

void GenLevel(void)
{       cleardevice();
  setbkcolor(0);
  settextstyle(0,0,1);
  int d=0;
  for(int i=0,j=40;i<20;i++,j++)
  {
    setcolor(i+1);
    setcolor(i%10);
    rectangle(i,j,640-i,480-i);
    delay(125);
  }

  for(int rj=90;rj<460;rj=rj+50)
  {
    d++;
    for(int c=0;c<3;c++)
    {
      setcolor(d);
      rectangle(314-c,rj-c,318+c,rj+4+c);
      delay(100);
    }
  }

  for(int bory=42,borx=0;borx<320;bory--,borx++)
  {
    setcolor(borx%10);

    if(bory>=7)
    {
      outtextxy(436,bory,"~");
      outtextxy(200,bory,"~");
    }
    outtextxy(320-borx,5,"*");
    outtextxy(320+borx,5,"*");
    delay(10);
  }
  setcolor(15);
  outtextxy(260,22,"YOUR SCORE : ");
  setcolor(RED);
  outtextxy(20,22,"LEVEL : ");
  setcolor(6);
  outtextxy(450,22,"LIVES : ");
  LivesLeft();
}

void LivesLeft(void)
{
  int i = 3 - overcount;
  setcolor(0);
  for(int j=0;j<3;j++)
    outtextxy(510+(15*j),22,"*");

  setcolor(6);
  for(j=0;j<i;j++)
    outtextxy(510+(15*j),22,"*");
}

void DifLevel(void)
{
  int z=20-dvar;
  setcolor(12);
  for(int i=0;i<(z/2);i++)
    outtextxy(80+(8*i),22,"!");
}

void GameOver(void)
{
  overcount++;
  LivesLeft();

  if(overcount<3)
  {
    PlaySound();
    DestroySnake();
    EatSound();
    PlayerDown();
    PopulateSnake();
    MoveLeft();
  }

  PlaySound2();

  for(int i=0;i<80;i++)

  {
    setcolor(rand()%15);
    circle(head->x,head->y,i);
    delay(20);
  }

  cleardevice();
  SaveGame();
  int shp1[26]={100,160,200,80,290,95,320,65,350,95,440,80,540,160,440,100,350,120,320,90,290,120,200,100,100,160};
  randomize();
  setcolor(15);
  drawpoly(13,shp1);
  setfillstyle(1,4);
  fillpoly(13,shp1);
  setcolor(RED);
  settextstyle(GOTHIC_FONT,0,6);
  outtextxy(155,130,"GAME OVER");
  setcolor(4);
  outtextxy(156,130,"GAME OVER");
  setcolor(RED);
  outtextxy(154,130,"GAME OVER");
  outtextxy(157,130,"GAME OVER");

  float A,Bb,D,G,F;

  Bb = 461;
  F = 687;
  A = 440;
  G = 780;
  D = 586;

  int sum=0;
  for(;;)
  {
    sum=sum+1;
    if(sum==2){clrscr();Draw();}
    for(int i=0;i<320;i++)

    {

      setcolor(0);
      setfillstyle(1,0);
      pieslice(135+i,random(40)+200,0,360,1);
      if(i%70==0)
      {
	sound(A);
	sound(Bb);
	delay(30);
	sound(D);
	delay(70);
	sound(A);
	delay(70);
	sound(Bb);
	delay(40);
	sound(F);
	delay(70);
	sound(G);
	delay(30);
	sound(G);
	delay(70);
	sound(Bb);
	delay(70);
	sound(F);
	delay(40);
	nosound();
      }

      while(kbhit())
      {
	char ch=getch();
	if(ch=='q') {ResetStats(); Draw();}
      }

      delay(5);
      setcolor(4);
      pieslice(random(180)+155,i+190,0,3.14,1.2);
      setcolor(0);
      delay(20);
      pieslice(155+i,random(40)+145,0,360,1);
      setcolor(4);
      pieslice(random(150)+335,i+190,0,3.14,1.2);
      setcolor(0);
      pieslice(175+i,random(40)+145,0,360,1);
      pieslice(random(180)+155,i+190,0,3.14,1);
      pieslice(random(150)+385,i+190,0,3.14,1);
      delay(10);
      putpixel(random(640),(random(480))+i,random(40));
    }
  }

}

void DestroySnake(void)
{
  Snake *tmp=tail;
  while(tmp->prv!=NULL)
  {
    setcolor(0);
    outtextxy(tmp->x,tmp->y,sbody);
    delay(40);
    tmp=tmp->prv;
  }
  setcolor(sclr);
}

int PlayerDown(void)
{
  int dvar2=700;
  int i=3-overcount;
  settextstyle(TRIPLEX_FONT,0,5);
  setcolor(4);

  if (i==2)
  {
    CleanFood();
    setcolor(RED);
    outtextxy(70,100,"TWO");
    outtextxy(70,200,"LIVES");
    outtextxy(70,300,"REMAIN...");
    setcolor(0);
    delay(dvar2);
    outtextxy(70,300,"REMAIN...");
    setcolor(4);
    outtextxy(70,300,"REMAIN...3");
    delay(dvar2);
    setcolor(0);
    outtextxy(70,300,"REMAIN...3");
    setcolor(4);
    outtextxy(70,300,"REMAIN...2");
    delay(dvar2);
    setcolor(0);
    outtextxy(70,300,"REMAIN...2");
    setcolor(4);
    outtextxy(70,300,"REMAIN...1");
    setcolor(0);
    delay(dvar2);

    outtextxy(70,100,"TWO");
    outtextxy(70,200,"LIVES");
    outtextxy(70,300,"REMAIN...1");

    delay(dvar2);

    settextstyle(0,0,0);
    MakeFood();
    return 0;
  }

  if(i==1)
  {
    CleanFood();
    setcolor(RED);
    outtextxy(70,100,"LAST");
    outtextxy(70,200,"LIFE");
    outtextxy(70,300,"REMAINS..");
    setcolor(0);
    delay(dvar2);
    outtextxy(70,300,"REMAINS..");
    setcolor(4);
    outtextxy(70,300,"REMAINS..3");
    delay(dvar2);
    setcolor(0);
    outtextxy(70,300,"REMAINS..3");
    setcolor(4);
    outtextxy(70,300,"REMAINS..2");
    delay(dvar2);
    setcolor(0);
    outtextxy(70,300,"REMAINS..2");
    setcolor(4);
    outtextxy(70,300,"REMAINS..1");
    setcolor(0);
    delay(dvar2);

    outtextxy(70,100,"LAST");
    outtextxy(70,200,"LIFE");
    outtextxy(70,300,"REMAINS..1");

    delay(dvar2);

    settextstyle(0,0,0);
    MakeFood();
    return 0;
  }

  return 0;
}



void PlaySound(void)
{
  float A,Bb,D,G,F;
  A = 440;
  G = 780;
  Bb = 461;
//D = 586;
  F = 687;
  sound(G);
  for(int i=0;i<1;i++)
  {
    sound(G);
    delay(100);
    sound(F);
    delay(100);
    sound(A);
    delay(100);
    sound(Bb);
    delay(100);
  }
  nosound();
}

void PlaySound2(void)
{
  float A,Bb,D,G,F;
  A = 440;
  G = 780;
  Bb = 461;
  D = 586;
  F = 687;
  sound(G);

  for(int i=0;i<1;i++)
  {
    sound(G);
    delay(100);
    sound(F);
    delay(100);
    sound(D);
    delay(100);
    sound(Bb);
    delay(100);
    sound(A);
    delay(100);
  }
  nosound();
}

void Login(void)
{
  cleardevice();
  int z=0,i=0,curlen=0;
  settextstyle(GOTHIC_FONT,0,6);
  outtextxy(100,80,"Before We Start..");
  delay(1000);
  cleardevice();
  outtextxy(100,80,"What's Your Name ?");

input:
  ch=getch();

  while(ch!=13)
  {
    while(ch==0)
    {
      ch=getch();
      ch=getch();
    }

    if(ch!=8)
    {
      if(ch<32 || ch>126) goto input;
    }

    if(ch==8)
    {
      if(curlen>0)
      {
	curlen--;
	z=0;
	while(P.PlayerName[z]!='\0')
	  z++;
	setcolor(0);
	outtextxy(225,200,P.PlayerName);
	if(z>0) P.PlayerName[z-1]='\0';
	setcolor(GREEN);
	outtextxy(225,200,P.PlayerName);
	i--;
	setcolor(15);
	goto input;
      }
      else goto input;
    }

    if(ch>=32 && ch<=126)
    {
      if(curlen<12)
      {
	curlen++;
	P.PlayerName[i]=ch;
	P.PlayerName[i+1]='\0';
	setcolor(0);
	outtextxy(225,200,P.PlayerName);
	setcolor(RED);
	outtextxy(225,200,P.PlayerName);
	ch=getch();
      }
      else
	goto input;
    }

    i++;
  }
  P.PlayerName[i]='\0';

  delay(2000);
  cleardevice();
  setcolor(WHITE);
}

void SaveGame(void)
{
  file.open("SCORES.dat",ios::out|ios::app|ios::binary);
  file.write((char *)&P,sizeof(P));
  file.close();
}

void HighScoreMaker(void)
{
  long EndOfFile=0;

  file.open("SCORES.dat",ios::in|ios::binary);

  Player ScoreList[50],X;

  file.seekg(0,ios::end);
  EndOfFile=file.tellg();
  EndOfFile-=sizeof(Player);

  file.seekg(0);

  int i=0;

  while(file.tellp()<=EndOfFile)
  {
    file.read((char *)&X,sizeof(P));
    ScoreList[i].SCORE=X.SCORE;
    strcpy(ScoreList[i].PlayerName,X.PlayerName);
    i++;
  }
  file.close();

  int z=i;

  for(i;i<6;i++)
  {
    ScoreList[i].SCORE=0;
    strcpy(ScoreList[i].PlayerName,"Empty");
  }

  for(i;i<50;i++)
    ScoreList[i].SCORE=-1;

  long tmp=0;
  char tmpname[50];


  for(i=0;i<z;i++)
    for(int j=0;j<z-i;j++)
    {
      if(ScoreList[j].SCORE < ScoreList[j+1].SCORE)
      {
	tmp=ScoreList[j].SCORE;
	strcpy(tmpname,ScoreList[j].PlayerName);

	ScoreList[j].SCORE=ScoreList[j+1].SCORE;
	strcpy(ScoreList[j].PlayerName,ScoreList[j+1].PlayerName);

	strcpy(ScoreList[j+1].PlayerName,tmpname);
	ScoreList[j+1].SCORE=tmp;
      }
    }

  strcpy(Top1,ScoreList[0].PlayerName);tops1=ScoreList[0].SCORE;
  strcpy(Top2,ScoreList[1].PlayerName);tops2=ScoreList[1].SCORE;
  strcpy(Top3,ScoreList[2].PlayerName);tops3=ScoreList[2].SCORE;
  strcpy(Top4,ScoreList[3].PlayerName);tops4=ScoreList[3].SCORE;
  strcpy(Top5,ScoreList[4].PlayerName);tops5=ScoreList[4].SCORE;
  strcpy(Top6,ScoreList[5].PlayerName);tops6=ScoreList[5].SCORE;
}

void DrawSC(void)
{
  MakeScore(tops1ar,tops1);
  MakeScore(tops2ar,tops2);
  MakeScore(tops3ar,tops3);
  MakeScore(tops4ar,tops4);
  MakeScore(tops5ar,tops5);
  MakeScore(tops6ar,tops6);

  cleardevice();
  settextstyle(0,0,0);
  int x1,y1,x2,y2,x3,y3;

  for(int i =0;i<60;i++)
  {
    int trap[14]={320+i,10+i,620-i,100-i,620-i,340+i,320+i,430-i,20+i,340+i,20+i,100-i,320-i,10+i};
    int rect[10]={30,105,610,105,610,335,30,335,30,105};
    setcolor(1);
    drawpoly(7,trap);
    setfillstyle(1,4) ;
    fillpoly(7,trap);

    drawpoly(5,rect);
    setfillstyle(1,30) ;
    fillpoly(5,rect);

    drawpoly(4,tri1);
    setfillstyle(1,1);
    fillpoly(4,tri1);

    drawpoly(4,tri2);
    fillpoly(4,tri2);
  }

  float A,Bb,D,G,F;
  A = 440;
  G = 780;
  D = 586;

  sound(G);
  sound(D);
  delay(100);
  sound(D);
  delay(500);
  sound(A);
  delay(500);
  sound(A);
  delay(100);
  sound(G);
  delay(500);
  sound(G);
  delay(100);
  sound(D);
  delay(500);
  sound(D);
  delay(500);
  sound(A);
  delay(100);
  nosound();

  setcolor(0);
  setfillstyle(1,GREEN);
  bar3d(30,110,605,330,10,20);

  setcolor(WHITE);
  setfillstyle(1,BLACK);
  settextstyle(1,0,5);
  bar(460,125,580,160);
  outtextxy(460,115,"SCORE");

  bar(45,125,150,160);
  outtextxy(45,115,"RANK");
  settextstyle(1,0,2);

  setcolor(0);
  setfillstyle(1,4);

  int k=0;
  for(int j=128;j<320;j=j+32)
  {
    switch(k)
    {
    case 0:outtextxy(250,j,Top1);
      break;
    case 1:outtextxy(250,j,Top2);
      break;
    case 2:outtextxy(250,j,Top3);
      break;
    case 3:outtextxy(250,j,Top4);
      break;
    case 4:outtextxy(250,j,Top5);
      break;
    case 5:outtextxy(250,j,Top6);
      break;
    }
    k++;
    delay(20);
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
  }

  char ch;
  for(;;)
  {
    while(kbhit())
    {
      ch=getch();
      if(ch==0) ch=getch();
      if(ch==72 || ch==80)
      {
	SCSelector();
      }

      if(ch=='q'){ResetStats();Draw();}
    }
  }
}

void SCSelector(void)

{

  for(;;)
  {
    while(kbhit())
    {
      char ch=getch();
      if(ch==0) ch=getch();
      if(ch=='q'){ResetStats();Draw();}
      if(ch==72)CycleUpSC();
      if(ch==80)CycleDownSC();
    }
  }
}

void CycleUpSC(void)
{
  setcolor(0);
  setfillstyle(1,0);
  fillpoly(4,tri1);
  delay(190);
  setfillstyle(1,1);
  fillpoly(4,tri1);
  setfillstyle(1,4);

  for(int j=288;j>108;j=j-32)
  {
    setfillstyle(1,YELLOW);

    delay(20);
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
    delay(20);

    setfillstyle(1,4);
    delay(20);
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
  }

  setcolor(RED);
  settextstyle(1,0,5);
  outtextxy(460,115,"SCORE");
  line(460,160,580,160);
  line(460,125,580,125);
  outtextxy(45,115,"RANK");
  line(45,160,150,160);
  line(45,125,150,125);

  delay(200);

  setcolor(WHITE);
  settextstyle(1,0,5);
  outtextxy(460,115,"SCORE");
  line(460,160,580,160);
  line(460,125,580,125);
  outtextxy(45,115,"RANK");
  line(45,160,150,160);
  line(45,125,150,125);

  settextstyle(1,0,2);


  if(counterSC==0)
  {
    counterSC=1;
    onSC=2;
  }

  switch(onSC)
  {
  case 1:	HighLight(6);
    onSC=6;
    SCSelector();
    break;

  case 2:	HighLight(1);
    onSC=1;
    SCSelector();
    break;

  case 3:	HighLight(2);
    onSC=2;
    SCSelector();
    break;

  case 4:	HighLight(3);
    onSC=3;
    SCSelector();
    break;

  case 5: HighLight(4);
    onSC=4;
    SCSelector();
    break;

  case 6: HighLight(5);
    onSC=5;
    SCSelector();
    break;
  }
}

void CycleDownSC(void)
{

  setcolor(0);
  setfillstyle(1,0);
  fillpoly(4,tri2);
  delay(190);
  setfillstyle(1,1);
  fillpoly(4,tri2);
  setfillstyle(1,4);

  for(int j=128;j<320;j=j+32)
  {
    setfillstyle(1,YELLOW);
    delay(20);
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
    delay(20);

    setfillstyle(1,4);
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
    delay(20);
  }


  setcolor(RED);
  settextstyle(1,0,5);
  outtextxy(460,115,"SCORE");
  line(460,160,580,160);
  line(460,125,580,125);
  outtextxy(45,115,"RANK");
  line(45,160,150,160);
  line(45,125,150,125);

  delay(200);

  setcolor(WHITE);
  settextstyle(1,0,5);
  outtextxy(460,115,"SCORE");
  line(460,160,580,160);
  line(460,125,580,125);
  outtextxy(45,115,"RANK");
  line(45,160,150,160);
  line(45,125,150,125);

  settextstyle(1,0,2);

  if(counterSC==0)
  {
    counterSC=1;
    onSC=6;
  }

  switch(onSC)
  {
  case 1:	HighLight(2);
    onSC=2;
    SCSelector();
    break;

  case 2:	HighLight(3);
    onSC=3;
    SCSelector();
    break;

  case 3:	HighLight(4);
    onSC=4;
    SCSelector();
    break;

  case 4:	HighLight(5);
    onSC=5;
    SCSelector();
    break;

  case 5: HighLight(6);
    onSC=6;
    SCSelector();
    break;

  case 6: HighLight(1);
    onSC=1;
    SCSelector();
    break;
  }
}


void HighLight(int np)
{
  setcolor(0);  //LIFT BLOCKS BOUNDARY COLOR
  for(int j=128;j<320;j=j+32)
  {
    bar3d(175,j,200,30+j,2,20);
    delay(20);
    bar3d(400,j,425,j+30,2,20);
  }

  //Highlight colour
  switch(np)
  {

  case 1: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    settextstyle(1,0,2);
    outtextxy(250,128,Top1);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops1ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"1");
    settextstyle(1,0,2);
    outtextxy(250,160,Top2);
    outtextxy(250,288,Top6);

    break;

  case 2: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    outtextxy(250,160,Top2);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops2ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"2");
    settextstyle(1,0,2);
    outtextxy(250,128,Top1);
    outtextxy(250,192,Top3);
    break;

  case 3: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    outtextxy(250,192,Top3);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops3ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"3");
    settextstyle(1,0,2);

    outtextxy(250,160,Top2);
    outtextxy(250,224,Top4);
    break;

  case 4: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    outtextxy(250,224,Top4);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops4ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"4");
    settextstyle(1,0,2);


    outtextxy(250,192,Top3);
    outtextxy(250,256,Top5);
    break;

  case 5: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    outtextxy(250,256,Top5);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops5ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"5");
    settextstyle(1,0,2);

    outtextxy(250,224,Top4);
    outtextxy(250,288,Top6);
    break;

  case 6: 	setfillstyle(1,GREEN);
    bar(445,165,600,260);
    bar(60,180,140,320);
    setfillstyle(1,RED);
    setcolor(RED);
    outtextxy(250,288,Top6);
    setcolor(0);
    settextstyle(1,0,8);
    outtextxy(446,180,tops6ar);
    settextstyle(1,0,10);
    outtextxy(72,160,"6");
    settextstyle(1,0,2);

    outtextxy(250,128,Top1);
    outtextxy(250,256,Top5);
    break;
  }
}



void ContactUs(void)
{
  settextstyle(4,0,4);
  setcolor(RED);
  outtextxy(10,50,"For Details/Feedback....");
  setcolor(CYAN);
  outtextxy(10,120,"Contact :");
  setcolor(WHITE);
  outtextxy(10,180,"Ashish Gupta");
  outtextxy(10,300,"Samriddh Singh");
  settextstyle(4,0,4);
  setcolor(LIGHTRED);
  outtextxy(165,120,".E.A.M .:X:. ");
  settextstyle(1,0,4);
  outtextxy(145,120,"T");
  setcolor(GREEN);
  outtextxy(10,230,"ashmew2@gmail.com");
  outtextxy(10,350,"rustyrazor.sx@gmail.com");
  getch();
}
