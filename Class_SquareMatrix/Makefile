export CPLUS_INCLUDE_PATH=../Class_RealNum;../Class_Matrix
#用于改变g++的搜索地址（只能搜索头文件）
VPATH=../Class_RealNum;../Class_Matrix
#用于改变make的搜索地址（可以搜索所有类型文件）
WORKFILE=test.cpp Matrix.h RealNum.h SquareMatrix.h SquareMatrix.cpp
OBJ=test.cpp ../Class_Matrix/Matrix.cpp ../Class_RealNum/RealNum.cpp SquareMatrix.cpp

main:$(WORKFILE)
	g++ -std=c++11  $(OBJ) -o main

debug:$(WORKFILE)
	g++ -std=c++11 -DDEBUG $(OBJ) -o main

debug2:$(WORKFILE)
	g++ -std=c++11 -DDEBUG -fno-elide-constructors $(OBJ) -o main

.PHONY:clean
clean:
	rm *.exe