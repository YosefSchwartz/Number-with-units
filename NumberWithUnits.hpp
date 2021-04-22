#pragma once
#include <fstream>
#include <iostream>
#include <map>

namespace ariel{
    class NumberWithUnits{
        private:
            double n; // number of units
            std::string type; //type of units
            static std::map<std::string,std::map<std::string,double>> conversionTable;
            bool isValidType(std::string type);
        
        public:
        //Constructor
        NumberWithUnits(double units,std::string type);
        //Read units from .txt file
        static void read_units(std::ifstream& file);
        //Geters
        double getN(){return n;}
        std::string getType(){return type;}
                
        NumberWithUnits operator- (){
            return NumberWithUnits(-n,type);
        };
        NumberWithUnits operator+ (){
            return NumberWithUnits(n,type);
        };

        friend NumberWithUnits operator+(const NumberWithUnits &num1,const NumberWithUnits &num2);
        friend NumberWithUnits operator-(const NumberWithUnits &num1,const NumberWithUnits &num2);
        NumberWithUnits operator+=(NumberWithUnits num2);
        NumberWithUnits operator-=(NumberWithUnits num2);

        friend const bool operator<(const NumberWithUnits &num1,const NumberWithUnits &num2) ;
        friend const bool operator>(const NumberWithUnits &num1,const NumberWithUnits &num2) ;
        friend const bool operator<=(const NumberWithUnits &num1,const NumberWithUnits &num2) ;
        friend const bool operator>=(const NumberWithUnits &num1,const NumberWithUnits &num2) ;
        friend const bool operator!=(const NumberWithUnits &num1,const NumberWithUnits &num2)  ;
        friend const bool operator==(const NumberWithUnits &num1,const NumberWithUnits &num2)  ;

        friend NumberWithUnits operator*(double k,NumberWithUnits &num);
        friend NumberWithUnits operator*(NumberWithUnits &num, double k);


        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);

        friend std::ostream& operator<<(std::ostream& os, const NumberWithUnits &num);
        friend std::istream& operator>>(std::istream& is, NumberWithUnits &num);    
    };
}