#include "BasicDrawPane.h"
#include "Game.h"
#include "wx/dcbuffer.h"
#include "SequenceRenderer.h"

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_CLOSE(BasicDrawPane::OnClose)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(-1, -1), wxSize(640, 480), wxTAB_TRAVERSAL)
{
	parentFrame = (MyFrame*)parent;
	sequenceRenderer = 0;

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

void BasicDrawPane::OnClose(wxCloseEvent& evt)
{
	/*
	if(frame)
		cvReleaseImage(&frame);
	*/

	if(capture)
		cvReleaseCapture(&capture);

	evt.Skip();
}

void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);

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
	
	drawSequence();

    //dc.SetBackground(*wxWHITE_BRUSH);
   // dc.Clear();
}

void BasicDrawPane::drawIplImage(IplImage *image, wxDC &dc) 
{
	cvCvtColor(image, image, CV_BGR2RGB);
	wxImage wxi(image->width, image->height, (unsigned char *)image->imageData, true);
	wxBitmap result(wxi);
	dc.DrawBitmap(result, 0, 0);
}

void BasicDrawPane::drawSequence()
{
	if(game.isNewTurn())
	{
		sequenceRenderer = shared_ptr<SequenceRenderer>(new SequenceRenderer(game.getSequence(), parentFrame));
	}

	if(sequenceRenderer)
	{
		if(sequenceRenderer->done())
			sequenceRenderer.reset();
		else
			sequenceRenderer->render();
	}
}