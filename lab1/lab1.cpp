#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class ZavdClass {
private:
    double a, b;
public:
    ZavdClass() {
        a = 0.0;
        b = 0.0;
    }

    void Fn_b(double x, double y, double z) {
        double part1 = pow(abs(x), 0.3) / (z + y);
        double part2 = pow(tan((x + pow(z, 2)) / (2.0 * x - 1.4)), 2);
        double term = pow(abs(part1 + part2), 1.0 / 3.0);
        b = y * term - z * exp(x * x - y);
    }

    void Fn_a(double x, double y, double z) {
        double num = 3.0 + exp(y - x) + sqrt(pow(abs(y * y + b), 0.3));
        double den = 1.0 + x * x * abs(y - pow(tan(z * z), 2));
        a = pow(abs(z), 0.2) * (num / den);
    }

    double geta() { return a; }
    double getb() { return b; }
};

int main() {
    int variant = 9;
    
    double y = 0.47 * variant;
    double z = -1.32 * variant;
    
    ZavdClass solver;

    // Single Calculation
    double x_single = 0.48 * variant;
    
    solver.Fn_b(x_single, y, z);
    solver.Fn_a(x_single, y, z);

    cout << "Single Calculation\n";
    cout << "Input parameters:\n";
    cout << "x = " << x_single << "\n";
    cout << "y = " << y << "\n";
    cout << "z = " << z << "\n\n";

    cout << "Calculation results:\n";
    cout << "b = " << solver.getb() << "\n";
    cout << "a = " << solver.geta() << "\n\n";


    //Tabulation
    cout << "Tabulation of functions a and b \n";
    cout << "y = " << y << ", z = " << z << "\n\n";
    
    cout << fixed << setprecision(5);
    cout << setw(10) << "x" << " | " 
         << setw(15) << "b" << " | " 
         << setw(15) << "a" << "\n";
    
    for (double x = -1.0; x <= 1.001; x += 0.2) {
        solver.Fn_b(x, y, z);
        solver.Fn_a(x, y, z);
        
        cout << setw(10) << x << " | " 
             << setw(15) << solver.getb() << " | " 
             << setw(15) << solver.geta() << "\n";
    }

    return 0;
}