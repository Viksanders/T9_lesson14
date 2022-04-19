#include "Trie.h"

Trie::Trie()
{
    root = new TrieNode;
}

Trie::~Trie()
{
    delete root;
}

void Trie::insert(std::string& key)
{
    TrieNode* triePtr = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; //���������� ��������� �����
        if (triePtr->children[index] == NULL) triePtr->children[index] = new TrieNode;
        triePtr = triePtr->children[index];
    }
    triePtr->isEndOfWord = true;
}

bool Trie::search(std::string& key)
{
    TrieNode* triePtr = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; //���������� ��������� �����
        if (triePtr->children[index] == NULL) return false;
        triePtr = triePtr->children[index];
    }
    return ((triePtr != NULL) && (triePtr->isEndOfWord == true));
}

bool Trie::isTrieEmpty()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL) return false;
    }
    return true;
}

bool Trie::isEmpty(TrieNode*& node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL) return false;
    }
    return true;
}

void Trie::removeKey(std::string& key)      //�������� ����� �� �������, ����������� ���������� �� �����
{
    if (root == NULL) return;                            //������� ����
    std::stack<TrieNode*> toDelete;                     //������� ����, ���� ������� ���� ��� ��������
    toDelete.push(root);
    TrieNode* triePtr = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; //���������� ��������� �����
        if (triePtr->children[index] == NULL) return;   //��� ������ �����
        toDelete.push(triePtr->children[index]);            //��������� ������ � ���� ��� ��������
        triePtr = triePtr->children[index];                 //�������� � ���������� �������
    }
    if (triePtr->isEndOfWord == true) triePtr->isEndOfWord = false; //������� ����� ����� �����
    if (isEmpty(triePtr) == false) return;               //���� ������ ���-�� ����, �� ������ �� ������� � �������
    //���� ������ �����, �� ������� ��, ��� ������� � ����
    int k = key.length() - 1;
    triePtr = toDelete.top(); toDelete.pop();
    while (k >= 0)
    {
        //���������, �������� �� ������ ������� ������ ������-���� �����, � ���� ���, ��
        if (triePtr->isEndOfWord == true) delete triePtr;     //������� ��������
        else break;                                          //���� ���������� �� ����������� ������ �� ������� �����, �� �������
        triePtr = toDelete.top();   //����������� ���������� ��������� �� �������� �� �����
        toDelete.pop();             //������������ �� �����...
        int delSymbolIndex = key[k] - 'a';                                //���������� ��������� �����
        if ((delSymbolIndex >= -32) && (delSymbolIndex <= -7)) delSymbolIndex += 32; //���������� ��������� �����
        triePtr->children[delSymbolIndex] = NULL; //�������� ���������� �� ���������� �������� ��������
        if (triePtr == root) break;      //���� �������� ������, �� ��, ������
        if (triePtr->isEndOfWord == true) break;     //���� ��� ����� ������� �����, �� ���� ������
        k--;                        //��� �� ������ �����
    }
}

void Trie::printShortestInner(TrieNode*& node, std::string& toPrint)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            toPrint.push_back((char)(i + 'a'));
            if (node->children[i]->isEndOfWord == true)
            {
                std::cout << toPrint << " ";
                //toPrint.clear();
                if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
                return;
            }
            printShortestInner(node->children[i], toPrint);
            if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
        }
    }
}

void Trie::printShortest()
{
    std::string toPrint;
    printShortestInner(root, toPrint);
    std::cout << "\n";
}

void Trie::printEverythingInner(TrieNode*& node, std::string& toPrint)
{
    if (isEmpty(node) == true)
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            toPrint.push_back((char)(i + 'a'));
            if (node->children[i]->isEndOfWord == true)
            {
                std::cout << toPrint << " ";
            }
            printEverythingInner(node->children[i], toPrint);
            if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
        }
    }
}

void Trie::printEverything()
{
    std::string str;
    printEverythingInner(root, str);
    std::cout << "\n";
}

void Trie::getWordsInner(TrieNode*& node, std::vector<std::string>& words, std::string& word, const int maxLength, int& currentLength)
{
    if (isEmpty(node) == true)   //����� �� ����� - ������������
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)  //��� �������� ����� ��������� ��� ��������� �����
    {
        if (node->children[i] != NULL)   //���� ����� ��������� ����� ��� - ��� � ��������� �� �������� ��������� ����� (�������� �� ����������)
        {
            currentLength++;                //����������� ����� ����� �� �������
            word.push_back((char)(i + 'a'));    //��������� ����� ��������� ����� � �������������� �����
            if (currentLength > maxLength)       //���� ����� ����� ��������� ������������ �����, �� (�� ����)
            {
                if (!word.empty())   //������� ���������, �� ����� �� �����
                {
                    word.erase(word.end() - 1); //���� ����� �� �����, �� ������� ��������� ����������� ������
                }
                currentLength--;    //��������� ����� ����� � ������������ ����� �� ��������
                return;
            }
            if (node->children[i]->isEndOfWord == true)  //���� ������ �������� �����������
            {
                words.push_back(word);  //�� ��������� ������������ ����� (� ������ ��������� �����) � ������ ������ ����
            }
            getWordsInner(node->children[i], words, word, maxLength, currentLength); //� ��� ������, � ��������� ����� ��������������� �����, ������ ��������
            if (!word.empty())   //��� ������ �� ���������� ������ �������� ���������, �� ����� �� �����, � ���� �� �����, �� �������� ��������� ������
            {
                word.erase(word.end() - 1);
                currentLength--;
            }
        }   //end if(node->children[i] != NULL)
    }
}

