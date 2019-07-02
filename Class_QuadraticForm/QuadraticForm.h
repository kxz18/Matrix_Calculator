#ifndef QUADRATICFORM
#define QUADRATICFORM
#include"SquareMatrix.h"

class QuadraticForm:public SquareMatrix{
    SquareMatrix Standard;              //standard form
    SquareMatrix SLinTran;              //linear transformation for standard form
    SquareMatrix Canonical;             //canonical form
    SquareMatrix CLinTran;              //linear transformation for canonical form
    std::string PosDef;

    bool isQua();
public:
    QuadraticForm(int a);
    void calculate();
    QuadraticForm& operator= (const Matrix& a);
    SquareMatrix getStd();
    SquareMatrix getStdLT();
    SquareMatrix getCnc();
    SquareMatrix getCncLT();
    std::string getPosDef();

    friend Matrix E1(int m,int n,int order);            //first kind of linear transformation
    friend Matrix E2(double l,int m,int n,int order);   //second kind of linear transfromation
    friend Matrix E3(double l,int m,int order);

    friend std::istream& operator>> (std::istream& in,QuadraticForm& dst);
};

#endif