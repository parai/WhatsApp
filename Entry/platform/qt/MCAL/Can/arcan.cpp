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
static bool IsXLReady = false;
static class arCan* self=NULL;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
arCanBus::arCanBus(unsigned long id):
    OcDevice(QString("/dev/can%1").arg(id))
{
    this->canCardId = id;
    setAutonomous(true);

    if(IsXLReady)
    {
    	char userName[32];
		sprintf(userName,"port%d",(int)id);
		XLaccess accessMask = 1<<id;
		XLstatus status= xlOpenPort(&xlPortHandle,userName,accessMask,&xlAccess,512,XL_INTERFACE_VERSION,XL_BUS_TYPE_CAN);

		if(XL_SUCCESS != status)
		{
			qDebug()<<xlGetErrorString(status);
			return;
		}

		setBaudRate(OcBaud_500K);	// default
    }
    else
    {
    	/* do nothing */
    }

}
void arCanBus::clear(void)
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
void arCanBus::registerRxMsg(OcMessage *msg,bool atFirst)
{
	if(atFirst)
	{
		msg->setTimestamp(GetOsTick());	/* for sure, send it as soon as possible */
		rxMsgList.push_front(msg);
	}
	else
	{
		rxMsgList.append(msg);
	}
}

void arCanBus::registerTxMsg(OcMessage *msg,bool atFirst)
{
	if(atFirst)
	{
		msg->setTimestamp(GetOsTick());	/* for sure, send it as soon as possible */
		txMsgList.push_front(msg);
	}
	else
	{
		txMsgList.append(msg);
	}
}

arCanBus::~arCanBus()
{
    qDebug() << "~arCanBus()";
    clear();
}

OcStatus arCanBus::startup()
{
    OcStatus retval = OcSuccess;
    if(!started)
    {
        started = true;
        OcDevice::startup();
        osTick = GetOsTick();
        prevMsgTimeStamp = osTick;
    }
    else
    {
        retval = OcFail;
    }

    if(IsXLReady)
    {
    	XLstatus status = xlActivateChannel(xlPortHandle,xlAccess,XL_BUS_TYPE_CAN,XL_ACTIVATE_RESET_CLOCK);
    	if(XL_SUCCESS == status)
    	{
    		qDebug() << xlGetErrorString(status);
    	}
    }
    return retval;
}

OcStatus arCanBus::shutdown()
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

    if(IsXLReady)
	{
		XLstatus status = xlDeactivateChannel(xlPortHandle,xlAccess);
		if(XL_SUCCESS == status)
		{
			qDebug() << xlGetErrorString(status);
		}
	}
    return retval;
}

OcStatus arCanBus::sendMessage(const OcMessage &msg)
{
    return OcSuccess;
}

OcStatus arCanBus::receivedMessage()
{
    OcStatus retv;

    if((false==rxMsgList.isEmpty()) && started)
    {
        TickType elapsedTick = GetOsElapsedTick(osTick);
        TickType limitTick = rxMsgList[0]->timestamp() - prevMsgTimeStamp;

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

    // 2
    if(IsXLReady)
    {
        unsigned int event_count=1;
    	XLevent event_list;
        XLstatus status = xlReceive(xlPortHandle, &event_count, &event_list);
        if(status == XL_SUCCESS)
		{
            qDebug()<< xlGetEventString(&event_list);
			retv = OcSuccess;
		}
		else
		{

		}
    }

    return retv;
}
OcStatus arCanBus::internalGetMessage(OcMessage *msg)
{
    OcStatus retv;
    if((false==rxMsgList.isEmpty()) && started)
    {
        *msg = *rxMsgList[0];

        osTick = GetOsTick();
        prevMsgTimeStamp = rxMsgList[0]->timestamp();
        rxMsgList.removeFirst();
        retv = OcSuccess;
    }
    else
    {
        retv = OcFail;
    }

    return retv;
}

int arCanBus::getBaudRate()
{
    return OcBaud_500K;
}

OcStatus arCanBus::setBaudRate(int baud)
{
	XLstatus status = xlCanSetChannelBitrate(xlPortHandle,xlAccess,baud);
    return OcSuccess;
}

arCan::arCan(QString name,unsigned long channelNumber, QWidget *parent) : arDevice(name,parent)
{
    this->channelNumber = channelNumber;
    this->createGui();
    this->setGeometry(25,120,1200,500);

    /* for simulation */
    for(unsigned long i=0;i<channelNumber;i++)
    {
        arCanBus* can = new arCanBus(i);
        canBusList.append( can );
        connect(can,SIGNAL(messageReceived(OcMessage*,QTime)),this,SLOT(on_messageReceived(OcMessage*,QTime)));
    }
    /* automatically start-up */
    for(unsigned long i=0;i<channelNumber;i++)
    {
        canBusList[i]->startup();
    }

    XLstatus status = xlOpenDriver();

    if(XL_SUCCESS == status)
    {
    	IsXLReady = true;
    }
    else
    {
    	IsXLReady = false;
    	qDebug() << "arCan::start CAN XL device failed.";
    }

    setVisible(true);

    self = this;

    startTimer(1);
}

arCan::~arCan()
{
    while (!canBusList.isEmpty())
    {
        delete canBusList.at(canBusList.size() - 1);
        canBusList.removeLast();
    }

    if(IsXLReady)
    {
    	xlCloseDriver();
    }
}

void arCan::on_btnPlayPause_clicked(void)
{

}

void arCan::on_btnStop_clicked(void)
{

}

void arCan::on_btnClearTrace_clicked(void)
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
        canBusList[i]->clear();
    }
}

