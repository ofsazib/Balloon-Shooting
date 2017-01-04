// A Game of Baloon Shooting...


#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13


void welcome_screen();
void Menu();
void play();
void help();
void draw_screen();
void draw_baloon(int x, int y, int c);
void draw_shaft(int x, int y, int c);
void show_score(int chance, int success, int score, int color);
void display_score();
void about();

int score;

void main()
{
	clrscr();

	int gd=0,detect;

	initgraph(&gd,&detect,"C:\\TC\\BGI ");

    welcome_screen();

    cleardevice();

	Menu();

	getch();
}

void welcome_screen()
{
    setfillstyle(0,3);
    bar(0,0,1000,500);

    settextstyle(1, HORIZ_DIR, 5);
    outtextxy(210,30,"WELCOME");
    outtextxy(270,80, "TO");

    setcolor(14);
    settextstyle(1,HORIZ_DIR,7);
    outtextxy(30,120, "BALOON SHOOTING");

    setcolor(15);
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(0,375,"DEVELOPED BY:");

    
    outtextxy(30,420,"Omar Faruk Sazib (CE12047)");
    

    outtextxy(430,375,"SUPERVISED BY:");

    outtextxy(460,400,"MORIUM AKTER");
    outtextxy(460,420,"LECTURER, DEPT. OF CSE");
    outtextxy(460,440,"MBSTU.");

    settextstyle(0,HORIZ_DIR,2);
    outtextxy(220,265,"LOADING");

    settextstyle(0,HORIZ_DIR,2);
    for(int i=0; i<3; i++)
    {
        for(int k=0; k<=24; k+=8)
        {
            setcolor(15);
            outtextxy(330+k,265,".");
            delay(1000);
        }

        for(k=24; k>=0; k-=8)
        {
            setcolor(0);
            outtextxy(330+k,265,".");
        }
    }
}

