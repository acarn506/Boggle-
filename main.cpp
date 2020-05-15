#include <iostream>
#include "Dictionary.cpp"

#define col 4
#define row 4
char Board[row][col];
int wordCount = 1;
char showBoard;

Dictionary myfDict("/Users/Acarn506/Desktop/C++/Data Structures/Prefix Tree/Prefix Tree/Dictionary.txt");
Dictionary emptyDict;

void clearPath(int newBoard[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newBoard[i][j] = 0;
        }
    }
}

void PrintBoard() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << ' ' << Board[i][j];  
        }
        cout << '\n';
    } 
} 

void printWord(string word, int wordPath[row][col]) {
    
    if (showBoard == 'n') {
        cout << "word: " << word << endl;
        cout << "Number of Words: " << wordCount++ << endl;
    }
    else {
        cout << "word: " << word << endl;
        cout << "Number of Words: " << wordCount++ << endl;

        PrintBoard();

        cout << '\n';
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << ' ' << wordPath[i][j];
            }
            cout <<"\n";
        }
        cout << "\n";
    }
}

void searchForWord(int r, int c, int h, int w, int visitPath[row][col], int wordPath[row][col], string curWord) 
{   
    visitPath[r][c] = -1;

    curWord += Board[r][c];
    wordPath[r][c] = curWord.length();

    if (myfDict.isPrefix(curWord)) {
        if (myfDict.isWord(curWord)) {
            if (emptyDict.isWord(curWord)) {
                wordPath[r][c] = 0;
                visitPath[r][c] = -1;
                return;
            }
            else {
                emptyDict.addWord(curWord);
                printWord(curWord, wordPath);
            }
        }
    } 

    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if (i >= 0 && j >= 0 && i < h && j < w && visitPath[i][j] != -1) {
                searchForWord(i, j, h, w, visitPath, wordPath, curWord);
            }
        }
    }

    curWord.erase(curWord.length() - 1);
    visitPath[r][c] = 0;
    wordPath[r][c] = 0;
}

void solveBoard() {
    int startRow ; 
    int startCol;
    int h = row; 
    int w = col;
    string curWord;

    int wordPath[row][col]; //tracks current word
    int visitPath[row][col]; //trakcs word path and already visted
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col ; j++)
        {
            startRow = i;
            startCol = j;
            searchForWord(startRow, startCol, h, w, visitPath, wordPath, curWord);
            clearPath(visitPath);
            clearPath(wordPath);
        }
    }
    

}

int main() {

    //read user board input
    cout << "\n";
    cout << "Enter Board" << endl;
    cout << "------------" << endl;
    for (int i = 0; i < row; i++) {
        cout << "Row " << i << ":" << endl;
        for (int j = 0; j < col; j++) {
            cin >> Board[i][j];
        }
    } 
    
    cout << "\n" << myfDict.wordCount() <<" words loaded \n" << endl;

    //print user board
    cout << "Enter Board" << endl;
    cout << "------------" << endl;
    for (int i = 0; i < row; i++) {
        cout << "Row " << i << ":";
        for (int j = 0; j < col; j++) {
            cout << ' ' << Board[i][j];  
        }
        cout << "\n";
    }
    cout << "\n";   

    cout << "Show Board (y/n)?: ";
    cin >> showBoard;
    
    solveBoard();
    
    return 0;
}
