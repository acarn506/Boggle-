#include <string>
#include <iostream>
using namespace std;

const int SIZE = 26;

struct Node {
    Node * nodeArr[SIZE];
    bool flag;
};

class Dictionary {

public:
Dictionary();
Dictionary(string file);
void addWord(string word);
bool isWord(string word);
bool isPrefix(string word);
void PrintWords(string prefix);
int wordCount();
    
private:
    Node * root;
    int numWords;
    Node* createNode();
    char letters[SIZE] = {'a','b','c','d','e','f','g','h','i',
                        'j','k','l','m','n','o','p','q','r',
                        's','t','u','v','w','x','y','z'};
    char convertChar(int index);
};  