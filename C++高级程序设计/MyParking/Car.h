#ifndef CAR_H
#define CAR_H
#define CarSizeNum 3
#include<string>
using namespace std;
static string carSize[] = {"小汽车","小卡","中卡","大卡"};
class Car{
private:
    string plate; // 车牌号
    string color;//颜色
    string size;//车型
public:
    Car(string plate="", string color="red", string size="小汽车"){
        setPlate(plate);
        setColor(color);
        setSize(size);
    }
    void setPlate(string plate)
    {
        if(plate.size()!=7){ //有效性检测
            //error()
            this->plate = "苏111111";
        }else{
            this->plate = plate;
        }
    }
    string getPlate()
    {
        return this->plate;
    }
    void setColor(string color)
    {
       this->color = color;
    }
    string getColor()
    {
        return this->color;
    }
    void setSize(string size)
    {
        for(int i = 0;i<CarSizeNum;++i){
            if(carSize[i]==size){
                this->size = size;
                return;
            }
        }
        this->size = carSize[0];
    }
    string getSize(){
        return this->size;
    }
};

#endif // CAR_H
