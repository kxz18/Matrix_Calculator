#ifndef REALNUM
#define REALNUM
#include<iostream>
#include<string>
#include<cmath>

class RealNum{
	double num;
	std::string expression;
protected:
	std::string trim(std::string& s);//get rid of brackets and spaces
	double Rational(std::string s);//turn fraction to double
	std::string Rational(double a);//turn rational number to fraction,if a is not a rational number, return"Failed"
	std::string PureIrr(double a);//turn irrational number(doesn't include rational part) to corresponding format
	std::string DToS(double a); //turn double to corresponding expression(if a has both rational part and irrational part, it will output double itself)
	double SToD(std::string s);//turn expression to double
public:
	RealNum();
	RealNum(double a);
	RealNum(std::string s);
	bool IsInt(double a);//return whether a is an int
	operator double() const;//implicit conversion
	
	friend RealNum& operator+= (RealNum &a,const double &b);//must be overloaded as implicit conversion is only triggered when calculating two RealNum (e.g a+=b,a\b are both RealNum)
	friend RealNum& operator-= (RealNum &a,const double &b);
	friend RealNum& operator*= (RealNum &a,const double &b);
	friend RealNum& operator/= (RealNum &a,const double &b);
	friend std::ostream& operator<< (std::ostream& out,const RealNum& src);
	friend std::istream& operator>> (std::istream& in,RealNum& dst);
	~RealNum();
};

#endif
