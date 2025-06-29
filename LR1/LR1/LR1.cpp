#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <windows.h>
#include <exception>

using namespace std;

class FileOpenException : public exception {
public:
    explicit FileOpenException(const string& filename) : msg("Не вдалося відкрити файл: " + filename) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    string msg;
};

class InputException : public exception {
public:
    explicit InputException(const string& message) : msg("Невірне введення: " + message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    string msg;
};

class MathException : public exception {
public:
    explicit MathException(const string& message) : msg("Математична помилка: " + message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    string msg;
};

double U(double x);
double T(double x);
double func_reg(double r, double m, double k);
double Rsv(double x, double y, double z);
double Qnk(double x, double y);
double Y(double x);
double Stext(double x, string text);
double Mtl(double x, double y, double z);
double Mts(double x, double y);
double Tsm(double x, double y);
double Qnkl(double x, double y);
double Qqnl(double x, double y, double z);
double U1(double x);
double T1(double x);

map<double, double> uValues;
map<double, double> tValues;
map<string, double> stextValues;

void loadData() {
    ifstream file1("dat1.dat");
    if (!file1) throw FileOpenException("dat1.dat");
    double x, u;
    while (file1 >> x >> u) {
        uValues[x] = u;
    }

    ifstream file2("dat2.dat");
    if (!file2) throw FileOpenException("dat2.dat");
    double t;
    while (file2 >> x >> t) {
        tValues[x] = t;
    }

    ifstream file3("dat3.dat");
    if (!file3) throw FileOpenException("dat3.dat");
    string text;
    while (file3 >> text >> x) {
        stextValues[text] = x;
    }
}

double U(double x) {
    for (auto& val : uValues) {
        if (x <= val.first) return val.second;
    }
    return uValues.rbegin()->second;
}

double T(double x) {
    for (auto& val : tValues) {
        if (x <= val.first) return val.second;
    }
    return tValues.rbegin()->second;
}

double func_reg(double r, double m, double k) {
    return 10 * k * pow(r - m * r, 2);
}

double Rsv(double x, double y, double z) {
    if (x * Qnk(x, y) + y * Qnk(y, z) + z * Qnk(z, x) > 0) return x * y * z;
    return 0;
}

double Qnk(double x, double y) {
    return Qnkl(x, y) * T(y);
}

double Y(double x) {
    if (x * x > 100) return 0;
    double val = x * sqrt(100 - x * x);
    if (val <= 0) throw MathException("Некоректне значення у log у Y(x)");
    return log(val);
}

double Stext(double x, string text) {
    if (stextValues.find(text) != stextValues.end()) {
        return stextValues[text];
    }
    if (text == "test") return x;
    if (text == "get") return x + 1;
    if (text == "net") return x + 2;
    return x + 3;
}

double Mtl(double x, double y, double z) {
    return x * Mts(x, y) + y * Mts(y, z);
}

double Mts(double x, double y) {
    return x * Tsm(x, y) - y * Tsm(y, x);
}

double Tsm(double x, double y) {
    double discriminant = 4 * y * y - x * x;
    if (discriminant < 0) return 0;
    double value = (5 * x * x - 3 * x * x + 2 * sqrt(discriminant)) * y;
    if (value <= 0) throw MathException("Некоректне значення у log2 у Tsm()");
    return log2(value);
}

double Qnkl(double x, double y) {
    return 1.15 * Qqnl(x, y, x + y) - 0.95 * Qqnl(y, x, x - y);
}

double Qqnl(double x, double y, double z) {
    double denominator = U1(x) + y * T1(y) - U1(z) * T1(z);
    if (abs(denominator) < 1e-8) throw MathException("Ділення на нуль у Qqnl()");
    return x / denominator;
}

double U1(double x) {
    return atan(asin(sin(3 * x)));
}

double T1(double x) {
    return atan(acos(sin(2 * x)));
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try {
        loadData();

        double x, y, z, r, m, k;
        string text;

        cout << "Введіть x: ";
        if (!(cin >> x)) throw InputException("x");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть y: ";
        if (!(cin >> y)) throw InputException("y");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть z: ";
        if (!(cin >> z)) throw InputException("z");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть r: ";
        if (!(cin >> r)) throw InputException("r");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть m: ";
        if (!(cin >> m)) throw InputException("m");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть k: ";
        if (!(cin >> k)) throw InputException("k");
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введіть text: ";
        cin >> text;

        cout << "U(x): " << U(x) << endl;
        cout << "T(x): " << T(x) << endl;
        cout << "func_reg(r,m,k): " << func_reg(r, m, k) << endl;
        cout << "Rsv(x,y,z): " << Rsv(x, y, z) << endl;
        cout << "Qnk(x,y): " << Qnk(x, y) << endl;
        cout << "Y(x): " << Y(x) << endl;
        cout << "Stext(x,\"" << text << "\"): " << Stext(x, text) << endl;
        cout << "Mtl(x,y,z): " << Mtl(x, y, z) << endl;
        cout << "Mts(x,y): " << Mts(x, y) << endl;
        cout << "Tsm(x,y): " << Tsm(x, y) << endl;
        cout << "Qnkl(x,y): " << Qnkl(x, y) << endl;
        cout << "Qqnl(x,y,z): " << Qqnl(x, y, z) << endl;
        cout << "U1(x): " << U1(x) << endl;
        cout << "T1(x): " << T1(x) << endl;

    }
    catch (const FileOpenException& e) {
        cerr << "Помилка доступу до файлу: " << e.what() << endl;
    }
    catch (const InputException& e) {
        cerr << "Помилка введення: " << e.what() << endl;
    }
    catch (const MathException& e) {
        cerr << "Математична помилка: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Невідома помилка: " << e.what() << endl;
    }

    return 0;
}