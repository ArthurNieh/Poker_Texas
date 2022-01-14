#include <iostream>
#include <iomanip>
#include "player.h"
#include"gaming.h"

const int initial_chip = 100;

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void welcome(int &n);//n:number of people
void setup(player thePlayers[], int n);//n:number of people

int main(int argc, char** argv) {

	int N;//player number
	welcome(N);

    while(1)
    {
        player* p = new player[N];

        setup(p, N);


       card* tmp = new card[5];
       cout<<endl<<"input general card"<<endl;
       for(int i=0;i<5;i++){
            int t; cin>>t;
            tmp[i].color = t;
            cin>>t;
            tmp[i].number =t;
        }

        gaming(p,N,tmp);



        cout<<"Continue or Stop the game ?"<<endl<<"C or S";
        char t; cin>>t;

        if(t=='C')
            continue;

        else if(t=='S')
        {
            cout<<"Enjoy the game see you next.";
            break;
        }
        else
            cout<<"Wrong input"<<" Please cin again";
    }

	return 0;
}

void welcome(int &n){
	cout<<"welcome\n";
	cout<<"rules...\n";
	cout<<"Please input the player number:"<<endl;
	cin>>n;
}
void setup(player thePlayers[], int n){
	cout<<"Set up stage\n\n";
	cout<<"Please come to the computer one by one to input your name.\n";
	cout<<"Please make sure you remember your player number\n\n";

	for(int i=0;i<n;i++){
		cout<<"Player number "<< i <<", please input your name:"<<endl;
		cin>>thePlayers[i].name;
		cout<<"Welcome "<<left<<setw(10)<<thePlayers[i].name<<"You are player "<<i<<endl;
		thePlayers[i].set_chips(100);
		cout<<"Your initial chip is set to "<<initial_chip<<" dollar.\n"<<endl;
		cout<<"set up hand cards"<<endl;

		/*  for(int j=0;j<2;j++){
            int t; cin>>t;
            thePlayers[i].handcards[j].color =t;
            cin>>t;
            thePlayers[i].handcards[j].number = t;
		}*/
	}
}


