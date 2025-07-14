#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addNumbersWithCarry(const string &num1, const string &num2, int carry) {
    int len1 = num1.length();
    int len2 = num2.length();
    int maxLen = max(len1, len2);

    string result(maxLen + 1, '0');
    int i = len1 - 1;
    int j = len2 - 1;
    int k = maxLen;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result[k--] = (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
    }

    if (result[0] == '0') {
        result.erase(result.begin());
    }

    return result;
}

string addLargeNumbers(const string &num1, const string &num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    int maxLen = max(len1, len2);

    string num1_padded = string(maxLen - len1, '0') + num1;
    string num2_padded = string(maxLen - len2, '0') + num2;

    if (maxLen == 1) {
        int sum = (num1_padded[0] - '0') + (num2_padded[0] - '0');
        return (sum >= 10) ? string(1, (sum - 10) + '0') : string(1, sum + '0');
    }

    int mid = maxLen / 2;
    string high1 = num1_padded.substr(0, maxLen - mid);
    string low1 = num1_padded.substr(maxLen - mid);
    string high2 = num2_padded.substr(0, maxLen - mid);
    string low2 = num2_padded.substr(maxLen - mid);

    string lowSum = addNumbersWithCarry(low1, low2, 0);
    string highSum = addNumbersWithCarry(high1, high2, 0);

    string combinedSum = addNumbersWithCarry(highSum + string(mid, '0'), lowSum, 0);

    return combinedSum;
}

int main() {
    string num1, num2;
    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;
    string result = addLargeNumbers(num1, num2);

    cout << "The sum is: " << result << std::endl;

    return 0;
}
