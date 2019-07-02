#include"QuadraticForm.h"


Matrix E1(int m,int n,int order){
    SquareMatrix x(order);
    x[m][m]=0,x[n][n]=0;
    x[m][n]=1,x[n][m]=1;
    return x;
} 

Matrix E2(double l,int m,int n,int order){
    SquareMatrix x(order);
    x[n][m]=l;
    return x;
} 

Matrix E3(double l,int m,int order){
    SquareMatrix x(order);
    x[m][m]=l;
    return x;
} 

bool QuadraticForm::isQua(){
	bool flag=0;
    for(int i=0;i<order&&flag==0;i++){
        for(int j=i;j<order&&flag==0;j++){
            if(this->matrix[i][j]!=this->matrix[j][i])flag=1;
        }
    }
	return flag;
}

void QuadraticForm::calculate(){
	#ifdef DEBUG
		std::cout<<"calculating quadratic form"<<std::endl;
	#endif
    if(this->isQua())std::cout<<"Warning: Not a Quadratic Form!"<<std::endl;
    else{
        SquareMatrix b(order),PT(order);
		SquareMatrix a=*this;
        int next=1;
		for(int j=0;j<column;j++){
			next=1; 
			for(int i=j+1;i<row&&next==1;i++){
				if(a[j][j]!=0)next=0;
				if(a[j][j]==0&&a[i][j]!=0){
					b=E2(1,i,j,order);		//此处不能用换行法是因为二次型的特点，换行法会将对角元素互换，而非上下位互换 
					a=b*a*b.Transpose();
                    PT=b*PT;
					next=0;
				}
			}
				for(int i=j+1;i<row&&a[j][j]!=0;i++){
					double l=-a[i][j]/a[j][j];
					b=E2(l,j,i,order);              //初始化b为I，再生成令第j行乘l再加至第i行的初等矩阵并存到b中 
					a=b*a*b.Transpose();
                    PT=b*PT;
				}
			}
			Standard=a;
			SLinTran=PT.Transpose();                //转置一下PT（因为之前过程用的是横向分块矩阵，求出的应该是变换矩阵的转置）
			for(int i=0;i<row;i++){
				for(int j=i+1;j<column&&a[i][i]<=0;j++){
					switch(a[j][j]>0){ 
						case 1:b=E1(i,j,order);
							   a=b*a*b;             //no need to transpose as E1 matrix is symetrical
                               PT=b*PT;
							   break;
						default:break;
					} 
				}
			}//把正数排到最前面 
            SquareMatrix len(order);
			double abs=0;
			int plus=0,sub=0; 
			for(int i=0;i<row;i++){
				for(int j=i+1;j<column&&a[i][i]==0;j++){
					switch(a[j][j]<0){ 
						case 1:b=E1(i,j,order);
							   a=b*a*b;
                               PT=b*PT;
							   break;
						default:break;
					} 
				}
				abs=a[i][i];
				if(a[i][i]<0){
					abs=-abs;
					sub++;
				}else if(a[i][i]>0){
					plus++;
				}
				if(abs>0){
					a[i][i]/=abs;
                    len[i][i]=sqrt(abs);
				}
			}//把负数排到0前面,并转化为规范型,途中顺带统计1与-1的个数 
			Canonical=a;
			PT=len*PT;                      //multiply coeficient of normalizing canonical form
			CLinTran=PT.Transpose();
			if(plus==row)PosDef="Positive-definite";
			else if(sub==row)PosDef="Negative-definite";
			else if(plus>0&&sub==0)PosDef="Positive-semidefinite";
			else if(plus==0&&sub>0)PosDef="Negative-semidefinite";
			else if(plus>0&&sub>0)PosDef="Indefinite";
			else PosDef="Null Matrix";
    }
}

QuadraticForm::QuadraticForm(int a):SquareMatrix(a),Standard(a),
	SLinTran(a),Canonical(a),CLinTran(a),PosDef(""){}

QuadraticForm& QuadraticForm::operator= (const Matrix& a){
	QuadraticForm tmp(a.getRow());
	for(int i=0;i<order;i++){
		for(int j=0;j<order;i++){
			tmp[i][j]=a[i][j];
		}
	}
	if(!(tmp.isQua()))std::cout<<"Not a quadratic form!"<<std::endl;
	else *this=std::move(tmp),this->calculate();
	return *this;
}

SquareMatrix QuadraticForm::getStd(){
	return Standard;
}

SquareMatrix QuadraticForm::getStdLT(){
	return SLinTran;
}

SquareMatrix QuadraticForm::getCnc(){
	return Canonical;
}

SquareMatrix QuadraticForm::getCncLT(){
	return CLinTran;
}

std::string QuadraticForm::getPosDef(){
	return PosDef;
}

std::istream& operator>> (std::istream& in,QuadraticForm& dst){
	for(int i=0;i<dst.row;i++){
		for(int j=0;j<dst.column;j++){
			in>>dst.matrix[i][j];
		}
	}
	if(dst.isQua())
	dst.calculate();
	return in;
}