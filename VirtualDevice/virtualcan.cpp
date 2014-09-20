#include "virtualcan.h"
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
VirtualCan::VirtualCan(QWidget *parent) : VirtualDevice("Can",parent)
{
    channelNumber = 4; // default set it 4
    this->createChannels();
}


void VirtualCan::createChannels(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {   // create trace
        QTableWidget* table = new QTableWidget();
        QStringList  list;
        list<<"Bus"<<"Time"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
        table->setColumnCount(12);
        table->setRowCount(channelNumber);
        table->setHorizontalHeaderLabels(list);
        table->setItem(0,0,new QTableWidgetItem("example"));
        vbox->addWidget(table);
    }

    {   // create control
        QPushButton* button;
        QCheckBox* checkbox;
        QHBoxLayout* hbox = new QHBoxLayout();

        button = new QPushButton("Load Trace...");
        hbox->addWidget(button);

        button = new QPushButton("Start");
        hbox->addWidget(button);

        button = new QPushButton("Stop");
        hbox->addWidget(button);

        checkbox = new QCheckBox("Hexl");
        checkbox->setToolTip("Default is decimal mode");
        hbox->addWidget(checkbox);

        checkbox = new QCheckBox("Real Time");
        checkbox->setToolTip("Default is Absolute time");
        hbox->addWidget(checkbox);

        hbox->setSpacing(20);

        vbox->addItem(hbox);
    }

    widget->setLayout(vbox);
    this->setCentralWidget(widget);
    resize(1200,500);
}
