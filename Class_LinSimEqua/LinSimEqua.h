#ifndef LINSIMEQUA
#define LINSIMEQUA

#include"Matrix.h"

class LinSimEqua:public Matrix{        //augmented matrix
    Matrix CoeMat;                     //coefficient matrix
    Matrix ResMat;                     //matrix of numbers on the right of equations
    int* judgegroup;                   //store if a column vector in CoeMat is independent

    void initialize();                 //initialize CoeMat,ResMat and judgegroup
public:
    LinSimEqua()=delete;
    LinSimEqua(const Matrix& a);
    LinSimEqua(int a, int b);
    int getEquaNum();                   //return number of equations 
    int getUnknowNum();                 //return number of unknowns
    bool homo();                        //judge if the equations are homogeneous
    std::string Judge();                //judge if the Linear Simultaneous equations have solutions
    Matrix getFunSol();                 //get fundamental solutions
    Matrix getSpeSol();                 //get one special solution
    Matrix getLSSol();                  //get least-square solution
    Matrix getOpLSSol();                //get optimal least-square solution
    void printSol();                    //print Solutions according to different situation
    LinSimEqua& operator= (const Matrix& a);

    friend std::istream& operator>> (std::istream& in,LinSimEqua& dst);
};

#endif