#include "zdbgfxwindow.h"

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "logo.h"

#include <iostream>
#include <QResizeEvent>
#include "stb_image.h"
using namespace std;


ZDBGFXWindow::ZDBGFXWindow(QWindow* parent)
    :QWindow(parent),isInit(false)
{
    width = this->QWindow::width();
    height =this->QWindow::height();
}

ZDBGFXWindow::~ZDBGFXWindow()
{

}
bool ZDBGFXWindow::initBGFX()
{
    if(isInit)
        return true;
    cout<<"Init BGFX"<<endl;
    bgfx::renderFrame();
    // Initialize bgfx using the native window handle and window resolution.
    bgfx::Init init;
    init.platformData.nwh = (void*)this->winId();

    init.resolution.width = (uint32_t)width;
    init.resolution.height = (uint32_t)height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return false;
    // Set view 0 to the same dimensions as the window and to clear the color buffer.
    const bgfx::ViewId kClearView = 0;
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

    isInit = true;
    return true;
}
void ZDBGFXWindow::renderNow()
{
    if(!isInit)
        return;

    const bgfx::ViewId kClearView = 0;
    int oldWidth = width, oldHeight = height;

    if (width != oldWidth || height != oldHeight) {
        bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
        bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
    }
    // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
    bgfx::touch(kClearView);
    // Use debug font to print information about this example.

    int image_width=0, image_height=0, image_channel = 0;
    unsigned char *image_data = stbi_load(
                "D:\\QTProject\\QML_SDL_BGFX\\test.png",
                &image_width,
                &image_height,
                &image_channel,
                0);



    bgfx::dbgTextClear();
    //bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
    uint8_t data[] = { 'f', 0x1, 'a', 0x2, 'b', 0x3, 'i', 0x4, 'o', 0x5, 'p', 0x6, 'o', 0x7, 'l', 0x8, 'i', 0x9, 'm', 0xa, 'e', 0xb, 'n', 0xc, 'i', 0xd };
    bgfx::dbgTextImage(
                0,
                0,
                20,
                1,
                data,
                1);
   // bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
    //bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
   // bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
    //bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
    const bgfx::Stats* stats = bgfx::getStats();
    bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
    // Enable stats or debug text.
    bgfx::setDebug(false ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
    // Advance to next frame. Process submitted rendering primitives.
    bgfx::frame();

    requestUpdate();
}

void ZDBGFXWindow::renderLater()
{
     requestUpdate();
}

bool ZDBGFXWindow::event(QEvent *event)
{

    switch (event->type()) {
    case QEvent::Show:
        cout<<"Show Expose"<<endl;
        this->initBGFX();
        renderNow();
        break;
    case QEvent::Close:
        cout<<"Hide Close"<<endl;
        isInit=false;
        this->destroy();
        bgfx::shutdown();
        break;
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
    return true;
}

void ZDBGFXWindow::resizeEvent(QResizeEvent * event)
{
    this->width = event->size().width();
    this->height =event->size().height();
    if (isExposed())
        renderNow();

}

void ZDBGFXWindow::exposeEvent(QExposeEvent *)
{
//    if (isExposed())
//        renderNow();
}


