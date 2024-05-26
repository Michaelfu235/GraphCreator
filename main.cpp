#include <iostream>
#include <cstring>
#include <iomanip>
#include <ios>
#include <algorithm>
#include <climits>

using namespace std;

class graph{
public:
  //2d lsit of edges, and a list of the verticies, with initialization function
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

  //function to display the list of vertices, along with the 2d list of edge lengths
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

  //add vertex, with the name and add 1 to the numV
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

  //for the remove vertex, if the vertex exists, remove it's row from the 2d list, and it's column and subtract 1 from numV. 
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

  //to add the edge, check if both veerticies exist and then changing the corect value in the 2d list
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

  //to remove the edge, check if the two verticies exist and then remove the appropiate value from the 2d list
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

  //dijkistrias algorithm to find the shortest path from one vertex to another
  void Dij(char start, char end){
    int v1 = -1;
    int v2 = -1;
    for(int i = 0;i<numV;i++){
      if(vertices[i] == start){
        v1 = i;
      }
      if(vertices[i] == end){
        v2 = i;
      }
    }

    if(v1 == -1 || v2 == -1){
      cout << "one or more of the verticies doesn't exist." << endl;
      return;
    }

    int dist[20];
    int prev[20];
    bool visited[20];

    for(int i = 0;i<numV;i++){
      dist[i] = INT_MAX;
      prev[i] = -1;
      visited[i] = false;
    }

    dist[v1] = 0;

    for(int count = 0;count < numV-1;count++){
      int minD = INT_MAX;
      int minIndex = -1;

      for(int i = 0;i<numV;i++){
        if(visited[i] == false && dist[i] < minD){
          minD = dist[i];
          minIndex = i;
        }
      }

      visited[minIndex] = true;

      for(int i = 0;i<numV;i++){
        if(visited[i] == false && g[minIndex][i] != 0 && dist[minIndex] != INT_MAX && dist[minIndex] + g[minIndex][i] < dist[i]){
          dist[i] = dist[minIndex] + g[minIndex][i];
          prev[i] = minIndex;
        }
      }
    }

    if(dist[v2] == INT_MAX || dist[v2]==INT_MIN || dist[v2]==-2119027900){
      cout << "No path exists between the 2 verticecs" << endl;
      return;
    }

    int path[20];
    int pathSize = 0;
    int currentVertex = v2;

    while(currentVertex != -1){
      path[pathSize] = currentVertex;
      currentVertex = prev[currentVertex];
      pathSize++;
    }

    cout << "shortest path from " << vertices[v1] << " to " << vertices[v2] << ":" << endl;
    for(int i = pathSize-1;i>=0;i--){
      cout << vertices[path[i]];
      if(i != 0){
        cout << " -> ";
      }
    }
    cout << endl;
    cout << "Total distance is " << dist[v2] << endl;

  }



  
};

int main(){
  graph g;
  bool justKeepGoing = true;
  char inputt[20];

  while(justKeepGoing){ //loop to ask for input and call the correct function on graph g
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
    } else if (strcmp(inputt, "F")==0){
      char v1, v2;

      cout << "starting verticie?" << endl;
      cin >> v1;
      cin.ignore();
      cout << "ending verticie?" << endl;
      cin >> v2;
      cin.ignore();

      g.Dij(v1, v2);
    } else if (strcmp(inputt, "Q")==0){
      justKeepGoing = false;
    } else if (strcmp(inputt, "ABC")==0){//testing thing
      g.addVertex('A');
      g.addVertex('B');
      g.addVertex('C');
      g.addVertex('D');
      g.addVertex('E');
      g.addEdge('A', 'B', 3);
      g.addEdge('A','E',7);
      g.addEdge('B','A',2);
      g.addEdge('B','C',5);
      g.addEdge('B','D',4);
      g.addEdge('C','B',2);
      g.addEdge('C','E',6);
      g.addEdge('D','A',5);
      g.addEdge('D','B',5);
      g.addEdge('D','C',6);
      g.addEdge('D','E',2);
      g.addEdge('E','A',3);
      g.addEdge('E','D',3);

    }
    
  }
}
