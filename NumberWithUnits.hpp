#pragma once
#include <fstream>
#include <iostream>

namespace ariel{
    class NumberWithUnits{
        private:
            int n;
            std::string type;

        public:
        //Constructor
        NumberWithUnits(int units,std::string type);
        //Read units from .txt file
        static void read_units(std::ifstream& file);


        NumberWithUnits operator- (){
            return NumberWithUnits(-n,type);
        };
        NumberWithUnits operator+ (){
            return NumberWithUnits(n,type);
        };

        friend NumberWithUnits operator+(NumberWithUnits &num1, NumberWithUnits &num2);
        friend NumberWithUnits operator-(NumberWithUnits &num1, NumberWithUnits &num2);
        NumberWithUnits operator+=(NumberWithUnits num2);
        NumberWithUnits operator-=(NumberWithUnits num2);

        friend bool operator<(NumberWithUnits &num1, NumberWithUnits &num2);
        friend bool operator>(NumberWithUnits &num1, NumberWithUnits &num2);
        friend bool operator<=(NumberWithUnits &num1, NumberWithUnits &num2);
        friend bool operator>=(NumberWithUnits &num1, NumberWithUnits &num2);
        bool operator!=(NumberWithUnits num);
        bool operator==(NumberWithUnits num);

        friend NumberWithUnits operator*(double k,NumberWithUnits &num);

        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);

        friend std::ostream& operator<<(std::ostream& os, const NumberWithUnits &num);
        friend std::istream& operator>>(std::istream& is, NumberWithUnits &num);    
    };
}