#include <iostream>
#include <bitset>
#include <random>
#include <vector>

using uint8 = unsigned char;

void PrintBits(uint8 val, int bits) {
    for (int i = bits - 1; i >= 0; i--)
        std::cout << ((val >> i) & 1);
}

// Кодирование одного блока (4 бита -> 8 бит)
uint8 Encode(uint8 x) {
    uint8 x0 = (x >> 3) & 1;
    uint8 x1 = (x >> 2) & 1;
    uint8 x2 = (x >> 1) & 1;
    uint8 x3 = x & 1;

    return (x0 << 5) | (x1 << 3) | (x2 << 2) | (x3 << 1) |
           ((x0 ^ x1 ^ x3) << 7) |
           ((x0 ^ x2 ^ x3) << 6) |
           ((x1 ^ x2 ^ x3) << 4) |
           (x0 ^ x1 ^ x2);
}

// Вычисление синдрома
uint8 Syndrome(uint8 v) {
    uint8 b0 = (v >> 7) & 1;
    uint8 b1 = (v >> 6) & 1;
    uint8 b2 = (v >> 5) & 1;
    uint8 b3 = (v >> 4) & 1;
    uint8 b4 = (v >> 3) & 1;
    uint8 b5 = (v >> 2) & 1;
    uint8 b6 = (v >> 1) & 1;
    uint8 b7 = v & 1;

    return ((b3 ^ b4 ^ b5 ^ b6) << 3) |
           ((b1 ^ b2 ^ b5 ^ b6) << 2) |
           ((b0 ^ b2 ^ b4 ^ b6) << 1) |
           (b0 ^ b1 ^ b2 ^ b3 ^ b4 ^ b5 ^ b6 ^ b7);
}

// Декодирование одного блока
uint8 Decode(uint8 v) {
    uint8 syn = Syndrome(v);
    uint8 errPos = (syn & 0xE) >> 1;

    if (errPos != 0) {
        uint8 mask = 1 << (8 - errPos);
        return v ^ mask;
    }

    return v;
}

// Извлечение информации
uint8 Extract(uint8 u) {
    return ((u >> 5) & 1) << 3 |
           ((u >> 3) & 1) << 2 |
           ((u >> 2) & 1) << 1 |
           ((u >> 1) & 1);
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> disErr(0, 7);

    const int BLOCKS = 8;

    std::vector<uint8> original(BLOCKS);
    std::vector<uint8> encoded(BLOCKS);
    std::vector<uint8> errors(BLOCKS);
    std::vector<uint8> received(BLOCKS);
    std::vector<uint8> decoded(BLOCKS);
    std::vector<uint8> extracted(BLOCKS);

    std::cout << "========== МНОГОБЛОЧНАЯ ПЕРЕДАЧА КОДА ХЭММИНГА (8,4) ==========\n\n";

    // 1. Исходное сообщение
    for (int i = 0; i < BLOCKS; i++)
        original[i] = dis(gen) & 0xF;

    std::cout << "1) Исходное сообщение (4 бита): ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(original[i], 4);
        std::cout << " ";
    }

    // 2. Кодирование
    for (int i = 0; i < BLOCKS; i++)
        encoded[i] = Encode(original[i]);

    std::cout << "\n2) Закодированное сообщение (8 бит): ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(encoded[i], 8);
        std::cout << " ";
    }

    // 3. Ошибки
    for (int i = 0; i < BLOCKS; i++) {
        if (dis(gen) < 8)
            errors[i] = 1 << (7 - disErr(gen));
        else
            errors[i] = 0;
    }

    std::cout << "\n3) Вектор ошибок: ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(errors[i], 8);
        std::cout << " ";
    }

    // 4. Принятое сообщение
    for (int i = 0; i < BLOCKS; i++)
        received[i] = encoded[i] ^ errors[i];

    std::cout << "\n4) Принятое сообщение (с ошибками): ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(received[i], 8);
        std::cout << " ";
    }

    // 5. Декодирование
    for (int i = 0; i < BLOCKS; i++)
        decoded[i] = Decode(received[i]);

    std::cout << "\n5) Декодированное сообщение: ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(decoded[i], 8);
        std::cout << " ";
    }

    // 6. Извлечение
    for (int i = 0; i < BLOCKS; i++)
        extracted[i] = Extract(decoded[i]);

    std::cout << "\n6) Извлечённое сообщение (4 бита): ";

    for (int i = 0; i < BLOCKS; i++) {
        PrintBits(extracted[i], 4);
        std::cout << " ";
    }

    // 7. Статистика
    int correct = 0;

    std::cout << "\n\n========== РЕЗУЛЬТАТЫ ПРОВЕРКИ ==========\n";

    for (int i = 0; i < BLOCKS; i++) {
        if (original[i] == extracted[i]) {
            correct++;

            if (errors[i] != 0)
                std::cout << "Блок " << i + 1 << ": ошибка БЫЛА и ИСПРАВЛЕНА\n";
            else
                std::cout << "Блок " << i + 1 << ": ошибок НЕ БЫЛО\n";
        } else {
            std::cout << "Блок " << i + 1
                      << ": ОШИБКА НЕ ИСПРАВЛЕНА (двойная ошибка)\n";
        }
    }

    std::cout << "\nИТОГ: " << correct
              << " из " << BLOCKS
              << " блоков переданы верно\n";

    if (correct == BLOCKS)
        std::cout << "РЕЗУЛЬТАТ: ВСЕ ОШИБКИ УСПЕШНО ИСПРАВЛЕНЫ!\n";
    else
        std::cout << "РЕЗУЛЬТАТ: НЕКОТОРЫЕ ОШИБКИ НЕ ИСПРАВЛЕНЫ "
                     "(соответствует теории)\n";

    return 0;
}