void play()
{
    draw_screen();

	int chance=5, success=0, chance_end=0, ball_diff=30, hit=0, flag=0;
	int shaft_x=185, shaft_y=200, shaft_color=4;

	score=0;

	int balon1_x = 400;
	int balon2_x = balon1_x + ball_diff;
	int balon3_x = balon2_x + ball_diff;

	int baloon_y = 400, baloon_color = 15;
    int baloon1 = 1, baloon2 = 1, baloon3 = 1;

	union REGS ii, oo;

	//Show Primary Score...

	show_score(chance, success, score, 0);

	draw_shaft(shaft_x, shaft_y, shaft_color);

	draw_baloon(balon1_x, baloon_y, baloon_color);
	draw_baloon(balon2_x, baloon_y, baloon_color);
	draw_baloon(balon3_x, baloon_y, baloon_color);

    char ch;

    while(1)
    {
        chance_end=0;

        baloon1 = 1; baloon2 = 1; baloon3 = 1;

        while(!chance_end)
        {
            //Moving up baloons until any key from the key board is hitted...

            while(!kbhit())
            {
                delay(35);   // Time delay '20' mili secoends.

                // Vanishing ballons...

                baloon_color = 1;

                draw_baloon(balon1_x, baloon_y, baloon_color);
                draw_baloon(balon2_x, baloon_y, baloon_color);
                draw_baloon(balon3_x, baloon_y, baloon_color);

                // Moving up baloons & draw in the new palace...

                --baloon_y;
                baloon_color = 15;

                draw_baloon(balon1_x, baloon_y, baloon_color);
                draw_baloon(balon2_x, baloon_y, baloon_color);
                draw_baloon(balon3_x, baloon_y, baloon_color);

            }

            ii.h.ah=0;
            int86(22,&ii,&oo);

            if(oo.h.al==0)  //if the pressed key was a function key....
            {
                switch(oo.h.ah)
                {
                    case UP:

                        //irrage shaft from the old place...

                        shaft_color=1;
                        draw_shaft(shaft_x, shaft_y, shaft_color);

                        //draw the shaft in the new place...

                        shaft_y -= 5;
                        shaft_color=4;
                        draw_shaft(shaft_x, shaft_y, shaft_color);

                        break;

                    case DOWN:

                         shaft_color=1;
                         draw_shaft(shaft_x, shaft_y, shaft_color);

                         shaft_y += 5;
                         shaft_color=4;
                         draw_shaft(shaft_x, shaft_y, shaft_color);

                        break;
                }
            }

            else
            {
                switch(oo.h.al)
                {
                    case ENTER:   //Enter key was pressed

                        //move the baloons & shaft...

                        do
                        {
                            delay(35);

                            // move baloon1 if it is ON...

                            if(baloon1==1)
                            {
                                baloon_color=1;
                                draw_baloon(balon1_x, baloon_y, baloon_color);

                                baloon_color=15;
                                draw_baloon(balon1_x, baloon_y-1, baloon_color);
                            }

                            //move baloon2 if it is on...

                            if(baloon2==1)
                            {
                                baloon_color=1;
                                draw_baloon(balon2_x, baloon_y, baloon_color);

                                baloon_color=15;
                                draw_baloon(balon2_x, baloon_y-1, baloon_color);
                            }

                            // move baloon3 if it is on...

                            if(baloon3==1)
                            {
                                baloon_color=1;
                                draw_baloon(balon3_x, baloon_y, baloon_color);

                                baloon_color=15;
                                draw_baloon(balon3_x, baloon_y-1, baloon_color);
                            }

                            baloon_y--;

                            shaft_color=1;
                            draw_shaft(shaft_x, shaft_y, shaft_color);
                            shaft_x += 5;
                            shaft_color=4;
                            draw_shaft(shaft_x, shaft_y, shaft_color);


                            //check if baloon1 is on & it is hitted...

                            if(baloon1==1 && (shaft_x > balon1_x-10 && shaft_x < balon1_x+10 && shaft_y  > baloon_y-10 && shaft_y < baloon_y+10))
                            {
                                baloon_color=1;
                                draw_baloon(balon1_x, baloon_y, baloon_color);

                                sound(1500);
                                delay(35);
                                nosound();

                                shaft_color=1;
                                draw_shaft(shaft_x, shaft_y, shaft_color);

                                show_score(chance, success, score, 3);

                                success++;
                                score += 10;

                                show_score(chance, success, score, 0);

                                hit++;
                                baloon1=0;

                                flag=1;
                            }

                            if(baloon2==1 && (shaft_x > balon2_x-10 && shaft_x < balon2_x+10 && shaft_y  > baloon_y-10 && shaft_y < baloon_y+10))
                            {
                                baloon_color=1;
                                draw_baloon(balon2_x, baloon_y, baloon_color);

                                sound(1500);
                                delay(35);
                                nosound();

                                shaft_color=1;
                                draw_shaft(shaft_x, shaft_y, shaft_color);

                                show_score(chance, success, score, 3);

                                success++;
                                score += 10;

                                show_score(chance, success, score, 0);

                                hit++;
                                baloon2=0;

                                flag=1;
                            }

                            if(baloon3==1 && (shaft_x > balon3_x-10 && shaft_x < balon3_x+10 && shaft_y  > baloon_y-10 && shaft_y < baloon_y+10))
                            {
                                baloon_color=1;
                                draw_baloon(balon3_x, baloon_y, baloon_color);

                                sound(1500);
                                delay(35);
                                nosound();

                                shaft_color=1;
                                draw_shaft(shaft_x, shaft_y, shaft_color);

                                show_score(chance, success, score, 3);

                                success++;
                                score += 10;

                                show_score(chance, success, score, 0);

                                hit++;
                                baloon3=0;

                                flag=1;
                            }


                            if(shaft_x > balon1_x+240 || baloon_y < 0)
                            {
                                // irrage both balon1 & shaft...

                                baloon_color=1;
                                draw_baloon(balon1_x, baloon_y, baloon_color);
                                draw_baloon(balon2_x, baloon_y, baloon_color);
                                draw_baloon(balon3_x, baloon_y, baloon_color);

                                shaft_color=1;
                                draw_shaft(shaft_x, shaft_y, shaft_color);

                                show_score(chance, success, score, 3);

                                show_score(chance, success, score, 0);

                                chance_end=1;
                                shaft_x=185;
                                shaft_y=200;

                                do
                                {
                                    balon1_x = rand()%600;
                                }while(balon1_x < 300);

                                baloon_y=400;
                                balon2_x=balon1_x+ball_diff;
                                balon3_x=balon2_x+ball_diff;
                            }

                        }while(!chance_end);

                        break;

                    case 27:
                        return;
                }

                if(flag==0)
                {
                    show_score(chance, success, score, 3);
                    chance--;
                    show_score(chance, success, score, 0);

                    if(chance==0)
                    {
                        cleardevice();

                        setcolor(1);
                        settextstyle(0,0,6);
                        outtextxy(120,200,"GAME OVER");

                        delay(2000);

                        return;
                    }
                }

                flag=0;
            }
        }
    }
}