void Trie::getWords(std::string& halfWord, const int maxLength)
{
    TrieNode* triePtr = root;
    std::vector<std::string> words;
    for (size_t i = 0; i < halfWord.size(); i++)
    {
        int index = halfWord[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; //���������� ��������� �����
        if (triePtr->children[index] == NULL) return;    //��� ������ ����� � ������� - �� ���������� ������
        triePtr = triePtr->children[index];             //��������� �� ����� ���������� ���������
    }
    TrieNode* hwEnd = triePtr;  //���������� ��������� ����� ���������� ���������

    //�����, ������� � �������� ����, �� ���� triePtr ��������� ������ words ��������� ���� word �� �������, ��� maxLength
    int currentLength = 0;
    std::string word;
    getWordsInner(triePtr, words, word, maxLength, currentLength);  //some recursive magik

    //����� �� �����
    //���� ����� ����� ���� �� ���� �������� ����������� ������, �� ��������� ��� � ������ ������������
    if (hwEnd->isEndOfWord == true) std::cout << halfWord << "\n";
    for (size_t i = 0; i < words.size(); i++)
    {
        std::cout << halfWord + words[i] << "\n";
    }
}

void Trie::findMinPrefixesWrapper()
{
    char buf[ALPHABET_SIZE];
    std::string res;
    int ind = 0;
    TrieNode* node = root;
    findMinPrefixes(node, buf, ind, res);
    std::cout << "\n" << res << "\n";
}

void Trie::findMinPrefixes(TrieNode* node, char buf[], int ind, std::string& res)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            buf[ind] = (char)(i + 'a');
            buf[ind + 1] = '\0';
            ind++;

            //����������, ������� ��������� ��� ����� �� ���������
            if ((isSingleThread(node->children[i]) == true) && (wordsCount(node->children[i]) == 1))
            {
                res += buf;
                res += " ";
                ind--;
            }
            else
            {
                findMinPrefixes(node->children[i], buf, ind, res);
                ind--;
            }

            //���� ������ ����������, ������� �������� ����� ����� ������������� ��������� ��� ���� ������� ��� ���� ����
            //���� �� ������� �������� ������, � �� ���� ����� � ����
            /*/
            if ( (isSingleThread(node->children[i]) == true) || (node->children[i]->isEndOfWord == true) )
            {
                res += buf;
                res += " ";
                ind--;
            }
            else
            {
                findMinPrefixes(node->children[i], buf, ind, res);
                ind--;
            }
            //*/

            /*
            if ((isSingleThread(node->children[i]) == true) && (wordsCount(node->children[i]) == 1))
            {
                res += buf;
                res += " ";
                ind--;
            }
            else if (node->children[i]->isEndOfWord == true)
            {
                res += buf;
                res += " ";
                ind--;
            }
            else
            {
                findMinPrefixes(node->children[i], buf, ind, res);
                ind--;
            }
            //*/

            /*
            if (node->children[i]->isEndOfWord == true)
            {
                res += buf;
                res += " ";
                if (isEmpty(node->children[i]))  ind--;
                else
                {
                    findMinPrefixes(node->children[i], buf, ind, res);
                    ind--;
                }
            }
            else if ((isSingleThread(node->children[i]) == true) && (wordsCount(node->children[i]) == 1))
            {
                res += buf;
                res += " ";
                ind--;
            }
            else
            {
                findMinPrefixes(node->children[i], buf, ind, res);
                ind--;
            }
            //*/
        }
    }
}

void Trie::isSingleThreadInner(TrieNode* node, bool& multiChildDetector)
{
    if (multiChildDetector == true) return; //���� �������� ������������ ��������, �� ������� �� �������� � ������ ������ �� ���������

    int ctr = 0;
    int who;
    for (int i = 0; i < ALPHABET_SIZE; i++) //����������, ������� ����������� � ������� ����
    {
        if (node->children[i] != nullptr)
        {
            who = i;        //���������� ������������� ���������, ����� ����� ������ ��� �� ����� �� ������
            ctr++;
        }
    }
    if (ctr >= 2)           // � ���� ������ 1, �� ������ �������� � ���
    {
        multiChildDetector = true;
        return;
    }
    if (ctr == 0) return;   //���� ����������� ���, �� ������ �����. �������� ����������� ������� ��� ���, false

    //���� ��-���� ��������� ����, � �� ������ ����, �� ��� ������ ������, � ��������� �������� �� ��� ���������
    //������, ��� �� � ��� ������� � ���������� int who
    //std::cout << (char)(who + 'a') << "\n";   //dbg
    isSingleThreadInner(node->children[who], multiChildDetector);
}

bool Trie::isSingleThread(TrieNode* node)
{
    bool multiChildDetector = false;
    isSingleThreadInner(node, multiChildDetector);
    return !multiChildDetector;
}

bool Trie::isSingleThreadWrapper()
{
    return !isSingleThread(root);
}

int Trie::wordsCountWrapper()
{
    return wordsCount(root);
}

int Trie::wordsCount(TrieNode* node)
{
    int count = 0;
    if (node->isEndOfWord == true) count++; //�������, ����� ������� ���� ���� ��������� �� ����� (���� ��� ��������� �� ����� �����)
    wordsCountInner(node, count);
    return count;
}

void Trie::wordsCountInner(TrieNode* node, int& count)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            if (node->children[i]->isEndOfWord == true)
            {
                count++;
            }
            wordsCountInner(node->children[i], count);
        }
    }
}

