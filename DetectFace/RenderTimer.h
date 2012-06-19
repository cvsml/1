#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

#include "wx/wx.h"
#include "wx/window.h"

#include "BasicDrawPane.h"

class RenderTimer : public wxTimer {
private:
    wxPanel *pane;

public:
    RenderTimer(wxPanel *pane);
    void Notify();
    void start();
};

#endif