#include "card.h"
#include <iostream>
using namespace std;

void card::showcard(){
	switch(number){
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			cout<<number;
			break;
		case 10:
			cout<<"T";
			break;
		case 1:
			cout<<"A";
			break;
		case 11:
			cout<<"J";
			break;
		case 12:
			cout<<"Q";
			break;
		case 13:
			cout<<"K";
			break;
		case 14:
			cout<<"Joker\n";
			break;
	}
		
	if(color != 4){
		cout<<" of ";
	}
	else{
		return;
	}
		
	switch(color){
		case 0:
			cout<<"spade"<<endl;
			break;
		case 1:
			cout<<"heart"<<endl;
			break;
		case 2:
			cout<<"diamond"<<endl;
			break;
		case 3:
			cout<<"club"<<endl;
			break;
	}
	return;
}
