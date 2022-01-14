#ifndef GAMING_H_INCLUDED
#define GAMING_H_INCLUDED
#include"bid.h"
#include"player.h"
#include"windows.h"
void gaming(player p[], int N, card* general)
{
    int bankcounter=0;
    while(1)
    {
        int broken = 0;
        bool* broke = new bool [N] {0};
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

        cout<<"\n\nRound "<<bankcounter + 1<<"\n\n";
        singlegaming(p,bankcounter,N,general);
        bankcounter++;

        Sleep(5000);
        system("cls");
    }
}


#endif // GAMING_H_INCLUDED
