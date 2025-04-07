#include <iostream>
using namespace std;
int main() {

   int a, b, c, d;
    cout << "Write a,b,c,d: "<<endl;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;



    unsigned int op_1 = (b << 11)+b;   //b*2049
    unsigned int op_2 = (d << 4)-d;   // d*15
    unsigned int op_3 = (a << 4)-(a << 2);  //12*a

    unsigned int op_4 = (c << 4)+c+c; //c*18
    unsigned int op_5 = (d << 7)-(d << 5)+(d <<3);   //d*104

    unsigned int op_7 = (op_2 + op_3) >> 11; // (d*15+a*15)/2048

    unsigned int res = op_1 + op_7 - op_4 + op_5;
    unsigned int test = (2049*b)+(d*15+a*15)/2048-(c*18)+(d*104);

    cout <<"result:"<< res << endl;
    cout <<"test:"<< test << endl;


    return 0;
}
