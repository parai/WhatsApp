#ifndef ENTRY_H
#define ENTRY_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
// ====================== [ ICON RESOURCES ] =======================
#define mICON_SAVE "D:/Qt/Projects/WhatsApp/res/isave.bmp"

class Entry : public QMainWindow
{
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = 0);

signals:

protected:
    void timerEvent(QTimerEvent *Event);
private slots:
    void save();
private:
    void createToolbar(void);

};

#endif // ENTRY_H
