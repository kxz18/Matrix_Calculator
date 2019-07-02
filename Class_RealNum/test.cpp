#include<iostream>
#include<string>
#include<cmath>
#include"RealNum.h"
using namespace std;

int main(){
	RealNum a;
	cout<<"Please enter a real number:";
	cin>>a;
	cout<<"The figure you've entered is "
		<<a<<endl;
	double b=a;
	cout<<"Figure in storage is: "<<b<<endl;
}
