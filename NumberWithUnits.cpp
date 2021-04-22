#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
// #include <map>
#include <vector>
#include "NumberWithUnits.hpp"
using namespace std;

#define EPS 0.00001

namespace ariel{
    //Declare on static mambers
    map<string,map<string,double>> NumberWithUnits::conversionTable;

    //Return true iff the type is in the convertion table, else false.
    bool NumberWithUnits::isValidType(std::string type){
        std::map<std::string,std::map<std::string,double>>::iterator itr;
        for(auto& t : NumberWithUnits::conversionTable){
            if(t.first == type)
                return true;
        }
        return false;
    }
    //Constructor
    NumberWithUnits::NumberWithUnits(double units,std::string type){
            //Check that this type is valid, else throw exception 
            if(!isValidType(type)) throw invalid_argument("Wrong type of units!\n our class doesnt know this type.\n");
            //Init the data
            this->n = units;
            this->type = type;
        }
    void NumberWithUnits::read_units(std::ifstream& file){
            while(!file.eof()){
                double first_value;
                file>>first_value;
                
                string first_type;
                file>>first_type;
                
                char equal_oper;
                file>>equal_oper;

                double second_value;
                file>>second_value;

                string second_type;
                file>>second_type;
                
                map<string,double>::iterator in_itr;
                for(in_itr = conversionTable[first_type].begin();in_itr != conversionTable[first_type].end();++in_itr){
                    conversionTable[second_type][in_itr->first]=(in_itr->second)*(1.0/(second_value));
                    conversionTable[in_itr->first][second_type]=conversionTable[in_itr->first][first_type]*second_value;
                }
                NumberWithUnits::conversionTable[first_type][second_type]=second_value;
                NumberWithUnits::conversionTable[second_type][first_type]=1.0/second_value;   
            }
        }

    NumberWithUnits operator+(const NumberWithUnits &num1,const NumberWithUnits &num2){
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        double nRes = num1.n+nByFirstType;
        NumberWithUnits a(nRes,num1.type);
        return a;
    }
    NumberWithUnits operator-(const NumberWithUnits &num1,const NumberWithUnits &num2){
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        double nRes = num1.n-nByFirstType;
        NumberWithUnits a(nRes,num1.type);
        return a;
    }
    NumberWithUnits NumberWithUnits::operator+=(NumberWithUnits num2){
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(this->type) * num2.n;
        this->n+=nByFirstType;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-=(NumberWithUnits num2){
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(this->type) * num2.n;
        this->n-=nByFirstType;
        return *this;
    }

    const bool operator<(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        return (num1.n - nByFirstType) < EPS;
    }

    const bool operator>(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        return (num1.n - nByFirstType) > EPS;    
    }

    const bool operator<=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        return (num1.n - nByFirstType) <= EPS;    
    }
    
    const bool operator>=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        return (num1.n - nByFirstType) >= -EPS;    
    }
    
    const bool operator!=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return !(num1==num2);
    }

    const bool operator==(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        double nByFirstType = NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;
        return abs(num1.n - nByFirstType) < EPS;
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
        this->n = n+1;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits tmp(this->n,this->type);
        this->n = n+1;
        return tmp;
    }

    NumberWithUnits& NumberWithUnits::operator--(){
        this->n = n-1;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits tmp(this->n,this->type);
        this->n = n-1;
        return tmp;
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
        unsigned int i = 0;
        string temp;
        while(line.at(i) != '['){
            temp+=line.at(i);
            i++;
        }
        i++;
        double tmp_n = stod(temp);
        temp = "";
        while(line.at(i) != ']'){
            temp += line.at(i);
            i++;
        }
        if(!(num.isValidType(temp)))
            throw invalid_argument("Invalid argument!\n Incorrect type!\n");
        num.n = tmp_n;
        num.type = temp;

        return is;
    }   
}

