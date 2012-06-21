#ifndef BASIC_DRAW_PANE_H
#define BASIC_DRAW_PANE_H

#include "wx/wx.h"
#include "Game.h"
#include <ctime>

class MyFrame;
class SequenceRenderer;

class BasicDrawPane : public wxPanel { 
private:
	void drawIplImage(IplImage *image, wxDC &dc);
	Game game;
	std::shared_ptr<SequenceRenderer> sequenceRenderer;

	void renderSequence();
	void renderPlayerGesture();

	MyFrame *parentFrame;

	time_t timeSinceBorderColored;
	GESTURE lastGesture;

public:
    BasicDrawPane(wxFrame* parent);
	~BasicDrawPane();

	CvCapture *capture;
	IplImage *frame, *frame_copy;

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);
    void OnClose(wxCloseEvent& evt);

	void newGame();

    DECLARE_EVENT_TABLE()
};

#endif