#include "Dictionary.HPP"
#include <iostream>
#include <fstream>

Dictionary::Dictionary() {
    root = nullptr;
    numWords = 0;
}

Dictionary::Dictionary(string file) {
    root = nullptr;
    numWords = 0;
    
    ifstream infile;
    string command;
    infile.open(file);
    
    if (!infile) {
        cout << "File not found!" << endl;
        exit(0);
    }
    
    infile >> command;
    while (command != "@") {
        addWord(command);
        infile >> command;
    }
   
    infile.close();
}

void Dictionary::addWord(string word) {
    
    if(!root){
        root = createNode();
    }
    
    Node * cur = root;
    int index;
    
    for (int i = 0; i < word.length(); i++) {
        index = word[i] - 'a';
        if (!cur->nodeArr[index]) {
            cur->nodeArr[index] = createNode();
        }
        cur = cur->nodeArr[index];
    }
    cur->flag = true;
    numWords++;
}

Node* Dictionary::createNode() {
    Node * newNode = new Node;
    
    newNode->flag = false;
    
    for (int i = 0; i < SIZE; i++) {
        newNode->nodeArr[i] = nullptr;
    }
    return newNode;
}

char Dictionary::convertChar(int index) {
    char letter = letters[index];
    return letter;
}

void Dictionary::PrintWords(string prefix) {
    Node *cur = root;
    for (int i = 0; i < prefix.length(); i++) {
        int index = prefix[i] - 'a';
        if (cur->nodeArr[index]) {
            cur = cur->nodeArr[index];
        }
    }
    
    if (!cur) {
        return;
    }
    else {
        for (int i = 0; i < prefix.length(); i++) {
            int index = prefix[i] - 'a';
            cout << convertChar(index);
        }
    }
}

int Dictionary::wordCount() {
    return numWords;
}

bool Dictionary::isPrefix(string word) {
    Node *cur = root;
    int index;
    
    for (int i = 0; i < word.length(); i++) {
        index = word[i] - 'a';
        if (cur->nodeArr[index]) {
            cur = cur->nodeArr[index];
        }
        else {
            return false;
        }
    }
    return true;
}

bool Dictionary::isWord(string word) {
    
    if (numWords == 0) {
        return false;
    }

    Node *cur = root;
    int index;
    
    for (int i = 0; i < word.length(); i++) {
        index = word[i] - 'a';
        if (cur->nodeArr[index]) {
            cur = cur->nodeArr[index];
        }
        else {
            return false;
        }
    }
    
    if (!cur) {
        return false;
    }
    else {
        return cur->flag;
    }
}

