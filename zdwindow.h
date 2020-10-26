#ifndef ZDWINDOW_H
#define ZDWINDOW_H

#include <QObject>
#include "zdbgfxwindow.h"

class ZDWindow : public QObject
{
    Q_OBJECT
public:
    ZDWindow();

    Q_INVOKABLE void createMeetingWindow();

private:
     ZDBGFXWindow* mChildWindow;

};

#endif // ZDWINDOW_H
