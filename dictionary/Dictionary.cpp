#include "Dictionary.h"

int Dictionary::wordCount = 0;

Dictionary::Dictionary() {}

Dictionary::Dictionary(const Dictionary& other) : tree(other.tree) {}

void Dictionary::fillDictionary(const std::string& filename) {
    std::ifstream file(filename);
    std::string english, russian;
    
    while (std::getline(file, english) && std::getline(file, russian)) {
        addWord(english, russian);
    }
    file.close();
}
void Dictionary::addWord(const std::string& english, const std::string& russian) {
    if (!translate(english)) {
        wordCount++;
    }
    tree.insert(english, russian);
}

bool Dictionary::removeWord(const std::string& english) {
    if (tree.remove(english)) {
        wordCount--;
        return true;
    }
    return false;
}

std::string* Dictionary::translate(const std::string& english) {
    return tree.find(english);
}

int Dictionary::getWordCount() {
    return wordCount;
}

AVLTree& Dictionary::getTree() {
    return tree;
}