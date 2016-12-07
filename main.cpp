// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//up to date
//aaa

#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <stdlib.h>
#define random(x) (rand()%x)

using namespace std;
typedef enum
{  //扑克牌面值：ACE(A),TWO(2)到TEN(10),JACK(J),QUEEN(Q),KING(K)
    ACK = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
}RankType;
typedef enum
{   //扑克牌花色：（梅花），DIAMONDS(方块)，HEARTS(红桃)和SPADES(黑桃)
    CLUBS, DIAMONDS, HEARTS, SPADES
} suitType;
typedef struct
{  //扑克牌结构体
    RankType rank;
    suitType suit;
}card;

class Game{
private:

    stack<RankType> banker;
    stack<RankType> player;

public:
    int callnumber; //初始为0 每叫一张牌 自加1
    card plate[52];
    Game(){
        callnumber = 0;
        for(int i = 0; i <= 3; i++){
            for (int j = 1; j <= 13; j++){
                plate[13 * i + j].rank = (RankType)j;
                plate[13 * i + j].suit =(suitType) i;

            }
        }
    }
    void Shuffle(){
        //洗牌
        for (int i = 1; i <= 52; i++){
            int ran = random(51) + 1;
            card temp;
            temp.rank = plate[ran].rank;
            temp.suit = plate[ran].suit;
            plate[ran].rank = plate[i].rank;
            plate[ran].suit = plate[i].suit;
            plate[i].rank = temp.rank;
            plate[i].suit = temp.suit;
        }
    }
    int get_banker_total_score(){
        //得到庄家的总分
        int sum=0;
        int number_1 = 0;
        while (!banker.empty())
        {

            int temp =(int) banker.top();
            if (temp == 1){
                number_1++;
            }
            if (temp >= 10){
                sum += 10;
            }
            else if(2<=temp&&temp<=9){
                sum += temp;
            }
            banker.pop();
        }
        while (number_1 != 0){
            if (sum + 11 <= 21){
                sum += 11;
            }
            else{
                sum += 1;
            }
            number_1--;
        }
        return sum;
    }
    int get_player_total_score(){
        //得到庄家的总分
        int sum = 0;
        int number_1 = 0;
        while (!player.empty())
        {
            int temp = (int)player.top();
            if (temp == 1){
                number_1++;
            }
            if (temp >= 10){
                sum += 10;
            }
            else if (2 <= temp&&temp <= 9){
                sum += temp;
            }
            player.pop();
        }
        while (number_1 != 0){
            if (sum + 11 <= 21){
                sum += 11;
            }
            else{
                sum += 1;
            }
            number_1--;
        }
        return sum;
    }
    int banker_call(){
        //庄家叫牌
        banker.push(plate[callnumber].rank);
        callnumber++;
        if (callnumber >= 52){
            callnumber = 0;
            Shuffle();
        }
        return (int)plate[callnumber - 1].rank;
    }
    int player_call(){
        //玩家叫牌
        player.push(plate[callnumber].rank);
        callnumber++;
        if (callnumber >= 52){
            callnumber = 0;
            Shuffle();
        }
        return (int)plate[callnumber - 1].rank;
    }
    friend ostream &operator<<(ostream &outStream, const Game &car)
        //操作结果：重载<<运算符
    {  //输出花色
        if (car.plate[car.callnumber].suit == CLUBS) outStream << "梅花";
        else if (car.plate[car.callnumber].suit == DIAMONDS) outStream << "方块";
        else if (car.plate[car.callnumber].suit == HEARTS) outStream << "红桃";
        else if (car.plate[car.callnumber].suit == SPADES) outStream << "黑桃";
        //输出面值
        if (car.plate[car.callnumber].rank == ACK) outStream << "A";
        else if (car.plate[car.callnumber].rank == JACK) outStream << "J";
        else if (car.plate[car.callnumber].rank == QUEEN) outStream << "Q";
        else if (car.plate[car.callnumber].rank == KING) outStream << "K";
        else cout << (int)car.plate[car.callnumber].rank;
        return outStream;
    }
};

