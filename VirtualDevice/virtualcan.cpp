#include "virtualcan.h"
VirtualCan::VirtualCan(QWidget *parent) : VirtualDevice("Can",parent)
{
    channelNumber = 4; // default set it 4
    this->createChannels();
}

void VirtualCan::play_pause(void)
{
    QString str = btnPlayPause->text();

    if(str == "Play")
    {
        btnPlayPause->setText("Pause");
    }
    else
    {
        btnPlayPause->setText("Play");
    }
}

void VirtualCan::stop(void)
{
    btnPlayPause->setText("Play");
}

void VirtualCan::clear_trace(void)
{

}

void VirtualCan::load_trace(void)
{
    QString file = QFileDialog::getOpenFileName(this,"Load CANoe Trace",".",tr("CAN Trace (*.asc *.rec *.txt)"));
    tableTrace->setItem(0,0,new QTableWidgetItem(file));
}

void VirtualCan::hexl_decimal(void)
{
    QString str = btnHexlDeci->text();

    if(str == "Hexl")
    {
        btnHexlDeci->setText("Decimal");
    }
    else
    {
        btnHexlDeci->setText("Hexl");
    }
}

void VirtualCan::abs_rel_time(void)
{
    QString str = btnAbsRelTime->text();

    if(str == "Real Time")
    {
        btnAbsRelTime->setText("Absolute Time");
    }
    else
    {
        btnAbsRelTime->setText("Real Time");
    }
}

void VirtualCan::createChannels(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {   // create trace
        tableTrace = new QTableWidget();
        QStringList  list;
        list<<"Bus"<<"Time"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
        tableTrace->setColumnCount(12);
        tableTrace->setRowCount(channelNumber);
        tableTrace->setHorizontalHeaderLabels(list);
        tableTrace->setItem(0,0,new QTableWidgetItem("example"));
        vbox->addWidget(tableTrace);
    }

    {   // create control
        QPushButton* button;
        QHBoxLayout* hbox = new QHBoxLayout();

        button = new QPushButton("Load Trace...");
        this->connect(button,SIGNAL(clicked()),this,SLOT(load_trace()));
        hbox->addWidget(button);

        btnPlayPause = new QPushButton("Play");
        this->connect(btnPlayPause,SIGNAL(clicked()),this,SLOT(play_pause()));
        hbox->addWidget(btnPlayPause);

        button = new QPushButton("Stop");
        this->connect(button,SIGNAL(clicked()),this,SLOT(stop()));
        hbox->addWidget(button);

        button = new QPushButton("Clear Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(clear_trace()));
        hbox->addWidget(button);

        btnHexlDeci = new QPushButton("Hexl");
        this->connect(btnHexlDeci,SIGNAL(clicked()),this,SLOT(hexl_decimal()));
        hbox->addWidget(btnHexlDeci);

        btnAbsRelTime = new QPushButton("Real Time");
        this->connect(btnAbsRelTime,SIGNAL(clicked()),this,SLOT(abs_rel_time()));
        hbox->addWidget(btnAbsRelTime);

        hbox->setSpacing(20);

        vbox->addItem(hbox);
    }

    widget->setLayout(vbox);
    this->setCentralWidget(widget);
    resize(1200,500);
}