void Menu()
{
    int a=0,t=0,p=140,s=1;

    do
    {
        do
        {

            cleardevice();

            setcolor(15);
            settextstyle(1,0,1);
            outtextxy(20,400,"Mawlana Bhasani Science & Tecnology University, Santosh,Tangail.");

            setcolor(YELLOW);
            settextstyle(1,0,6);
            outtextxy( 210, 30, "MENU" );

            setfillstyle( 1, 2 );
            bar( 200, 100, 370, 105 );

            settextstyle( 1, 0, 1 );
            setcolor( 10 );
            outtextxy( 220, 137, "PLAY GAME" );
            outtextxy( 220, 167, "SCORES" );
            outtextxy( 220, 197, "HELP" );
            outtextxy( 220, 227, "ABOUT" );
            outtextxy( 220, 257, "EXIT" );

            setcolor( RED );
            rectangle( 200, p, 350, p + 20 );

            a = getch();

            switch(a)
            {
                case UP: if(p>140)
                {
                    p-=30;
                    s--;
                }
                break;

                case DOWN: if(p<260)
                {
                    p+=30;
                    s++;
                }
                break;

                case ENTER:
                a=1;
                break;

                default:
                break;
            }


        }while(a!=1);

        switch ( s )
        {
            case 1: play();
            break;

            case 2: display_score();
            break;

            case 3: help();
            break;

            case 4: about();
            break;

            case 5: exit(0);
            break;
        }

    }while(t==0);
}

void draw_screen()
{
    settextstyle(0,HORIZ_DIR,1);

	setfillstyle(1,2);
	bar(0,0,150,20);
	outtextxy(30,5,"SCORE BOARD");

	setfillstyle(1,3);
	bar(0,20,150,250);
	setcolor(1);
	outtextxy(30,40,"TOTAL CHANCE");
	outtextxy(30,100,"SUCCESS");
	outtextxy(30,160, "SCORE");

	setcolor(15);
	setfillstyle(1,2);
	bar(0,255,150,275);
	outtextxy(30,260,"CONTROL KEY");
	setfillstyle(1,3);
	bar(0,275,150,479);

	setcolor(1);
	outtextxy(30,290,"UP");
	setcolor(4);
	for(int i=0; i<=5; i++)
    line(100-i,285+i,100+i,285+i);

	line(100,290,100,300);

	setcolor(1);
	outtextxy(30,330,"DOWN");
	setcolor(4);
	for(i=0; i<=5; i++)
	line(95+i,330+i,105-i,330+i);

	line(100,320,100,330);

	setcolor(1);
	outtextxy(30,370,"SHOOT");
	setcolor(4);
	outtextxy(100,370,"ENTER");

	setcolor(1);
	outtextxy(30,410,"EXIT");
	setcolor(4);
	outtextxy(100,410,"ESC");

	setfillstyle(1,1);
	bar(151,0,639,479);
}

void draw_baloon(int x, int y, int c)
{
    setcolor(c);
    setfillstyle(1,c);
    sector(x,y,0,180,10,10);

    for(int i=0; i<=12; i++)
    line(x-10+i,y+i,x+10-i,y+i);
}

void draw_shaft(int x, int y, int c)
{
    setcolor(c);
    rectangle(x-1,y-1,x-30,y+1);

    line(x,y,x-30,y);
    line(x,y,x-6,y-4);
    line(x,y,x-6,y+4);
}

void show_score(int chance, int success, int score, int color)
{
    setcolor(color);

    char str[3];

    gcvt(chance, 3, str);
    outtextxy(40,60,str);

    gcvt(success,3,str);
    outtextxy(40,120,str);

    gcvt(score,3,str);
    outtextxy(40,180,str);
}

void help()
{
    cleardevice();

    settextstyle( 4, 0, 6 );
    setcolor( RED );
    outtextxy( 240, 10, "help" );

    setcolor(YELLOW);

    settextstyle( 1, 0, 1);

    outtextxy(0,100,"Baloon Shooting is a very silly game of shooting baloons.");
    outtextxy(0,130,"Some baloons are randomly passing around.");
    outtextxy(0,150,"And you have to shoot those baloons.");
    outtextxy(0,210,"Use upper & lower arrow to move the shaft.");
    outtextxy(0,240,"Press enter to shoot the baloons.");

    getch();
    return ;
}

void display_score()
{
    cleardevice();

    setcolor(1);

    settextstyle(0,0,3);

    outtextxy(80,100,"YOUR SCORE : ");

    char str[3];

    gcvt(score, 3, str);
    outtextxy(390,100,str);

    getch();

}

void about()
{
    cleardevice();

    settextstyle( 4, 0, 6 );
    setcolor( RED );
    outtextxy( 240, 10, "About" );

    setcolor(YELLOW);

    settextstyle( 1, 0, 1);

    outtextxy(0,100,"This game (Baloon shooting) is created in C programing language.");
    outtextxy(0,130,"The developer developed this game using his own idea.");
    outtextxy(0,160,"Enjoy the game.");

    getch();

    return ;
}




