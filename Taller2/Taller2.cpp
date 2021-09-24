#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h> 

using namespace std;

vector<char> barajarRecursivo(queue<char> X, queue<char> Y, vector<char> Z);

int main(){
    vector<char> Z;

    queue<char> X;
    queue<char> Y;

    X.push('C');
    X.push('A');
    X.push('S');
    X.push('A');

    Y.push('C');
    Y.push('A');
    Y.push('R');
    Y.push('R');
    Y.push('O');

    Z = barajarRecursivo(X, Y, Z);
    for(vector<char>::iterator it = Z.begin(); it != Z.end(); ++it){
      cout << *it;
    }
    cout << '\n';
}

vector<char> barajarRecursivo(queue<char> X, queue<char> Y, vector<char> Z){
    if(X.empty() && Y.empty()){
        return Z;
    }
    else{
        int selection = rand() % 2;
        //cout << "Rand: " << selection << endl;
        if(selection == 0 && !X.empty()){
            Z.push_back(X.front());
            //cout << "Pushed back to Z" << endl;
            X.pop();
            //cout << "Popped from X" << endl;
        }
        if(selection == 1 && !Y.empty()){
            Z.push_back(Y.front());
            //cout << "Pushed back to Z" << endl;
            Y.pop();
            //cout << "Popped from Y" << endl;
        }
    }
    return barajarRecursivo(X, Y, Z); 
}