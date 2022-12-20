#include <direct.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define PINK COLOR(255,0,255)

using namespace std;
void help();
void game();
void check();
void dead();
void level();
void high();
int snake_x[500], snake_y[500], snake_size = 4, score, highscore, spd = 100, l, obs_ = 4;

bool checkdied = false, BONUS = false;
main() {

	int gdirect = DETECT, gmode;  //request autodetection
	initgraph ( &gdirect, &gmode, "" );
	//int m[5], n[5], temp;

	int cursor_y = 140;
	char ch;
	while ( 1 ) {
		setcolor ( CYAN );
		settextstyle ( 10, 0, 6 );
		outtextxy ( 200, 30, "~SNAKE~" );
		setcolor ( WHITE );
		settextstyle ( 10, 0, 3 );
		outtextxy ( 200, 140, "NEW GAME" );
		outtextxy ( 200, 170, "SELECT LEVEL" );
		outtextxy ( 200, 200, "HIGHSCORE!!" );
		outtextxy ( 200, 230, "HELP :( " );
		outtextxy ( 200, 260, "WANNA EXIT??" );
		setcolor ( CYAN );
		outtextxy ( 160, cursor_y, "->" );
		settextstyle ( 10, 0, 3 );
		setcolor ( CYAN );
		outtextxy ( 150, 300, "Please Select Level First" );
		if ( kbhit ) {

			ch = getch();
			setcolor ( BLACK );
			outtextxy ( 150, cursor_y, "->" );
			if ( ch == 13 ) {
				if ( cursor_y == 260 ) exit ( 0 );
				else if ( cursor_y == 140 ) game();
				else if ( cursor_y == 170 ) level();
				else if ( cursor_y == 200 ) high();
				else if ( cursor_y == 230 ) help();
			}
		}
		setcolor ( CYAN );
		if ( ch == 80 ) {
			cursor_y += 30;
			if ( cursor_y > 260 ) cursor_y = 140;
		}
		if ( ch == 72 ) {
			cursor_y -= 30;
			if ( cursor_y < 140 ) cursor_y = 260;
		}
		outtextxy ( 150, cursor_y, "->" );

	}
	return 0;
}
void help() {
	setcolor ( WHITE );
	outtextxy ( 100, 300, "Move the snake using the Arrow keys." );
	char ch = getch();
	clearviewport();
	return;

}
void game() {
	clearviewport();
	freopen ( "GameData.dat", "r", stdin );
	cin >> highscore;
	cleardevice();
	char ch;
	string key = "right";
	int maxx = getmaxx();
   int maxy = getmaxy() - 60;

	int x = 10, y = 10;
	int food_x = rand() % maxx, food_y = rand() % maxy;
	int temp;
	temp = food_x % 10;
	food_x -= temp;
	temp = food_y % 10;
	food_y  -= temp;
	int i = 0;
	int bonus = 500;


	while ( true ) {
	    clearviewport();





		if ( score > 0 && score % 5 == 4 ) BONUS = true;
		else {
			bonus = 500;
			BONUS = false;
		}
		if ( !BONUS || bonus == 0 ) {
			setcolor ( RED );
			outtextxy ( 250, 450, "HURRY!DUDE." );
			setcolor ( WHITE );
			setfillstyle ( SOLID_FILL, WHITE );
			circle ( food_x, food_y, 5 );
			floodfill ( food_x, food_y, WHITE );
		} else {
			setcolor ( RED );
			setfillstyle ( SOLID_FILL, RED );
			circle ( food_x, food_y, 7 );
			floodfill ( food_x, food_y, RED );
			char spp[1000];
			sprintf ( spp, "Hurry!! %d", bonus );
			outtextxy ( 250, 450, "Hurry!! 888" );
			setcolor ( MAGENTA );
			outtextxy ( 250, 450, spp );
		}
		//maxx = getmaxx();
		//maxy = getmaxy() - 60;
		setcolor ( WHITE );
		line ( 0, maxy + 8, maxx, maxy + 8 );
		//int m[5], n[5], temp;

		if ( kbhit() ) {
			ch = getch();
			if ( ch == 0 ) ch = getch();
			if ( ch == 72 && key != "down" ) key = "up";
			if ( ch == 80 && key != "up" ) key = "down";
			if ( ch == 75 && key != "right" ) key = "left";
			if ( ch == 77 && key != "left" ) key = "right";
			if ( ch == 27 ) {
				cleardevice();
				return;
			}
		}
		if ( i < 10 ) {
			snake_x[i] = x - 240;
			snake_y[i] = y - 285;
			i++;
		}
		else {
			for ( int _size = snake_size - 2; _size >= 0; _size-- ) {
				snake_x[_size + 1] = snake_x[_size];
				snake_y[_size + 1] = snake_y[_size];
			}
			snake_x[0] = x;
			snake_y[0] = y;
			setcolor ( WHITE );
			bar(snake_x[0] - 5,snake_y[0] - 5,snake_x[0]+5,snake_y[0]+5);
			//setfillstyle ( SOLID_FILL, BLACK);
			//floodfill ( snake_x[0], snake_y[0], WHITE);
			setcolor ( PINK );
			for ( int _size = 1; _size < snake_size; _size++ ) {
				circle ( snake_x[_size], snake_y[_size], 5 );
				//setfillstyle ( SOLID_FILL, PINK );
				//floodfill ( snake_x[_size], snake_y[_size], PINK );
				bar(310,240,350,280);
               //bar(100,120,150,170);
                bar(460,300,500,340);


			}
			char ara[100];
			sprintf ( ara, "Score: %d", score );
			setcolor ( CYAN );

			outtextxy ( 00, maxy + 10,  ara  );
			sprintf ( ara, "Bestscore: %d", highscore );
			setcolor ( WHITE );
			outtextxy ( 450, maxy + 10, ara );

			delay ( spd );

		}

		if ( x == food_x && y == food_y ) {
			snake_size++;
			score++;
			if ( score % 5 == 0 && score > 0 )
				score += bonus;

		food_x = rand() % maxx, food_y = rand() % maxy;
		temp = food_x % 10;
		food_x -= temp;
		temp = food_y % 10;
		food_y -= temp;
		if ( food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5 ) {
			while ( food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5 ) {
				food_x = rand() % maxx, food_y = rand() % maxy;
				temp = food_x % 13;
				food_x -= temp;
				temp = food_y % 13;
				food_y -= temp;
			}
		}


	}
	    if ( key == "right" ) x = x + 10;
		if ( x > maxx ) x = 0;
		if ( key == "left" ) x = x - 10;
		if ( x < 0 ) x = maxx - ( maxx % 10 );
		if ( key == "up" ) y = y - 10;
		if ( y > maxy ) y = 0;
		if ( key == "down" ) y = y + 10;
		if ( y < 0 ) y = maxy - ( maxy % 10 );
		check();
		if( checkdied )
        {
            dead();
            return;
        }
        if(BONUS)
        {
            if(bonus > 0)
                bonus -= 10;
        }
         setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[_size],snake_y[_size],BLACK);
        }


    }

}
void check()
{
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
        cout <<score<<endl;
    else cout <<highscore<<endl;
    for ( int i = 1; i < snake_size; i++ ) {
		if ( snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i] ) {
			delay ( 1000 );
			setcolor ( WHITE );
			for ( int i = 0; i < snake_size; i++ ) {
				circle ( snake_x[i], snake_y[i], 5 );
				setfillstyle ( SOLID_FILL, RED );
				floodfill ( snake_x[i], snake_y[i], WHITE );
			}
			while ( 1 ) {
				if ( kbhit() ) {
					char ch = getch();
					if ( ch == 13 ) {
						checkdied = true;
						cleardevice();
						clearviewport();
						return;
					}
				}
			}
		}//
	}
