/**
 * Test to check Number with units exam.
 * cpp course.
 *
 * AUTHORS: Yosef Schwartz.
 * 
 * Date: 14 on April 2021.
 */

#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <sstream>
using namespace ariel;

#include <string>
using namespace std;
ifstream units_file{"units.txt"};

TEST_CASE("Create objects") {
    CHECK_THROWS(NumberWithUnits(3,"km")); // Try create object before init the conversion table.

    NumberWithUnits::read_units(units_file);

    CHECK_NOTHROW(NumberWithUnits(3,"km")); 
    CHECK_NOTHROW(NumberWithUnits(340,"cm")); 
    CHECK_NOTHROW(NumberWithUnits(7,"kg")); 
    CHECK_NOTHROW(NumberWithUnits(3,"ton")); 
    CHECK_NOTHROW(NumberWithUnits(50,"min")); 
    CHECK_NOTHROW(NumberWithUnits(4,"hour")); 
    CHECK_NOTHROW(NumberWithUnits(6,"ILS")); 
    //Worng type of the unit type
    CHECK_THROWS(NumberWithUnits(23,"Kilograms"));
    CHECK_THROWS(NumberWithUnits(50,"minutes"));
    CHECK_THROWS(NumberWithUnits(10,"Ils"));
    CHECK_THROWS(NumberWithUnits(3,"kM"));
    CHECK_THROWS(NumberWithUnits(56,"M"));
    CHECK_THROWS(NumberWithUnits(6,"Tons"));
    CHECK_THROWS(NumberWithUnits(5.5,"HOUR")); 
}

TEST_CASE("Value of objects"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{7,"km"};
    CHECK_EQ(a.getN(),7);
    CHECK_EQ(a.getType(),"km");

    NumberWithUnits b{380, "cm"};
    CHECK_EQ(b.getN(),380);
    CHECK_EQ(b.getType(),"cm");

    NumberWithUnits c{4,"min"};
    CHECK_EQ(c.getN(),4);
    CHECK_EQ(c.getType(),"min");
}

TEST_CASE("Get input from string"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits num(1,"km");

    istringstream issA{"78      [    km   ]"};
    issA>> num;
    CHECK_EQ(num.getN(),78);
    CHECK_EQ(num.getType(),"km");

    istringstream issB{"     6    [ton   ]"};
    issB>>num;
    CHECK_EQ(num.getN(),6);
    CHECK_EQ(num.getType(),"ton");

    istringstream issC{"     21    [ min   ]"};
    issC>>num;
    CHECK_EQ(num.getN(),21);
    CHECK_EQ(num.getType(),"min");
}

TEST_CASE("Output configuration"){
    NumberWithUnits::read_units(units_file);
    stringstream ss;
    string temp;

    NumberWithUnits num1(42.2,"km");
    ss<<num1;
    ss>>temp;
    CHECK(temp == "42.2[km]");
    ss.clear();

    NumberWithUnits num2(1.5,"hour");
    ss<<num2;
    ss>>temp;
    CHECK(temp == "1.5[hour]");
    ss.clear();

    NumberWithUnits num3(7,"sec");
    ss<<num1;
    ss>>temp;
    CHECK(temp == "7[sec]");
    ss.clear();

    NumberWithUnits num4(25,"ILS");
    ss<<num1;
    ss>>temp;
    CHECK(temp == "25[ILS]");
    ss.clear();

    NumberWithUnits num5(15.7,"kg");
    ss<<num1;
    ss>>temp;
    CHECK(temp == "15.7[kg]");
    ss.clear();

    NumberWithUnits num6(200,"g");
    ss<<num1;
    ss>>temp;
    CHECK(temp == "200[g]");
}

TEST_CASE("Math operators"){
    NumberWithUnits::read_units(units_file);
    const double EPS = 0.0001;

    NumberWithUnits distance_A(1,"km");
    NumberWithUnits distance_B(700,"m");
    NumberWithUnits distance_C(60,"cm");
    CHECK(((distance_A + distance_B).getN() - 1.7)<EPS);
    CHECK(((distance_B + distance_C).getN() - 700.06)<EPS);
    CHECK((distance_C + distance_B).getType() == "cm");
    //CHECK(((distance_A + distance_B + distance_C).getN() - 1.700060)<EPS);
    CHECK(((30*distance_C).getN() - 1800) < EPS);

    distance_B+= distance_C;
    CHECK(distance_B.getN() == 1700);
    CHECK(distance_B.getType() == "m");
    
    NumberWithUnits time_A(1.5,"hour");
    NumberWithUnits time_B(45,"min");
    NumberWithUnits time_C(30,"sec");
    CHECK(((time_B - time_C).getN() - 44.5)<EPS);
    CHECK(((time_A - time_B).getN() - 0.75)<EPS);
    //CHECK(((time_B - time_A - time_C).getN() - -45.5) < EPS);
    CHECK((-time_C).getN() == -30);
    CHECK(time_C.getN() == 30);
    time_B-=time_C;
    CHECK((time_B.getN() - 44.5)<EPS);
    CHECK(time_B.getType() == "min");
    CHECK((time_C--).getN() == 29);
    CHECK((--time_C).getN() == 29);
    CHECK(time_C.getN() == 28);

    NumberWithUnits weight_A(0.5,"ton");
    NumberWithUnits weight_B(-300,"kg");
    NumberWithUnits weight_C(250,"g");

    CHECK(((weight_A + weight_B).getN() - 0.8)<EPS);
    CHECK((-weight_B).getN() == 300);
    CHECK((+weight_B).getN() == -300);
    CHECK((weight_A++).getN() == 1.5);
    CHECK(((weight_A*3).getN() - 1.5)<EPS);
    CHECK((++weight_C).getN()== 250);
    CHECK(weight_C.getN() == 251);

    //Try to calculate different kind of types
    CHECK_THROWS(weight_A+time_B);
    CHECK_THROWS(time_B - distance_A);
    CHECK_THROWS(time_C+=weight_B);
    CHECK_THROWS(weight_C-=distance_B);
}

TEST_CASE("Comparisons"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits distance_A(1,"km");
    NumberWithUnits distance_B(700,"m");
    NumberWithUnits distance_C(60,"cm");
    NumberWithUnits distance_D(0.5,"km");
    NumberWithUnits distance_E(4700,"m");
    NumberWithUnits distance_F(1000000,"cm");

    CHECK(distance_A < distance_E);
    CHECK(distance_C < distance_D);
    CHECK(distance_E > distance_C);
    CHECK(distance_F > distance_D);
    CHECK(distance_F>=distance_A);
    CHECK(distance_D>=distance_E);
    CHECK(distance_D <= distance_B);
    CHECK(distance_C <= distance_D);
    CHECK_FALSE(distance_F!=distance_A);
    CHECK(distance_A!=distance_B);
    CHECK(distance_F == distance_A);
    CHECK_FALSE(distance_C == distance_E);

    //Comparisons of different types
    NumberWithUnits weight_A(0.5,"ton");
    NumberWithUnits weight_B(-300,"kg");
    NumberWithUnits weight_C(250,"g");

    NumberWithUnits time_A(1.5,"hour");
    NumberWithUnits time_B(45,"min");
    NumberWithUnits time_C(30,"sec");
    bool temp;
    CHECK_THROWS(temp = (weight_A>time_B));
    CHECK_THROWS(temp = (time_B <distance_A));
    CHECK_THROWS(temp = (time_C>=weight_B));
    CHECK_THROWS(temp = (weight_C<=distance_B));
    CHECK_THROWS(temp = (time_A == distance_C));
    CHECK_THROWS(temp = (weight_A != distance_B));
}



