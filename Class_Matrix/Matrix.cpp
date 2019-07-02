#include"Matrix.h"
#include"RealNum.h"

void Matrix::RowSwap(int m,int n){
	RealNum t=0;
	for(int k=0;k<column;k++){
		t=std::move(matrix[m][k]);
		matrix[m][k]=std::move(matrix[n][k]);
		matrix[n][k]=std::move(t);
	}
}

Matrix::Matrix(int a):row(a),column(a){
	#ifdef DEBUG
		std::cout<<"Matrix::Matrix(int a) called"<<std::endl;
	#endif
	if(a<=0){
		std::cout<<"Invalid matrix order!\n"
				 "Order revised to 1 automatically"<<std::endl;
		row=column=1;
	}
	matrix=new RealNum*[row];
	for(int i=0;i<a;i++){
		matrix[i]=new RealNum[column];
		matrix[i][i]=1;
	}
} 

Matrix::Matrix(int a,int b):row(a),column(b){
	#ifdef DEBUG
		std::cout<<"Matrix::Matrix(int a, int b) called"<<std::endl;
	#endif
	if(a<=0){
		std::cout<<"Invalid row parameter!\n"
				 "Row revised to 1 automatically"<<std::endl;
		row=1;
	}
	if(b<=0){
		std::cout<<"Invalid column parameter!\n"
			 	 "Column revised to 1 automatically"<<std::endl;
		column=1;
	}
	matrix=new RealNum*[row];
	for(int i=0;i<a;i++){
		matrix[i]=new RealNum[column];
		for(int j=0;j<column;j++){
			matrix[i][j]=0;										//initialize all elements to 0
		}
	}
}

Matrix::Matrix(const Matrix &a){
	#ifdef DEBUG
		std::cout<<"Matrix::Matrix(Matrix &a) called"<<std::endl;
	#endif
	row=a.row;
	column=a.column;
	matrix=new RealNum*[row];
	for(int i=0;i<row;i++){
		matrix[i]=new RealNum[column];
		for(int j=0;j<column;j++){
			matrix[i][j]=a[i][j];
		}
	}
}

Matrix::Matrix(Matrix &&a){
	#ifdef DEBUG
		std::cout<<"Matrix::Matrix(Matrix &&a) called"<<std::endl;
	#endif
	row=std::move(a.row);
	column=std::move(a.column);
	matrix=new RealNum*[row];
	for(int i=0;i<row;i++){
		matrix[i]=new RealNum[column];
		for(int j=0;j<column;j++){
			matrix[i][j]=std::move(a[i][j]);
		}
	}
}

int Matrix::getRow() const{
	return row;
}

int Matrix::getColumn() const{
	return column;
}

RealNum* Matrix::operator[] (int i){
	return this->matrix[i];
}

RealNum* Matrix::operator[] (int i) const{
	return this->matrix[i];
}

