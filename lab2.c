#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void *threadFunc(void *arg);


int main()
{
	initscr();
	printw("Enter the name of file \n");
  char fname[10];
  getstr(fname);
  FILE * file = fopen(fname, "r");
  if (file==NULL)
  {
	  endwin();
	  printf("\nIncorrect name of file \n", fname);
		return 0;
  } 	
	
	keypad(stdscr, true);
	noecho();
  pthread_t thread;
	halfdelay(100);
	printw("Press 'S' to start, 'S' again to pause, 'Q' to exit \n");
	
	bool end = false;
	bool pause = true;
	while(!end)
	{
		int ch = getch();
		switch(ch)
		{
			case ERR: 
				{
				break;
				}
			case 115:
				{
				pause=!pause;
				if(pause){
				 printw("\nPAUSE \nPress 'S' to continue, 'Q' to exit \n");
				 pthread_cancel(thread);
				 break;}
				 else {
				 pthread_create(&thread, NULL, threadFunc, file);
				 break;}
				}
			case 113: 
				{
				pthread_cancel(thread);
				end=true; 
				break;
				}
			default:
				{
				printw("Unknown key \n"); 
				break;
				}
		}
		refresh();
	}
	pthread_join(thread, NULL);
	endwin();
	return 0;
}


static void *threadFunc(void *arg)

{

    char spases;
    fread(&spases, 1, 1, arg);	
    while (!feof(arg))
    {

        printw("%c", spases);
        fread(&spases, 1, 1, arg);
	      napms(100);    
	      refresh();
    }
    pthread_exit(NULL);

}
