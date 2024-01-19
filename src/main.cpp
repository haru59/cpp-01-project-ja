#include<iostream>
#include<array>
#include<string>

int make_map(); //初期の地図を作成
const int rows = 10;
const int column = 10;
std::array<std::array<char, column>, rows> map;

void show_state();

int input_command(); //ユーザーのコマンド入力関数
int command{0}; //ユーザーのコマンド

int change_direction();
int direction{1}; //車の向き、画面上1：上(North)、2：右(East)、3：下(South)、4：左(West)

int change_speed();
int speed{1}; //現在の車速、初期値1

int change_fuel();
int fuel{3}; //ガソリン残量、初期値50

int move_car();
int start_rows = 1;
int start_column = 1;
int after_rows = 1;
int after_column = 1;

bool test{1};
int judge_location();


//######################################################################

int main(){
    make_map();//初期のマップを作成、表示する 
    while(test == 1){
        show_state();//現在の状態を表示する
        input_command(); //ユーザーのコマンド入力
        change_direction(); //ユーザーのコマンドによって車の向きを変える
        change_speed();//ユーザーのコマンドによって車速を変える
        change_fuel();//ユーザーのコマンドによってガソリンの残量を変える
        move_car(); //車両を移動する
        judge_location(); //車両の現在地を地図上で表示＋範囲外に車両が行ったらエラーを出す
        }
    }


//######################################################################
// 関数：make_map()
// 概要：初期の地図を作成する

int make_map(){
    map = {{
    {'-','-','-','-','-','-','-','-','-','-'},
    {'|','P',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ','F',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ','G','|'},
    {'-','-','-','-','-','-','-','-','-','-'},
    }};
    std::cout << std::endl;
    std::cout << "Game start" << std::endl;
    std::cout << "Go to the Goal" << std::endl;    
    std::cout << "**********************" << std::endl;               
    std::cout << "        North    " << std::endl;
    std::cout << "    West  4  East    " << std::endl;
    std::cout << "        South    " << std::endl;
    for(int i{0}; i <rows; i++){
        for(int j{0}; j < column; j++){
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "P:Player, F:Gas station, G:Goal" << std::endl;
    return 0;
}

//######################################################################
// 関数：show_state()
// 概要：現在の車速、ガソリン残量、車が向いている方角を表示する

void show_state(){
    std::string dir;
    if(direction==1){
        dir ="North";
    }else if(direction==2){
        dir ="East";
    }else if(direction==3){
        dir ="Sorth";
    }else{
        dir ="West";
    }
    std::cout << "**********Current state list**********: " << speed << std::endl;
    std::cout << "Current car speed: " << speed << std::endl;
    std::cout << "Current fuel level: " << fuel << std::endl;
    std::cout << "Direction the car is facing: " << dir << std::endl;
    std::cout << "**************************************: " << speed << std::endl;
}

//######################################################################
// 関数：input_command()
// 概要：ユーザーのコマンド入力に対応する

int input_command(){
    std::cout << "***Command list*****************" << std::endl;
    std::cout << "* 1 : turn left                *" << std::endl;
    std::cout << "* 2 : turn right               *" << std::endl;
    std::cout << "* 3 : continue straight        *" << std::endl;
    std::cout << "* 4 : accelerate               *" << std::endl;
    std::cout << "* 5 : decelerate               *" << std::endl;
    std::cout << "* 6 : stop                     *" << std::endl;
    std::cout << "********************************" << std::endl;
    std::cout << "Please enter a command(1 ~ 6):" ;
    std::cin >> command;
    if (command < 1 || command >6 ){
        throw std::out_of_range("Invalid input");
        }
    return command; 
}

//######################################################################
// 関数：change_direction()
// 概要：車の進行方向を変える（マスは動かない）

int change_direction(){
    if (command == 2){
        if(direction == 4){
            direction = 1;
        }else{
            direction = direction + 1;
        }
    }
    if (command == 1){
        if(direction == 1){
            direction = 4;
        }else{
            direction = direction - 1 ;
        } 
    }
    return direction; 
}

//######################################################################
// 関数：change_speed()
// 概要：車速変更（マスは動かない）

int change_speed(){
    if (command == 4){
        speed = speed + 1;
    }else if(command == 5){
        if(speed == 0){ //すでにスピードがゼロならゼロのままにする
            speed = 0;
        }else{
            speed = speed - 1;
        }
    }else if(command == 6){
        speed = 0;;
    }
    return speed; 
}

//######################################################################
// 関数：change_fuel()
// 概要：ガソリン量変更

int change_fuel(){
    if (command == 3){ //前進したときのみガソリンを減らす
        fuel = fuel - (1 * speed); //車速に応じてガソリンを減らす
    }
    //Add
    if(fuel == 0){
        test =0;
        std::cout << "Gameover" << std::endl;
    }
    //Add
    return fuel; 
}

//######################################################################
// 関数：move_car()
// 概要：ユーザーコマンドが”continue straight”の時に現在の車速、車の向きに応じて車を移動する

int move_car(){
    if(direction == 1 && command ==3 && speed != 0){ //画面上の上（北）に移動、行のみ変更で列は動かさない
        after_rows = start_rows-(1*speed);
        after_column = start_column;
        map[after_rows][after_column] = 'P';
        map[start_rows][start_column] =' ';
        start_rows = after_rows;
        start_column = after_column;
    }else if(direction == 2 && command ==3 && speed != 0){ //画面上の右（西）に移動、列のみ変更で行は動かさない
        after_rows = start_rows;
        after_column = start_column+(1*speed);
        map[after_rows][after_column] = 'P';
        map[start_rows][start_column] =' ';
        start_rows = after_rows;
        start_column = after_column;
    }else if(direction == 3 && command ==3 && speed != 0){ //画面上の下（南）に移動、行のみ変更で列は動かさない
        after_rows = start_rows+(1*speed);
        after_column = start_column;
        map[after_rows][after_column] = 'P';
        map[start_rows][start_column] =' ';
        start_rows = after_rows;
        start_column = after_column;
    }else if(direction == 4 && command ==3 && speed != 0){ //画面上の左（西）に移動、列のみ変更で行は動かさない
        after_rows = start_rows;
        after_column = start_column-(1*speed);
        map[after_rows][after_column] = 'P';
        map[start_rows][start_column] =' ';
        start_rows = after_rows;
        start_column = after_column;
    }
    return 0;
}


//######################################################################
// 関数：judge_location()
// 概要：車両の現在地を地図上で表示＋範囲外に車両が行ったらエラーを出す
int judge_location(){
    if(after_rows <= 0 || after_rows >= 9 || after_column <= 0 || after_column >=9){//車両が地図の範囲外の場合
        throw std::out_of_range("Car is in out of map");
    }else if(after_rows==8 && after_column==8){
        test = 0;
        std::cout << "Goal" << std::endl;
        std::cout << "        North    " << std::endl;
        std::cout << "    West  4  East    " << std::endl;
        std::cout << "        South    " << std::endl;
        for(int i{0}; i <rows; i++){
            for(int j{0}; j < column; j++){
                std::cout << map[i][j] << " ";
            }
        std::cout << std::endl;
        }
    }else{
        std::cout << "        North    " << std::endl;
        std::cout << "    West  4  East    " << std::endl;
        std::cout << "        South    " << std::endl;
        for(int i{0}; i <rows; i++){
            for(int j{0}; j < column; j++){
                std::cout << map[i][j] << " ";
            }
        std::cout << std::endl;
        }
        std::cout << "P:Player, F:Gas station, G:Goal" << std::endl;
    }
    return 0;
}
