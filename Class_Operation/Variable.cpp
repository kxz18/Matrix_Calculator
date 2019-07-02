#include"Variable.h"

Variable::Variable():name("tmp"),type(""),value(NULL){
    #ifdef DEBUG
        std::cout<<"Variable::Variable() called"<<std::endl;
    #endif
}

Variable::Variable(std::string typ):name(""),type(typ),value(NULL){}

Variable::Variable(std::string nam, std::string typ):
name(nam),type(typ),value(NULL){}

//use different types to initialize
Variable::Variable(R a):type("R"){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(R a) called"<<std::endl;
    #endif
    R* tmp=new R(a);
    value=(void*)tmp;
}

Variable::Variable(Matrix a):type("matrix"){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(Matrix a) called"<<std::endl;
    #endif
    Matrix* tmp=new Matrix(a);
    value=(void*)tmp;
}

Variable::Variable(SquareMatrix a):type("square matrix"){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(SquareMatrix a) called"<<std::endl;
    #endif
    SquareMatrix* tmp=new SquareMatrix(a);
    value=(void*)tmp;
}

Variable::Variable(LinSimEqua a):type("equations"){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(LinSimEqua a) called"<<std::endl;
    #endif
    LinSimEqua* tmp=new LinSimEqua(a);
    value=(void*)tmp;
}

Variable::Variable(QuadraticForm a):type("quadratic form"){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(QuadraticForm a) called"<<std::endl;
    #endif
    QuadraticForm* tmp=new QuadraticForm(a);
    value=(void*)tmp;
}

//copy constructors and move constructors
Variable::Variable(const Variable& a){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(const Variable& a) called"<<std::endl;
    #endif
    this->type=a.type;
    this->clearVal();
    if(type=="R"){
        R* tempo=new R(a.showVal<R>());
        this->value=tempo;
    } else if(type=="matrix"){
        Matrix* tempo=new Matrix(a.showVal<Matrix>());
        this->value=tempo;
    }else if(type=="square matrix"){
        SquareMatrix* tempo=new SquareMatrix(a.showVal<SquareMatrix>());
        this->value=tempo;
    }else if(type=="equations"){
        LinSimEqua* tempo=new LinSimEqua(a.showVal<LinSimEqua>());
        this->value=tempo;
    }else if(type=="quadratic form"){
        QuadraticForm* tempo=new QuadraticForm(a.showVal<QuadraticForm>());
        this->value=tempo;
    }       
}

Variable::Variable(Variable&& a){
    #ifdef DEBUG
        std::cout<<"Variable::Variable(Variable&& a) called"<<std::endl;
    #endif
    this->name=std::move(a.name);
    this->type=std::move(a.type);
    this->value=a.value;
    a.value=NULL;
}

//copy assignment and move assignment
Variable& Variable::operator= (const Variable& a){
    #ifdef DEBUG
        std::cout<<"Variable::operator= (const Variable& a) called"<<std::endl;
    #endif
    this->type=a.type;
    this->clearVal();
    if(type=="R"){
        R* tempo=new R(a.showVal<R>());
        this->value=tempo;
    } else if(type=="matrix"){
        Matrix* tempo=new Matrix(a.showVal<Matrix>());
        this->value=tempo;
    }else if(type=="square matrix"){
        SquareMatrix* tempo=new SquareMatrix(a.showVal<SquareMatrix>());
        this->value=tempo;
    }else if(type=="equations"){
        LinSimEqua* tempo=new LinSimEqua(a.showVal<LinSimEqua>());
        this->value=tempo;
    }else if(type=="quadratic form"){
        QuadraticForm* tempo=new QuadraticForm(a.showVal<QuadraticForm>());
        this->value=tempo;
    }       
    return *this;
}

Variable& Variable::operator = (Variable&& a) {
    #ifdef DEBUG
        std::cout<<"Variable::operator= (Variable&& a) called"<<std::endl;
    #endif
    this->name=std::move(a.name);
    this->type=std::move(a.type);
    this->value=a.value;
    a.value=NULL;
	return *this;
}

void Variable::setName(std::string a){
    this->name=a;
}

std::string Variable::getType(){
    return type;
}

std::string Variable::getName() const{
    return name;
}

Variable::~Variable(){
    #ifdef DEBUG
        std::cout<<"Variable::~Variable() called"<<std::endl;
    #endif
    this->clearVal();
}

std::istream& operator>> (std::istream& in,Variable& dst){
    if(dst.type=="R"){
        R* tmp=new R(0);
        in>>*tmp;
        dst.setVal<R>(tmp);
    }
    else if(dst.type=="matrix")in>>*(dst.setVal<Matrix>());
    else if(dst.type=="square matrix")in>>*(dst.setVal<SquareMatrix>());
    else if(dst.type=="equations")in>>*(dst.setVal<LinSimEqua>());
    else if(dst.type=="quadratic form")in>>*(dst.setVal<QuadraticForm>());
    return in;
}

std::ostream& operator<< (std::ostream& out,const Variable& src){
    if(src.type=="R")out<<src.showVal<R>();
    else if(src.type=="matrix")out<<src.showVal<Matrix>();
    else if(src.type=="square matrix")out<<src.showVal<SquareMatrix>();
    else if(src.type=="equations")out<<src.showVal<LinSimEqua>();
    else if(src.type=="quadratic form")out<<src.showVal<QuadraticForm>();
    return out;
}

