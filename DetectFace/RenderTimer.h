#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

#include "wx/wx.h"
#include "wx/window.h"

#include "BasicDrawPane.h"

class RenderTimer : public wxTimer {
private:
    BasicDrawPane *pane;

public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start();
};

#endif