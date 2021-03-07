#include<iostream.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
int x[21],y[21];
int h[15],k[15];  //co-ordinates of centre of 15 mines
int box[15][15];  //2D array storing status of each box
int flag[15][15]; //2D array storing the flag status of each box
int val[15][15];  /*2D array of values corresponding to the number of mines
			adjacent to each box */
int stat;  //status of game(win/lose)
void grid(); //function to lay the grid and determine position of mines
void inst(); //function to display instructions panel
void dispmine(); //function to show mines
void move(char p,int &q,int &r); //register the movement of cursor
void mark(int r,int s); //actions to take place when box is marked
void main()
{
	start:
	stat=0;
	randomize();
	for(int a=0;a<15;a++)
	{
		for(int b=0;b<15;b++)
		{
			box[a][b]=0; //each box is niether marked nor occupies a mine initially
			flag[a][b]=0; //no box is flagged initially
		}
	}
	int gd=DETECT,gm;
	rprs:
	initgraph(&gd,&gm,"c:/tc/bgi");
	cout<<"\t\tWELCOME TO MINESWEEPER\n\n\n";
	delay(500);
	grid(); //laying the grid
	inst(); //instruction panel
	for(int c=0;c<15;c++)
	{
		box[((h[c]-70)/20)-1][((k[c]-70)/20)-1]=1; /*box having mines
							     have value 1*/
	}
	for(int d=0;d<15;d++)
	{
		for(int e=0;e<15;e++)
		{
			if(box[d][e]==0)
			{
				int count=0; //stores the number of adjacent mines
				if(d>0 && box[d-1][e]==1)
					++count;
				if(d<14 && box[d+1][e]==1)
					++count;
				if(e>0 && box[d][e-1]==1)
					++count;
				if(e<14 && box[d][e+1]==1)
					++count;
				if(d>0 && e>0 && box[d-1][e-1]==1)
					++count;
				if(d>0 && e<14 && box[d-1][e+1]==1)
					++count;
				if(d<14 && e>0 && box[d+1][e-1]==1)
					++count;
				if(d<14 && e<14 && box[d+1][e+1]==1)
					++count;
				val[d][e]=count; //stores value for each box
			}
		}
	}
	int r=230,s=230; //coordinates of initial position of cursor
	setcolor(LIGHTGREEN);  //colour of cursor is light green
	rectangle(r-5,s-5,r+5,s+5); //cursor
	setcolor(BLACK);
	while(stat==0)
	{
		int p=getch(); //accept key for movement
		switch(p)
		{
			case 'w':{                   //up
					if(s>90) /*ensure cursor doesn't move
						   when in top row*/
						move(p,r,s); //move cursor
				}
				 break;
			case 's':{                    //down
					if(s<370) /*ensure cursor doesn't move
						    when in bottom row*/
						move(p,r,s);
				 }
				 break;
			case 'a':{                    //left
					if(r>90) /*doesn't move when in
						   leftmost row*/
						move(p,r,s);
				 }
				 break;
			case 'd':{                    //right
					if(r<370) /*doesn't move when in
						    rightmost row*/
						move(p,r,s);
				 }
				 break;
			case 'x':{                    //box is marked
					if(flag[((r-70)/20)-1][((s-70)/20)-1]!=1 && box[((r-70)/20)-1][((s-70)/20)-1]!=2) //doesn't mark if box is marked or flagged
					{
						mark(r,s); //mark the box
						if(val[((r-70)/20)-1][((s-70)/20)-1]==0 && stat==0)
						//box has no adjacent mines
						{
							//mark all adjacent boxes
							if(r>90)
								mark(r-20,s);
							if(r<370)
								mark(r+20,s);
							if(s>90)
								mark(r,s-20);
							if(s<370)
								mark(r,s+20);
							if(r>90 && s>90)
								mark(r-20,s-20);
							if(r>90 && s<370)
								mark(r-20,s+20);
							if(r<370 && s>90)
								mark(r+20,s-20);
							if(r<370 && s<370)
								mark(r+20,s+20);
						}
						setcolor(LIGHTGREEN);
						rectangle(r-5,s-5,r+5,s+5);
						int m,n;
						for(m=0;m<15;m++) //loop to check each box
						{
							for(n=0;n<15;n++)
							{
								if(box[m][n]==0)
									break;
							}
							if(box[m][n]==0)
								break;
						}
						if(m==14 && n==15) //all boxes are marked or have a mine
							stat=2;
					}
				 }
				 break;
			case 'f':{
					if(box[((r-70)/20)-1][((s-70)/20)-1]!=2) //box isn't marked
					{
						if(flag[((r-70)/20)-1][((s-70)/20)-1]==0) //box isn't marked
						{
							flag[((r-70)/20)-1][((s-70)/20)-1]=1; //flag it
							setcolor(LIGHTRED);
						}
						else
						{
							flag[((r-70)/20)-1][((s-70)/20)-1]=0; //remove flag
							setcolor(BLACK);
						}
						int n=0;
						while(n<4) //indicate flag
						{
							circle(r,s,n);
							n++;
						}
					}
				 }
				 break;
			case 'e':{
					cout<<"Exit?(Y/N) ";
					e:
					int e=getch();
					switch(e)
					{
						case 'y':return;
							 break;
						case 'n':cout<<"\b\b\b\b\b\b\b\b\b\b\b          \b\b\b\b\b\b\b\b\b\b\b";
							 break;
						default:goto e; //to not count any other input
							break;
					}
				}
			case 'g':{
				instruction();
				goto rprs;
			}
		}
		int q;
		switch(stat)
		{
			case 1:{              //game lost
					dispmine(); //show mines
					cout<<"GAME OVER!!!\n";
					delay(1000);
					cout<<"Press E to exit or N for new game";
					a:
					q=getch();
					switch(q)
					{
						case 'e':return; //leave game
							 break;
						case 'n':goto start;
							 break;
						default:goto a;
							break;
					}
				}
				break;
			case 2:{              //game won
					cout<<"YOU WIN!!!\n";
					delay(1000);
					cout<<"Press E to exit or N for new game";
					b:
					q=getch();
					switch(q)
					{
						case 'e':return; //leave game
							 break;
						case 'n':goto start; //new game
							 break;
						default:goto b;
							break;
					}
				}
				break;
		}
	}
	getch();
	cleardevice();
	closegraph();
}
void grid() //function to lay grid
{
	for(int i=1;i<=16;i++) //vertical lines
	{
		x[i]=(20*i)+60;
		line(x[i],80,x[i],380);
		delay(100);
	}
	for(int j=1;j<=16;j++) //horizontal lines
	{
		y[j]=(20*j)+60;
		line(80,y[j],380,y[j]);
		delay(100);
	}
	for(int a=0;a<15;a++) //coordinates of mines
	{
		h[a]=((random(15)+1)*20)+70;
		k[a]=((random(15)+1)*20)+70;
	}
}
void inst() //function to show instructions panel
{
	rectangle(450,95,630,330);
	outtextxy(480,85,"INSTRUCTIONS");
	outtextxy(460,105,"Movement - WASD");
	outtextxy(460,115,"Mark - X");
	outtextxy(460,125,"Flag/Unflag - F");
	outtextxy(460,140,"0 adjacent mines");
	outtextxy(460,155,"1 adjacent mine");
	outtextxy(460,170,"2 adjacent mines");
	outtextxy(460,185,"3 adjacent mines");
	outtextxy(460,200,"4 adjacent mines");
	outtextxy(460,215,"5 adjacent mines");
	outtextxy(460,230,"6 adjacent mines");
	outtextxy(460,245,"7 adjacent mines");
	outtextxy(460,260,"8 adjacent mines");
	outtextxy(460,275,"Exit - E");
	outtextxy(460,290,"Gameplay - G");
	for(int i=0;i<=8;i++)
	{
		switch(i)
		{
			case 0:setcolor(LIGHTGRAY);
				break;
			case 1:setcolor(BROWN);
				break;
			case 2:setcolor(MAGENTA);
				break;
			case 3:setcolor(RED);
				break;
			case 4:setcolor(LIGHTMAGENTA);
				break;
			case 5:setcolor(BLUE);
				break;
			case 6:setcolor(LIGHTBLUE);
				break;
			case 7:setcolor(CYAN);
				break;
			case 8:setcolor(LIGHTCYAN);
				break;
		}
		int l=0;
		while(l<5)
		{
			rectangle(600,145+(15*i)-l,610,145+(15*i)+l);
			++l;
		}
	}
}
void dispmine() //function to show mines
{
	for(int b=0;b<=14;b++)
	{
		setcolor(YELLOW);
		for(int c=7;c>=1;c--)
		{
			circle(h[b],k[b],c);
		}
		setcolor(WHITE);
	}
}
void move(char p,int &q,int &r) //function to move cursor
{
	setcolor(BLACK);
	rectangle(q-5,r-5,q+5,r+5);
	switch(p)
	{
		case 'w':r-=20; //up
			 break;
		case 'a':q-=20; //left
			 break;
		case 's':r+=20; //down
			 break;
		case 'd':q+=20; //right
			 break;
	}
	setcolor(LIGHTGREEN);
	rectangle(q-5,r-5,q+5,r+5);
}
void mark(int r,int s) //function to mark box
{       //colours depicting no. of adjacent bombs
	if(val[((r-70)/20)-1][((s-70)/20)-1]==0)
		setcolor(LIGHTGRAY);  //0 adjacent mines
	if(val[((r-70)/20)-1][((s-70)/20)-1]==1)
		setcolor(BROWN);      //1
	if(val[((r-70)/20)-1][((s-70)/20)-1]==2)
		setcolor(MAGENTA);    //2
	if(val[((r-70)/20)-1][((s-70)/20)-1]==3)
		setcolor(RED);        //3
	if(val[((r-70)/20)-1][((s-70)/20)-1]==4)
		setcolor(LIGHTMAGENTA); //4
	if(val[((r-70)/20)-1][((s-70)/20)-1]==5)
		setcolor(BLUE);         //5
	if(val[((r-70)/20)-1][((s-70)/20)-1]==6)
		setcolor(CYAN);         //6
	if(val[((r-70)/20)-1][((s-70)/20)-1]==7)
		setcolor(LIGHTBLUE);    //7
	if(val[((r-70)/20)-1][((s-70)/20)-1]==8)
		setcolor(LIGHTCYAN);    //8
	int l=0;
	while(l<10)
	{
		rectangle(r-l,s-l,r+l,s+l);
		l++;
	}
	if(box[((r-70)/20)-1][((s-70)/20)-1]==1) //if marked box has mine
	{
		stat=1; //game lost
	}
	box[((r-70)/20)-1][((s-70)/20)-1]=2; //marked box has value 2
}
void instruction()
{​​​​​
clrscr();
delay(100);
outtextxy(40,40,"You are presented with a board of squares.");
delay(100);
outtextxy(40,50,"Some squares contain mines (bombs), others don't.");
delay(100);
outtextxy(40,60,"If you click on a square containing a bomb, you lose.");
delay(100);
outtextxy(40,70,"If you manage to click all the empty squares you win.");
delay(100);
outtextxy(40,90,"Clicking a square which doesn't have a bomb reveals the number of");
delay(100);
outtextxy(40,100,"neighbouring squares containing bombs.");
delay(100);
outtextxy(40,110,"Use this information plus some guess work to avoid the bombs.");
delay(100);
outtextxy(40,130,"To open a square, point at the square and click on it.");
delay(100);
outtextxy(40,140,"To mark a square you think is a bomb, point and");
delay(100);
outtextxy(40,150,"right-click (or hover with the mouse and press Space).");
char orp;
cin>>orp;
if(orp='e')
{​​​​​
exit;
}​​​​​
}​​​​​