#include <iostream>

using namespace std;

class Calculator {
public:
    virtual double add(double a, double b) = 0;
    virtual double subtract(double a, double b) = 0;
    virtual double multiply(double a, double b) = 0;
    virtual double divide(double a, double b) = 0;
    virtual ~Calculator() {}
};

class StandardCalculator : public Calculator {
public:
    double add(double a, double b) {
        return a + b;
    }
    
    double subtract(double a, double b) {
        return a - b;
    }
    
    double multiply(double a, double b) {
        return a * b;
    }
    
    double divide(double a, double b) {
        if (b == 0) {
            return 0;
        }
        return a / b;
    }
};

class IntegerCalculator : public Calculator {
public:
    double add(double a, double b) {
        return (int)a + (int)b;
    }
    
    double subtract(double a, double b) {
        return (int)a - (int)b;
    }
    
    double multiply(double a, double b) {
        return (int)a * (int)b;
    }
    
    double divide(double a, double b) {
        if ((int)b == 0) {
            return 0;
        }
        return (int)a / (int)b;
    }
};

int main() {
    Calculator* calc1 = new StandardCalculator();
    Calculator* calc2 = new IntegerCalculator();

    double num1 = 7.5;
    double num2 = 2.2;

    cout << "Numbers: " << num1 << " and " << num2 << "\n\n";

    cout << "Standard Calculator Results:\n";
    cout << "Add: " << calc1->add(num1, num2) << "\n";
    cout << "Subtract: " << calc1->subtract(num1, num2) << "\n";
    cout << "Multiply: " << calc1->multiply(num1, num2) << "\n";
    cout << "Divide: " << calc1->divide(num1, num2) << "\n\n";

    cout << "Integer Calculator Results:\n";
    cout << "Add: " << calc2->add(num1, num2) << "\n";
    cout << "Subtract: " << calc2->subtract(num1, num2) << "\n";
    cout << "Multiply: " << calc2->multiply(num1, num2) << "\n";
    cout << "Divide: " << calc2->divide(num1, num2) << "\n";

    delete calc1;
    delete calc2;

    return 0;
}