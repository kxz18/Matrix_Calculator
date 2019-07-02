#include"SquareMatrix.h"

RealNum Pro(RealNum* a,RealNum* b,int dim){
	RealNum pro=0;
	for(int i=0;i<dim;i++){
		pro+=a[i]*b[i];
	}
	return pro;
}

SquareMatrix::SquareMatrix(int a):Matrix(a),order(a){}

SquareMatrix SquareMatrix::Uptri(){
    int next=1,cnt=0;                       //cnt is running times of rowswap
	RealNum first=0;
    SquareMatrix a=*this;
	for(int j=0;j<column;j++){
		next=1;
		for(int i=j;i<row&&next==1;i++){
			if(a[i][j]!=0){
				a.RowSwap(i,j);
				if(i!=j)cnt++;
				next=0;
			}
		}
		for(int i=j+1;i<row&&a[j][j]!=0;i++){
			first=a[i][j];
			for(int k=j;k<column;k++){
				a[i][k]=a[i][k]-first/a[j][j]*a[j][k];
			}
		}		
	}
    return a;
}

RealNum SquareMatrix::det(){
    Matrix a=this->Uptri();
    RealNum det=1;
    for(int i=0;i<row;i++){
        det*=a[i][i];
    }
    return det;
}

SquareMatrix SquareMatrix::Inverse(){
	SquareMatrix b(order);							//initialize to I
	if(this->det()==0){
		std::cout<<"Cannot be inversed!"<<std::endl;
		return b;
	}
	SquareMatrix a=*this;
	int next=1;
	RealNum first=0;
	for(int j=0;j<column;j++){
		for(int i=j;i<row&&next==1;i++){
			if(a[i][j]!=0){
				a.RowSwap(i,j);
				b.RowSwap(i,j);
				next=0;
			}
		}
		for(int i=j+1;i<row&&a[j][j]!=0;i++){
			first=a[i][j];
			for(int k=0;k<column;k++){					//k start from 0 as elements below diagonal line of column1~j are not 0 in b, which is different from that in Upri()
				a[i][k]=a[i][k]-first/a[j][j]*a[j][k];
				b[i][k]=b[i][k]-first/a[j][j]*b[j][k];
			}
		}		
	}
	for(int j=column-1;j>=0;j--){
		for(int i=j-1;i>=0;i--){
			first=a[i][j];
			a[i][j]=0;
			for(int k=column-1;k>=0;k--){
				b[i][k]=b[i][k]-first/a[j][j]*b[j][k];
			}
		}
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			b[i][j]/=a[i][i];
		}
	}
	return b;
}

SquareMatrix SquareMatrix::QR(char c){
	RealNum pro1=0,pro2=0;
	SquareMatrix Q(order),R(order);
	for(int j=0;j<column;j++){
		int cnt=0;
		for(int i=0;i<row;i++){
			Q[i][j]=this->matrix[i][j];
			for(int k=0;k<j;k++){
				pro1=Pro((this->Transpose())[j],Q.Transpose()[k],order);
				pro2=Pro((Q.Transpose())[k],(Q.Transpose())[k],order);
				Q[i][j]-=pro1/pro2*Q[i][k];
				if(cnt<j){
					R[k][j]=pro1/pro2;
					cnt++;
				}
			}	
		}	
	}
	SquareMatrix coe1(order),coe2(order);//存放令Q单位化以及对R修正的矩阵（两者互逆，对角元互为倒数） 
	for(int i=0;i<row;i++){
		pro1=Pro((Q.Transpose())[i],(Q.Transpose())[i],order);
		coe1[i][i]=sqrt((double)pro1); 
		coe2[i][i]=1/sqrt((double)pro1);
	}
	R=coe1*R;
	Q=Q*coe2;
	if(c=='Q'||c=='q')return Q;
	else if(c=='R'||c=='r')return R;
	else return *this;
}

SquareMatrix& SquareMatrix::operator= (const Matrix& a){
	if(a.getRow()!=a.getColumn()){
		std::cout<<"Not a square matrix!"<<std::endl;
	}else{
		this->order=a.getRow();
		for(int i=0;i<order;i++){
			for(int j=0;j<order;j++){
				this->matrix[i][j]=a[i][j];
			}
		}
	}
	return *this;
}

