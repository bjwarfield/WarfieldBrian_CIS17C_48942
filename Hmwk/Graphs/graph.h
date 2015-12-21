#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "hash.h"
#include "simplevector.h"
#include "DoubleLinkedList.h"
#include "tree.h"
#include <QDebug>

using namespace std;
class Graph
{
public:
    //struct to represent and adjacency list node
    struct AdjListNode{
        QString dest;//Key of connected node
        AdjListNode *next;//link to next connection
        int weight;//weight of connection
    };
    //struct to represent the adjacency list
    struct AdjList{
        AdjListNode *head;
    };
    //struct to represtn an edge
    struct edge{
        edge(){source = ""; dest = ""; weight = 0;}
        edge(QString source, QString dest, int weight):
        source(source),dest(dest),weight(weight){}
        edge(const edge &other):
            source(other.source),dest(other.dest),weight(other.weight){}

        QString source;
        QString dest;
        int weight;

        //comperator overloading
        bool operator >(edge const &other)const{
            return other.weight > this->weight;
        }
        bool operator <(edge const &other)const{
            return other.weight < this->weight;
        }

        bool operator ==(edge const &other)const{
            return other.weight == weight;
        }
        void operator=(edge const &other){
            source = other.source;
            dest = other.dest;
            weight = other.weight;
        }

    };

    Graph(Vector<QString> vertexList);
    ~Graph();
    AdjListNode *newAdjListNode(QString dest, int weight);
    void addEdge(QString src, QString dest, int weight);
    void printGraph();
    void DFT(QString start);
    void BFT(QString start);
    void PrimMST();


private:
    Hash<AdjList*> map;
    int edges;
    void DFT_Util(QString &vertex, Hash<bool> &visited);


};

/**
 * Graph Constructor
 * @param number of vertexes in Graph
 */
Graph::Graph(Vector<QString> vertexList):
map(vertexList.size())
{

    for (int i = 0; i < vertexList.size(); ++i) {
        map.Add(vertexList[i], new AdjList());
        map[vertexList[i]]->head = NULL;
    }

}

/**
 * @brief Graph::~Graph
 */
Graph::~Graph()
{
}

/**
 * Helper Function creates new node with given connection and returns it
 * @param dest of connetion
 * @return new AdjListNode
 */
Graph::AdjListNode *Graph::newAdjListNode(QString dest, int weight)
{
    AdjListNode *newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

/**
 * Adds connection between 2 vertexes of a graph.
 * @param src AdjList which to add connection
 * @param dest index of connected node;
 * @param weight of connection
 */
void Graph::addEdge(QString src, QString dest, int weight)
{
    //create new list node
    AdjListNode *newNode = newAdjListNode(dest, weight);
    //push it to beginning of source
    newNode->next = map[src]->head;
    map[src]->head = newNode;

    //add symetric connection
    newNode = newAdjListNode(src, weight);
    newNode->next = map[dest]->head;
    map[dest]->head = newNode;

    //increment edges
    ++edges;
}

void Graph::printGraph()
{
    Hash<AdjList*>::iterator it;
    for(it = map.begin(); it!= map.end(); ++it){
        AdjListNode *worker = (*it)->head;
        cout <<"Adjacency List of vertex \"" << it.key().toStdString()  << "\"\nhead ";
        while (worker) {
            cout << "->Nd: " << worker->dest.toStdString() << " Wt: " << worker->weight << " ";
            worker = worker->next;
        }
        cout << "\n";
    }

}

/**
 * @brief Depth first trversat
 * @param start
 */
void Graph::DFT(QString start)
{
    //list of visited nodes
    Hash<bool> visited(map.width());

    //initialize to false
    Hash<AdjList *>::iterator it;
    for(it = map.begin(); it!= map.end(); ++it){
        visited[it.key()] == false;
    }
    cout << "Depth First Traversal from Vertex: "<< start.toStdString() <<endl;
    //start traversal
    DFT_Util(start, visited);
    cout << "\n\n";
}

/**
 * @brief Graph::DFT_Util Depth first traverdal utility function
 * @param vertex to traverse
 * @param visited hashmap of vidited nodes
 */
void Graph::DFT_Util(QString &vertex, Hash<bool> &visited)
{
    //mark vertex as visited
    visited[vertex] = true;
    cout << vertex.toStdString() << " | ";

    //get vertex
    AdjListNode *worker = map[vertex]->head;

    //traverse connections
    while(worker){
        //skip nodes already visited
        if(!visited[worker->dest]){
            //recursivly call utility function
            DFT_Util(worker->dest, visited);
        }
        worker = worker->next;
    }
}

/**
 * @brief Breadth first traversal
 * @param start
 */
void Graph::BFT(QString start)
{
    //mark all nodes as not vidited
    Hash<bool> visited(map.width());
    Hash<AdjList *>::iterator it;
    for(it = map.begin(); it!= map.end(); ++it){
        visited[it.key()] = false;
    }

    //create queue for BFS
    DList<QString> queue;
    visited[start]=true;
    queue.append(start);

    cout << "Breadth First Traversal from Vertex: "<< start.toStdString() <<endl;

    while(!queue.isEmpty()){
        //dequeue a vertec from queue and print it
        start = queue.first();
        cout <<  queue.pullFront().toStdString() << " | ";

        //get all adjacent verticec of the dequeued vertex start.
        //if adjacent nas not been vidited, then mark it visited and enqueue it
       AdjListNode *worker = map[start]->head;
       while(worker){
           if(!visited[worker->dest]){
               visited[worker->dest]=true;
               queue.append(worker->dest);
           }
           //traverse conected nodes
           worker = worker->next;
       }
    }

    cout << "\n";
}

void Graph::PrimMST()
{

    //Adjacency list iterator
    Hash<AdjList *>::iterator it;

    //map of visited vertexes
    Hash<int> visited(map.width());
    //mark all to false
    for(it = map.begin(); it!= map.end(); ++it){
        visited[it.key()] = false;
    }

    //create edgelist
    Tree<edge> edgesQueue;

    //get names of vertexes
    Vector<QString> vertexList;
    for(it = map.begin(); it!= map.end(); ++it){
        vertexList.append(it.key());
    }
    //create new graph tp represent spanning tree
    Graph mst(vertexList);

    QString current = vertexList[0];

    int i = 0;
    while(i < vertexList.size()){
        //if current vertex not visited
        if(!visited[current] ){
            //mark it as visited
            visited[current] = true;

            //add all connected vertices to edgeQueue
            AdjListNode *worker = map[current]->head;
            while(worker){
                //add edge
                edgesQueue.add(edge(current,worker->dest , worker->weight));
                worker = worker->next;
            }

            //pull min edge from list
            edge temp = edgesQueue.min();
            edgesQueue.remove(edgesQueue.min());

            //if destination has not been visited, add to MST
            if(!visited[temp.dest]){
                mst.addEdge(temp.source, temp.dest, temp.weight);
            }
            current = temp.dest;

            i++;
        }else{//if vertex has been vidited
            //pull min edge from list
            edge temp = edgesQueue.min();
            edgesQueue.remove(edgesQueue.min());

            current = temp.source;
            //if destination has not been visited, add to MST
            if(!visited[temp.dest]){
                mst.addEdge(temp.source, temp.dest, temp.weight);
            }
            current = temp.dest;
        }

    }

    cout<<"Min Spanning tree using prim\n";
    mst.printGraph();
}





#endif // GRAPH_H
