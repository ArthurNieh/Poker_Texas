#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include "card.h"

class player
{
	friend class card;
	public:
		player();
		std::string name;
		card* handcard;
		int cardNumber;//number of card in hand
		bool comCheck;// check if this player a computer player
		void setcardNumber(int, int);//set number, playerNumber
		void initializer(int);//set name for human player
		void cominitializer(int);//initializer fo computer
		void setmoney(int moneyw){money = moneyw;};
		int getmoney(){return money;};
		void sethandcard(int*, int);
		void sorthandcard();//to sort handcard
		void showhandcards();//to show handcard
		void dealpairedcards();//getting rid of all the paired cards at te beginning
		void getridofcard(int);//getting rid of one particular handcard
		void addhandcard(card);//add a card into handcard
		
	protected:
		int number;//½s¸¹ 
		int money;//¿ú 
};

#endif
