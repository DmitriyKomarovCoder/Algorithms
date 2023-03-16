/* Использование арифметических операций запрещено.
Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде.
1.2 Вернуть значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K
*/

#include <iostream>

int bitValue(int value, int k) {
    return (value >> k) & 1;
}


int main() {
    int value;
    int k;
    std::cin >> value >> k;
    std::cout << bitValue(value, k) << std::endl;
    return 0;
}