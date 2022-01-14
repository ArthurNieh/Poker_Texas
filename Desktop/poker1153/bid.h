#ifndef BID_H_INCLUDED
#define BID_H_INCLUDED
#include"compare.h"
#include"card.h"
#include"player.h"
#include"windows.h"
void initial(player [],const int, int & , bool [],int);
void after(player [],const int,int &,bool [],int,int,card*);
bool judge(const bool [],player [],int,int);

void singlegaming(player p[],int bankcounter, int N, card* general ) // 玩家狀態 、莊家換誰、玩家數、公牌
{

    for(int i=0;i<N;i++){
        cout<<"Round "<<bankcounter + 1<<"\n\n";
        cout<<p[i].name<<" this is your handcards\n\n";
        p[i].showhandcards(); ///這邊有問題
        Sleep(2000);
        system("cls");
    }

    int moneypot = 0; // 中央總錢
    int stage =0;


    bool fold[N]={0}; // 這局誰蓋牌了

    initial(p, bankcounter, moneypot,fold,N);


    cout<<"Now we disclose three general cards\n\n";
    for(int i=0;i<3;i++)
        general[i].showcard();
    cout<<"\n\n";

    stage = 3;

    after(p,bankcounter,moneypot,fold,N,stage,general);

    if(judge(fold,p,moneypot,N))
        return;




    cout<<"Now we disclose four general cards\n\n";
    for(int i=0;i<4;i++)
        general[i].showcard();
    cout<<"\n\n";

    stage = 4;

    after(p,bankcounter,moneypot,fold,N,stage,general);

    if(judge(fold,p,moneypot,N))
        return;




    cout<<"Now we disclose five general cards\n\n\n";
    for(int i=0;i<5;i++)
        general[i].showcard();
    cout<<"\n\n";

    stage = 5;

    after(p,bankcounter,moneypot,fold,N,stage,general);
    if(judge(fold,p,moneypot,N))
        return;


    int max=0;
    int win;
    int value[N];
    int draw=1;

    for(int i=0;i<N;i++){
        card* hands = new card[5];
        card* temp =  arrange(p[i].handcard, general);

        for(int j=0;j<5;j++)
            hands[j] = temp[j];

        int tmp = countvalue(hands);
        value[i] = tmp;

        if(tmp ==  max)
            draw++;

        if(tmp > max){
            max = tmp;
            win = i;
        }
    }

    if(draw==1){
        cout<<"Congratulation "<<p[win].name<<" this turn you get "<<moneypot<<" dollars.";
        p[win].plus_chips(moneypot);
    }
    else{
        cout<<"Congratulation  ";
        for(int i=0;i<N;i++){
            if(max == value[i])
                cout<<p[i].name<<" ";
        }
        cout<<"this turn you "<<draw<<" get "<<moneypot / draw<<" dollars ";
    }

    Sleep(1500);
    for(int i=0;i<N;i++)
        p[i].set_bitThisRound(0);

    system("pause");

    return ;



}


