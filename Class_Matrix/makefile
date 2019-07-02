export CPLUS_INCLUDE_PATH=../Class_RealNum
#用于改变g++的搜索地址（只能搜索头文件）
VPATH=../Class_RealNum
#用于改变make的搜索地址（可以搜索所有类型文件）
WORKFILE=test.cpp Matrix.h Matrix.cpp RealNum.h 
OBJ=test.cpp Matrix.cpp ../Class_RealNum/RealNum.cpp

main:$(WORKFILE)
	g++ -std=c++11  $(OBJ) -o main

debug:$(WORKFILE)
	g++ -std=c++11 -DDEBUG $(OBJ) -o main

debug2:$(WORKFILE)
	g++ -std=c++11 -DDEBUG -fno-elide-constructors $(OBJ) -o main

.PHONY:clean
clean:
	rm *.exe