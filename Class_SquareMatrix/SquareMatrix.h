#ifndef SQUAREMATRIX
#define SQUAREMATRIX

#include"Matrix.h"

class SquareMatrix:public Matrix{
protected:   
    int order;
public:
    SquareMatrix(int a);
    SquareMatrix Uptri();            //return uptriangle matrix
    RealNum det();                   //get determinant
    SquareMatrix Inverse();          //return inverse matrix
    SquareMatrix QR(char c);         //QR(Q) or QR(q) will return Q and QR(R) or QR(r) will return R
    SquareMatrix& operator= (const Matrix& a);

    friend RealNum Pro(RealNum* a,RealNum* b,int dim);//inner product,dim is the dimension of vector
};

#endif