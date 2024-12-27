/* PROCEDURE */
// STEP (1) - read input into string variable "input".
// STEP (2) - read the string variable character by character.
// STEP (2a) - if the current character is a number, push it to stack "S" and create a new null tree.
// STEP (2b) - if the current character is an operator, pop the top 2 number in the stack 
//   and push a new tree (with the two trees as the branches) to the stack.
// STEP (3) - display the tree via in-order traversal.
// STEP (3a) - if the currently-displayed tree's data is not a number, 
//   add brackets to the display before the next tree.

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Tree {
private:
    char data;
    Tree *Left, *Right;

public:
    Tree(char d, Tree *L, Tree *R) {
        data = d;
        Left = L;
        Right = R;
    }
    ~Tree() { };
    char getData() { return data; };
    Tree* getLeft() { return Left; }
    Tree* getRight() { return Right; }
};

void inOrder(Tree *T);

int main() {
    stack<Tree*> S;
    int stringlength;
    Tree* temp[2];
    string input;
    Tree *null = NULL;
    Tree *T;
    int i; // index.
    /* --- STEP (1) --- */
    getline(cin, input);
    stringlength = input.length();
    /* --- STEP (2) --- */
    for (i = 0; i < stringlength; i++) {
        if ((input[i] >= '0') && (input[i] <= '9')) {
            /* --- STEP (2a) --- */
            S.push(new Tree(input[i], null, null));
        } else if ((input[i] == '+') || (input[i] == '-')
            || (input[i] == '*') || (input[i] == '/')) {
            /* --- STEP (2b) --- */
            temp[0] = S.top();
            S.pop();
            temp[1] = S.top();
            S.pop();
            S.push(new Tree(input[i], temp[1], temp[0]));
        }
        T = S.top();
    }
    /* --- STEP (3) --- */
    inOrder(T);
}

void inOrder(Tree *T) {
    if (T == NULL) {
        return;
    }
    if ((T->getData() < '0') || (T->getData() > '9')) {
        /* STEP (3a) */
        cout << "(";
    }
    inOrder(T->getLeft());
    cout << T->getData();
    inOrder(T->getRight());
    if ((T->getData() < '0') || (T->getData() > '9')) {
        /* STEP (3a) */
        cout << ")";
    }
}