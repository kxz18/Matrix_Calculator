export CPLUS_INCLUDE_PATH=../Class_RealNum;../Class_Matrix;../Class_SquareMatrix;../Class_LinSimEqua;../Class_QuadraticForm
#用于改变g++的搜索地址（只能搜索头文件）
VPATH=../Class_RealNum;../Class_Matrix;../Class_SquareMatrix;../Class_LinSimEqua;../Class_QuadraticForm
#用于改变make的搜索地址（可以搜索所有类型文件）
WORKFILE=calculate.cpp Matrix.cpp RealNum.cpp SquareMatrix.cpp LinSimEqua.cpp QuadraticForm.cpp Variable.cpp
OBJ=Variable.cpp Operations.h ../Class_Matrix/Matrix.cpp ../Class_RealNum/RealNum.cpp ../Class_SquareMatrix/SquareMatrix.cpp ../Class_LinSimEqua/LinSimEqua.cpp ../Class_QuadraticForm/QuadraticForm.cpp calculate.cpp 

release:$(WORKFILE)
	g++ -std=c++11  $(OBJ) -o main

debug:$(WORKFILE)
	g++ -std=c++11 -DDEBUG $(OBJ) -o main

debug2:$(WORKFILE)
	g++ -std=c++11 -DDEBUG -fno-elide-constructors $(OBJ) -o main

.PHONY:clean
clean:
	rm *.exe