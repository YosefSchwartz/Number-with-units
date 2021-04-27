#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "NumberWithUnits.hpp"
using namespace std;


namespace ariel{
    //Declare on static mambers
    map<string,map<string,double>> NumberWithUnits::conversionTable;
    const double  EPS = 0.00001;

    //Return true iff the type is in the convertion table, else false.
    bool NumberWithUnits::isValidType(const std::string& type){
        std::map<std::string,std::map<std::string,double>>::iterator itr;
        for(auto& t : NumberWithUnits::conversionTable){
            if(t.first == type)
            {return true;}
        }
        return false;
    }
    void NumberWithUnits:: printTable_k(){
        map<string,map<string,double>> :: iterator ex_itr;
        map<string,double> :: iterator in_itr;
        for(ex_itr = NumberWithUnits::conversionTable.begin(); ex_itr != NumberWithUnits::conversionTable.end(); ex_itr++)
        {   
            cout<<"FIRST: "<<ex_itr->first<<"\t|"<<endl;
            for(in_itr = NumberWithUnits::conversionTable[ex_itr->first].begin(); in_itr != NumberWithUnits::conversionTable[ex_itr->first].end(); in_itr++){
                cout<<"\t\t|SECOND: "<<in_itr->first<<" = VALUE: "<<in_itr->second<<endl;
            }
            cout<<"____________________________________________________"<<endl;
        }
    }
    //Constructor
    NumberWithUnits::NumberWithUnits(double units,const std::string& type){
            //Check that this type is valid, else throw exception 
            if(!isValidType(type)){
                throw invalid_argument("Wrong type of units!\n our class doesnt know this type.\n");}
            //Init the data
            this->n = units;
            this->type = type;
        }
    void NumberWithUnits::read_units(std::ifstream& file){
            string values;
            
            while(getline(file,values)){
                stringstream values_ss{values};
                string temp;
                values.clear();

                while (getline(values_ss,temp,' ')){
                    values+=temp;
                }
                stringstream clearData(values);
                string first,second;
                getline(clearData,first, '=');
                getline(clearData,second);
                for(unsigned int i=0;i<first.length();++i){
                    if(isdigit(first.at(i))==0 && first.at(i)!= '.'){
                        string firstHalf = first.substr(0,i);
                        string secondHalf = first.substr(i,first.length());
                        firstHalf += ' ' + secondHalf;
                        first = firstHalf;
                        i = first.length();
                    }
                }
                for(unsigned int i=0;i<second.length();++i){
                    if(isdigit(second.at(i))==0 && second.at(i)!= '.'){
                        string firstHalf = second.substr(0,i);
                        string secondHalf = second.substr(i,second.length());
                        firstHalf += ' ' + secondHalf;
                        second = firstHalf;
                        i = second.length();
                    }
                }
                stringstream firstValue_ss{first};
                stringstream secondValue_ss{second};

                double first_value = 0;
                firstValue_ss>>first_value;
                string first_type;
                firstValue_ss>>first_type;
            
                double second_value = 0;
                secondValue_ss>>second_value;
                string second_type;
                secondValue_ss>>second_type;
                
                map<string,double>::iterator itr;

                for(itr = conversionTable[first_type].begin();itr != conversionTable[first_type].end();++itr){
                    conversionTable[itr->first][second_type] = conversionTable[itr->first][first_type] * second_value;
                    conversionTable[second_type][itr->first] = 1.0/conversionTable[itr->first][second_type];
                }
                for(itr = conversionTable[second_type].begin();itr != conversionTable[second_type].end();++itr){
                    conversionTable[itr->first][first_type] = conversionTable[itr->first][second_type] * first_value/second_value;
                    conversionTable[first_type][itr->first] = 1.0/conversionTable[itr->first][first_type];
                }

                NumberWithUnits::conversionTable[first_type][second_type]=second_value;
                NumberWithUnits::conversionTable[second_type][first_type]=first_value/second_value;
            }
        }

    NumberWithUnits operator+(const NumberWithUnits &num1,const NumberWithUnits &num2){
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                { nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            double nRes = num1.n+nByFirstType;
            NumberWithUnits a(nRes,num1.type);
            return a;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }
    }
    NumberWithUnits operator-(const NumberWithUnits &num1,const NumberWithUnits &num2){
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            double nRes = num1.n-nByFirstType;
            NumberWithUnits a(nRes,num1.type);
            return a;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }
    }
    NumberWithUnits NumberWithUnits::operator+=(NumberWithUnits num2){
        try{
            double nByFirstType = 0;
            if(this->type == num2.getType())
                {nByFirstType = num2.getN();}
            else            
                {nByFirstType = NumberWithUnits::conversionTable[num2.type].at(this->type) * num2.n;}
                
            this->n+=nByFirstType;
            return *this;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + this->type + "]";
            throw invalid_argument(err);
        }
    }
    NumberWithUnits NumberWithUnits::operator-=(NumberWithUnits num2){
        try{
            double nByFirstType = 0;
            if(this->type == num2.getType())
                {nByFirstType = num2.getN();}
            else            
                {nByFirstType = NumberWithUnits::conversionTable[num2.type].at(this->type) * num2.n;}

            this->n-=nByFirstType;
            return *this;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + this->type + "]";
            throw invalid_argument(err);
        }
    }

    bool operator<(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}

            return num1.n - nByFirstType < -EPS;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }
    }

    bool operator>(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            return num1.n - nByFirstType > EPS;  
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }  
    }

    bool operator<=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            return num1.n - nByFirstType <= EPS;  
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }  
    }
    
    bool operator>=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            return num1.n - nByFirstType >= -EPS;  
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }
    }
    
    bool operator!=(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        return !(num1==num2);
    }

    bool operator==(const NumberWithUnits &num1,const NumberWithUnits &num2) {
        try{
            double nByFirstType = 0;
            if(num1.type == num2.type)
                {nByFirstType = num2.n;}
            else
                {nByFirstType= NumberWithUnits::conversionTable[num2.type].at(num1.type) * num2.n;}
                
            return abs(num1.n - nByFirstType) < EPS;
        } catch (exception e){
            string err;
            err += "Units do not match - ["+ num2.type +  "] cannot be converted to [" + num1.type + "]";
            throw invalid_argument(err);
        }
    }
    NumberWithUnits operator*(double k,NumberWithUnits num){
        double temp = num.getN()*k;
        return NumberWithUnits(temp,num.getType());
    }
    NumberWithUnits operator*(NumberWithUnits num, double k){
        double temp = num.getN()*k;
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
        string firstObject_s;
        while(is.peek()!=']'){
            char c = is.get();
            firstObject_s += c;
        }
        char c = is.get();
        firstObject_s+= c;

        stringstream firstObject_ss{firstObject_s};
        string temp;
        string dataStr;
   
        while(getline(firstObject_ss,temp,' ')){
            dataStr+=temp;
        }
        stringstream clearData{dataStr};
        double tmp_n = 0;
        clearData>>tmp_n;
        string tmp_type;
        clearData>>tmp_type;
        tmp_type.erase(0, 1);
        tmp_type.erase(tmp_type.length()-1);

        if(!(num.isValidType(tmp_type)))
            {throw invalid_argument("Invalid argument!\n Incorrect type!\n");}
        num.n = tmp_n;
        num.type = tmp_type;
        return is;
    }   
}

