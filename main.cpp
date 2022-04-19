#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>
#include "Trie.h"


int main()
{
    setlocale(LC_ALL, "");
    Trie TR;
    std::string a = "home";
    std::string b = "hold";
    std::string c = "hell";
    std::string d = "hello";
    std::string e = "hey";
    std::string f = "heyaaaaaaaaaaaa";
    std::string g = "bus";
    std::string h = "busstation";
    std::string i = "bussy";
    std::string j = "busz";
    std::string str1 = "apple";
    std::string str2 = "appreciate";
    std::string str3 = "application";
    std::string str4 = "aprove";
    std::string str5 = "apricot";
    std::string str6 = "AppLication";   //�������� �� ������ ��������, ������� ���� ������������������ � ��������
    TR.insert(a); TR.insert(b); TR.insert(c); TR.insert(d); TR.insert(e); TR.insert(f);
    TR.insert(g); TR.insert(h); TR.insert(i); TR.insert(j);
    TR.insert(str1); TR.insert(str2); TR.insert(str3); TR.insert(str4); TR.insert(str5);
    
    //���������� ��������� �������
    int max_letters = 5;    //���������� ����� ���������� ����, ������� ��������� � ��������� ����� (��� ����� �� �������� ������� ������� ����� �� ����� ��������� �����)
    std::cout << "��������� ���������� ��������� �������� ���� �� ������� �� ��������� ������\n";
    std::cout << "��� ���� ��� ������ ���������� max_letters (��. �������� ���) ����� ������, ��������� ������� ����� ����� ����������\n";
    std::cout << "�� ������� ������ ��������� �����, ����� ������ ��������� ����� + ��� " << max_letters << " ����" << "\n";
    std::cout << "��������� ����� � �������:\n\n";
    TR.printEverything();
    std::cout << "\n��� ������ �� ��������� ������� -1\n";
    std::string input;

    while (1)
    {
        std::cout << "������� ����� ��� ��� ������: ";
        std::getline(std::cin,input);
        if (input == "-1") break;
        TR.getWords(input, max_letters);
    }

    std::cout << "The end!\n";




    //����� ���� ������������ ���������� ������� �������� (����������� ���������� �� �����) � ��������� ����� �9
    /*
    
    std::cout << "ALL WORDS: \n";
    TR.printEverything();
    std::cout << "Now shortest: \n";
    TR.printShortest();
    std::cout << "Now shortest 2: \n";
    TR.findMinPrefixesWrapper();

    std::cout << "T9 goes next\n";
    std::string he = "ap";
    TR.getWords(he, 15);
    std::cout << "\nNOW REMOVING THE WORD " << str6 << "\n";
    TR.removeKey(str6);
    TR.printEverything();
    std::cout << "\nNOW REMOVING THE WORD " << h << "\n";
    TR.removeKey(h);
    TR.printEverything();
    TR.getWords(he, 15);
    //*/

    
    //������ ������-������ �������� ��� ��� �������������� ������
    /*
    std::string abc = "abc"; std::string abcb = "abcb"; std::string aabc = "aabc"; std::string abcd = "abcd"; std::string qwerty = "qwerty";
    TR.insert(abc);
    TR.insert(abcb);
    TR.insert(qwerty);

    TR.printEverything();
    TR.printShortest();

    std::cout << "Removing...\n";
    TR.removeKey(abc);

    TR.printEverything();
    TR.printShortest();

    std::cout << "is abc here? " << TR.search(abc) << "\n";
    std::cout << "is abcb here? " << TR.search(abcb) << "\n";
    std::cout << "is qwerty here? " << TR.search(qwerty) << "\n";

    std::cout << "Removing...\n";
    TR.removeKey(qwerty);

    TR.printEverything();
    TR.printShortest();

    std::cout << "is abc here? " << TR.search(abc) << "\n";
    std::cout << "is abcb here? " << TR.search(abcb) << "\n";
    std::cout << "is qwerty here? " << TR.search(qwerty) << "\n";

    TR.removeKey(abcb);
    TR.insert(aabc);
    TR.printEverything();
    //*/


    

    //��� ��� ������� 14.8.2

    //Trie TR2_test;

    /*
    std::string one = "a";
    std::string two = "answer";
    std::string three = "hero";
    std::string four = "heroplane";
    std::string five = "the";
    //*/

    /*
    std::string one = "cat";
    std::string two = "call";
    std::string three = "cult";
    std::string four = "run";
    std::string five = "rut";
    //*/

    /*
    std::string one = "dog";
    std::string two = "dot";
    std::string three = "dove";
    std::string four = "duck";
    std::string five = "zebra";
    //*/

    /*
    TR2_test.insert(one); TR2_test.insert(two); TR2_test.insert(three); TR2_test.insert(four); TR2_test.insert(five);
    TR2_test.printEverything();
    //std::cout << TR2_test.isSingleThreadWrapper() << "\n";
    //std::cout << TR2_test.wordsCountWrapper() << "\n";
    TR2_test.findMinPrefixesWrapper();

    //*/




    return 0;
}