int main()
{
    double money;//玩家金钱
    int  insurance_A;//庄家开局中的明牌面值
    int compare;//玩牌风格
    ifstream in;
    Game game;
    int player_score;
    int banker_score;
    game.Shuffle();
    in.open("money.txt");
    if (!in){
        cout << "文件打开失败" << endl;
        return 0;
    }
    in >> money;
    cout << "您当前的金币为:" << money << endl;
    in.close();
    cout << "请输入数字选择电脑的玩牌风格" << endl << "1 保守型：13点或者13点以上就不再拿牌"
        << endl << "2 进取型：15点或者15点以上就不再拿牌" << endl << "3 疯狂型：17点或者17点以上就不再拿牌" << endl;
    int in_type;
    cin >> in_type;
    switch (in_type){
    case 1:
        compare = 13;//保守型：13点或者13点以上就不再拿牌
        break;
    case 2:
        compare = 15;//进取型：15点或者15点以上就不再拿牌
        break;
    case 3:
        compare = 17;//疯狂型：17点或者17点以上就不再拿牌
        break;
    default:
        cout << "玩牌风格未按要求输入";
        return 0;
    }
    cout << "请设置赌金：" << endl;
    double bet;
    cin >> bet;
    while (true){

        if (money >= bet*1.5){
            break;
        }
        else{
            cout << "您当前的剩余金钱不足以设置这么高的赌金，请重新输入：" << endl;
            cin >> bet;
        }
    }


    cout << "您设置的赌金为：" << bet << "  现在开始游戏!" << endl;
    cout << "玩家发牌：玩家第一张牌：";
    cout << game<<"    ";
    game.player_call();
    cout << "玩家第二张牌：" << game << endl;
    game.player_call();
    cout << "庄家发牌：庄家发一张暗牌；庄家发一张明牌";
    game.banker_call();
    cout << game<< endl;
    insurance_A = game.banker_call();
    if (game.get_player_total_score() == 21){
        cout << "您拥有黑杰克" << endl;
        if (game.get_banker_total_score() != 21){
            cout << "恭喜您，您赢得了双倍赌金" << endl;
            money += (bet * 2);
            ofstream out("money.txt", ios::trunc);
            if (!out){
                cout << "打开文件失败";
                return 0;
            }
            out << money;
            out.close();
            return 0;
        }
    }
    if (insurance_A == 1){
        string signal;
        cout << "请问您是否买保险，请输入“1”买保险  “2”不买保险" << endl;
        cin >> signal;
        while (true){
            if (signal == "1"){
                cout << "您购买了保险，保险金额为：" << bet / 2 << endl;
                if (game.get_banker_total_score() == 21){
                    cout << "庄家为黑杰克，您拿回保险金，并赢得了赌金." << endl;
                    money += bet;
                    ofstream out("money.txt", ios::trunc);
                    if (!out){
                        cout << "打开文件失败";
                        return 0;
                    }
                    out << money;
                    out.close();
                    return 0;
                }
                else{
                    cout << "庄家不为黑杰克，您输掉了保险金,比赛继续." << endl;
                    money -= bet / 2;
                    break;
                }
            }
            else if (signal == "2"){
                cout << "您未购买保险金，继续比赛" << endl;
                break;
            }
            else {
                cout << "输入错误，请重新输入:" << endl;
                cin >> signal;
            }
        }

    }
    cout << "您是否继续要牌，请输入“1”继续要牌  “2”结束要牌" << endl;
    string player_signal;
    cin >> player_signal;
    while (true){
        if (player_signal == "1"){
            cout << "玩家再发一张牌：" << game << endl;
            game.player_call();
            cout << "您是否继续要牌，请输入“1”继续要牌  “2”结束要牌" << endl;
            cin >> player_signal;
        }
        else if (player_signal == "2"){
            cout << "玩家结束要牌" << endl;
            break;
        }
        else{
            cout << "输入错误，请重新输入：" << endl;
            cin >> player_signal;
        }
    }
    cout << "玩家的总点数为：" << game.get_player_total_score() << endl;
    if (game.get_player_total_score() >21){
        cout << "玩家爆牌，游戏结束，玩家输掉了赌金！" << endl;
        money -= bet;
        ofstream out("money.txt", ios::trunc);
        if (!out){
            cout << "打开文件失败";
            return 0;
        }
        out << money;
        out.close();
        return 0;
    }

    cout << "轮到庄家选择！" << endl;
    while (game.get_banker_total_score() < compare){
        cout << "庄家叫牌：" << game << endl;
        game.banker_call();
    }
    cout << "庄家的点数为：" << game.get_banker_total_score() << endl;
    if (game.get_banker_total_score()>21){
        cout << "庄家爆牌,游戏结束，玩家赢得了赌金。" << endl;
        money += bet;
    }
    if (game.get_banker_total_score() > game.get_player_total_score()){

        cout << "庄家赢得了比赛，玩家输掉赌金。" << endl;
        money -= bet;
    }
    else if (game.get_banker_total_score() == game.get_player_total_score()){

        cout << "该局打成平手" << endl;
    }
    else{

        cout << "玩家赢得了赌金。";
        money += bet;
    }
    ofstream out("money.txt", ios::trunc);
    if (!out){
        cout << "打开文件失败";
        return 0;
    }
    out << money;
    out.close();
    return 0;
}

