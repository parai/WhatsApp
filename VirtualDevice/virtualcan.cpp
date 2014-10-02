#include "virtualcan.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

SimulationCan::SimulationCan(unsigned long id):
    OcDevice(QString("/dev/can%1").arg(id))
{
    this->canCardId = id;
    setAutonomous(true);
}

SimulationCan::~SimulationCan()
{

}

OcStatus SimulationCan::startup()
{
    OcStatus retval = OcSuccess;
    if(!started)
    {
        started = true;
        OcDevice::startup();
    }
    else
    {
        retval = OcFail;
    }
    return retval;
}

OcStatus SimulationCan::shutdown()
{
    OcStatus retval = OcSuccess;
    if(started)
    {
        started = false;
        OcDevice::shutdown();
    }
    else
    {
        retval = OcFail;
    }
    return retval;
}

OcStatus SimulationCan::sendMessage(const OcMessage &msg)
{
    return OcSuccess;
}

OcStatus SimulationCan::receivedMessage()
{
    return OcSuccess;
}
OcStatus SimulationCan::internalGetMessage(OcMessage *msg)
{
    return OcFail;
}

int SimulationCan::getBaudRate()
{
    return OcBaud_500K;
}

OcStatus SimulationCan::setBaudRate(int baud)
{
    return OcSuccess;
}

VirtualCan::VirtualCan(unsigned long channelNumber, QWidget *parent) : VirtualDevice("Can",parent)
{
    this->channelNumber = channelNumber;
    this->createGui();
    this->setGeometry(25,120,1200,500);

    for(unsigned long i=0;i<channelNumber;i++)
    {
        SimulationCan * can = new SimulationCan(i);
        //simulationCanList.push_back( new SimulationCan(i) );
    }
}

VirtualCan::~VirtualCan()
{
    while (!simulationCanList.isEmpty())
    {
        delete simulationCanList.at(simulationCanList.size() - 1);
        simulationCanList.removeLast();
    }
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
    QStringList  list;
    tableTrace->clear();
    list<<"Bus"<<"Time"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
    tableTrace->setColumnCount(12);
    tableTrace->setRowCount(0);
    tableTrace->setHorizontalHeaderLabels(list);
}

void VirtualCan::load_trace(void)
{
    static QRegularExpression reComment("^\\s*//");
    static QRegularExpression reEntry("^\\s*(\\d)\\s+(\\d+)\\s+(RX|TX)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)");
    QString filename = QFileDialog::getOpenFileName(this,"Load CANoe Trace",".",tr("CAN Trace (*.asc *.rec *.txt)"));
    qDebug() <<"Load Trace: " << filename;

    QFile file(filename);
    if (file.open(QFile::ReadOnly))
    {
        qint64 lineLength;
        char buf[1024];
        do
        {
            lineLength = file.readLine(buf, sizeof(buf));
            if (lineLength != -1)
            {   // the line is available in buf
                QString entry = QString(buf);
                QRegularExpressionMatch match = reComment.match(entry);
                if (match.hasMatch())
                {
                    qDebug() << "File Comment:" << match;
                }
                else
                {
                    match = reEntry.match(entry);
                    if(match.hasMatch())
                    {
                        qDebug() << "File Entry:" << match;
                    }
                }
                qDebug() << "File:" << buf;
            }
        } while(lineLength != -1);
    }
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

void VirtualCan::createGui(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {   // create trace
        tableTrace = new QTableWidget();
        QStringList  list;
        list<<"Bus"<<"Time"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
        tableTrace->setColumnCount(12);
        tableTrace->setRowCount(0);
        tableTrace->setHorizontalHeaderLabels(list);
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
}
