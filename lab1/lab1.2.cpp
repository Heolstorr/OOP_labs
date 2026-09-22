#include <iostream>
#include <iomanip>
#include <cmath>

class ZavdClass {
private:
    double a, b;
public:
    ZavdClass() {
        a = 0.0;
        b = 0.0;
    }

    void Fn_b(double x, double y, double z) {
        double part1 = std::pow(std::abs(x), 0.3) / (z + y);
        double part2 = std::pow(std::tan((x + std::pow(z, 2)) / (2.0 * x - 1.4)), 2);
        double term = std::pow(std::abs(part1 + part2), 1.0 / 3.0);
        b = y * term - z * std::exp(x * x - y);
    }

    void Fn_a(double x, double y, double z) {
        double num = 3.0 + std::exp(y - x) + std::sqrt(std::pow(std::abs(y * y + b), 0.3));
        double den = 1.0 + x * x * std::abs(y - std::pow(std::tan(z * z), 2));
        a = std::pow(std::abs(z), 0.2) * (num / den);
    }

    double geta() { return a; }
    double getb() { return b; }
};

int main() {
    int variant = 9;
    double y = 0.47 * variant;
    double z = -1.32 * variant;

    ZavdClass solver;

    std::cout << "Tabulation of functions a and b\n";
    std::cout << "y = " << y << ", z = " << z << "\n\n";
    
    std::cout << std::fixed << std::setprecision(5);
    std::cout << std::setw(10) << "x" << " | " 
              << std::setw(15) << "b" << " | " 
              << std::setw(15) << "a" << "\n";

    for (double x = -1.0; x <= 1.001; x += 0.2) {
        solver.Fn_b(x, y, z);
        solver.Fn_a(x, y, z);
        
        std::cout << std::setw(10) << x << " | " 
                  << std::setw(15) << solver.getb() << " | " 
                  << std::setw(15) << solver.geta() << "\n";
    }

    return 0;
}