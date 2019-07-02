#include"LinSimEqua.h"

void LinSimEqua::initialize(){
	for(int i=0;i<row;i++){
		for(int j=0;j<column-1;j++){
			CoeMat[i][j]=this->matrix[i][j];
		}
	}

	for(int i=0;i<row;i++){
		ResMat[i][0]=this->matrix[i][column-1];
	}

	judgegroup=new int[CoeMat.getColumn()];
	Matrix lad=this->Ladder();
	for(int i=0;i<CoeMat.getColumn();i++)judgegroup[i]=0;
	int next=1,record=0;
	for(int i=0;i<row;i++){
		next=1;
		for(int j=record;j<CoeMat.getColumn();j++){
			if(lad[i][j]!=0&&next==1){
				judgegroup[j]=1;
				record=j+1,next=0; 
			}
		}
	}
}

LinSimEqua::LinSimEqua(int a, int b):Matrix(a,b),CoeMat(a,b-1),ResMat(a,1){
	#ifdef DEBUG
        std::cout<<"LinSimEqua::LinSimEqua(int a, int b) called"<<std::endl;
    #endif
}

LinSimEqua::LinSimEqua(const Matrix& a):Matrix(a),CoeMat(a.getRow(),a.getColumn()-1),ResMat(a.getRow(),1){
	#ifdef DEBUG
        std::cout<<"LinSimEqua::LinSimEqua(const Matrix& a) called"<<std::endl;
    #endif
	this->initialize();
}

int LinSimEqua::getEquaNum(){
	return row;
}

int LinSimEqua::getUnknowNum(){
	return column-1;
}

bool LinSimEqua::homo(){
	int cnt=0;
	for(int i=0;i<row;i++){
		if(ResMat[i][0]==0)cnt++;
	}
	return cnt==row;
}

std::string LinSimEqua::Judge(){
    std::string judge;int cnt=0;
	int AugRank=this->Rank();
	int CoeRank=CoeMat.Rank();
	if(AugRank!=CoeRank)judge="No solution";
	else if(AugRank==CoeRank&&CoeRank<column-1)judge="Infinite solutions";
	else judge="Unique solution";
    return judge;
}

Matrix LinSimEqua::getFunSol(){
	Matrix a=this->Ladder();
	int CoeCol=this->getUnknowNum(),r=this->Rank();
	Matrix x(CoeCol,CoeCol-r);	
	int num=0,col=0;
	for(int LoopTime=1;LoopTime<=(CoeCol-r);LoopTime++){						//assign values for pivots 
		num=0;			
		for(int i=0;i<CoeCol;i++){
			if(judgegroup[i]==0){
				num++;
				switch (num==LoopTime){
				case 1:x[i][col]=1;break;
				case 0:x[i][col]=0;break;
				}
			}
		}	
		for(int i=row-1;i>=0;i--){
			for(int j=0;j<CoeCol;j++){
				if(a[i][j]!=0){
					RealNum sigma=0;
					for(int p=j+1;p<CoeCol;p++){
						sigma+=a[i][p]*x[p][col];
					}
					x[j][col]=(-sigma)/a[i][j];
					break;
				}
			}	
		}
		col++;
	}
	return x;
}

Matrix LinSimEqua::getSpeSol(){
	Matrix a=this->Ladder();
	Matrix y(this->getUnknowNum(),1);
	int CoeCol=CoeMat.getColumn();
	RealNum sigma=0;
	for(int i=0;i<CoeCol;i++){
		if(judgegroup[i]==0)y[i][0]=0;
	}
	for(int i=row-1;i>=0;i--){
		for(int j=0;j<CoeCol;j++){
			if(!(a[i][j]>-1e-10&&a[i][j]<1e-10)){			//after so many times of calculating, there will be some deviation caused by transitions between binary and decimal
				sigma=0;
				for(int p=j+1;p<CoeCol;p++){
					sigma+=a[i][p]*y[p][0];
				}
				y[j][0]=(a[i][column-1]-sigma)/a[i][j];
				break;
			}
		}	
	}
	return y;					
}

Matrix LinSimEqua::getLSSol(){				//Coefficient matrix is A^(T)A, the result matrix is A^(T)b
	LinSimEqua tempo=this->CoeMat.Transpose()*(*this);
	return tempo.getSpeSol();
}

Matrix LinSimEqua::getOpLSSol(){			//unfinished
	return *this;
}

void LinSimEqua::printSol(){
	std::string judge=this->Judge();
	if(judge=="No solution"){
		std::cout<<"No precise solution!\nThe least-square solution is:"<<std::endl;
		std::cout<<this->getLSSol()<<std::endl;
		std::cout<<"The optimal solution is:(unfinished)\n"<<this->getOpLSSol()<<std::endl;
	}else if(judge=="Unique solution"){
		std::cout<<"The linear simultaneous equations have a unique solution\n"
				 <<this->getSpeSol()<<std::endl;
	}else{
		std::cout<<"Fundamental solutions system is\n"
				 <<this->getFunSol()<<std::endl;
		if(this->homo()==false){
			std::cout<<"A special solution is\n"
					 <<this->getSpeSol()<<std::endl;
		}
	}
}

LinSimEqua& LinSimEqua::operator= (const Matrix& a){
	LinSimEqua tmp(a);
	*this=tmp;
	return *this;
}

std::istream& operator>> (std::istream& in,LinSimEqua& dst){	//you can't just in>>dst as this will be a dead loop
	for(int i=0;i<dst.row;i++){
		for(int j=0;j<dst.column;j++){
			in>>dst.matrix[i][j];
		}
	}
	dst.initialize();
	return in;
}