#include<bits/stdc++.h>
using namespace std;

class TestClass{
    string names;
    int age;
    public: 
    TestClass(){};
    TestClass(string names, int age);
    void printDta(){
        cout<< "Names: "<<names<<endl;
    }
};

int main(){

TestClass testClass;
testClass.printDta();

return 0;
}