#endif // BID_H_INCLUDED
bool judge(const bool fold[], player p[],int moneypot, int N)
{

    int winner;
    int folder = 0;
    for(int i=0;i<N;i++)
    {
        if(fold[i]) folder++;
        else
            winner = i;
    }

    if(folder==N-1){
        cout<<"player "<<winner<<", "<<p[(winner)%N].name<<" You are winner /n";
        p[winner].plus_chips(moneypot);
        cout<<"Now you have "<<p[winner].get_chips()<<" dollars\n\n";
        return 1;
     }
     return 0;

}
void after(player p[], const int bank, int &moneypot, bool fold[],int N, int stage, card* general)
{

    int pass =0;
    int folder=0;
    int highest= 0;

    for(int i=0;i<N;i++) //4 是自己設的
    {
        p[i].set_bitThisRound(0);
        if(fold[i]) folder++;
    }


    while(pass + folder!= N || folder !=N-1){

        if(pass+folder== N || folder ==N-1) break;

        for(int i=0;i<N;i++){
            if(pass+folder== N || folder == N-1) break;

            if(fold[i] == 1){
                continue;
            }


            int turn = (bank + 1 + i)%N;
            cout<<"Moneypot is "<<moneypot<<" dollars\n\n";

            if(highest > p[turn].get_bitThisRound()){
                cout<<p[turn].name<<"\nYou need to spend "<<highest - p[turn].get_bitThisRound()<<" dollars to call\nNow you have "<<p[turn].get_chips()<<" dollars\n";
                cout<<"You can choose \n1.see handscard again\n2.call\n3.raise \n4.fold\n\n";
            }
            else{
                cout<<p[turn].name<<"\nYou need to spend "<<highest - p[turn].get_bitThisRound()<<" dollars to call\nNow you have "<<p[turn].get_chips()<<" dollars\n";
                cout<<"You can choose \n1.see handscard again\n2.call\n3.raise \n4.fold\n5.pass\n\n"; // 自己就是最高的
            }


            int t; //while cin t
            while(cin>>t)
            {

                if(t==1){
                    cout<<"You choose to see again\n";
                    cout<<"Which one do you want to see? \n";
                    cout<<"H for hands  or G for generals ? \n";
                    char k; cin>>k;

                    if(k=='H'){
                        cout<<"this is your handcards\n";

                            p[i].showhandcards();
                    }
                    else if(k=='G'){
                        for(int j=0;j<stage;j++)
                            general[j].showcard();
                    }

                    else
                        cout<<"wrong input \n " << "You should operate again\n\n";


                    cout<<"input what you want to do again\n\n";

                }
                else if(t==2) {
                    cout<<"You choose to call\n\n";
                     //跟注
                    p[turn].plus_chips(-highest + p[turn].get_bitThisRound());
                    moneypot +=  highest - p[turn].get_bitThisRound();
                    p[turn].plus_bitThisRound( highest - p[turn].get_bitThisRound() );
                    pass++;
                    break;
                }

                else if(t==3){
                    cout<<"You choose to raise\n";
                    int tmp;
                    cout<<"You can raise money bigger than "<<highest - p[turn].get_bitThisRound()<<endl;
                    cout<<"Now input money you want to raise"<<endl;

                    while(cin>>tmp){

                        if(tmp < highest - p[turn].get_bitThisRound())
                            cout<<"\nwrong input Please input again"<<endl;

                        else if(tmp > p[turn].get_chips())
                            cout<<"\nYou don't have enough money, please cin again"<<endl;

                        else if(tmp == p[turn].get_chips()){
                            cout<<"\nAre you sure to ALL IN ?"<<endl;
                            cout<<"Y or N"<<endl;
                            char t; cin>>t;

                            if(t=='N'){
                                cout<<"please input again the money you want to raise\n";
                                continue;
                            }
                            else{
                                cout<<"You choose to ALL IN "<<tmp<<" dollars\n\n";
                                moneypot += tmp;
                                highest = p[turn].get_chips() + p[turn].get_bitThisRound();
                                p[turn].plus_bitThisRound(p[turn].get_chips());
                                p[turn].set_chips(0);

                                break;
                            }
                        }
                        else
                        {
                            cout<<"You choose to raise "<<tmp<<" dollars\n\n";
                            moneypot += tmp;
                            p[turn].plus_bitThisRound(tmp);
                            p[turn].plus_chips(-tmp);
                            highest = p[turn].get_bitThisRound();
                            pass = 0;
                            break;
                        }
                    }
                    break;
                }
                else if(t==4)
                {
                    if(highest == p[i].get_bitThisRound()){
                        cout<<"Are you sure? You bid the most in this round !\n"<<"Y or N\n";
                        char t; cin>>t;
                        if(t=='N')
                        {
                            cout<<"You should operate again\n\n";
                             continue;
                        }


                        else if(t=='Y'){}
                        else{
                            cout<<"wrong input\n";
                            continue;
                        }
                    }
                    fold[turn]=1;
                    folder++;
                    break;
                }
                else if(t==5){
                    pass++;
                    break;

                }
            }


        }
        Sleep(1000);
            system("cls");





    }








  //  for
}

