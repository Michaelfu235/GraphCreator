#include <iostream>
#include <cstring>
#include <iomanip>
#include <ios>
#include <algorithm>

using namespace std;

class graph{
public:
  int g[20][20];
  char vertices[20];
  int numV;

  graph(){
    numV = 0;
    for(int i = 0;i<20;i++){
      for(int j = 0;j<20;j++){
	g[i][j] = 0;
      }
    }
    
    
  }

  void display(){
    cout << "adjacency table:" << endl;
    cout << "Vertices:" << endl;
    cout << endl;
    for(int i = 0;i<numV;i++){
      cout << setw(4);
      cout << vertices[i];
    }
    cout << endl;
    cout << endl;

    for(int i = 0;i<numV;i++){
      for(int j = 0;j<numV;j++){
	cout << setw(4);
	cout << g[i][j];
      }
      cout << endl;
    }
    cout << endl;
  }

  void addVertex(char name){
    for(int i = 0;i<20;i++){
      if(vertices[i]==name){
	cout << "this name is already in use" << endl;
	return;
      } else{
	vertices[numV] = name;
	numV++;
	cout << "verticie has been added" << endl;
	return;
      }
    }
  }

  void removeVertex(char name){
    int index = -1;
    for(int i = 0;i<numV;i++){
      if(vertices[i] == name){
	index = i;
      }
    }
    if(index == -1){
      cout << "vertex not found" << endl;
      return;
    }
    for(int i = index;i<numV-1;i++){
      vertices[i] = vertices[i+1];
      for(int j = 0;j<numV;j++){
	g[i][j] = g[i+1][j];
	g[i+1][j] = 0;
      }
    }
    vertices[numV-1] = '\0';
    numV--;

    for(int i = index; i < numV; i++) {
      for(int j = 0; j < numV; j++) { 
	g[j][i] = g[j][i+1];
	g[j][i+1] = 0;
      }
    }
    //    numV--;
    /*
    for(int i = 0;i<numV;i++){
      g[i][index] = 0;
      }*/
    cout << name << " is removed." << endl;
  }

  void addEdge(char v1, char v2, int weight){
    int v1Index = -1;
    int v2Index = -1;
    for(int i = 0;i<numV;i++){
      if(vertices[i] == v1){
	v1Index = i;
      }
      if(vertices[i] == v2){
	v2Index = i;
      }
    }

    if(v1Index != -1 && v2Index != -1){
      g[v1Index][v2Index] = weight;
      cout << "edge added" << endl;
    } else if(v1Index == v2Index){
      cout << "edge can't be added between the same verticie" << endl;
    } else {
      cout << "edge doesn't exist" << endl;
    }
  }

  void removeEdge(char a, char b){
    int v1 = -1;
    int v2 = -1;
    for(int i = 0;i<numV;i++){
      if(vertices[i]==a){
        v1 = i;
      }
      if(vertices[i]==b){
        v2 = i;
      }
    }

    if(v1 == -1 || v2 == -1){
      cout << "one or more of the verticies does not exist" << endl;
      return;
    }
    if(g[v1][v2] == 0){
      cout << "edge doesn't exist between verticies" << endl;
      return;
    }
    g[v1][v2] = 0;

    cout << "edge removed" << endl;

    
  }


  
};

int main(){
  graph g;
  bool justKeepGoing = true;
  char inputt[20];

  while(justKeepGoing){
    cout << "--------------------------------------" << endl;
    g.display();

    cout << "add verticie (AV), add edge (AE), remove verticie (RV), remove edge (RE), find shortest path (F), or quit (Q)." << endl;
    cin.get(inputt, 20, '\n');
    cin.ignore();

    if(strcmp(inputt, "AV")==0){
      char name;
      cout << "enter name (1 character, like A, B, etc.)" << endl;
      cin >> name;
      cin.ignore();

      g.addVertex(name);
    } else if (strcmp(inputt, "AE")==0){
      char v1, v2;
      int weight;

      cout << "enter starting vertex: ";
      cin >> v1;
      cin.ignore();
      cout << "enter ending vertex: ";
      cin >> v2;
      cin.ignore();
      cout << "enter edge weight: ";
      cin >> weight;
      cin.ignore();
      
      g.addEdge(v1, v2, weight);
    } else if (strcmp(inputt, "RV")==0){
      char vname;
      cout << "insert name of verticie you would like to delete" << endl;
      cin >> vname;
      cin.ignore();

      g.removeVertex(vname);
    } else if (strcmp(inputt, "RE")==0){
      char v1, v2;

      cout << "starting verticie?" << endl;
      cin >> v1;
      cin.ignore();
      cout << "ending verticie?" << endl;
      cin >> v2;
      cin.ignore();

      g.removeEdge(v1, v2);
    } else if (strcmp(inputt, "Q")==0){
      justKeepGoing = false;
    }
    
  }
}
