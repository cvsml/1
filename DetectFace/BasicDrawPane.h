#ifndef BASIC_DRAW_PANE_H
#define BASIC_DRAW_PANE_H

#include "wx/wx.h"
#include "Game.h"
//#include "SequenceRenderer.h"
//#include "MyFrame.h"

class MyFrame;
class SequenceRenderer;
class BasicDrawPane : public wxPanel { 
private:
	void drawIplImage(IplImage *image, wxDC &dc);
	Game game;
	std::shared_ptr<SequenceRenderer> sequenceRenderer;
	void drawSequence();
	MyFrame *parentFrame;

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

#endif