void initial(player p[], const int bank, int &moneypot, bool fold[],int N)
{


    cout<<"player "<<p[bank].name<<". Now you are banker\n\n";

    p[bank].plus_bitThisRound(5); //大盲注
    p[bank].plus_chips(-5);
    p[(bank+1) % N].plus_bitThisRound(3); //小盲注
    p[(bank+1)%N].plus_chips(-3);

    moneypot += 8;
    int highest = 5;
    int pass = 0;
    int folder = 0; // fold用來記錄誰 folder 用來記錄撙數

    while( (pass+folder)!=  N|| folder != N-1)
    {

        if((pass+folder)== N || folder == N-1) break;

        for(int i=0;i<N;i++) // 5是自己先設的
        {
            if(pass+folder== N || folder == N-1) break;

            int turn = (bank+1+i)%N;
            if(fold[turn] == 1) continue;

            cout<<"Moneypot is "<<moneypot<<" dollars\n\n";

            if(highest > p[turn].get_bitThisRound()){
                cout<<p[turn].name<<"\nYou need to spend "<<highest - p[turn].get_bitThisRound()<<" dollars to call\nNow you have "<<p[turn].get_chips()<<" dollars\n";
                cout<<"You can choose \n1.see handscard again\n2.call\n3.raise \n4.fold\n\n";
            }
            else{
                cout<<p[turn].name<<"\nYou need to spend "<<highest - p[turn].get_bitThisRound()<<" dollars to call\nNow you have "<<p[turn].get_chips()<<" dollars\n";
                cout<<"You can choose \n1.see handscard again\n2.call\n3.raise \n4.fold\n5.pass\n\n"; // 自己就是最高的
            }


            int t;
            while(cin>>t){

                if(t==1){
                    cout<<"You choose to see again\n";
                    cout<<"this is your handcards\n";

                        p[i].showhandcards();
                    cout<<"input what you want to \n\n";
                }

                else if(t==2) {
                    cout<<"You choose to call\n\n";
                     //跟注
                    p[turn].plus_chips(-highest + p[turn].get_bitThisRound());
                    moneypot +=  highest - p[turn].get_bitThisRound();
                    p[turn].plus_bitThisRound( highest - p[turn].get_bitThisRound() );
                    pass++;
                    break;
                }

                else if(t==3){
                    cout<<"You choose to raise\n";
                    int tmp;
                    cout<<"You can raise money bigger than "<<highest - p[turn].get_bitThisRound()<<endl;
                    cout<<"Now input money you want to raise"<<endl;

                    while(cin>>tmp){

                        if(tmp < highest - p[turn].get_bitThisRound())
                            cout<<"\nwrong input Please input again"<<endl;

                        else if(tmp > p[turn].get_chips())
                            cout<<"\nYou don't have enough money, please cin again"<<endl;

                        else if(tmp == p[turn].get_chips()){
                            cout<<"\nAre you sure to ALL IN ?"<<endl;
                            cout<<"Y or N"<<endl;
                            char t; cin>>t;

                            if(t=='N'){
                                cout<<"please input again the money you want to raise\n";
                                continue;
                            }
                            else{
                                cout<<"You choose to ALL IN "<<tmp<<" dollars\n\n";//p[turn].get_chips()+p[turn].get_bitThisRound()
                                moneypot += tmp;//p[turn].get_chips()-p[turn].get_bitThisRound();
                                highest = p[turn].get_chips() + p[turn].get_bitThisRound();
                                p[turn].plus_bitThisRound(p[turn].get_chips()) ;
                                p[turn].set_chips(0);

                                break;
                            }
                        }
                        else
                        {
                            cout<<"You choose to raise "<<tmp<<"dollars\n\n";
                            moneypot += tmp;
                            p[turn].plus_bitThisRound(tmp);
                            p[turn].plus_chips(-tmp);
                            highest = p[turn].get_bitThisRound();
                            pass = 0;
                            break;
                        }
                    }
                    break;
                }
                else if(t==4)
                {
                    if(highest == p[i].get_bitThisRound()){
                        cout<<"Are you sure? You bid the most in this round !\n"<<"Y or N\n";
                        char t; cin>>t;
                        if(t=='N'){
                            cout<<"You should input what you want to do  again\n\n";
                             continue;
                        }


                        else if(t=='Y'){}
                        else{
                            cout<<"wrong input\n";
                            continue;
                        }
                    }
                    fold[turn]=1;
                    folder++;
                    break;
                }
                else if(t==5){
                    pass++;
                    break;

                }
            }

        }
        Sleep(1000);
            system("cls");


    }

}

