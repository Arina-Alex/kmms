#include <cmath>
#include <iostream>

double calculateF1(double x);
double calculateF2(double x);

int main() {
    double angle;
    std::cout << "Введите угол:" << std::endl;
    std::cin >> angle;

    double result1 = calculateF1(angle);
    
    if (result1 != 0) { 
        std::cout << "F(x1) = " << result1 << std::endl;
    } else {
        std::cout << "Неверный ввод в F(x1)" << std::endl;
    }

    double result2 = calculateF2(angle);
    
    if (result2 != 0) { 
        std::cout << "F(x2) = " << result2 << std::endl;
    } else {
        std::cout << "Неверный ввод в F(x2)" << std::endl;
    }

    system ("pause");
    return 0;
}

double calculateF1(double x) {
    double numerator = 1 + sin(2 * x);
    double denominator = 1 - cos(2 * x);
    
    if (std::abs(denominator) == 0.0) { 
        return 0;
    }
    return numerator / denominator;
}


double calculateF2(double x) {
    double numerator = 1 + tan(x) * tan(x);
    double denominator = 1 - tan(x) * tan(x);
    
    if (std::abs(denominator) == 0.0) { 
        return 0;
    }
    return numerator / denominator;
}