Matrix& Matrix::operator= (const Matrix& a){
	#ifdef DEBUG
		std::cout<<"Matrix& Matrix::operator= (const Matrix& a) called"<<std::endl;
	#endif
	this->row=a.row;
	this->column=a.column;
	if(this->matrix!=nullptr){
		#ifdef DEBUG
			std::cout<<"In assignment operator=, delete[] called"<<std::endl;
		#endif
		delete[] this->matrix;
	}
	this->matrix=new RealNum*[row];
	for(int i=0;i<row;i++){
		this->matrix[i]=new RealNum[column];
		for(int j=0;j<column;j++){
			this->matrix[i][j]=a[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+= (const Matrix& a){
	*this=*this+a;
	return *this;
}

Matrix Matrix::Transpose(){
	Matrix tempo(column,row);
	for(int i=0;i<tempo.row;i++){
		for(int j=0;j<tempo.column;j++){
			tempo[i][j]=this->matrix[j][i];
		}
	}
	return tempo;
}

Matrix Matrix::Ladder(){
	#ifdef DEBUG
		std::cout<<"\n------entering Matrix Matrix::ladder()------"<<std::endl;
	#endif
	int next=1,lasti=0,i=0,j=0;
	RealNum first=0;
	Matrix tempo=*this;
	for(j=0;j<column&&lasti<row;j++){
		next=1;
		for(i=lasti;i<row&&next==1;i++){
			if(tempo[i][j]!=0){
				tempo.RowSwap(i,lasti);
				next=0;
			} 
		}
		for(i=lasti+1;i<row&&tempo[lasti][j]!=0;i++){
			first=tempo[i][j];
			for(int k=j;k<column;k++){
				tempo[i][k]=tempo[i][k]-first/tempo[lasti][j]*tempo[lasti][k];
			}
		}
		switch(tempo[lasti][j]==0){
			case 1:break;
			default:lasti++;break;
		}
	}
	#ifdef DEBUG
		std::cout<<"------ending Matrix Matrix::ladder()------\n"<<std::endl;
	#endif
	return tempo;
}

Matrix Matrix::MaxLIG(){
	#ifdef DEBUG
		std::cout<<"\n------entering Matrix Matrix::MaxLIG()------"<<std::endl;
	#endif
	Matrix a=this->Ladder();
	int* judgegroup=new int[column];							//record if a column is in MILG(1 for yes and 0 for no)
	for(int i=0;i<column;i++)judgegroup[i]=0;					//this is necessary!Firstly I put this initialzie after line 139, which make me debug for 3 hours on this function, as the last few position may not be initialized when row<column;and at that time I choose judgegroup[i]!=0 as the condition(now it's ==1), so it really annoyed me for a long time
	int next=1,cnt=0;											//cnt as a record of how many vectors are in the Maximum linear independence group
	for(int i=0;i<row;i++){										//find pivot(ึ๗ิช) of each row
		next=1;
		for(int j=0;j<column&&next==1;j++){
			if(a[i][j]!=0){
				judgegroup[j]=1;
				cnt++; 
				next=0;
			}
		}
	}
	if(cnt==0){
		std::cout<<"All elements are 0!"<<std::endl;
		delete[] judgegroup;
		#ifdef DEBUG
		std::cout<<"------ending Matrix Matrix::MaxLIG()------\n"<<std::endl;
		#endif
		return Matrix(1,1);
	}else{
		Matrix b(row,cnt);
		int b_col=0;
		for(int j=0;j<column;j++){
			if(judgegroup[j]==1){
				for(int i=0;i<row;i++){
					b[i][b_col]=matrix[i][j];
				}
				b_col++;
			}
		}
		#ifdef DEBUG
			std::cout<<"ready to delete judgegroup"<<std::endl;
		#endif
		delete[] judgegroup;
		#ifdef DEBUG
		std::cout<<"------ending Matrix Matrix::MaxLIG()------\n"<<std::endl;
		#endif
		return b;
	}
}

int Matrix::Rank(){
	#ifdef DEBUG
		std::cout<<"\n------entering int Matrix::Rank()------"<<std::endl;
	#endif
	#ifdef DEBUG
		std::cout<<"------ending int Matrix::Rank()------\n"<<std::endl;
	#endif
	return (this->MaxLIG()).column;
}

Matrix::~Matrix(){
	#ifdef DEBUG
		std::cout<<"Matrix::~Matrix() called"<<std::endl;
	#endif
	delete[] matrix;
}

Matrix operator+ (const Matrix &a,const Matrix &b){
	if(a.row==b.row&&a.column==b.column){
		Matrix c(a.row,a.column);
		for(int i=0;i<a.row;i++){
			for(int j=0;j<a.column;j++){
				c[i][j]=a[i][j]+b[i][j];
			}
		}
		return c;
	}else{
		std::cout<<"Sizes of Matrixes don't match!\n"
				 "Output 0 automatically!"<<std::endl;
		Matrix c(1,1);
		return c;
	}
}

Matrix operator- (const Matrix &a,const Matrix &b){
	if(a.row==b.row&&a.column==b.column){
		Matrix c(a.row,a.column);
		for(int i=0;i<a.row;i++){
			for(int j=0;j<a.column;j++){
				c[i][j]=a[i][j]-b[i][j];
			}
		}
		return c;
	}else{
		std::cout<<"Sizes of Matrixes don't match!\n"
				 "Output 0 automatically!"<<std::endl;
		Matrix c(1,1);
		return c;
	}
}

Matrix operator* (const Matrix &a,const Matrix &b){
	if(a.column==b.row){
		Matrix c(a.row,b.column);
		for(int i=0;i<a.row;i++){
			for(int j=0;j<b.column;j++){
				c[i][j]=0;										//initialize c[i][j] with 0(otherwise += may faied as c[i][j] may have an unknown value)
				for(int k=0;k<a.column;k++){
				c[i][j]+=a[i][k]*b[k][j];
				}
			}
		}
		return c;
	}else{
		std::cout<<"Column of the first matrix doesn't "
					"match row of the second one!\n"
					"Output 0 automatically!"<<std::endl;
		Matrix c(1,1);
		return c;
	}
}

std::istream& operator>> (std::istream& in, Matrix& dst){
	for(int i=0;i<dst.row;i++){
		for(int j=0;j<dst.column;j++){
			in>>dst[i][j];
		}
	}
	return in;
}

std::ostream& operator<< (std::ostream& out, const Matrix& src){
	for(int i=0;i<src.row;i++){
		for(int j=0;j<src.column;j++){
			out<<src.matrix[i][j]<<"\t";						//src is a const &, so only const function can get access to src, thus [] can't be adopted directly
		}
		out<<"\n";
	}
	return out;
}


