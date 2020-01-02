#ifndef PARK_H
#define PARK_H
#include"Position.h"
#define PosRow 3
#define PosCol 3
class Park{
private:
    static Position **p;
    static constexpr double feePerHour=1.0;//每小时的停车费用

public:
    Park();
   static string queryEmptyPos(int flag);//查询空车位，返回包含空车位位置信息的字符串
   static Position** initAll(); // 初始化静态成员变量
    bool parkCar(Car car);//泊车,返回泊车是否成功的布尔值
    string takeCar(Car car);//取车,返回取车的结果(一共花费的时间,车停在什么地方)
    string queryCar(string plate);//查询车的信息,如果成功返回车的位置,不然返回失败串

};
Position **Park::p = Park::initAll();
#endif // PARK_H
