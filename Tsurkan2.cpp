#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

// Функція для підрахунку парності
int calculateParity(unsigned short value) {
    int parity = 0;
    while (value) {
        parity ^= (value & 1);  // Підраховуємо кількість одиничних бітів
        value >>= 1;
    }
    return parity;  // 1, якщо непарна кількість одиничних бітів, 0 — якщо парна
}

// Функція для шифрування символів
void Shifruvanna(char S[64], unsigned short Rez[64]) {
    for (int i = 0; i < 64; i++) {
        unsigned short r = 0;
        char c = S[i];

        // Біт 0-3: Позиція символу в рядку (6 біт)
        r |= (i & 0x3F);

        // Біт 4-7: Старша частина ASCII-коду символу
        r |= ((c >> 4) & 0xF) << 4;

        // Біт 8: Парність для полів 0-7
        r |= (calculateParity(r & 0xFF) << 8);

        // Біт 9-12: Молодша частина ASCII-коду символу
        r |= (c & 0xF) << 9;

        // Біт 13-14: Позиція символу в рядку (2 біти)
        r |= ((i & 0x03) << 13);

        // Біт 15: Парність для полів 9-14
        r |= (calculateParity((r >> 8) & 0x7F) << 15);

        // Записуємо зашифрований символ в масив
        Rez[i] = r;
    }
}



int main() {
    char S[64] = {0};  // Масив для зберігання тексту
    unsigned short Rez[64];  // Масив для зашифрованих даних

    // Читання тексту з файлу
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    // Зчитуємо текст з файлу до 64 символів
    inputFile.get(S, 64);
    inputFile.close();

    // Доповнення рядків до 16 символів пробілами
    for (int i = 0; i < 64; i++) {
        if (S[i] == '\0') {
            S[i] = ' ';  // Якщо символ порожній, замінюємо його пробілом
        }
    }

    // Викликаємо функцію для шифрування
    Shifruvanna(S, Rez);

    // Виведення зашифрованих даних у шістнадцятковому форматі
    cout << "Зашифрований результат у шістнадцятковому форматі:" << endl;
    for (int i = 0; i < 64; i++) {
        cout << hex << Rez[i] << endl;
    }

    // Запис результату в бінарний файл
    ofstream outputFile("encrypted.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<char*>(Rez), sizeof(Rez));  // Записуємо зашифровані дані
    outputFile.close();

    cout << "Результат записано у файл 'encrypted.bin'." << endl;

    return 0;
}
