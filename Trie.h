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
    bool isTrieEmpty();                     //���� �� �������
    void removeKey(std::string& key);      //��������� � ����������� �������, ��� ��� ��������
    void printEverything();                 //������� �������, ������� ������� ������ ��� �����, ������ ��� �������

    //�������
    void getWords(std::string& halfWord, const int maxLength);   //���������� ����� �� ��������� ��������� ����� �����, �������� ������� 14.10.1 (HW-04)

    void printShortest();                   //��� ������� ���������� ������� 14.8.2, �� ����� ����� ������ ��������� ����� �������� �����, � �� ��������

    //������� 14.8.2
    void findMinPrefixesWrapper();    //������ ��� ������� �� ������� 14.8.2, �.�. � ������ ��� ������������ � ���������� � ����� �-���������, � ����� �����
    bool isSingleThreadWrapper();                     //������ ������������� ��� ����� isSingleThread ��� ���������� �� ������
    int wordsCountWrapper();                            //������ ��� ����� wordsCount

private:
    bool isEmpty(TrieNode*& node);          //���� �� ���������� ����
    void printEverythingInner(TrieNode*& node, std::string& toPrint);

    //�������
    void getWordsInner(TrieNode*& node, std::vector<std::string>& words, std::string& word, const int maxLength, int& currentLength);

    void printShortestInner(TrieNode*& node, std::string& toPrint);

    //������� 14.8.2
    void findMinPrefixes(TrieNode* node, char buf[], int ind, std::string& res);    //������� 14.8.2 ��� ��� �������� � ������, �� ��� ���������� �� ������ ��� ��������� �������
    bool isSingleThread(TrieNode* node);  //��������������� �������, ������� ����������, �������� �� ������ �����, ������� �� ������� ����
    void isSingleThreadInner(TrieNode* node, bool& multiChildDetector); //������� ��� �������� isSingleThread
    int wordsCount(TrieNode* node);                         //��������������� �������, ������������ ���������� isEndOfWord == true ������� �� ������� ����
    void wordsCountInner(TrieNode* node, int& count);   //�������� ��� wordsCount


    TrieNode* root;
};
