#include <iostream>
#include <string>
#include <fstream>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{
        NumberWithUnits::NumberWithUnits(int units,string type){
            this->n = units;
            this->type = type;
        }
        //Read units from .txt file
        void NumberWithUnits::read_units(std::ifstream& file){

        }
        NumberWithUnits operator+(NumberWithUnits &num1, NumberWithUnits &num2){
            int nRes = num1.n+num2.n;
            return NumberWithUnits(nRes,num1.type);
        }
        NumberWithUnits operator-(NumberWithUnits &num1, NumberWithUnits &num2){
            int nRes = num1.n-num2.n;
            return NumberWithUnits(nRes,num1.type);
        }
        NumberWithUnits NumberWithUnits::operator+=(NumberWithUnits num2){
            this->n+=num2.n;
            return *this;
        }
        NumberWithUnits NumberWithUnits::operator-=(NumberWithUnits num2){
            this->n-=num2.n;
                return *this;
        }

        bool operator<(NumberWithUnits &num1, NumberWithUnits &num2){
            return true;
        }
        bool operator>(NumberWithUnits &num1, NumberWithUnits &num2){
            return true;
        }
        bool operator<=(NumberWithUnits &num1, NumberWithUnits &num2){
             return true;
        }
        bool operator>=(NumberWithUnits &num1, NumberWithUnits &num2){
             return true;
        }
        bool NumberWithUnits::operator!=(NumberWithUnits num){
            return true;
        }
        bool NumberWithUnits::operator==(NumberWithUnits num){
            return true;
        }

        NumberWithUnits operator*(double k,NumberWithUnits &num){
            num.n*=k;
            return num;
        }

        NumberWithUnits& NumberWithUnits::operator++(){
            return *this;
        }
        NumberWithUnits NumberWithUnits::operator++(int){
            return *this;
        }

        ostream& operator<<(ostream& os, const NumberWithUnits &num){
            return os;
        }
        istream& operator>>(istream& is, NumberWithUnits &num){
            return is;
        }   
    
}
