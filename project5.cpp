/*
Christian Gonzaga
CSC 382
Project 5
*/
#include <iostream>
using namespace std;
//implementing linked list
struct Node {
    int vertex;
    Node *next;

    Node()
        : vertex(0)
        , next(NULL)
    {}
};

// go to the end of the list and started to delete
// nodes from the end of the list
void ClearList(Node * node) {
    if(node != NULL) {
        ClearList(node->next);
        delete node;
    }
}
//modified verison of professo'rs graph class
class Graph {
public:
    //constructor
    Graph(int nodes)
        : n (nodes)
        , headnodes (new Node[n])
    {
        //headnodes[i].vertext =i;
        //headnodes[i].next=0;
    }


     //The create function which is to use
     //to create the linked-list of the graph
    void Create() {
        // type the number offedges
        cin >> e;
        cout<<"Enroute From " <<"Enroute To " <<endl;
        for(int i = 0; i < e; i++) {
            int from, to;

            cin >> from >> to;
            //OK, we use Add Edge function
            //That will connect from a vertex to another
            AddEdge(from, to);
            // add inverted edge because it's undirected graph
            AddEdge(to, from);
        }
    }



    //destructor
    ~Graph() {
        for(int node = 0; node < n; node++) {
            // delete adjacent nodes
            ClearList(headnodes[node].next);
        }
        // delete the main array
        delete[] headnodes;
    }

    Node* GetAdjacent(int v) const {
        return headnodes[v].next;
    }

private:

    // Add edge from vertex to vertext by using `from` to vertex `to`
    // by allocating memory for one node
    void AddEdge(int from, int to) {
        //adj[u].push_back(from);
        //adj[v].push_back(to);
        Node* current = &headnodes[from];
        Node* previous = NULL;
        while(current != NULL) {
            previous = current;
            current = current->next;
        }
        //connect
        current = new Node;
        current->vertex = to;
        previous->next = current;
    }

    // number of nodes
    int n;
    // number of edges
    int e;
    // array of vertex
    Node * headnodes;
};
//modified DFS
void DFS(const Graph&graph, int vertex, int father, int *markVisit, int * parents) {
    //bool vertex;
    //visited

    // mark as opened
    markVisit[vertex] = 1;
    // get adjacent vertex
    Node * adj = graph.GetAdjacent(vertex);
    while(adj != NULL) { // visite all adjacent vertices
        // if this vertex wasn't visited (color == 0)
        if(markVisit[adj->vertex] == 0) {
            // update parent of the vertex
            parents[adj->vertex] = vertex;
            DFS(graph, adj->vertex, vertex, markVisit, parents); // go forward with DFS
        }
        else if(markVisit[adj->vertex] == 1 && adj->vertex != father) {
            // we met an adjacent vertex `adj->vertex` which is  already visited but not closed
            // It's also not parent of the current processed `vertex`
            // (need this check because it's an undirected graph)
            // Print whole cycle backwards
            cout << "\n Our Discovered Cycle: ";
            int v = vertex;
            while(parents[v] != -1 && adj->vertex != v) {
                cout << "(" << v << " " << parents[v] <<"), ";
                v = parents[v];
            }
            cout << "(" << adj->vertex << " " << vertex << ")\n";
        }
        // next adjacent vertex
        adj = adj->next;
    }
    // mark as closed vertex
    markVisit[vertex] = 2;
}

/*
void DFS(int father, int v)
{   Visited [v]=true;
     node* adjnode=headnodes[v].next
     while (!adjnode) // visit all vertices adjacent to v
            {  if (!Visited[adjnode.vertex]) //if adjacent vertex to v was not visited previously
                            DFS(v,adjnode.vertex); // when we call DFS, we pass the father vertex of the call
                      else if (father !=adjnode.vertex) // if the vertex adjacent to v is not the father, we have a
                                                                          //cycle
                             {cycle=true;
                              }
              }
}
*/

/*
void DFSRES(vector<int> adj[], ints, bool visited[]
            visted[]= true;
            cout <<s << " ";
            if(visited[] == false);
*/

int main() {

    cout<<"Hello there!, Please Type The number of Nodes: "<<endl;
    int n;
    cin >> n;
    Graph graph(n);
    cout<<"Type the number of edges"<<endl;
    graph.Create();


    /* mark is used as an indicated of a visted array so:
        0 indicates vertex hasn't visited yet
     1 indicates visited but not all children are processed
     2 indicates visited and its closed closed: all children hae been processed
    */

    int* mark = new int[n];
    int* parent = new int[n];
    // mark every vertex as unvisited
    for(int i = 0; i < n; i++) {
        mark[i] = 0;
        parent[i] = -1; // default value, means - no parent
    }
    int Nmbrcmpnts = 0;
    // start DFS for every vertex which is still unvisited
    //findComponents(marked[]);
    for(int i = 0; i < n; i++) {
        if(!mark[i]) {
            Nmbrcmpnts++;
            DFS(graph, i, parent[i], mark, parent);
        }
    }
    cout << "\n Components Founded: " << Nmbrcmpnts << "\n";
    //  letsclean up allocated memory
    delete[] mark;
    delete[] parent;
    return 0;
}
