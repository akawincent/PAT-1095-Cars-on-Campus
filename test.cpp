/*
 * @Author: akawincent 3511606256@qq.com
 * @Date: 2023-02-09 22:33:21
 * @LastEditors: akawincent 3511606256@qq.com
 * @LastEditTime: 2023-02-11 10:34:33
 * @FilePath: \undefinedc:\Users\Administrator\Desktop\test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>

using namespace std;

class Car{
    public:
        Car(string name,int time,bool status){
            m_Name.resize(8);
            this->m_Name = name;
            this->m_time = time;
            this->m_status = status; 
        }
        ~Car(){}
    public:
        string m_Name;
        int m_time;
        bool m_status;
};

class Parking{
    public:
        Parking(string name,int period){
            this->Name = name;
            this->Period = period;
        }
        ~Parking(){}
    public:
        string Name;
        int Period;
};

int ConvertTimeToInt(string time){
    int hh = (time[0]-0x30) * 10 + (time[1]-0x30);
    int mm = (time[3]-0x30) * 10 + (time[4]-0x30);
    int ss = (time[6]-0x30) * 10 + (time[7]-0x30);
    return (hh * 3600 + mm * 60 + ss);
}

string ConvertTimeToStr(int period){
    string tt;tt.resize(8);
    int h,m,s;
    h = period/3600;
    m = (period - 3600 * h) / 60;
    s = period - 3600 * h - m * 60;
    return string(1, h / 10 + '0') + string(1, h % 10 + '0') + ":" + string(1, m / 10 + '0') + string(1, m % 10 + '0') + ":" + string(1, s / 10 + '0') + string(1, s % 10 + '0');
}

bool ConvertStatusToInt(string status){
    bool res;
    if(status[0] == 'i') res = 1;
    else res = 0;
    return res;
}

bool CompareTime(const Car &c1,const Car &c2){
    if(c1.m_time != c2.m_time) return c1.m_time < c2.m_time;
    else return c1.m_status>c2.m_status;
}

bool CompareTimeAndName(const Car &c1,const Car &c2){
    if(c1.m_Name != c2.m_Name)
        return c1.m_Name < c2.m_Name;	
	else if(c1.m_time != c2.m_time)
        return c1.m_time < c2.m_time;
    else
        return c1.m_status > c2.m_status;
}

bool CompareName(const Parking &p1,const Parking &p2){
    return p1.Name < p2.Name;
}

bool ComparePeriod(const Parking &p1,const Parking &p2){
    return p1.Period < p2.Period;
}

int main(){
    int n,k;
    string name;name.resize(8);
    string time;time.resize(8);
    string status;status.resize(3);
    string time_stamp;time_stamp.resize(8);
    int Time_stamp;
    int Time;
    bool Status;
    int period = 0;
    int counter = 0;
    int max_period = -99999;

    std::vector<Car> cars;
    std::vector<Car> cars_filter;
    std::vector<Parking> parkings;
    std::vector<Car>::iterator pos;
    std::vector<Car>::iterator pos_stamp;
    std::vector<int> period_list;
    std::vector<int> counters;

    cin>>n>>k;

    for(int i=0;i<n;i++){
        cin>>name;
        cin>>time;
        cin>>status;

        Time = ConvertTimeToInt(time);
        Status = ConvertStatusToInt(status);

        Car car(name,Time,Status);
        cars.push_back(car);
    }

    sort(cars.begin(),cars.end(),CompareTimeAndName);

    for(std::vector<Car>::iterator it = (cars.begin() + 1); it != cars.end(); ++it){
        if((*it).m_Name == (*(it-1)).m_Name && (*it).m_status == false && (*(it-1)).m_status == true){
                cars_filter.push_back((*it));
                cars_filter.push_back((*(it-1)));
        }
    }

    sort(cars_filter.begin(),cars_filter.end(),CompareTimeAndName);

    for(std::vector<Car>::iterator it = cars_filter.begin(); it != (cars_filter.end() - 1); it++){
        if((*it).m_Name == (*(it+1)).m_Name && (*it).m_status == true && (*(it+1)).m_status == false){
            period = (*(it+1)).m_time - (*it).m_time;

            Parking parking((*it).m_Name,period);

            if(parkings.empty()){
                parkings.push_back(parking);
            }
            else{
                bool flag = 0;
                for(std::vector<Parking>::iterator iit = parkings.begin(); iit != parkings.end(); iit++){
                    if((*iit).Name == parking.Name){
                        (*iit).Period = (*iit).Period + period;
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0){
                    parkings.push_back(parking);
                }
            }
        }
    }

    sort(cars_filter.begin(),cars_filter.end(),CompareTime);
    sort(parkings.begin(),parkings.end(),ComparePeriod);
    max_period = (*(parkings.end()-1)).Period;
    sort(parkings.begin(),parkings.end(),CompareName);

    pos_stamp = cars_filter.begin();
    for(int j = 0;j<k;j++){
        cin>>time_stamp;
        Time_stamp = ConvertTimeToInt(time_stamp);
        for(std::vector<Car>::iterator it = pos_stamp; it != cars_filter.end(); ++it){
            if((*it).m_time <= Time_stamp){
                if((*it).m_status == true){
                    counter++;
                }
                else if((*it).m_status == false){
                    counter--;
                }
            }
            else{
                pos_stamp = it;
                break;
            }
        }
        cout<<counter<<endl;
    } 

    for(std::vector<Parking>::iterator it = parkings.begin(); it != parkings.end(); it++){
        if((*it).Period == max_period){
            cout<<(*it).Name<<" ";
        }
        //cout<<(*it).Name<<" "<<(*it).Period<<endl;
    }

    cout<<ConvertTimeToStr(max_period);

    return 0;
}