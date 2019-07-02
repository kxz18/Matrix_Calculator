#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<new>
#include"RealNum.h"

class Matrix{
protected:
	int row;
	int column;
	RealNum** matrix;
	void RowSwap(int m,int n);
public:
	Matrix(int a);//square matrix
	Matrix(int a,int b);//normal matrix
	Matrix()=delete;
	Matrix(const Matrix &a);//As members include a pointer, redefination of copy constructor and move constructor is necassary
	Matrix(Matrix &&a);
	int getRow() const;
	int getColumn() const;
	RealNum* operator[] (int i);//return RealNum* for another []
	RealNum* operator[] (int i) const;//for const Matrix&
	Matrix& operator= (const Matrix& a);//default "=" which will use constructors will only be called when a new variable is defined (like Matrix A=B);but assignments will use operator= defined by yourself(default version is deleted)
	Matrix& operator+= (const Matrix& a);
	Matrix Transpose();//return transposed *this without causing changes to *this
	Matrix Ladder();//turn *this to row-echelon matrix(return the result without changing *this)
	Matrix MaxLIG();//return Maximum Linear Independence Group
	int Rank();//return rank of the matrix
	~Matrix();

	friend Matrix operator+ (const Matrix &a,const Matrix &b);
	friend Matrix operator- (const Matrix &a,const Matrix &b);
	friend Matrix operator* (const Matrix &a,const Matrix &b);
	friend std::istream& operator>> (std::istream& in, Matrix& dst);
	friend std::ostream& operator<< (std::ostream& out, const Matrix& src);
};

#endif 
