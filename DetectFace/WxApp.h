#ifndef WX_APP
#define WX_APP

#include "wx/wx.h"
#include "wx/window.h"

#define _USE_MATH_DEFINES

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

class BasicDrawPane;
 
class RenderTimer : public wxTimer {
private:
    BasicDrawPane* pane;

public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start();
};
 
class BasicDrawPane : public wxPanel { 
private:
	void drawIplImage(IplImage *image, wxDC &dc);

public:
    BasicDrawPane(wxFrame* parent);
	~BasicDrawPane();

	CvCapture *capture;
	IplImage *frame, *frame_copy;

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);
    
    DECLARE_EVENT_TABLE()
};
 
class MyFrame;
 
class MyApp : public wxApp {
private:
    bool OnInit();
    MyFrame* frame;

public:

};

class MyFrame : public wxFrame
{
    RenderTimer* timer;
    BasicDrawPane* drawPane;
    
public:
    MyFrame();
    ~MyFrame();
    void onClose(wxCloseEvent& evt);

    DECLARE_EVENT_TABLE()
};
 
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
END_EVENT_TABLE()

#endif