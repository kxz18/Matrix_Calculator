#include"Operations.h"
#include"Variable.h"
#include<string>
#include<sstream>
#include<map>
//#include<pair>
#include<stack>

std::map<std::string,Variable> Variables;
std::stack<operation*> Operations;
std::stack<Variable*> opVars;
std::vector<Variable*> bye;             //used to store temporary variables to be deleted(release storage) 

void lowercase(std::string &s){         //turn uppercase to lowercase
    for(char &a:s){
        if(a>='A'&&a<='Z') a+='a'-'A';
    }
}

bool checkName(std::string &s){            //only letters and numbers are available in variable name,# is the end signal
    bool flag=0;
    for(char a:s){
        if(!((a>=0&&a<=9)||(a>='A'&&a<='Z')||(a>='a'&&a<='z')||a=='#')){
            flag=1;
            break;
        }
    }
    return flag;
}

Variable& createVar(std::string type,std::string name){
    #ifdef DEBUG
        std::cout<<"\n------entering Variable& createVar(std::string type,std::string name)------"<<std::endl;
    #endif
    lowercase(type);
    if(checkName(name)){
        std::cout<<"Only English letters and numbers are available in variable name!"<<std::endl;
    }else if(name=="#"||name==""){
        std::cout<<"ERROR: You didn't enter the name of variable!"<<std::endl;
    }else if(Variables.count(name)!=0){
        if(type!="#")std::cout<<"Variable already existed. Operation failed"<<std::endl; //"#"to signal this is not a create cmd
    }else{
        for(auto &a:type){
            if(a=='('||a==')'||a==',')a=' ';
        }
        std::stringstream in(type);
        std::string tmp,first,second;in>>tmp;           //tmp is the type,first\second are optional parameter
        #ifdef DEBUG
            std::cout<<"type="<<type<<std::endl;
            std::cout<<"name="<<name<<std::endl;
            std::cout<<"tmp="<<tmp<<std::endl; 
        #endif
        if(tmp=="r"){                                   //I don't know why , but Variables[name]=Variable(R(0)) is forbidden;update:that's because I didn't define move assignment function, map[name] will first call default constructor to build an object, then use assignment operator= to change it
            Variables[name]=Variable(R(0));
        }
        else if(tmp=="matrix"){
            in>>first>>second;
            if(first!=second)Variables[name]=Variable(Matrix(stoi(first),stoi(second)));
            else Variables[name]=Variable(SquareMatrix(stoi(first)));
        }else if(tmp=="square"){
            in>>first>>second;
            Variables[name]=Variable(SquareMatrix(stoi(second)));
        }else if(tmp=="equations"){
            in>>first>>second;
            Variables[name]=Variable(LinSimEqua(stoi(first),stoi(second)));
        }else if(tmp=="quadratic"){
            in>>first>>second;
            Variables[name]=Variable(QuadraticForm(stoi(second)));
        }
        Variables[name].setName(name);
        std::cout<<"Please enter the value:"<<std::endl;
        std::cin>>Variables[name];
        std::cin.ignore();                                              //after cin there will be an "enter" left in cin, leading to another analyse()
        std::cout<<"Successfully created"<<std::endl;
        #ifdef DEBUG
            std::cout<<"Variables["<<name<<"]="<<std::endl;
            std::cout<<Variables[name]<<std::endl;
        #endif
    }
    #ifdef DEBUG
        std::cout<<"------ending Variable& createVar(std::string type,std::string name)------\n"<<std::endl;
    #endif
    return Variables[name];
}

void addVar(Variable* a){                               //it's not good to use & on vector, which will cause unknown data loss(I've been through it).At last it turns out to be deleted somewhere I don't know
    opVars.push(a);
}

void addOperation(operation *a){                        //execute operations whose priority is greater than current one
    #ifdef DEBUG
        std::cout<<"\n------entering void addOperation(operation *a)------"<<std::endl;
        if(a!=NULL)std::cout<<"Here operation type="<<a->getType()<<std::endl;
        else std::cout<<"Here operation type=NULL"<<std::endl;
    #endif
    while(Operations.size()!=0&&(Operations.top()->priorCheck(a)||a==NULL)){
    #ifdef DEBUG
        if(a!=NULL)std::cout<<"Enter loop@operation type="<<a->getType()<<std::endl;
        else std::cout<<"Enter loop@operation type=NULL"<<std::endl;
    #endif
        if(a!=NULL&&a->getType()=="("){
            #ifdef DEBUG
                std::cout<<"break"<<std::endl;
            #endif
            break;
        }
        operation *ifbra=NULL;                          //for brackets
        if(Operations.top()->getType()==")"){
            ifbra=Operations.top();
            Operations.pop();
            if(Operations.top()->getType()=="("){
                delete ifbra;
                ifbra=Operations.top();
                Operations.pop();
                delete ifbra;
                ifbra=NULL;
                if(a!=NULL){
                    #ifdef DEBUG
                        std::cout<<"goto end"<<std::endl;
                    #endif
                    continue;
                }                       //break to prevent once more operating, a!=NULL to prevent break at the wrong time,but can't just break as the loop should go on
            }
        }
        #ifdef DEBUG
            std::cout<<"processing"<<std::endl;
        #endif
      
        operation *lastOp=Operations.top();
        for(int i=0;i<lastOp->getNum();i++){            //put variables of operation into varlist
            lastOp->addVar(opVars.top());
            if(opVars.top()->getName()=="kjy") bye.push_back(opVars.top());
            opVars.pop();
        }
        lastOp->operate();
        Variable *res=lastOp->getResult();
        opVars.push(res);
        delete lastOp;                                   //release storage
        Operations.pop();
        if(ifbra!=NULL)Operations.push(ifbra);
    }
    Operations.push(a);
    #ifdef DEBUG
        std::cout<<"------ending void addOperation(operation *a)------\n"<<std::endl;
    #endif
}

