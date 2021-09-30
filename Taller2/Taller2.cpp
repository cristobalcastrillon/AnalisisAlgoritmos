#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;

bool barajarRecursivo(vector<char> X, vector<char> Y, vector<char> Z);

bool barajarMemoizado (vector<char> X, vector<char>Y, vector<char> Z, char **aux, int indices[3]);

bool barajarBottomUp (vector<char> X, vector<char>Y, vector<char> Z);
int main(){
    vector<char> X;
    vector<char> Y;
    vector<char> Z;
    int indice[3] = {0, 0, 0};

    X.push_back('C');
    X.push_back('A');
    X.push_back('S');
    X.push_back('A');

    Y.push_back('C');
    Y.push_back('A');
    Y.push_back('R');
    Y.push_back('R');
    Y.push_back('O');

    Z.push_back('C');
    Z.push_back('C');
    Z.push_back('A');
    Z.push_back('R');
    Z.push_back('R');
    Z.push_back('A');
    Z.push_back('S');
    Z.push_back('O');
    Z.push_back('A');

    //Contiene las posiciones de Vector.
    char **miArray;
    miArray = new char *[X.size() + 1];
    for(int i = 0; i < X.size() + 1; i++)
    {
      miArray[i] = new char [Y.size() + 1];
    }

    // Pruebas:
    cout << barajarRecursivo(X, Y, Z) << endl;

    cout << barajarMemoizado(X, Y, Z, miArray, indice) << endl;

    cout << barajarBottomUp(X, Y, Z) << endl;
    for(int i = 0; i < X.size() + 1; i++)
    {
      delete miArray[i];
    }
    delete miArray;
}

bool barajarRecursivo(vector<char> X, vector<char> Y, vector<char> Z)
{
  // Invariante:
  // (la sumatoria de las cardinalidades de las secuencias X y Y debe ser igual a la cardinalidad de la secuencia Z)
  if(Z.size() != (X.size() + Y.size()))
    return false;

  // Caso base
  if(Z.size() == 0)
    return true;
  // Si el último elemento de X y de Y es igual al último elemento de Z, se debe...
  if (!X.empty() && !Y.empty())
  {
    if((Z[Z.size()-1] == X[X.size()-1]) && (Z[Z.size()-1] == Y[Y.size()-1]))
    {

      vector<char> nX = X, nY = Y, nZ = Z;
      nX.pop_back();
      nZ.pop_back();
      if (barajarRecursivo(nX, nY, nZ))
      {
         return true;
      }
      else
      {  
        nZ = Z;
        nX = X;
        nY.pop_back();
        nZ.pop_back();
        if (barajarRecursivo (nX, nY, nZ))
        {
        return true;
        }
      }
      
    }
  }

  if (!X.empty())
  {
    if(Z[Z.size()-1] == X[X.size()-1]){
      X.pop_back();
      Z.pop_back();
      return barajarRecursivo(X, Y, Z);
    }
  }

  if (!Y.empty())
  {
    if(Z[Z.size()-1] == Y[Y.size()-1]){
      Y.pop_back();
      Z.pop_back();
      return barajarRecursivo(X, Y, Z);
    }
  }
  
  return false;
}

bool barajarMemoizado (vector<char> X, vector<char>Y, vector<char> Z, char **aux, int indices[3])
{
  int n[3];
  for (int i = 0; i < 3; i++)
      n[i] = indices[i];

  if(Z.size() != (X.size() + Y.size()))
    return false;
 
  if((Z.size()) == indices[2])
    return true;
  
  //Si ya recorrio este camino, devuelve falso. No hay razon porque seguir.
  if(aux[indices[0]][indices[1]] == 'y')
    return false;
  
  aux[indices[0]][indices[1]] = 'y';
  
  //Entrar acá crea las ramas del arbol.
  //El peor caso es que siempre entré acá, creando O(2^n).
  if (indices[0] < X.size() && indices[1] < Y.size())
  {
    if (X[indices[0]] == Z[indices[2]] && Y[indices[1]] == Z[indices[2]])
    {
        n[2]++;
        n[0]++;
        if (barajarMemoizado(X, Y, Z, aux, n))
          return true;
        n[0]--;
        n[1]++; 
        if (barajarMemoizado(X, Y, Z, aux, n))
          return true;
    }
  }
  if (indices[0] < X.size())
  {
    if ((X[indices[0]] == Z[indices[2]])&& (Y[indices[1]] != Z[indices[2]]))
    {
      n[0]++;
      n[2]++;
      return barajarMemoizado (X, Y, Z, aux, n);
    }
  
  }
  if (indices[1] < Y.size())
  {
    if ((Y[indices[1]] == Z[indices[2]]) && (X[indices[0]] != Z[indices[2]]))
     {
       n[1]++;
       n[2]++;
       return barajarMemoizado (X, Y, Z, aux, n);
      }
  }
  return false;
}

bool barajarBottomUp (vector<char> X, vector<char>Y, vector<char> Z)
{
    char auxFork[X.size() + Y.size() + 1];
    int contX = 0, contY = 0, contAux = 0;
    for( int i = 0; i < (X.size() + Y.size()); i++)
    {
      if ((X[contX] == Z[i]) && (Y[contY] == Z[i]))
      {
        if ((Z[i + 1] == X[contX + 1] && Z[i + 1] == Y[contY + 1]))
        {
          contX++;
          contY++;
          contAux++;
        }
        else if (Z[i + 1] == Y[contY + 1])
        {
          contY ++;
          contX = contX - contAux;
          contAux = 0;
        }
        else if (Z[i + 1] == X[contX + 1])
        {
          contX ++;
          contY = contY - contAux;
          contAux = 0;
        }
        else if (X[contX] == Z[i + 1])
        {
          contX++;
        }
        else
        {
          return false;
        }

      }
      else if(X[contX] == Z[i])
      {
        contX++;
      }
      else if (Y[contY] == Z[i])
      {
        contY++;
      }
      else
      {
        return false;
      }
    }
    return true;
}

