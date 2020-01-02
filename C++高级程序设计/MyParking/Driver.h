#pragma once
#ifndef DRIVER_H
#define DRIVER_H
#include"Car.h"
#include"Park.h"
class Driver {
private:
	Car car;
public:
	Driver(Car car);
	void parkCar();//泊车
	string queryEmptyPos();//查询空车位
	string takeCar();//取车
	void payForPark();//缴费
};

#endif