#include "ImagePane.h"
#include "wx/dcbuffer.h"
#include "Logger.h"

BEGIN_EVENT_TABLE(ImagePane, wxPanel)
EVT_PAINT(ImagePane::paintEvent)
END_EVENT_TABLE()

void ImagePane::init(wxBitmap &image)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	setImage(image);
}

ImagePane::ImagePane(wxFrame *parent, wxString file, wxBitmapType format) : wxPanel(parent) 
{
	image.LoadFile(file, format);
	init(image);
}

ImagePane::ImagePane(wxFrame *parent, wxBitmap &image) : wxPanel(parent) 
{
	init(image);
}

ImagePane::~ImagePane()
{

}

void ImagePane::setImage(wxBitmap &image)
{
	this->image = image;
	Refresh();
}

void ImagePane::paintEvent(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.SetBackground(backgroundColor);
    dc.Clear();

	if(image.Ok())
	{
		dc.DrawBitmap(image, 5, 5, false);
	}
}

void ImagePane::setBackgroundColor(wxColour backgroundColor)
{
	this->backgroundColor = backgroundColor;
	Refresh();
}