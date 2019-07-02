#include"QuadraticForm.h"

int main(){
    QuadraticForm a(2);
    std::cin>>a;
    std::cout<<a.getStd()<<a.getStdLT()<<a.getCnc()<<a.getCncLT()<<a.getPosDef();
    return 0;
}