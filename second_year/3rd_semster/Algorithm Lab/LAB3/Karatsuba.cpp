#include<iostream>
#include<string>
#include<cmath>
using namespace std;

// int stringToNumber(string str){
//     int num = 0;
//     for(int i = 0 ; i < str.length() ; i++){
//         num += ((int)str[i] - 48);
//         num *= 10;
//     }
//     return num/10;
// }

// string numToString(int num){
//     int digit = 0;
//     for(int i = num ; i > 0 ; i /= 10){
//         digit++;
//     }
//     string str[digit+1];
//     cout << "digit == " << digit;
//     for(int i = digit -1 ; i >= 0 ; i--){
//         str[i] = num % 10;
//         num = num/10;
//     }
//     str[digit+1] = '\0';
//     return str;
// }

string karatsuba(string num1, string num2) {
    if (num1.size() == 1 || num2.size() == 1) {
        return to_string(stoi(num1) * stoi(num2));
    }

    int maxi = max(num1.size(), num2.size());
    int n = maxi / 2;

    string num11 = num1.substr(0, num1.size() - n); //Lnum1 A1
    string num10 = num1.substr(num1.size() - n);  //Rnum1 A2
    string num21 = num2.substr(0, num2.size() - n); //Lnum2 B1
    string num20 = num2.substr(num2.size() - n);  // Rnum2 B2
    //cout << num11 << " " << num10 << " " << num21 << " " << num20 << " " << endl;
    string q2 = karatsuba(num11, num21);// Lnum1 * Lnum2 A1 * B1
    string q0 = karatsuba(num10, num20);//Rnum1 * Rnum2 A2 * B2
    //A1 * A2 + B1 * B2
    string q1 = karatsuba(to_string(stoi(num11) +stoi(num10)), to_string(stoi(num21) + stoi(num20)));
    //(A1*A2)(B1*B2) - (A1*B1)-(A2*B2)
    string q4 = to_string(stoi(q1) - stoi(q2) - stoi(q0));
    string num = to_string(stoi(q2) * pow(10, 2 * n) + stoi(q4) * pow(10, n) + stoi(q0));
    return num;
}


int main(){
    string num1 ,num2;
    cout <<"Enter two numbers : ";
    cin >> num1 >> num2;
    //cout << " num = " << stringToNumber(num1) << endl;
    cout << "num1 => " << num1 << " * num2 => " << num2 <<" = " << karatsuba(num1 ,num2) << endl;

}