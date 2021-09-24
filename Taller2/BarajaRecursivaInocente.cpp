#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h> 

using namespace std;

vector<char> barajar(queue<char> X, queue<char> Y);
vector<char> barajarAux(queue<char> X, queue<char> Y, vector<char> Z);

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

    Z = barajar(X, Y);
    for(vector<char>::iterator it = Z.begin(); it != Z.end(); ++it){
      cout << *it;
    }
    cout << '\n';
}

vector<char> barajar(queue<char> X, queue<char> Y){
    vector<char> Z;
    return barajarAux(X, Y, Z);
}

vector<char> barajarAux(queue<char> X, queue<char> Y, vector<char> Z){
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
    return barajarAux(X, Y, Z); 
}