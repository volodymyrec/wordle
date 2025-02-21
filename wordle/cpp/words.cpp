//
//  words.cpp
//  wordle
//
//  Created by Володимир  on 07.02.2025.
//

#include "words.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Завантаження слів із файлу
vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);

    if (!file) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        if (word.length() == 5) {  // Тільки 5-літерні слова
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

// Вибір випадкового слова
string getRandomWord() {
    vector<string> words = loadWordsFromFile("words.txt");

    if (words.empty()) {
        cerr << "Помилка: Файл порожній або немає правильних слів!" << endl;
        exit(1);
    }

    srand(time(0));
    return words[rand() % words.size()];
}

// Вибір "Слова дня" (одне слово на день)
string getWordOfTheDay(const string& date) {
    vector<string> words = loadWordsFromFile("words.txt");

    if (words.empty()) {
        cerr << "Помилка: Файл порожній або немає правильних слів!" << endl;
        exit(1);
    }

    size_t index = stoi(date) % words.size();
    return words[index];
}
