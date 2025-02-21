//
//  main.cpp
//  wordle
//
//  Created by Володимир  on 07.02.2025.
//

#include "game.h"
#include <iostream>

using namespace std;

int main() {
    while (true) {
        cout << "Оберіть режим:\n";
        cout << "1 - Звичайна гра\n";
        cout << "2 - Слово дня\n";
        cout << "0 - Вийти\n";
        cout << "Ваш вибір: ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            playGame(false);
        } else if (choice == 2) {
            playGame(true);
        } else if (choice == 0) {
            break;
        } else {
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    }
    
    return 0;
}
