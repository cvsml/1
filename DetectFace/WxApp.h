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
    void OnClose(wxCloseEvent& evt);

    DECLARE_EVENT_TABLE()
};
 
BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_CLOSE(BasicDrawPane::OnClose)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

class MyFrame;
 
class MyApp : public wxApp {
private:
    bool OnInit();
    MyFrame* frame;

public:

};

class MyFrame : public wxFrame
{
private:
    RenderTimer *timer;

	wxMenuBar *menuBar;
    wxMenu *fileMenu;
    wxMenu *helpMenu;

	void createMenu();
	void menuOnAbout(wxCommandEvent& WXUNUSED(event));
	void menuOnExit(wxCommandEvent& WXUNUSED(event));

public:
	BasicDrawPane* drawPane;

    MyFrame();
    ~MyFrame();
    void OnClose(wxCloseEvent& evt);

    DECLARE_EVENT_TABLE()
};
 
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::OnClose)
EVT_MENU(wxID_EXIT, MyFrame::menuOnExit)
EVT_MENU(wxID_ABOUT, MyFrame::menuOnAbout)
END_EVENT_TABLE()

#endif