#include<bits/stdc++.h>
using namespace std;


int main(){

double x = 900054.34;
string x_string = to_string(x);

cout << x_string << endl;

double varD = setprecision(10) << stod(x_string);
cout << varD << endl;
    return 0;
}