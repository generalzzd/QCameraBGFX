#include "zdwindow.h"
#include <iostream>
using namespace std;



ZDWindow::ZDWindow()
{

}

void ZDWindow::createMeetingWindow()
{

    cout <<" Helllas d"<<endl;

    if(mChildWindow!=NULL){
        mChildWindow->close();
        delete mChildWindow;
    }
    mChildWindow = new ZDBGFXWindow();
    mChildWindow->setWidth(800);
    mChildWindow->setHeight(600);
    mChildWindow->requestUpdate();
    mChildWindow->show();

}
