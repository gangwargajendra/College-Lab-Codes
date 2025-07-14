#include <iostream>
#include <string>
#include <algorithm>
#include<cmath>
using namespace std;

// Function to multiply two numbers using Karatsuba algorithm
string karatsuba(string& x, string& y) {
    // Base case for recursion: when numbers are small
    if (x.size() == 1 || y.size() == 1) {
        return to_string(stoi(x) * stoi(y));
    }

    int n = max(x.size(), y.size());
    int m = n / 2;

    string x1 = x.substr(0, x.size() - m); //12
    string x0 = x.substr(x.size() - m);  //34
    string y1 = y.substr(0, y.size() - m); //56
    string y0 = y.substr(y.size() - m);  // 78

    string z2 = karatsuba(x1, y1);
    string z0 = karatsuba(x0, y0);
    string z1 = karatsuba(to_string(stoi(x1) + stoi(x0)), to_string(stoi(y1) + stoi(y0)));
    z1 = to_string(stoi(z1) - stoi(z2) - stoi(z0));

    // Combine the results
    string result = to_string(stoi(z2) * pow(10, 2 * m) + stoi(z1) * pow(10, m) + stoi(z0));

    // Remove leading zeros
    result.erase(0, result.find_first_not_of('0'));

    return result.empty() ? "0" : result;
}

int main() {
    string num1 = "1234";
    string num2 = "5678";

    string result = karatsuba(num1, num2);

    cout << "Product of " << num1 << " and " << num2 << " is: " << result << endl;

    return 0;
}
