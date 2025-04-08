#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

unsigned char parity4(unsigned char val) {
    val = val & 0xF;
    unsigned char count = 0;
    for (int i = 0; i < 4; ++i) {
        if (val & (1 << i)) count++;
    }
    return count % 2;
}

void encrypt() {
    std::ifstream infile("C:\\Users\\Dell\\Lab2.OOP2\\input.txt");
    std::ofstream outfile("\\Users\\Dell\\Lab2.OOP2\\out.bin", std::ios::binary);

    if (!infile || !outfile) {
        std::cerr << "Помилка при відкритті файлів.\n";
        return;
    }

    std::vector<std::string> lines(16);
    std::string temp;
    for (int i = 0; i < 16 && std::getline(infile, temp); ++i) {
        lines[i] = temp;
        lines[i].resize(4, ' '); // доповнюємо до 4 символів
    }

    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 4; ++col) {
            char ch = lines[row][col];
            unsigned char ascii = static_cast<unsigned char>(ch);

            unsigned short code = 0;

            unsigned char row_bits = row & 0xF;
            unsigned char ascii_high = (ascii >> 4) & 0xF;
            unsigned char p1 = parity4((row_bits << 4) | ascii_high);

            unsigned char ascii_low = ascii & 0xF;
            unsigned char col_bits = col & 0x3;
            unsigned char p2 = parity4((ascii_low << 2) | col_bits);

            code |= row_bits;                      // біти 0-3
            code |= (ascii_high << 4);             // біти 4-7
            code |= (p1 << 8);                     // біт 8
            code |= (ascii_low << 9);              // біти 9-12
            code |= (col_bits << 13);              // біти 13-14
            code |= (p2 << 15);                    // біт 15

            outfile.write(reinterpret_cast<char*>(&code), sizeof(code));

            std::bitset<16> bits(code);
            std::cout << bits << " ";
        }
        std::cout << '\n';
    }

    infile.close();
    outfile.close();
    std::cout << "\nШифрування завершено. Дані збережено в out.bin\n";
}

void decrypt() {
    std::ifstream infile("C:\\Users\\Dell\\Lab2.OOP2\\out.bin", std::ios::binary);
    std::ofstream outfile("C:\\Users\\Dell\\Lab2.OOP2\\decrypted.txt");

    if (!infile || !outfile) {
        std::cerr << "Помилка при відкритті файлів.\n";
        return;
    }

    std::vector<std::string> lines(16, std::string(4, ' '));
    unsigned short code;

    while (infile.read(reinterpret_cast<char*>(&code), sizeof(code))) {
        unsigned char row = code & 0xF;
        unsigned char ascii_high = (code >> 4) & 0xF;
        unsigned char ascii_low = (code >> 9) & 0xF;
        unsigned char col = (code >> 13) & 0x3;

        char ch = static_cast<char>((ascii_high << 4) | ascii_low);
        lines[row][col] = ch;
    }

    for (const auto& line : lines) {
        outfile << line << '\n';
    }

    infile.close();
    outfile.close();
    std::cout << "Дешифрування завершено. Результат збережено в decrypted.txt\n";
}

int main() {
    system("chcp 65001");
    std::cout << "Оберіть режим: (e - шифрування, d - дешифрування): ";
    char mode;
    std::cin >> mode;

    if (mode == 'e') {
        encrypt();
    } else if (mode == 'd') {
        decrypt();
    } else {
        std::cerr << "Невірний режим. Використовуйте 'e' або 'd'.\n";
    }

    return 0;
}


