#include"RealNum.h"

std::string RealNum::trim(std::string& s){
	for(int i=0;i<s.length();i++){
		if(s[i]=='('||s[i]==')'||s[i]==' '){
			s.erase(i,1);
			i--;
		}else break;
	}
	for(int i=s.length()-1;i>0;i--){
		if(s[i]=='('||s[i]==')'||s[i]==' '){
			s.erase(i,1);
			i++;
		}else break;
	}
	return s;
}

bool RealNum::IsInt(double a){
	double delta=0;
	if(a<0)a=-a;							//turn negative figures to positive figures as static_cast<int> adopts a different method to turn negative figures(e.g -1.6->-1)
	if(a>0)delta=a-static_cast<int>(a+1e-5);//avoid .99999999 (slight deviation for binary storage)
	if(delta<1e-10&&delta>-1e-10)return true;
	else return false;
}

double RealNum::Rational(std::string s){
	if(!(s.find("/")==std::string::npos)){
		double numerator=0, denominator=0;
		int pos=s.find("/");
		numerator=std::stod(s.substr(0,pos));pos++;
		denominator=std::stod(s.substr(pos,s.length()-pos));
		return numerator/denominator;
	}else if(!(s.find("^")==std::string::npos)){
		double base=0,exp=0;
		int pos=s.find("^");
		base=std::stod(s.substr(0,pos));pos++;
		exp=std::stod(s.substr(pos,s.length()-pos));
		return pow(base,exp);
	}else{
		return std::stod(s);
	}
}

std::string RealNum::Rational(double a){
	int k=1;
	double numerator=a;	
	for(k=1;;k++){
		numerator=a*k;
		if(IsInt(numerator)==true)break;
		if(k>=1e5){
			return "Failed";
		}
	}
	int NumRevise=0;
	if(numerator>=0)NumRevise=static_cast<int>(numerator+1e-5);
	else NumRevise=static_cast<int>(numerator-1e-5);
	if(k==1)return std::to_string(NumRevise);
	return std::to_string(NumRevise)+"/"+std::to_string(k);
}

std::string RealNum::PureIrr(double a){
	double inner=a; int k=1;
	std::string Rtnl;
	for(k=1;;k++){
		inner=pow(a,k);
		Rtnl=Rational(inner);
		if(Rtnl!="Failed")break;
		if(k>=2e2)return "Failed";
	}																//find denominator of the exponent
	int numerator=0,denominator=0;
	if(!(Rtnl.find("/")==std::string::npos)){
		int pos=Rtnl.find("/");
		numerator=std::stoi(Rtnl.substr(0,pos));
		pos++;
		denominator=std::stoi(Rtnl.substr(pos,Rtnl.length()-pos));
		numerator*=pow(denominator,k-1);
	}else{
		numerator=std::stoi(Rtnl);
	}
	for(int i=static_cast<int>(pow(numerator,1.0/k));i>0;i--){
		inner=numerator/pow(i,k);
		if(IsInt(inner)==true){
			numerator=i;
			break;
		}
	}
	int j;
	for(j=k-1;j>0;j--){
		if(IsInt(pow(inner,1.0/j))==true){
			inner=pow(inner,1.0/j);
			break;
		}
	}
	std::string RPart="",IrrPart="";
	if(denominator==0)RPart=std::to_string(numerator);
	else RPart=Rational(static_cast<double>(numerator)/denominator);
	if(RPart=="1"){
		RPart="";
		IrrPart=std::to_string(static_cast<int>(inner+1e-5))
				+"^"+"("+std::to_string(j)+"/"+std::to_string(k)+")";
	}else IrrPart="("+std::to_string(static_cast<int>(inner+1e-5))
			+"^"+"("+std::to_string(j)+"/"+std::to_string(k)+"))";
	if(!(RPart.find("/")==std::string::npos)){
		RPart="("+RPart+")";
	}
	if(a<0)RPart="-"+RPart;
	return RPart+IrrPart;
}

std::string RealNum::DToS(double a){
	std::string result=Rational(a);
	if(result!="Failed")return result;
	else{
		result=PureIrr(a);
		if(result!="Failed")return result;
	}
	return std::to_string(a);
} 

double RealNum::SToD(std::string s){
	if(s.find("(")==std::string::npos){
		return Rational(s);
	}else{
		std::string exp="1",base="1",coe="1";		//if left-half bracket is found, there must be an exponent
		int PosEx=s.find_last_of("^");				//there might be exponent in the base
		exp=s.substr(PosEx+1,s.length()-PosEx-1);
		s.erase(PosEx,exp.length()+1);
		trim(exp);									//get the exponent and delete the part from s
		int pos=s.find("(",1);
		for(int i=1;pos!=-1&&pos!=0&&s[pos-1]!=')';i++){
			pos=s.find("(",pos-i);
		}
		int	width=s.length()-pos-1;
		if(pos==-1)base=s,trim(base);				//no left-half bracket means no coefficient
		else{
			base=s.substr(pos+1,width);
			if(!(base.find("^")==std::string::npos))base=std::to_string(SToD(base));//iteration in case base is an exponent
			else base=std::to_string(Rational(base));
			trim(base);
			s.erase(pos+1,width);
			trim(s);
			if(s.length()!=0){coe=s;}
		}
		return Rational(coe)*pow(stod(base),Rational(exp));
	}
}

RealNum::RealNum():num(0),expression("0"){}

RealNum::RealNum(double a):num(a),expression(DToS(a)){}

RealNum::RealNum(std::string s):num(SToD(s)),expression(DToS(num)){}

RealNum::operator double() const{return num;}

RealNum& operator+= (RealNum &a,const double &b){
	a=a+b;
	return a;								//As a+b will give a double, RealNum(a+b) is necessary
}													//this function is still beta

RealNum& operator-= (RealNum &a,const double &b){
	a=a-b;
	return a;
}

RealNum& operator*= (RealNum &a,const double &b){
	a=a*b;
	return a;
}

RealNum& operator/= (RealNum &a,const double &b){
	a=a/b;
	return a;
}

std::ostream& operator<< (std::ostream& out,const RealNum& src){
	#ifdef DECIMAL
		std::cout<<"num="<<src.num<<std::endl;
		out<<src.num;
	#else
		out<<src.expression;
	#endif
	return out;
}

std::istream& operator>> (std::istream& in,RealNum& dst){
	in >> dst.expression;
	dst.num = dst.SToD(dst.expression);
	if(!(dst.expression.find(".")==std::string::npos)){
		int pos=dst.expression.find(".");
		if(pos!=-1&&(dst.expression.length()-pos-1<5)){
			dst.expression = dst.DToS(dst.num);//numbers with >=5 decimal places don't deserve format revising
		}
	}else{
		dst.expression = dst.DToS(dst.num);
	}
	return in;
}

RealNum::~RealNum(){}
