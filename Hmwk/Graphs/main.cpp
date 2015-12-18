#include "graph.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Vector<QString> vertexList;
    vertexList.append("Riverside");
    vertexList.append("Perris");
    vertexList.append("Temecula");
    vertexList.append("Palm Springs");
    vertexList.append("Corona");
    vertexList.append("Redlands");
    vertexList.append("Ontario");
    Graph graph(vertexList);

    graph.addEdge("Riverside","Perris",21);
    graph.addEdge("Riverside","Palm Springs",56);
    graph.addEdge("Riverside","Redlands",21);
    graph.addEdge("Riverside","Ontario",24);
    graph.addEdge("Perris","Temecula",22);
    graph.addEdge("Corona","Ontario",18);
    graph.addEdge("Corona","Riverside",22);
    graph.addEdge("Perris","Redlands",30);
    graph.addEdge("Temecula","Corona", 41);
    graph.addEdge("Temecula","Redlands", 52);
    graph.addEdge("Palm Springs","Redlands", 44);
    graph.addEdge("Perris","Corona",29);
    graph.addEdge("Riverside","Corona",12);


    graph.printGraph();

    cout<<"\n\n";

    graph.DFT("Riverside");
    cout<<"\n";

    graph.BFT("Riverside");
    cout<<"\n\n";

    graph.PrimMST();
    return 0;
}
