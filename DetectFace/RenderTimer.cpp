#include "RenderTimer.h"

RenderTimer::RenderTimer(BasicDrawPane *pane) : wxTimer()
{
    RenderTimer::pane = pane;
}
 
void RenderTimer::Notify()
{
    pane->Refresh();
}
 
void RenderTimer::start()
{
    wxTimer::Start(16);
}