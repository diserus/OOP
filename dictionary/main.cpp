#include "Dictionary.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");
    
    Dictionary dict;
    dict.fillDictionary("ENRUS.TXT");
    
    std::cout << "Словарь загружен. Всего слов: " << dict.getWordCount() << std::endl;
    
    std::string word;
    
    while (true)
    {
        std::cout << "\nВведите слово для перевода (или ESC для выхода): ";
        std::getline(std::cin, word);
        

        if (word.empty() || word[0] == 27)
            break;
        
        std::string *translation = dict.translate(word);
        
        if (translation)
        {
            std::cout << "Перевод: " << *translation << std::endl;
        }
        else
        {
            std::cout << "Слово не найдено в словаре" << std::endl;
        }
    }


    std::cout << "\nОбход дерева:" << std::endl;
    printTree(dict.getTree());
    std::cout << "Программа завершена" << std::endl;
    return 0;
}