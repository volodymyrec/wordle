//
//  game.cpp
//  wordle
//
//  Created by Володимир  on 07.02.2025.
//

#include "game.h"
#include "words.h"
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>

using namespace std;

// Функція порівняння слів (з урахуванням дублікатів)
void checkGuess(const string& secret, const string& guess) {
    string result = "*****";
    map<char, int> letterCount;

    // Підраховуємо кількість кожної літери у загаданому слові
    for (char c : secret) {
        letterCount[c]++;
    }

    // Перевіряємо правильні літери у правильних позиціях
    for (int i = 0; i < 5; ++i) {
        if (guess[i] == secret[i]) {
            result[i] = toupper(guess[i]);  // Велика літера, якщо правильно
            letterCount[guess[i]]--;        // Відмічаємо, що ця літера використана
        }
    }

    // Перевіряємо правильні літери у неправильних позиціях
    for (int i = 0; i < 5; ++i) {
        if (result[i] == '*') {  // Якщо буква ще не визначена
            if (letterCount[guess[i]] > 0) {
                result[i] = tolower(guess[i]);  // Маленька літера, якщо не на місці
                letterCount[guess[i]]--;
            }
        }
    }

    cout << result << endl;
}

// Функція отримання поточної дати у вигляді YYYYMMDD
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateStr[9];
    sprintf(dateStr, "%04d%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(dateStr);
}

// Функція перевірки, чи "Слово дня" вже відгадане
bool isWordOfTheDayGuessed(const string& date) {
    ifstream file("word_of_the_day.txt");
    string savedDate;
    if (file >> savedDate) {
        file.close();
        return savedDate == date;
    }
    return false;
}

// Функція збереження відгаданого "Слова дня"
void saveWordOfTheDay(const string& date) {
    ofstream file("word_of_the_day.txt");
    file << date;
    file.close();
}

// Гра зі звичайним або "Словом дня"
void playGame(bool isWordOfTheDay) {
    string date = getCurrentDate();
    string secret = isWordOfTheDay ? getWordOfTheDay(date) : getRandomWord();
    
    if (isWordOfTheDay && isWordOfTheDayGuessed(date)) {
        cout << "Слово дня вже було відгадане! Спробуйте звичайний режим." << endl;
        return;
    }

    string guess;
    int attempts = 0;
    cout << "Вгадайте слово з 5 літер!" << endl;

    while (true) {
        cout << "Введіть слово: ";
        cin >> guess;

        if (guess.length() != 5) {
            cout << "Слово має містити рівно 5 літер!" << endl;
            continue;
        }

        attempts++;
        checkGuess(secret, guess);

        if (guess == secret) {
            cout << "Вітаємо! Ви вгадали слово за " << attempts << " спроб(у/и)!" << endl;
            if (isWordOfTheDay) saveWordOfTheDay(date);
            break;
        }
    }
}
