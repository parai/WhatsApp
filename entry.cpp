#include "entry.h"

Entry::Entry(QWidget *parent) :
    QMainWindow(parent)
{
        this->createToolbar();
        this->startTimer(1000);
}
// ==================== [ SIGNALS       ] =====================================
void Entry::timerEvent(QTimerEvent *Event)
{
    static int iCounter = 0;
    iCounter ++ ;
    (void)Event;
    qDebug() << iCounter << "s Timer Elapsed!\n";
}

// ==================== [ PRIVATE SLOTS ] ======================================
void Entry::save()
{
    QMessageBox::about(this,"Save","Toolbar Icon Save Clicked!");
}

// ==================== [ PRIVATE FUNCTIONS ] ==================================
void Entry::createToolbar(void)
{
    QToolBar* toolbar = NULL;
    QAction * action = NULL;
    toolbar = this->addToolBar("Console");

    action = new QAction(QIcon(mICON_SAVE),tr("&Save"),this);
    action->setShortcut(tr("Ctrl+S"));
    this->connect(action,SIGNAL(triggered()),this,SLOT(save()));
    toolbar->addAction(action);
}
