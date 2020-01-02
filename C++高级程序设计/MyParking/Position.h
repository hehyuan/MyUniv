#ifndef POSITION_H
#define POSITION_H
#include<ctime>
#include"Car.h"
class Position{
private:
    Car *car; // 在这个停车位上的车
    int col,row; //位置
    string inTime;//入场时间
    string outTime;//出场时间
    int flag;//标志位，记录该车位用于小型、中型、还是大型车
    bool valid;
public:
    Position(int col,int row,int flag);
    Position();
    bool isValid();
    void setValid();
    void resetValid();
    void setPos(int col, int row);
    void setInTime(string t);
    string getInTime();
    void setOutTime(string t);
    string getOutTime();
    int getFlag();
};

#endif // POSITION_H
