#ifndef GAMING_H_INCLUDED
#define GAMING_H_INCLUDED
#include"bid.h"
#include"player.h"
#include"windows.h"
#include<ctime>

void serve(player* , int,int);
void gaming(player p[], int N)
{
    int bankcounter=0;
    while(1)
    {

        int broken = 0;
        bool broke[N] ={0};
        int winner;

        for(int i=0;i<N;i++)
        {
            if(p[i].get_chips() == 0){
                broke[i] = 1;
                broken++;
            }
            else
                winner = i;

        }

        if(broken == N-1){
            cout<<p[winner].name<<" You are winner!!!!!!!!!!!!!!"<<endl;
            break;
        }

        for(int i=0;i<N;i++)
        	p[i].cardNumber = 0;
        system("cls");

        serve(p,N,2);
       
        player * publics = new player[1];
        serve(publics,1,5);


        singlegaming(p,bankcounter,N, publics->handcard);
        bankcounter++;


    }
}

void serve(player* p, int numberOfPeople,int number){
	bool allcards[53] = {0};
	srand(time(0));

	for(int i=0;i<numberOfPeople;i++){
		int* mycard = new int[number];

		for(int j=0;j<number;j++){
			int take;
			do{
				take = rand()%53;
			}while(allcards[take] == 1);
			mycard[j] = take;
			allcards[take] = 1;
			p[i].cardNumber++;
		}
		p[i].sethandcard(mycard, number);

	}

}



#endif // GAMING_H_INCLUDED
