#include<iostream>
#include"Matrix.h"
using namespace std;

int main(){
    int row,column;
    cin>>row>>column;
    Matrix A(row,column);
    cin>>A;
    //Matrix B=A.MaxLIG();
    //cout<<B;
    Matrix B(1,1);
    B=A;
    cout<<"Ladder=\n"<<A.Ladder()<<endl;
    cout<<"MaxLIG=\n"<<A.MaxLIG()<<endl;
    cout<<"Rank="<<A.Rank();
    A+=A.Ladder();
    cout<<A;
    return 0;
}