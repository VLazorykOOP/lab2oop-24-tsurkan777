#include <iostream>
using namespace std;
int main() {

    {
        setlocale(LC_CTYPE, "ukr");
        cout << "Введіть числа a,b,c,d"<< endl;
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        int result =((b << 11) + b) + ((d << 4) - d + ((a >> 11) << 3)) - ((c << 6) + (c << 5) + (c << 2)) + ((d << 6) + (d << 5) + (d << 3));

        cout << "Результат: " << result << endl;
    }
    return 0;
}
