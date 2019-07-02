#include"LinSimEqua.h"
using namespace std;
int main(){
    int row,column;
    cout<<"input:"<<std::endl;
    cin>>row>>column;
    LinSimEqua test(row,column);
    test.printSol();
    return 0;
}