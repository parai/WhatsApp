/**
 * WhatsApp - the open source AUTOSAR platform https://github.com/parai
 *
 * Copyright (C) 2014  WhatsApp <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "arcan.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
SimulationCan::SimulationCan(unsigned long id):
    OcDevice(QString("/dev/can%1").arg(id))
{
    this->canCardId = id;
    setAutonomous(true);
}
void SimulationCan::clear(void)
{
    while (!rxMsgList.isEmpty())
    {
        delete rxMsgList.at(rxMsgList.size() - 1);
        rxMsgList.removeLast();
    }

    while (!txMsgList.isEmpty())
    {
        delete txMsgList.at(txMsgList.size() - 1);
        txMsgList.removeLast();
    }
}
void SimulationCan::registerRxMsg(OcMessage *msg)
{
    rxMsgList.append(msg);
}

void SimulationCan::registerTxMsg(OcMessage *msg)
{
    txMsgList.append(msg);
}

SimulationCan::~SimulationCan()
{
    qDebug() << "~SimulationCan()";
    clear();
}

OcStatus SimulationCan::startup()
{
    OcStatus retval = OcSuccess;
    if((!started) &&(rxMsgList.size()>0))
    {
        started = true;
        OcDevice::startup();
        osTick = GetOsTick();
        prevMsgTimeStamp = 0;
        rxMsgIndex = 0;
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
    OcStatus retv;

    if((rxMsgIndex < rxMsgList.size()) && started)
    {
        TickType elapsedTick = GetOsElapsedTick(osTick);
        TickType limitTick = rxMsgList[rxMsgIndex]->timestamp() - prevMsgTimeStamp;

        if(elapsedTick >= limitTick)
        {
            retv = OcSuccess;
        }
        else
        {
            retv = OcFail;
        }
    }
    else
    {
        retv = OcFail; // over flow
    }

    return retv;
}
OcStatus SimulationCan::internalGetMessage(OcMessage *msg)
{
    OcStatus retv;
    if((rxMsgIndex < rxMsgList.size()) && started)
    {
        *msg = *rxMsgList[rxMsgIndex];

        osTick = GetOsTick();
        prevMsgTimeStamp = rxMsgList[rxMsgIndex]->timestamp();
        rxMsgIndex ++;
        retv = OcSuccess;
    }
    else
    {
        retv = OcFail;
    }

    // stop as all the rxMsg has been played
    if(rxMsgIndex>=rxMsgList.size())
    {
        shutdown();
    }
    return retv;
}

int SimulationCan::getBaudRate()
{
    return OcBaud_500K;
}

OcStatus SimulationCan::setBaudRate(int baud)
{
    return OcSuccess;
}

arCan::arCan(QString name,unsigned long channelNumber, QWidget *parent) : arDevice(name,parent)
{
    this->channelNumber = channelNumber;
    this->createGui();
    this->setGeometry(25,120,1200,500);

    for(unsigned long i=0;i<channelNumber;i++)
    {
        SimulationCan* can = new SimulationCan(i);
        simulationCanList.append( can );
        connect(can,SIGNAL(messageReceived(OcMessage*,QTime)),this,SLOT(on_messageReceived(OcMessage*,QTime)));
    }


    setVisible(true);
}

arCan::~arCan()
{
    while (!simulationCanList.isEmpty())
    {
        delete simulationCanList.at(simulationCanList.size() - 1);
        simulationCanList.removeLast();
    }
}

void arCan::on_play_pause(void)
{
    QString str = btnPlayPause->text();

    if(str == "Play")
    {
        btnPlayPause->setText("Pause");
        for(unsigned long i=0;i<channelNumber;i++)
        {
            simulationCanList[i]->startup();
        }
        btnLoadTrace->setDisabled(true);
        btnStop->setDisabled(false);
        btnPlayPause->setDisabled(true);
    }
    else
    {
        btnPlayPause->setText("Play");
    }
}

void arCan::on_stop(void)
{
    btnPlayPause->setText("Play");
    btnPlayPause->setDisabled(false);
    btnLoadTrace->setDisabled(false);
    btnStop->setDisabled(true);
    for(unsigned long i=0;i<channelNumber;i++)
    {
        simulationCanList[i]->shutdown();
    }
}

void arCan::on_clear_trace(void)
{
    QStringList  list;
    tableTrace->clear();
    list<<"Bus"<<"Time"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
    tableTrace->setColumnCount(12);
    tableTrace->setRowCount(0);
    tableTrace->setHorizontalHeaderLabels(list);
}

void arCan::clear(void)
{
    for(unsigned long i=0;i<channelNumber;i++)
    {
        simulationCanList[i]->clear();
    }
}

void arCan::on_save_trace(void)
{
    quint32 prevTime;
    QString filename = QFileDialog::getSaveFileName(this,"Save CAN Trace",".",tr("CAN Trace (*.rec *.txt)"));
    QFile file(filename);

    if(file.open(QFile::WriteOnly))
    {
        //file.write()
    }
}

void arCan::on_load_trace(void)
{
    static QRegularExpression reComment("^\\s*//");
    static QRegularExpression reEntry("^\\s*(\\d)\\s+(\\d+)\\s+(RX|TX)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)");
    QString filename = QFileDialog::getOpenFileName(this,"Load CAN Trace","../WhatsApp/example",tr("CAN Trace (*.rec *.txt)"));

    clear();    // clear history log information
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
                }
                else
                {
                    match = reEntry.match(entry);
                    if(match.hasMatch())
                    {
                        quint32 bus;
                        OcMessage* msg = entry2msg(match);
                        bus = msg->busid();
                        if(NULL != msg)
                        {
                            simulationCanList[bus]->registerRxMsg(msg);
                        }
                    }
                }
            }
        } while(lineLength != -1);
    }
}