void analyse(std::string s){
    #ifdef DEBUG
        std::cout<<"\n------entering void analyse(std::string s)------"<<std::endl;
    #endif
    std::stringstream in(s);
    std::string command,type,name;
    in>>command;lowercase(command);
    if(command=="create"){     //create operation is special
        in>>type;in>>name;lowercase(type);
        if(type=="square"||type=="quadratic"){
            type.append(" "+name);
            in>>name;
        }
        createVar(type,name);
    }else if(command=="delete"){
        in>>name;
        if(Variables.find(name)==Variables.end()){
            std::cout<<"Variable named "<<name<<" not found"<<std::endl;
        }
        else{
            Variables.erase(name);
            std::cout<<"Variable "<<name<<" deleted"<<std::endl;
        }
    }else if(command=="use"){               //use digital mode or fraction mode
        in>>type;
        if(type=="decimal"){
            #define DECIMAL
        }else if(type=="fraction"){
            #undef DIGITAL
        }
    }else if(command=="help"){
        std::cout<<"Please read \"readme.pdf\""<<std::endl;
    }else{
        std::string Varname="";     //name of variables
        std::string Varval="";      //value of variables
        for(int i=0;i<s.size();i++){
            if(s[i]=='+'){
                operation* op=new addOp;
                addOperation(op);
            }else if(s[i]=='-'){
                if(s[i-1]=='('||s[i-1]==' '){                            //in case this is a negative number instead of an operation
                    Variable* tmp=new Variable("kjy","R");
                    *tmp=R(0);
                    opVars.push(tmp);
                }
                operation* op=new subOp;
                addOperation(op);
            }else if(s[i]=='*'){
                operation* op=new mulOp;
                addOperation(op);
            }else if(s[i]=='/'){
                operation* op=new divOp;
                addOperation(op);
            }else if(s[i]=='^'){
                operation* op=new powOp;
                addOperation(op);
            }else if(s[i]=='='){
                operation* op=new setValOp;
                addOperation(op);
            }else if(s[i]=='('){
                operation* op=new lBracket;
                addOperation(op);
            }else if(s[i]==')'){
                operation* op=new rBracket;
                addOperation(op);
            }else if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')){//name of variable or English named operation
                Varname+=s[i];
                if(!((s[i+1]>='a'&&s[i+1]<='z')||(s[i+1]>='A'&&s[i+1]<='Z'))){
                    if(Varname=="print"){
                        operation* op=new printOp;
                        addOperation(op);
                    }else if(Varname=="det"){
                        operation* op=new detOp;
                        addOperation(op);
                    }else if(Varname=="solve"){
                        operation* op=new solOp;
                        addOperation(op);
                    }else if(Varname=="rank"){
                        operation* op=new rankOp;
                        addOperation(op);
                    }else if(Varname=="QR"){
                        operation* op=new QROp;
                        addOperation(op);
                    }else if(Varname=="QRq"){
                        operation* op=new QROp('q');
                        addOperation(op);
                    }else if(Varname=="QRr"){
                        operation* op=new QROp('r');
                        addOperation(op);
                    }else if(Varname=="analyse"){
                        operation* op=new analyseOp;
                        addOperation(op);
                    }else if(Varname=="T"){
                        Variable* tmp=new Variable("tmp","T");
                        opVars.push(tmp);
                    }else{                                                          //else it is the name of a variable
                        if(Variables.find(Varname)==Variables.end()){
                            std::cout<<"Variable "<<Varname<<" not found!"<<std::endl;
                            break;
                        }
                        addVar(&(Variables[Varname]));
                    }
                    Varname="";
                }
            }else if((s[i]>='0'&&s[i]<='9')||s[i]=='.'){
                Varval+=s[i];
                if(!((s[i+1]>='0'&&s[i+1]<='9')||s[i+1]=='.')){
                    Variable* tmp=new Variable(R(stod(Varval)));
                    opVars.push(tmp);
                    Varval="";
                }
            }else if(s[i]=='#'){
                addOperation(NULL);
            }
        }
    }
    #ifdef DEBUG
        std::cout<<"------ending void analyse(std::string s)------\n"<<std::endl;
    #endif
}

int main(){
    std::string expression;
    while(getline(std::cin,expression)){
        if(expression=="exit"||expression=="quit")break;
        expression.append(" #");
        analyse(expression);
        #ifdef DEBUG
            std::cout<<"Before clearing"<<std::endl;
            std::cout<<"Operations is empty: "<<std::boolalpha<<Operations.empty()
                     <<"\nSize of it is: "<<Operations.size()<<std::endl;
            std::cout<<"opVars is empty: "<<std::boolalpha<<opVars.empty()
                     <<"\nSize of it is: "<<opVars.size()<<std::endl;
        #endif
        while(!Operations.empty()) Operations.pop();                        //drop left NULL
        while(!opVars.empty()){
            if(opVars.top()->getName()=="kjy") bye.push_back(opVars.top());
            opVars.pop();
        }
        #ifdef DEBUG
            std::cout<<bye.size()<<" Variables in bye to be released"<<std::endl;
        #endif
        for(auto a:bye) delete a;
        bye.clear();
    }
    std::cout<<"bye~"<<std::endl;
    return 0;
}