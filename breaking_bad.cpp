#include <iostream>
#include <cmath>

using namespace std;



double calkuj(double (*funkcja)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double wynik = 0.0f;
    for (int i = 0; i < n; ++i) {
        double x1 = a+i*h;
        double x2 = a+(i+1)*h;
        double gx1 = funkcja(x1);
        double gx2 = funkcja(x2);
        if(gx1 > 0 && gx2 > 0){
            wynik+= (gx1*gx1+gx2*gx2)*h/2.0f;
        }
    }
    return wynik * M_PI;
}

int main() {
     std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int x, y, z, n;
    double p;
    cin >> x >> y >> z >> p >> n;
    
    double pojemnosc_akwarium = x * y * z ; 
    double wypelnienie_akwarium= pojemnosc_akwarium*p;
    int numer_butelki = -1; 
    
    for (int i = 0; i < n; ++i) {
        double wypelnienie;
        cin >> wypelnienie;
        double objetosc_napoju = calkuj(butelka, 0, wypelnienie, 1000); 
        wypelnienie_akwarium+= objetosc_napoju; 
        if (wypelnienie_akwarium > pojemnosc_akwarium) { 
            numer_butelki = i+1;
            break;
        }
    }
    

    if (numer_butelki != -1) {
        cout << numer_butelki << endl;  
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}