void arCan::on_btnSaveTrace_clicked(void)
{
    quint32 prevTime;
    QString filename = QFileDialog::getSaveFileName(this,"Save CAN Trace",".",tr("CAN Trace (*.rec *.txt)"));
    QFile file(filename);

    if(file.open(QFile::WriteOnly))
    {
        //file.write()

    	file.close();
    }
}

void arCan::on_btnLoadTrace_clicked(void)
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
                            canBusList[bus]->registerRxMsg(msg);
                        }
                    }
                }
            }
        } while(lineLength != -1);
        file.close();
    }
}

void arCan::on_btnHexlDeci_clicked(void)
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

void arCan::on_btnAbsRelTime_clicked(void)
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
void arCan::putMsg(OcMessage*msg,bool isRx)
{
    quint32 index = tableTrace->rowCount();
    tableTrace->setRowCount(index+1);
    tableTrace->setItem(index,0,new QTableWidgetItem(QString("%1").arg(msg->busid())));
    tableTrace->setItem(index,1,new QTableWidgetItem(QString("%1").arg(GetOsTick())));
    if(isRx)
    {
    	tableTrace->setItem(index,2,new QTableWidgetItem(QString("RX")));
    }
    else
    {
    	tableTrace->setItem(index,2,new QTableWidgetItem(QString("TX")));
    }
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
	msg->setSWHandle((quint32)swHandle);
	this->swMsg.append(msg);
}

class arCan* arCan::Self ( void )
{
	assert(self!=NULL);

	return self;
}

void arCan::ReceiveMessage(OcMessage *msg)
{
	int bus = msg->busid();

	canBusList[bus]->registerRxMsg(msg,true);
}

void arCan::timerEvent(QTimerEvent *Event)
{
	if(false == swMsg.isEmpty())
	{
		OcMessage *msg = swMsg[0];
		Can_TxConfirmation( msg->SWHandle() );

		putMsg(msg);

		swMsg.removeFirst();

		delete msg;
	}
	else
	{
		/* no mseesage */
	}
}
void arCan::on_messageReceived(OcMessage *msg, const QTime &time)
{
	putMsg(msg);

	Can_RxIndication((uint8)msg->busid(),(uint32)msg->id(),(uint8)msg->length(),(uint8*)msg->data());

    delete msg;
}

void arCan::on_btnTriggerTx_clicked(void)
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
        this->connect(btnLoadTrace,SIGNAL(clicked()),this,SLOT(on_btnLoadTrace_clicked()));
        hbox->addWidget(btnLoadTrace);

//        btnPlayPause = new QPushButton("Play");
//        this->connect(btnPlayPause,SIGNAL(clicked()),this,SLOT(on_btnPlayPause_clicked()));
//        hbox->addWidget(btnPlayPause);
//
//        btnStop = new QPushButton("Stop");
//        this->connect(btnStop,SIGNAL(clicked()),this,SLOT(on_btnStop_clicked()));
//        hbox->addWidget(btnStop);
//        btnStop->setDisabled(true);

        button = new QPushButton("Clear Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(on_btnClearTrace_clicked()));
        hbox->addWidget(button);

//        button = new QPushButton("Save Trace");
//        this->connect(button,SIGNAL(clicked()),this,SLOT(on_btnSaveTrace_clicked()));
//        hbox->addWidget(button);
//
//        btnHexlDeci = new QPushButton("Hexl");
//        this->connect(btnHexlDeci,SIGNAL(clicked()),this,SLOT(on_btnHexlDeci_clicked()));
//        hbox->addWidget(btnHexlDeci);
//        btnHexlDeci->setDisabled(true); // TODO
//
//        btnAbsRelTime = new QPushButton("Real Time");
//        this->connect(btnAbsRelTime,SIGNAL(clicked()),this,SLOT(on_btnAbsRelTime_clicked()));
//        hbox->addWidget(btnAbsRelTime);
//        btnAbsRelTime->setDisabled(true);   // TODO

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
        connect(button,SIGNAL(clicked()),this,SLOT(on_btnTriggerTx_clicked()));
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
            quint32 timestamp =  match.captured(2).toLong(NULL,10)+GetOsTick();
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
