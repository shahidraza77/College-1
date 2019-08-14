#include <QApplication>
#include "sources/graph.h"
#include "sources/contolpanel.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Display simulation");

    Graph *graph = new Graph();
    ControlPanel *controlpanel = new ControlPanel();

    QLayout *parentlayout = new QHBoxLayout;
    parentlayout->addWidget(graph);
    parentlayout->addWidget(controlpanel);

    QObject::connect(controlpanel,SIGNAL(GraphResetSignal(int,int)),graph,SLOT(GraphResetSlot(int,int)));
    QObject::connect(graph,SIGNAL(pointSelect(pair<int,int>)),controlpanel,SLOT(getPointClicked(pair<int,int>)));
    QObject::connect(graph,SIGNAL(pointHover(pair<int,int>)),controlpanel,SLOT(getPointHover(pair<int,int>)));
    QObject::connect(controlpanel->getAlgo(),SIGNAL(pointRequest(int)),graph,SLOT(pointRequest(int)));
    QObject::connect(graph,SIGNAL(sendPoint(pair<int,int>,int)),controlpanel->getAlgo(),SLOT(receivePoint(pair<int,int>,int)));


    window->setLayout(parentlayout);
    window->show();
    return app.exec();
}