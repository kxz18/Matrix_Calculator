#ifndef VARIABLE
#define VARIABLE

#include"RealNum.h"
#include"Matrix.h"
#include"SquareMatrix.h"
#include"LinSimEqua.h"
#include"QuadraticForm.h"
#include<new>

typedef RealNum R;

class Variable{
    std::string name;                       //used only for operation "="
    std::string type;                           
    void* value;

    void clearVal(){
        if(value!=NULL){
            #ifdef DEBUG
                std::cout<<"storage cleared,this->value@"<<std::hex<<value<<std::endl;
            #endif 
            if(type=="R"){
                R* tempo=(R*)value;
                delete tempo;
            } else if(type=="matrix"){
                Matrix* tempo=(Matrix*)value;
                delete tempo;
            }else if(type=="square matrix"){
                SquareMatrix* tempo=(SquareMatrix*)value;
                delete tempo;
            }else if(type=="equations"){
                LinSimEqua* tempo=(LinSimEqua*)value;
                delete tempo;
            }else if(type=="quadratic form"){
                QuadraticForm* tempo=(QuadraticForm*)value;
                delete tempo;
            }   
        }
    }

    template<typename T>
    void setVal(T *a){
        this->clearVal();
        value=(void*)a;
    }

    template<typename T>
    T* setVal(){
        T* tmp=(T*)value;
       return tmp;
    }

    template<typename T>
    T showVal() const{
        //T* tempo=(T*)value;
        //return *tempo;
        return *(T*)value;
    }
public:
    Variable();
    Variable(std::string typ);
    Variable(std::string nam, std::string typ);
    Variable(R a);
    Variable(Matrix a);
    Variable(SquareMatrix a);
    Variable(LinSimEqua a);
    Variable(QuadraticForm a);
    Variable(const Variable& a);
    Variable(Variable&& a);
    Variable& operator= (const Variable& a);
    Variable& operator= (Variable&& a);
    void setName(std::string a);
    std::string getType();
    std::string getName() const;
    ~Variable();

    friend std::istream& operator>> (std::istream& in,Variable& dst);
    friend std::ostream& operator<< (std::ostream& out,const Variable& src);
    template<typename T>
    friend Variable* add(const Variable &a,const Variable &b);  //friend declaration is not a function declaration, that's why we need to declare it again out of the class defination
    template<typename T>
    friend Variable* sub(const Variable &a,const Variable &b);
    template<typename T>
    friend Variable* mul(const Variable &a,const Variable &b);
    friend Variable* div(const Variable &a,const Variable &b);
    friend Variable* power(const Variable &a,const Variable &b);  //sqrt is a special kind of pow
    friend Variable* matpow(const Variable &a,const Variable &b);
    friend Variable* transpose(const Variable &a);
    friend Variable* det(const Variable &a);
    friend Variable* solve(const Variable &a);
    friend Variable* rank(const Variable &a);
    friend Variable* QR(const Variable &a,char kind);
    friend Variable* analyse(const Variable &a);
};


template<typename T>
Variable* add(const Variable &a,const Variable &b){           //template functions must be defined where it is declared
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* add(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    T* tmp=new T(a.showVal<T>());
    *tmp=a.showVal<T>()+b.showVal<T>();
    res->value=(void*)tmp;
    #ifdef DEBUG
        std::cout<<"------ending Variable* add(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
    return res;
}

template<typename T>
Variable* sub(const Variable &a,const Variable &b){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* sub(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    T* tmp=new T(a.showVal<T>());
    *tmp=a.showVal<T>()-b.showVal<T>();
    res->value=(void*)tmp;
    #ifdef DEBUG
        std::cout<<"------ending Variable* sub(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
    return res;
}

template<typename T>
Variable* mul(const Variable &a,const Variable &b){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* mul(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    T* tmp=new T(a.showVal<T>());
    *tmp=a.showVal<T>()*b.showVal<T>();
    res->value=(void*)tmp;
    #ifdef DEBUG
        std::cout<<"------ending Variable* mul(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
    return res;
}

#endif

