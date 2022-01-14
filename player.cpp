#include "player.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#define initialMoney 100
using namespace std;

player::player(){
	
	setmoney(initialMoney);
	handcard = NULL;
	
}

void player::setcardNumber(int num, int playernum){
	number = num;
	if(num<(53%playernum)){
		cardNumber = 53/playernum +1;
	}
	else{
		cardNumber = 53/playernum;
	}
}
void player::initializer(int num){
	
	cout<<"Welcome player "<<num<<"\n";
	cout<<"please type in your name"<<endl;
	string yourname;
	cin>>yourname;
	name = yourname;
	cout<<"Hellow "<<yourname<<"\n";
	comCheck = 0;
}
void player::cominitializer(int order){
	char comorder = 'A' + order;
	name = "Computer ";
	name[8] = comorder;
	cout<<name<<endl;
	comCheck = 1;
}
void player::sethandcard(int* cardnotprocessed, int ncards){
	
	handcard = new card[ncards];
	for(int i=0;i<ncards;i++){
		handcard[i].color = cardnotprocessed[i] % 4;
		if(cardnotprocessed[i] == 52){
			handcard[i].number = 14;
			handcard[i].color = 4;
		}
		else if(cardnotprocessed[i] / 4 == 0){
			handcard[i].number = 13;
		}
		else{
			handcard[i].number = cardnotprocessed[i] / 4;
		}
		
	}
}
bool cardcompare(card a, card b){
	if(a.number != b.number){
		return (a.number < b.number);
	}
	else{
		return (a.color < b.color);
	}
}
void player::sorthandcard(){
	sort(handcard, handcard + cardNumber, cardcompare);
}
void player::showhandcards(){
	if(cardNumber == 0){
		cout<<"\n--------------------\n\n";
		cout<<"There is no card in "<<name<<"'s hand."<<endl;
		return;
	}
	for(int i=0;i<cardNumber;i++){
		handcard[i].showcard();
	}
}
void player::dealpairedcards(){
	if(!comCheck){
		cout<<"throwing out the paired cards";
		for(int i=0;i<3;i++){
			cout<<".";
			Sleep(200);
		}
		cout<<endl;
	}
	
	int index = 0;
	while(index < cardNumber - 1){
		if(handcard[index].number == handcard[index+1].number){
			getridofcard(index);
			getridofcard(index);
		}
		else{
			index++;
		}
	}
}
void player::getridofcard(int index){
	card* temp = new card[cardNumber-1];
	int counttemp = 0;
	for(int i=0;i<cardNumber;i++){
		if(i != index){
			temp[counttemp] = handcard[i];
			counttemp++;
			
		}
	}
	delete handcard;
	handcard = temp;
	cardNumber-=1;
}
void player::addhandcard(card thecard){
	card* temp = new card[cardNumber+1];
	for(int i=0;i<cardNumber;i++){
		temp[i] = handcard[i];
	}
	temp[cardNumber] = thecard;
	delete handcard;
	handcard = temp;
	sorthandcard();
	cardNumber++;
	return;
}

