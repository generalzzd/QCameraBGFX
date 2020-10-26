#ifndef ZDBGFXWINDOW_H
#define ZDBGFXWINDOW_H

#include <QWindow>

class ZDBGFXWindow : public QWindow
{
public:
    ZDBGFXWindow(QWindow* parent = NULL);
    virtual ~ZDBGFXWindow();

    bool event(QEvent *event);
    void resizeEvent(QResizeEvent *);
    void exposeEvent(QExposeEvent *);
private:
    int width, height;
    bool isInit;
    bool initBGFX();

public slots:
    void renderNow();
    void renderLater();

};

#endif // ZDBGFXWINDOW_H
