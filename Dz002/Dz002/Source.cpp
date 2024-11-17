#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>

void Save()
{
    int numbers;
    std::ofstream file("digits.txt"); 
    std::cout << "Press 20 numbers:"; std::cin >> numbers;
    file << numbers << std::endl; 
    file.close();
}

// Функція для читання чисел з файлу
std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> numbers;
    int number;
    while (file >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

// Функція для вилучення всіх парних елементів
void removeEvenNumbers(std::vector<int>& numbers) {
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; }), numbers.end());
}

// Функція для вилучення всіх елементів, кратних 3
void removeMultiplesOfThree(std::vector<int>& numbers) {
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int x) { return x % 3 == 0; }), numbers.end());
}

// Функція для виведення вектора
void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    //Записуе у файл
    Save();
    // Зчитуємо числа з файлу
    std::vector<int> numbers = readNumbersFromFile("digits.txt");

    // Копіюємо вектор для другого потоку
    std::vector<int> numbersForSecondThread = numbers;

    // Створюємо потоки для виконання функцій
    std::thread t1(removeEvenNumbers, std::ref(numbers));
    std::thread t2(removeMultiplesOfThree, std::ref(numbersForSecondThread));

    // Очікуємо завершення потоків
    t1.join();
    t2.join();

    // Виводимо результати
    std::cout << "After removing even numbers: ";
    printVector(numbers);

    std::cout << "After removing multiples of three: ";
    printVector(numbersForSecondThread);

    return 0;
}
