#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *masterFunc();// хозяин
void *guest1Func();// гость 1
void *guest2Func();// гость 2
void *guest3Func();// гость 3

int nbotle_refr = 10; //колличество бутылок в холодильнике
int visit[3][2]; //состояниt гостей
bool masterstat=0; //состояние хозяина
int i;  

pthread_mutex_t refr; 
pthread_t gst1,gst2,gst3, master;	

int main()
{
	initscr();
	printw("\n");
	pthread_create(&master, NULL, masterFunc, NULL);	
        pthread_create(&gst1, NULL, guest1Func, NULL);
	pthread_create(&gst2, NULL, guest2Func, NULL);
	pthread_create(&gst3, NULL, guest3Func, NULL); 
	
	visit[1][2]=0; //количество выпитых бутылок 0
	visit[2][2]=0;
	visit[3][2]=0;
       
	//печати информации 
	while(1)
	{
		

		for(i=1; i<=3; i++)
		{
			printw("\n");
			//имя гостя
			if(i==1) printw("	Guest 1 ");
			if(i==2) printw("	Guest 2 ");
			if(i==3) printw("	Guest 3 ");

			//состояние
			printw("drank %d bottles. Now he ", visit[i][2]);
			if(visit[i][1]==1) printw("stands in queue to fridge.");
			if(visit[i][1]==2) printw("takes a bottle of beer.");
			if(visit[i][1]==3) printw("drinks beer.");
			if(visit[i][1]==4) printw("sleeps.");
			
			printw("\n\n\n");
				
		}
		if(masterstat==1)   printw("	Master puts 5 new bottle\n	*Visitor can not use the fridge\n\n");
		if(masterstat==0)   printw("	Master is hanging around\n\n");
		printw("        Bottles in the fridge: %d\n", nbotle_refr );		
		refresh();		
		napms(1000);
		clear();
		if(nbotle_refr==0){
		printw("The beer ran out.");
		refresh();
		napms(60000);
		endwin();}
		
	}
	return 0;
}
	


void *masterFunc()
{
	pthread_mutex_init(&refr, NULL);
	srand(time(NULL));//инициализация ф-ии rand значением ф-ии time 
	//цикл функционирования хозяина	
	while(1)
	{
		//с веротяностью 1/25 владелец зайдет, посчитает бутылки и добавит 3 новых 
		if(rand()%25 +1 == 1) 
		{
			masterstat=1;//владелец открыл холодильник и снял все lock
			pthread_mutex_init(&refr, NULL);
			pthread_mutex_lock(&refr);
			napms(30000); 
			pthread_mutex_unlock(&refr);
			nbotle_refr+=3;	
			masterstat=0;//занимается своими делами
		}
		napms(1000);	
	}
}


void *guest1Func()
{
	//цикл функционирования 1ого гостя
	while(1)
	{
		visit[1][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[1][1]=2;//гость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(masterstat==0)	pthread_mutex_unlock(&refr);  
		
		
		visit[1][1]=3;//пьет пиво 20 секунд
		napms(20000);
 		nbotle_refr--;
		visit[1][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[1][2]==10) {visit[1][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}

void *guest2Func()
{
	//цикл функционирования 2ого гостя
	while(1)
	{
		visit[2][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[2][1]=2;//гость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(masterstat==0)	pthread_mutex_unlock(&refr);  
		
		
		visit[2][1]=3;//пьет пиво 20 секунд
		napms(20000); 
                nbotle_refr--;
		visit[2][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[2][2]==10) {visit[2][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}

void *guest3Func()
{
	//цикл функционирования 3ого гостя
	while(1)
	{
		visit[3][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[3][1]=2;//гость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(masterstat==0) pthread_mutex_unlock(&refr);  
		
		
		visit[3][1]=3;//пьет пиво 20 секунд
		napms(20000);
		nbotle_refr--; 
		visit[3][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[3][2]==10) {visit[3][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}