void arCan::on_hexl_decimal(void)
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

void arCan::on_abs_rel_time(void)
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
void arCan::putMsg(OcMessage*msg)
{
    quint32 index = tableTrace->rowCount();
    tableTrace->setRowCount(index+1);
    tableTrace->setItem(index,0,new QTableWidgetItem(QString("%1").arg(msg->busid())));
    tableTrace->setItem(index,1,new QTableWidgetItem(QString("%1").arg(GetOsTick())));
    tableTrace->setItem(index,2,new QTableWidgetItem(QString("RX")));
    tableTrace->setItem(index,3,new QTableWidgetItem(QString("%1").arg(msg->id(),0,16)));
    quint8 *data = msg->data();
    for(int i=0;i<8;i++)
    {
        tableTrace->setItem(index,4+i,new QTableWidgetItem(QString("%1").arg(data[i],0,16).toUpper()));
    }
    tableTrace->setCurrentCell(index,0);
}
void arCan::WriteMessage(PduIdType swHandle,OcMessage *msg)
{
	putMsg(msg);
    int timer_id = startTimer(1);

	this->swHandle.append(swHandle);
    this->timerId.append(timer_id);
}

void arCan::timerEvent(QTimerEvent *Event)
{
	int swHandle = this->swHandle[0];
    int timer_id = this->timerId[0]; // TODO: Event->timerId()
    this->killTimer(timer_id);

	Can_TxConfirmation( swHandle );

	this->swHandle.removeFirst();
    this->timerId.removeFirst();
}
void arCan::on_messageReceived(OcMessage *msg, const QTime &time)
{

	putMsg(msg);

	Can_RxIndication((uint8)msg->busid(),(uint32)msg->id(),(uint8)msg->length(),(uint8*)msg->data());
    // check all is finished
    quint32 isFinished = true;
    for(unsigned long i=0;i<channelNumber;i++)
    {
        if(simulationCanList[i]->isStarted())
        {
            isFinished = false;
        }
    }

    if(isFinished)
    {
        btnLoadTrace->setDisabled(false);
        btnPlayPause->setText("Play");
        btnPlayPause->setDisabled(false);
        btnStop->setDisabled(true);
    }
}

void arCan::on_trigger_tx(void)
{
    bool ok;
    quint32 id = leId->text().toLong(&ok,16);
    if(ok)
    {
        int i;
        quint8 data[8];
        quint32 bus = cbBus->currentIndex();
        QStringList sdata = leData->text().split(" ",QString::SkipEmptyParts);
        ok = true;
        if((sdata.size()>0) && (sdata.size()<=8))
        {
            for(i=0;i<sdata.size();i++)
            {
                bool iOk;
                data[i] = sdata[i].toLong(&iOk,16);
                if(!iOk)
                {
                    ok = false;
                }
            }
            for(;i<8;i++)
            {
                data[i] = 0x55;
            }
        }
        else
        {
            ok = false;
        }

        if(ok)
        {
            static QTime qTime;
            OcMessage* msg = new OcMessage(id,data,8,false,0);
            msg->setBusId(bus);
            this->on_messageReceived(msg,qTime);
            delete msg;
        }
        else
        {
            QMessageBox::warning(this,"Invalid Data",QString("Invalid Data: \" %1 \"" ).arg(leData->text()));
        }
    }
    else
    {
        QMessageBox::warning(this,"Invalid Id",QString("Invalid Id: \" %1 \"").arg(leId->text()));
    }
}