Variable* div(const Variable &a,const Variable &b){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* div(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    if(a.type!="R"||b.type!="R"){
        std::cout<<"Incompatible types!"<<std::endl;
    }else{
        R* tmp=new R(a.showVal<R>());
        *tmp=a.showVal<R>()/b.showVal<R>();
        res->value=(void*)tmp;
    }
    #ifdef DEBUG
        std::cout<<"------ending Variable* div(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
    return res;
}

Variable* power(const Variable &a,const Variable &b){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* power(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    if(a.type=="R"&&b.type=="R"){
        R tmp1=pow(a.showVal<R>(),b.showVal<R>());
        *res=tmp1;
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* power(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
}
Variable* matpow(const Variable &a,const Variable &b){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* matpow(const Variable &a,const Variable &b)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    double expo=b.showVal<R>();
    if(b.showVal<R>().IsInt(expo)){
        if(expo==-1){
            *res=a.showVal<SquareMatrix>().Inverse();
        }else if(expo!=-1&&expo<0){
            std::cout<<"Invalid exponent!"<<std::endl;
            SquareMatrix tmp(1);
            *res=tmp;
        }else{
            SquareMatrix tmp=a.showVal<SquareMatrix>();
            for(int i=0;i<expo;i++){
                tmp=tmp*tmp;
            }
            *res=static_cast<SquareMatrix>(tmp);
        }
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* matpow(const Variable &a,const Variable &b)------\n"<<std::endl;
    #endif
}

Variable* transpose(const Variable &a){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* transpose(const Variable &a)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy",a.type);
    if(a.type=="matrix"||a.type=="square matrix"){
        Matrix tmp=a.showVal<Matrix>().Transpose();
        *res=tmp;
    }else if(a.type=="quadratic form"){
        QuadraticForm tmp=a.showVal<QuadraticForm>();
        *res =tmp;
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* transpose(const Variable &a)------\n"<<std::endl;
    #endif
}

Variable* det(const Variable &a){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* det(const Variable &a)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy","R");
    if(a.type=="quadratic form"||a.type=="square matrix"){
        R tmp=a.showVal<SquareMatrix>().det();
        *res=tmp;
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* det(const Variable &a)------\n"<<std::endl;
    #endif
}

Variable* solve(const Variable &a){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* solve(const Variable &a)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy","equations");
    if(a.type=="equations"){
        LinSimEqua tmp=a.showVal<LinSimEqua>();
        tmp.printSol();
        *res=tmp;
    }else{
        *res=a;
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* solve(const Variable &a)------\n"<<std::endl;
    #endif
}

Variable* rank(const Variable &a){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* rank(const Variable &a)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy","R");
    if(a.type=="equations"||a.type=="matrix"||a.type=="square matrix"||a.type=="quadratic form"){
        R tmp=a.showVal<Matrix>().Rank();
        *res=tmp;
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* rank(const Variable &a)------\n"<<std::endl;
    #endif
}

Variable* QR(const Variable &a,char kind){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* QR(const Variable &a,char kind)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy","square matrix");
    if(a.type=="square matrix"||a.type=="quadratic form"){
        if(a.showVal<SquareMatrix>().det()!=0){
            if(kind=='q'){
                SquareMatrix tmp=a.showVal<SquareMatrix>().QR('q');
                *res=tmp;
            }else if(kind=='r'){
                SquareMatrix tmp=a.showVal<SquareMatrix>().QR('r');
                *res=tmp;
            }else{
                std::cout<<a.getName()<<"=QR"<<std::endl;
                std::cout<<"Q=\n"<<a.showVal<SquareMatrix>().QR('q');
                std::cout<<"R=\n"<<a.showVal<SquareMatrix>().QR('r');
                *res=a;
            }
        }else{
            std::cout<<"ERROR: det("<<a.getName()<<")=0! Can't be QR decomposed!"<<std::endl;
        }
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* QR(const Variable &a,char kind)------\n"<<std::endl;
    #endif
}

Variable* analyse(const Variable &a){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable* analyse(const Variable &a)------"<<std::endl;
    #endif
    Variable* res=new Variable("kjy","quadratic form");
    *res=a;
    if(a.type=="quadratic form"){
        QuadraticForm tmp=a.showVal<QuadraticForm>();tmp.calculate();
        std::cout<<"The standard form is\n"<<tmp.getStd()<<std::endl;
        std::cout<<"Corresponding transform matrix is\n"<<tmp.getStdLT()<<std::endl;
        std::cout<<"The canonical form is\n"<<tmp.getCnc()<<std::endl;
        std::cout<<"Corresponding transform matrix is\n"<<tmp.getCncLT()<<std::endl;
        std::cout<<"This quadratic form is "<<tmp.getPosDef()<<std::endl;
    }else{
        std::cout<<"incompatible types!"<<std::endl;
    }
    return res;
    #ifdef DEBUG
        std::cout<<"------ending Variable* analyse(const Variable &a)------\n"<<std::endl;
    #endif
}