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
        if ((index >= -32) && (index <= -7)) index += 32; //выправляем заглавные буквы
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
        if ((index >= -32) && (index <= -7)) index += 32; //выправляем заглавные буквы
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

void Trie::removeKey(std::string& key)      //удаление слова из словаря, итеративная реализация на стеке
{
    if (root == NULL) return;                            //словарь пуст
    std::stack<TrieNode*> toDelete;                     //создали стек, куда положим узлы для удаления
    toDelete.push(root);
    TrieNode* triePtr = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; //выправляем заглавные буквы
        if (triePtr->children[index] == NULL) return;   //нет такого слова
        toDelete.push(triePtr->children[index]);            //добавляем символ в стек для удаления
        triePtr = triePtr->children[index];                 //движемся к следующему символу
    }
    if (triePtr->isEndOfWord == true) triePtr->isEndOfWord = false; //убираем метку конца слова
    if (isEmpty(triePtr) == false) return;               //если дальше что-то есть, то ничего не удаляем и выходим
    //если дальше пусто, то удаляем всё, что сложили в стек
    int k = key.length() - 1;
    triePtr = toDelete.top(); toDelete.pop();
    while (k >= 0)
    {
        //проверяем, является ли данный чилдрен концом какого-либо слова, и если нет, то
        if (triePtr->isEndOfWord == true) delete triePtr;     //удаляем чилдрена
        else break;                                          //если наткнулись на завершающий символ от другого слова, то выходим
        triePtr = toDelete.top();   //вытаскиваем следующего кандидата на удаление из стека
        toDelete.pop();             //вытаскивание из стека...
        int delSymbolIndex = key[k] - 'a';                                //выправляем заглавные буквы
        if ((delSymbolIndex >= -32) && (delSymbolIndex <= -7)) delSymbolIndex += 32; //выправляем заглавные буквы
        triePtr->children[delSymbolIndex] = NULL; //зануляем удаленного на предыдущей итерации чилдрена
        if (triePtr == root) break;      //если вытащили корень, то всё, хватит
        if (triePtr->isEndOfWord == true) break;     //если это конец другого слова, то тоже хватит
        k--;                        //идём на символ назад
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
    if (isEmpty(node) == true)   //Дошли до конца - возвращаемся
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)  //для заданной буквы проверяем все следующие буквы
    {
        if (node->children[i] != NULL)   //Если такой следующей буквы нет - идём к следующей по алфавиту следующей букве (извините за тавталогию)
        {
            currentLength++;                //увеличиваем длину слова на единицу
            word.push_back((char)(i + 'a'));    //Добавляем новую найденную букву в предполагаемое слово
            if (currentLength > maxLength)       //если длина слова превысила максимальную длину, то (см ниже)
            {
                if (!word.empty())   //сначала проверяем, не пусто ли слово
                {
                    word.erase(word.end() - 1); //если слово не пусто, то удаляем последний добавленный символ
                }
                currentLength--;    //уменьшаем длину слова и возвращаемся вверх по рекурсии
                return;
            }
            if (node->children[i]->isEndOfWord == true)  //если символ оказался завершающим
            {
                words.push_back(word);  //то добавляем составленное слово (а вернее окончание слова) в массив концов слов
            }
            getWordsInner(node->children[i], words, word, maxLength, currentLength); //и идём дальше, к следующей букве предполагаемого слова, вглубь рекурсии
            if (!word.empty())   //при выходе из очередного уровня рекурсии проверяем, не пусто ли слово, и если не пусто, то затираем последний символ
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
        if ((index >= -32) && (index <= -7)) index += 32; //выправляем заглавные буквы
        if (triePtr->children[index] == NULL) return;    //нет такого слова в словаре - не предлагаем ничего
        triePtr = triePtr->children[index];             //двигаемся до конца введенного полуслова
    }
    TrieNode* hwEnd = triePtr;  //запоминаем последнюю букву введенного полуслова

    //далее, начиная с текущего узла, то есть triePtr заполняем вектор words остатками слов word не длиннее, чем maxLength
    int currentLength = 0;
    std::string word;
    getWordsInner(triePtr, words, word, maxLength, currentLength);  //some recursive magik

    //вывод на экран
    //если часть слова сама по себе является полнцоенным словом, то добавляем его в список предлагаемых
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

            //реализация, успешно прошедшая все тесты на платформе
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

            //НИЖЕ ДРУГИЕ РЕАЛИЗАЦИИ, КОТОРЫЕ ВОЗНИКЛИ ВВИДУ МОЕГО НЕПРАВИЛЬНОГО ПОНИМАНИЯ ЧТО ЕСТЬ ПРЕФИКС ДЛЯ ДВУХ СЛОВ
            //ОДНО ИЗ КОТОРЫХ СОДЕРЖИТ ДРУГОЕ, Я ОБ ЭТОМ ПИСАЛ В СЛАК
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
    if (multiChildDetector == true) return; //если детектор разветвления сработал, то выходим из рекурсии и дальше ничего не проверяем

    int ctr = 0;
    int who;
    for (int i = 0; i < ALPHABET_SIZE; i++) //определяем, сколько наследников у текущей ноды
    {
        if (node->children[i] != nullptr)
        {
            who = i;        //запоминаем существующего наследник, чтобы потом второй раз по циклу не бегать
            ctr++;
        }
    }
    if (ctr >= 2)           // и если больше 1, то ставим детектор в тру
    {
        multiChildDetector = true;
        return;
    }
    if (ctr == 0) return;   //если наследников нет, то просто ретёрн. Детектор наследников остаётся как был, false

    //если всё-таки наследник есть, и он только один, то идём вглубь дальше, и проверяем ветвится ли уже наследник
    //помним, что он у нас записан в переменную int who
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
    if (node->isEndOfWord == true) count++; //добавил, чтобы текущая нода тоже считалась за слово (если она указывает на конец слова)
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

