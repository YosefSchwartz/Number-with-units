#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
// #include <map>
#include <vector>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{
    //Constructor
    NumberWithUnits::NumberWithUnits(double units,std::string type){
            this->n = units;
            this->type = type;
        }
    void NumberWithUnits::read_units(std::ifstream& file){
        cout<<"DO READ UNITS"<<endl;
        }

    NumberWithUnits operator+(NumberWithUnits &num1, NumberWithUnits &num2){
        double nRes = num1.n+num2.n;
        NumberWithUnits a(nRes,num1.type);
        return a;
    }
    NumberWithUnits operator-(NumberWithUnits &num1, NumberWithUnits &num2){
        double nRes = num1.getN()-num2.getN();
        return NumberWithUnits(nRes,num1.getType());
    }
    NumberWithUnits NumberWithUnits::operator+=(NumberWithUnits num2){
        this->n+=num2.n;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-=(NumberWithUnits num2){
        this->n-=num2.n;
            return *this;
    }
    const bool operator<(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return true;
    }
    const bool operator>(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return true;
    }
    const bool operator<=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
         return true;
    }
    const bool operator>=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
         return true;
    }
    const bool operator!=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return true;
    }
    const bool operator==(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return true;
    }
    NumberWithUnits operator*(double k,NumberWithUnits &num){
        double temp = num.n*k;
        return NumberWithUnits(temp,num.getType());
    }
    NumberWithUnits operator*(NumberWithUnits &num, double k){
        double temp = num.n*k;
        return NumberWithUnits(temp,num.getType());
    }
    NumberWithUnits& NumberWithUnits::operator++(){
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        return *this;
    }
    ostream& operator<<(ostream& os, const NumberWithUnits &num){
        os<<num.n<<"["<<num.type<<"]";
        return os;
    }
    istream& operator>>(istream& is, NumberWithUnits &num){
        string line;
        string word;
        while(!is.eof()){
            is>>word;
            line+=word;
        }
        return is;
    }   
}

