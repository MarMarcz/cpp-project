#include <iostream>

// Przykładowa funkcja dodająca dwie liczby
int add(int a, int b) {
    return a + b;
}

// Funkcja main
int main() {
    int num1 = 5;
    int num2 = 3;

    std::cout << "Wynik dodawania: " << add(num1, num2) << std::endl;

    return 0;
}
