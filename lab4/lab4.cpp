#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;


class Circle {
protected:
    double r;
public:
    explicit Circle(double radius);
    ~Circle();

    double area() const;
    double circumference() const; 
    void show(ostream& os) const;
};

class Rhombus {
protected:
    double d1, d2;             
public:
    Rhombus(double diag1, double diag2);
    ~Rhombus();

    double side() const;           
    double area() const;            
    void show(ostream& os) const; 
};


class CircleInRhombus : public Circle, public Rhombus {
private:

    static double inradius(double diag1, double diag2);
public:
    CircleInRhombus(double diag1, double diag2);
    ~CircleInRhombus();

    double freeArea() const;        
    void show(ostream& os) const; 
};



static const double PI = 3.14159265358979323846;


Circle::Circle(double radius) : r(radius) {
    if (r <= 0) throw invalid_argument("Радіус має бути додатним");
    cout << "  [Конструктор Circle]  r = " << r << endl;
}

Circle::~Circle() {
    cout << "  [Деструктор Circle]" << endl;
}

double Circle::area() const { return PI * r * r; }
double Circle::circumference() const { return 2 * PI * r; }

void Circle::show(ostream& os) const {
    os << "Коло: радіус = " << r
       << ", площа = " << area()
       << ", довжина кола = " << circumference() << '\n';
}


Rhombus::Rhombus(double diag1, double diag2) : d1(diag1), d2(diag2) {
    if (d1 <= 0 || d2 <= 0) throw invalid_argument("Діагоналі мають бути додатними");
    cout << "  [Конструктор Rhombus] d1 = " << d1 << ", d2 = " << d2 << endl;
}

Rhombus::~Rhombus() {
    cout << "  [Деструктор Rhombus]" << endl;
}

double Rhombus::side() const { return sqrt(d1 * d1 + d2 * d2) / 2; }
double Rhombus::area() const { return d1 * d2 / 2; }

void Rhombus::show(ostream& os) const {
    os << "Ромб: діагоналі = " << d1 << " і " << d2
       << ", сторона = " << side()
       << ", площа = " << area() << '\n';
}

double CircleInRhombus::inradius(double diag1, double diag2) {
    if (diag1 <= 0 || diag2 <= 0) throw invalid_argument("Діагоналі мають бути додатними");
    return diag1 * diag2 / (2 * sqrt(diag1 * diag1 + diag2 * diag2));
}

CircleInRhombus::CircleInRhombus(double diag1, double diag2)
    : Circle(inradius(diag1, diag2)), Rhombus(diag1, diag2) {
    cout << "  [Конструктор CircleInRhombus]" << endl;
}

CircleInRhombus::~CircleInRhombus() {
    cout << "  [Деструктор CircleInRhombus]" << endl;
}

double CircleInRhombus::freeArea() const {
    return Rhombus::area() - Circle::area();
}

void CircleInRhombus::show(ostream& os) const {
    os << " Коло, вписане в ромб  \n";
    Rhombus::show(os);
    Circle::show(os);
    os << "Площа ромба поза колом = " << freeArea() << "\n\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    const string filename = "results.txt";

    ofstream fout(filename, ios::out | ios::trunc);
    if (!fout.is_open()) {
        cerr << "Не вдалося відкрити файл " << filename << " для запису\n";
        return 1;
    }

    cout << "Введіть діагоналі ромба d1 та d2 (через пробіл).\n"
         << "Для завершення введіть 0 0 або натисніть Ctrl+D / Ctrl+Z.\n";

    double d1, d2;
    int count = 0;
    while (cout << "\nd1 d2: ", cin >> d1 >> d2) {
        if (d1 == 0 && d2 == 0) break;
        try {
            CircleInRhombus fig(d1, d2);
            ++count;

            fig.show(cout);   
            fig.show(fout);         

            cout << "  Circle::area() = " << fig.Circle::area()
                 << ", Rhombus::area() = " << fig.Rhombus::area() << endl;
        }                                 
        catch (const invalid_argument& e) {
            cout << "Помилка: " << e.what() << endl;
        }
    }
    fout.close();

    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Не вдалося відкрити файл " << filename << " для читання\n";
        return 1;
    }
    cout << "\n Вміст файлу " << filename << " (фігур: " << count << ") \n";
    string line;
    while (getline(fin, line)) cout << line << '\n';
    fin.close();

    return 0;
}