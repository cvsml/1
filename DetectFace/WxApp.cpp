#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
 
#include "WxApp.h"
#include "wx/dcbuffer.h"
#include "wx/wx.h"

#define _USE_MATH_DEFINES

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
#include <cmath>
#include <sstream>

#include "Game.h"

using namespace std;
using namespace cv;

Game game;

RenderTimer::RenderTimer(BasicDrawPane* pane) : wxTimer()
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
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
    frame = new MyFrame();
    frame->Show();

    return true;
} 

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()
 
MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Simon"), wxPoint(50,50), wxSize(640, 480))
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new BasicDrawPane(this);
    sizer->Add(drawPane, 1, wxEXPAND);
    SetSizer(sizer);
        
    timer = new RenderTimer(drawPane);
    Show();
    timer->start();
}

MyFrame::~MyFrame()
{
    delete timer;
}
void MyFrame::onClose(wxCloseEvent& evt)
{
	cvReleaseCapture(&drawPane->capture);
	cvReleaseImage(&drawPane->frame);
    timer->Stop();
    evt.Skip();
}

BasicDrawPane::BasicDrawPane(wxFrame* parent) : wxPanel(parent)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    // Images to capture the frame from video or camera or from file
    frame = 0;
	frame_copy = 0;

	game.newGame();

	capture = 0;
    capture = cvCaptureFromCAM(0);
}
 
BasicDrawPane::~BasicDrawPane()
{

}

void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
    render(dc);
}

void BasicDrawPane::drawIplImage(IplImage *image, wxDC &dc) 
{
	cvCvtColor(image, image, CV_BGR2RGB);
	wxImage wxi(image->width, image->height, (unsigned char *)image->imageData, true);
	wxBitmap result(wxi);
	dc.DrawBitmap(result, 0, 0);
}

void BasicDrawPane::render(wxDC &dc)
{
	 // Capture the frame and load it in IplImage
    if(!cvGrabFrame(capture)) {
        return;
	}

    frame = cvRetrieveFrame(capture);
    // If the frame does not exist, quit the loop
    if(!frame)
        return;
            
    // Allocate framecopy as the same size of the frame
	float scale = 640.0f / (float)frame->width;
    if(!frame_copy) {
		frame_copy = cvCreateImage(cvSize((int)(frame->width * scale), (int)(frame->height * scale)), IPL_DEPTH_8U, frame->nChannels);
	}

    cvFlip(frame, frame_copy, 1); // Flip around the vertical axis, so the image is mirrored

	game.update(frame_copy);

	drawIplImage(frame_copy, dc);

	dc.SetTextForeground(wxColour(wxString("Red", wxConvUTF8)));
	dc.DrawText(wxString(game.getFPS().c_str(), wxConvUTF8), 40, 40); 
	
    //dc.SetBackground(*wxWHITE_BRUSH);
   // dc.Clear();
}