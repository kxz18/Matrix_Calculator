#include"SquareMatrix.h"
using namespace std;
int main(){
    cout<<"input:\n";
    int order;
    cin>>order;
    SquareMatrix test(order);
    cin>>test;
    cout<<test.QR('q')<<endl;
    cout<<test.QR('r')<<endl;
    cout<<test.QR('q')*test.QR('r')<<endl;
    return 0;
}