#include <iostream>

void first_variant (double a, b, c, d){
    //сложение
    std::cout << a + c << "+" << b + d << "i" << std::endl;
    // 12 + 12i
    //вычитание
    std::cout << a - c << "-" << b - d << "i" << std::endl;
    // z_1=a+bi
    // z_2=c+di
    //умножение
    std::cout << a * c - b * d << "+" << a * b + b * c << "i" << std::endl;
}

// z^n=(a+bi)^n
void second_variant (double a, b, c, d){
    // x действительная часть результата
    // x мнимая часть результата
    for(int i = 0; i < n; i++){
        int t = x * a - y * b;
        y = x * b + y * a;
        x = t;
    }
    cout << x << " + " << y << "i";
}

#include <complex>
void power_variant (double a, double b, int n){
    complex<double> z(a, b);
    z = pow(z, n);
    std:: cout << z.real() << "+" << z.imag() << "i";
}

int main(){
    return 0;
}