for(int m = 310; m <= 350; m += 10)
                {
                    for(int n = 240; n <= 280; n += 10)
                    {
                        if(snake_x[0] == m && snake_y[0] == n)
                             {
			delay ( 1000 );
			setcolor ( WHITE );
			for ( int i = 0; i < snake_size; i++ ) {
				circle ( snake_x[i], snake_y[i], 5 );
				setfillstyle ( SOLID_FILL, RED );
				floodfill ( snake_x[i], snake_y[i], WHITE );
			}
			while ( 1 ) {
				if ( kbhit() ) {
					char ch = getch();
					if ( ch == 13 ) {
						checkdied = true;

						cleardevice();
						clearviewport();

						return;
					}
				}
			}
		}
        }
}//
for(int m = 460 ; m <= 500 ; m += 10)
                {
                    for(int n = 300; n <= 340; n += 10)
                    {
                        if(snake_x[0] == m && snake_y[0] == n)
                             {
			delay ( 1000 );
			setcolor ( WHITE );
			for ( int i = 0; i < snake_size; i++ ) {
				circle ( snake_x[i], snake_y[i], 5 );
				setfillstyle ( SOLID_FILL, RED );
				floodfill ( snake_x[i], snake_y[i], WHITE );
			}
			while ( 1 ) {
				if ( kbhit() ) {
					char ch = getch();
					if ( ch == 13 ) {
						checkdied = true;
						cleardevice();
						clearviewport();
						return;
					}
				}
			}
		}
        }
}//



}
void dead()
{
     snake_x[500]={},snake_y[500]={};
    checkdied = false;
    snake_size = 4;
    score = 0;

}
void level()
{

    char ch;
    char ara[100];
    while(true)
    {
        int i = abs ( spd / 10 - 10 );
		sprintf ( ara, "SELECT LEVEL : %d", i );
		setcolor ( WHITE );
		outtextxy ( 180, 350, ara );

		if ( kbhit() ) {
			ch = getch();
			if ( ch == 80 ) {
				spd -= 10;
				if ( spd < 0 ) spd = 100;
			} else if ( ch == 72 ) {
				spd += 10;
				if ( spd > 100 ) spd = 0;
			} else if ( ch == 13 )
				break;
			sprintf ( ara, "SELECT LEVEL : %d", i );
			setcolor ( BLACK );
			outtextxy ( 180, 350, ara );
		}
    } clearviewport();
//    return 0;
}
void high()
{
    freopen("GameData.dat","r",stdin);
	cin >> highscore;
	char ara[100];
	sprintf ( ara, "Highscore: %d", highscore );
	cout<<"HI";
	//setcolor ( WHITE );
	outtextxy ( 200, 350, ara );
	char ch = getch();
	clearviewport();
//	return 0;
}



