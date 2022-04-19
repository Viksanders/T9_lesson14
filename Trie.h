#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    TrieNode()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
        }
        isEndOfWord = false;
        //std::cout << "TrieNode " << this << " created\n";
    }
    ~TrieNode()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (children[i] != NULL) delete children[i];
        }
        //std::cout << "TrieNode " << this << " deleted\n";
    }

    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie
{
public:
    Trie();
    ~Trie();
    void insert(std::string& key);
    bool search(std::string& key);
    bool isTrieEmpty();                     //Пуст ли словарь
    void removeKey(std::string& key);      //Переделал в итеративную функцию, мне так понятнее
    void printEverything();                 //добавил функцию, которая выводит вообще все слова, удобно для отладки

    //ДОМАШКА
    void getWords(std::string& halfWord, const int maxLength);   //предлагает слова по введенной начальной части слова, домашнее задание 14.10.1 (HW-04)

    void printShortest();                   //Мой вариант выполнения задания 14.8.2, по факту здесь просто выводятся самые короткие слова, а не префиксы

    //ЗАДАНИЕ 14.8.2
    void findMinPrefixesWrapper();    //Обёртка для функции по заданию 14.8.2, т.к. в модуле оно предлагается к реализации в стиле С-программы, а здесь класс
    bool isSingleThreadWrapper();                     //обёртка исключительно для теста isSingleThread при реализации на классе
    int wordsCountWrapper();                            //обёртка для теста wordsCount

private:
    bool isEmpty(TrieNode*& node);          //пуст ли конкретный узел
    void printEverythingInner(TrieNode*& node, std::string& toPrint);

    //ДОМАШКА
    void getWordsInner(TrieNode*& node, std::vector<std::string>& words, std::string& word, const int maxLength, int& currentLength);

    void printShortestInner(TrieNode*& node, std::string& toPrint);

    //ЗАДАНИЕ 14.8.2
    void findMinPrefixes(TrieNode* node, char buf[], int ind, std::string& res);    //Задание 14.8.2 как оно задумано в модуле, но для реализации на классе это внутрення функция
    bool isSingleThread(TrieNode* node);  //вспомогательная функция, которая определяет, ветвится ли дальше слово, начиная от текущей ноды
    void isSingleThreadInner(TrieNode* node, bool& multiChildDetector); //функция для рекурсии isSingleThread
    int wordsCount(TrieNode* node);                         //вспомогательная функция, подсчитывает количество isEndOfWord == true начиная от текущей ноды
    void wordsCountInner(TrieNode* node, int& count);   //рекурсия для wordsCount


    TrieNode* root;
};
