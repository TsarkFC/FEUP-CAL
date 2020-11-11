#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1(){
    GraphViewer *gv = new GraphViewer(600, 600, true);
    gv->setBackground("../resources/background.png");
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0);
    gv->addNode(1);
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->removeNode(1);
    gv->addNode(2);
    gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
    gv->setVertexLabel(2, "Node2");
    gv->setEdgeLabel(1, "Edge1n"); //last character is omitted
    gv->setVertexColor(2, "green");
    gv->setEdgeColor(1, "yellow");
    gv->rearrange();
}

void exercicio2(){
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);

    gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::DIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::DIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::DIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::DIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::DIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::DIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::DIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::DIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::DIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::DIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::DIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::DIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::DIRECTED);

    int pos12 = 200;
    int pos13 = 400;
    int id12 = 12, id13 = 13;
    int sign12 = 5, sign13 = -5;
    sleep(1);
    while (true){
        pos12 += sign12;
        pos13 += sign13;
        if (pos12 == 250) sign12 = -5;
        else if (pos12 == 200) sign12 = 5;
        if (pos13 == 400) sign13 = -5;
        else if (pos13 == 350) sign13 = 5;

        gv->removeNode(id12);
        gv->removeNode(id13);
        id12 = id13 + 1;
        id13 = id12 + 1;
        gv->addNode(id12, pos12, 550);
        gv->addNode(id13, pos13, 550);
        gv->addEdge(12, 11, id12, EdgeType::DIRECTED);
        gv->addEdge(13, 11, id13, EdgeType::DIRECTED);
        sleep(1);
        gv->rearrange();
    }

}

void exercicio3(){
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    ifstream vertices("../resources/mapa1/nos.txt");
    string line;
    while(getline(vertices, line)){
        replace(line.begin(), line.end(), ';', ' ');
        stringstream ss(line);
        int id, x, y;
        ss >> id >> x >> y;
        cout << id << " " << x << " " << y << endl;
        gv->addNode(id, x, y);
    }

    ifstream edges("../resources/mapa1/arestas.txt");
    while(getline(edges, line)){
        replace(line.begin(), line.end(), ';', ' ');
        stringstream ss(line);
        int id, ori, des;
        ss >> id >> ori >> des;
        gv->addEdge(id, ori, des, EdgeType::DIRECTED);
    }

}

int main() {
    //Uncomment to run exercise
    //exercicio1();

    //exercicio2();

	exercicio3();

	getchar();
	return 0;
}
