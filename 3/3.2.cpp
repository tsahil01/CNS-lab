#include <iostream>

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    int a, b, x, y;
    std::cout << "Enter two integers: ";
    std::cin >> a >> b;
    
    int gcd = extendedGCD(a, b, x, y);
    std::cout << "GCD of " << a << " and " << b << " is " << gcd << std::endl;
    std::cout << "Coefficients x and y are " << x << " and " << y << " respectively" << std::endl;
    std::cout << "Verification: " << a << " * " << x << " + " << b << " * " << y << " = " << gcd << std::endl;
    return 0;
}
