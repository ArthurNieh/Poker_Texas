#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include"player.h"
#include"card.h"

int countvalue(card*);
bool compare(card, card);

card* arrange(card* hand, card* general){

    card* total = new card[7];
    card* random = new card [5];
    card* best = new card[5];
    int max =0;

    for(int i=0;i<7;i++){
        if(i<=4)
            total[i] = general[i];
        else
            total[i] = hand[i-5];
    }

    for(int i=0;i<7;i++){
        for(int j=i+1;j<7;j++){
            int tmp =0;

            for(int k=0;k<5;k++){
                if(tmp == i) tmp++;
                if(tmp == j) tmp++;

                random[k] = total[tmp];
                tmp++;
            }
                int t = countvalue(random);
                if(t > max){
                    for(int i=0;i<5;i++){
                        best[i].number = random[i].number;
                        best[i].color = random[i].color;}
                    max = t;
                }

          }
    }
    return best;
 }

 int countvalue(card* combine)
 {
    int color[4]={0};
    for(int i=0;i<5;i++){
        color[combine[i].color]++;}

    int number[14]={0};
    for(int i=0;i<5;i++){
        number[combine[i].number]++;}

    bool fivecolors = 0;

    for(int i=0;i<5;i++){
        if(color[i]==5)
            fivecolors = 1;
    }
    bool fourkinds=0;
    bool threekinds =0;
    int pairs=0;

    for(int i=0;i<14;i++){
        if(number[i]==4)
            fourkinds = 1;
        if(number[i]==3)
            threekinds = 1;
        if(number[i]==2)
            pairs++;
    }

    card* temp= combine;
    sort(temp,temp+5,compare); // temp[0].number 是最大 且 1 (A)在頭


    if(fivecolors == 1){         // 桐花或童話順
// temp
        if((pairs==0 && temp[0].number - 4 == temp[4].number ) || (pairs==0 && temp[0].number ==1 && temp[4].number==10))
        {
            return 5000 + temp[4].number; // 桐花順
        }
        else{
            if(temp[0].number==1)
                return 3500 + 14;
            else
                return 3500 + temp[0].number;

        }//桐花
    }

    else if(fourkinds){ //鐵支
        int x;
        for(int i=0;i<14;i++)
            if(number[i]==4)
                x = number[i];

            if(temp[0].number==1)
                return 4500 + 14;
            else
               return  4500 + x;
    }

    else if(threekinds){ //條 葫蘆
        if(pairs==0)
        {
            if(temp[0].number==1)
                return 3000 + 14;
            else
                return 3000 + temp[2].number; // 第二張一錠是條的
        }

        else{
            if(temp[0].number==1)
                return 4000 + 14;
            else
                return 4000 + temp[2].number;
        }
    }

    else if(pairs == 2) //2 pairs
    {
        if(temp[1].number==temp[0].number && temp[3].number==temp[4].number){
           if(temp[0].number == 1)
                return 350 + 13*13*14 + 13* temp[3].number + temp[2].number;
            else
                return 350 + 13*13*temp[1].number + 13* temp[3].number + temp[2].number;
        }
 // 兩對經過排序後 1,3號一定是對子中的元素

        else if(temp[2].number==temp[3].number){
            if(temp[0].number == 1)
                return 350 + 13*13*14 + 13* temp[3].number + temp[4].number;
            else
                return 350 + 13*13*temp[1].number + 13* temp[3].number + temp[4].number;
        }
        else if(temp[1].number==temp[2].number)
        {   if(temp[0].number == 1)
                return 350 + 13*13*temp[1].number + 13* temp[3].number + 14;
            else
                return 350 + 13*13*temp[1].number + 13* temp[3].number + temp[0].number;
        }
    }

    else if(pairs==1) //pair
    {
        if(temp[0].number==temp[1].number)
        {   if(temp[0].number==1)
                return 20 + 13*14 +temp[2].number;
            else
                return 20 + 13*temp[0].number + temp[2].number;
        }
        else{
            int x;
            for(int i=0;i<14;i++)
                if(number[i]==2)
                    x = i;

            if(temp[0].number==1)
                return 20 + 14 + x*13;

            else
            {
                return 20 + temp[0].number + x*13;
            }
        }

    }

    else if(pairs==0)
    {
        if((pairs==0 && temp[0].number - 4 == temp[4].number ) || (pairs==0 && temp[0].number ==1 && temp[4].number==10)){
            return 3200 + temp[4].number;
        }
        else
        {
            if(temp[0].number == 1)
                return 14;
            else
                return temp[0].number;
        }

    }
 }

 bool compare(card a, card b){

    if(a.number == 1)
        return 1;
    else if(b.number ==1)
        return false;

	return a.number > b.number;
}




// 如果是high card: 點數由2~14
// 一對: 對本身13 再加上 單張13=> 169種 就不考慮重複了先把range訂出來    22 2 是 最小 28  AA A是最大 196  pair*13 + high card if A =>14
// 兩對: 本身 13 再加上 13 單張 13 13*13*13 2197種  350 + highpair*13*13+lowpair*13 + high card 最小366  最大 2562
// 三條: 2800+13
// 順子:13 3000 + head if違規就變成單張  加頭好處是不用處理尾巴是A
// 桐花:13 3500+ highcard 最小2852 最大2864
// 葫蘆:13  4000 + 13
// 鐵支:13  4500 + head
// 桐花順:13  5000 + head




#endif // COMPARE_H_INCLUDED