void arCan::createGui(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {   // create trace
        tableTrace = new QTableWidget();
        QStringList  list;
        list<<"Bus"<<"Time(ms)"<<"Direction"<<"Id"<<"Byte 0"<<"Byte 1"<< "Byte 2"<< "Byte 3"<< "Byte 4"<< "Byte 5"<< "Byte 6"<< "Byte 7";
        tableTrace->setColumnCount(12);
        tableTrace->setRowCount(0);
        tableTrace->setHorizontalHeaderLabels(list);
        vbox->addWidget(tableTrace);
    }

    {   // create control
        QPushButton* button;
        QHBoxLayout* hbox = new QHBoxLayout();

        btnLoadTrace = new QPushButton("Load Trace...");
        this->connect(btnLoadTrace,SIGNAL(clicked()),this,SLOT(on_load_trace()));
        hbox->addWidget(btnLoadTrace);

        btnPlayPause = new QPushButton("Play");
        this->connect(btnPlayPause,SIGNAL(clicked()),this,SLOT(on_play_pause()));
        hbox->addWidget(btnPlayPause);

        btnStop = new QPushButton("Stop");
        this->connect(btnStop,SIGNAL(clicked()),this,SLOT(on_stop()));
        hbox->addWidget(btnStop);
        btnStop->setDisabled(true);

        button = new QPushButton("Clear Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(on_clear_trace()));
        hbox->addWidget(button);

        button = new QPushButton("Save Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(on_save_trace()));
        hbox->addWidget(button);

        btnHexlDeci = new QPushButton("Hexl");
        this->connect(btnHexlDeci,SIGNAL(clicked()),this,SLOT(on_hexl_decimal()));
        hbox->addWidget(btnHexlDeci);
        btnHexlDeci->setDisabled(true); // TODO

        btnAbsRelTime = new QPushButton("Real Time");
        this->connect(btnAbsRelTime,SIGNAL(clicked()),this,SLOT(on_abs_rel_time()));
        hbox->addWidget(btnAbsRelTime);
        btnAbsRelTime->setDisabled(true);   // TODO

        hbox->setSpacing(20);

        vbox->addItem(hbox);
    }
    // automatic send
    {
        QHBoxLayout* hbox = new QHBoxLayout();
        QLabel *label = new QLabel("Bus:");
        QPushButton *button;
        hbox->addWidget(label);
        cbBus = new QComboBox();
        for(int i=0;i<channelNumber;i++)
        {
            cbBus->addItem(QString("%1").arg(i));
        }
        cbBus->setCurrentIndex(0);
        hbox->addWidget(cbBus);

        label = new QLabel("Id:");
        hbox->addWidget(label);
        leId = new QLineEdit();
        hbox->addWidget(leId);
        leId->setMaximumWidth(50);
        leId->setText("201");

        label = new QLabel("Data:");
        hbox->addWidget(label);
        leData = new QLineEdit();
        hbox->addWidget(leData);
        leData->setText(("55 55 55 55 55 55 55 55"));

        button = new QPushButton("Trigger Tx");
        connect(button,SIGNAL(clicked()),this,SLOT(on_trigger_tx()));
        hbox->addWidget(button);

        hbox->setSpacing(5);

        vbox->addItem(hbox);
    }

    widget->setLayout(vbox);
    this->setCentralWidget(widget);
}

OcMessage* arCan::entry2msg(QRegularExpressionMatch match)
{
    OcMessage* msg = NULL;
    // bus  time(ms)  direction(RX|TX)  Id    Byte 0  Byte 1   Byte 2   Byte 3   Byte 4   Byte 5   Byte 6   Byte 7
    if("RX" == match.captured(3))
    {
        quint32 bus = (unsigned long)match.captured(1).toLong();
        if(bus < channelNumber)
        {
            quint32 Id = match.captured(4).toLong(NULL,16);
            quint32 timestamp =  match.captured(2).toLong(NULL,10);
            quint8 data[8];
            for(int i=0;i<8;i++)
            {
                data[i] = match.captured(5+i).toLong(NULL,16);
            }
            msg = new OcMessage(Id,data,8,false,timestamp);
            msg->setBusId(bus);
        }
        else
        {
            qDebug() << "CAN: invalid can bus " << bus ;
        }
    }
    else
    {
        qDebug() << "CAN: ignore can tx msg ";
    }

    return msg;
}
