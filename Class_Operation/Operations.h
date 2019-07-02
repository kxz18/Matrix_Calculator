#ifndef OPERATIONS
#define OPERATIONS

#include"Variable.h"
#include<vector>

class operation{
protected:  
    int opPri;                      //priority
    int opNum;                      //number of objects
    std::string type;
    std::vector<Variable*> Varlist;  //Variable list of objects
    Variable* res;                  //result of the operation,this will not be deleted when operation is deleted,instead it will be assigned a name of "kjy" for recognition and put to "bye"
public:
    virtual void operate()=0;
    void addVar(Variable *a){
        Varlist.push_back(a);
    }
    int getPrior(){return opPri;}
    int getNum(){return opNum;}
    std::string getType(){return type;}
    Variable* getResult() const{return res;}
    bool priorCheck(operation* a){
        if(a==NULL)return true;
        else return this->opPri>=a->opPri;
    }
};

class setValOp:public operation{
public:
    setValOp(){
        opPri=-1;
        opNum=2;
        type="=";
    }
    void operate(){
        *Varlist[1]=*Varlist[0];       //remeber last in first out, so Varlist[0] should be the variable on the right of "="
        res=new Variable("kjy","");
        *res=*Varlist[0];               
    }
};

class printOp:public operation{
public:
    printOp(){
        opPri=-2;
        opNum=1;
        type="print";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"printOp->operate()"<<std::endl;
        #endif
        std::cout<<*Varlist[0]<<std::endl;
        res=new Variable("kjy","");
        *res=*Varlist[0];
    }
};


class addOp:public operation{
public:
    addOp(){
        opPri=1;
        opNum=2;
        type="+";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"addOp->operate()"<<std::endl;
            std::cout<<"adding "<<Varlist[1]->getName()<<" and "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType(),
                    type2=Varlist[1]->getType();
        if(type1=="R"&&type2=="R"){
            res=add<R>(*Varlist[0],*Varlist[1]);
        }else if(type2!="R"){
            if(type1=="matrix")res=add<Matrix>(*Varlist[0],*Varlist[1]);
            else if(type1=="square matrix")res=add<SquareMatrix>(*Varlist[0],*Varlist[1]);
            else if(type1=="quadratic form")res=add<QuadraticForm>(*Varlist[0],*Varlist[1]);
            else if(type1=="equations")res=add<LinSimEqua>(*Varlist[0],*Varlist[1]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class subOp:public operation{
    public:
    subOp(){
        opPri=1;
        opNum=2;
        type="-";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"subOp->operate()"<<std::endl;
            std::cout<<"subing "<<Varlist[1]->getName()<<" and "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[1]->getType(),
                    type2=Varlist[0]->getType();
        if(type1=="R"&&type2=="R"){
            res=sub<R>(*Varlist[1],*Varlist[0]);
        }else if(type2!="R"){
            if(type1=="matrix")res=sub<Matrix>(*Varlist[1],*Varlist[0]);
            else if(type1=="square matrix")res=sub<SquareMatrix>(*Varlist[1],*Varlist[0]);
            else if(type1=="quadratic form")res=sub<QuadraticForm>(*Varlist[1],*Varlist[0]);
            else if(type1=="equations")res=sub<LinSimEqua>(*Varlist[1],*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class mulOp:public operation{
    public:
    mulOp(){
        opPri=2;
        opNum=2;
        type="*";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"mulOp->operate()"<<std::endl;
            std::cout<<"multiplying "<<Varlist[1]->getName()<<" with "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[1]->getType(),
                    type2=Varlist[0]->getType();
        if(type1=="R"&&type2=="R"){
            res=mul<R>(*Varlist[1],*Varlist[0]);
        }else if(type2!="R"){
            if(type1=="matrix")res=mul<Matrix>(*Varlist[1],*Varlist[0]);
            else if(type1=="square matrix"){
                if(type2==type1)res=mul<SquareMatrix>(*Varlist[1],*Varlist[0]);
                else res=mul<Matrix>(*Varlist[1],*Varlist[0]);
            }else if(type1=="quadratic form")res=mul<QuadraticForm>(*Varlist[1],*Varlist[0]);
            else if(type1=="equations")res=mul<LinSimEqua>(*Varlist[1],*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class divOp:public operation{
    public:
    divOp(){
        opPri=2;
        opNum=2;
        type="/";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"divOp->operate()"<<std::endl;
            std::cout<<"dividing "<<Varlist[1]->getName()<<" with "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[1]->getType(),
                    type2=Varlist[0]->getType();
        if(type1=="R"&&type2=="R"){
            res=div(*Varlist[1],*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class powOp:public operation{
public:
    powOp(){
        opPri=3;
        opNum=2;
        type="^";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"powOp->operate()"<<std::endl;
            std::cout<<"powering "<<Varlist[1]->getName()<<" with "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[1]->getType(),
                    type2=Varlist[0]->getType();
        if(type1=="R"&&type2=="R"){
            res=power(*Varlist[1],*Varlist[0]);
        }else if((type1=="square matrix"||type1=="quadratic form")&&type2=="R"){
            res=matpow(*Varlist[1],*Varlist[0]);
        }else if(type2=="T"){
            res=transpose(*Varlist[1]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class lBracket: public operation{
public:
    lBracket(){
        opPri=0;
        opNum=0;
        type="(";
    }
    void operate(){};
};

class rBracket: public operation{
public:
    rBracket(){
        opPri=5;
        opNum=0;
        type=")";
    }
    void operate(){};
};

class detOp: public operation{
public:
    detOp(){
        opPri=4;
        opNum=1;
        type="det";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"detOp->operate()"<<std::endl;
            std::cout<<"calculating "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType();
        if(type1=="square matrix"||type1=="quadratic form"){
            res=det(*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class solOp: public operation{
public:
    solOp(){
        opPri=4;
        opNum=1;
        type="solve";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"solOp->operate()"<<std::endl;
            std::cout<<"solving "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType();
        if(type1=="equations"){
            res=solve(*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class rankOp: public operation{
public:
    rankOp(){
        opPri=4;
        opNum=1;
        type="rank";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"rankOp->operate()"<<std::endl;
            std::cout<<"calculating rank of "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType();
        if(type1=="equations"||type1=="matrix"||type1=="square matrix"||type1=="quadratic form"){
            res=rank(*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class QROp: public operation{
    char kind;
public:
    QROp(){
        opPri=4;
        opNum=1;
        type="QR";
        kind='e';
    }
    QROp(char c){
        opPri=4;
        opNum=1;
        type="QR";
        kind=c;
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"QROp->operate()"<<std::endl;
            std::cout<<"calculating QR decomposition of "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType();
        if(type1=="square matrix"||type1=="quadratic form"){
            res=QR(*Varlist[0],kind);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};

class analyseOp:public operation{
public:
    analyseOp(){
        opPri=4;
        opNum=1;
        type="analyse quadratic form";
    }
    void operate(){
        #ifdef DEBUG
            std::cout<<"analyseOp->operate()"<<std::endl;
            std::cout<<"analysing "<<Varlist[0]->getName()<<std::endl;
        #endif
        std::string type1=Varlist[0]->getType();
        if(type1=="quadratic form"){
            res=analyse(*Varlist[0]);
        }else{
            std::cout<<"incompatible types!"<<std::endl;
        }
    }
};
#endif