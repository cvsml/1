#include "ImagePane.h"
#include "wx/dcbuffer.h"
#include "Logger.h"

BEGIN_EVENT_TABLE(ImagePane, wxPanel)
EVT_PAINT(ImagePane::paintEvent)
END_EVENT_TABLE()

ImagePane::ImagePane(wxPanel *parent, wxString file, wxBitmapType format) : wxPanel(parent) 
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	image.LoadFile(file, format);
}

ImagePane::ImagePane(wxPanel *parent, wxBitmap &image) : wxPanel(parent) 
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	setImage(image);
}

ImagePane::~ImagePane()
{

}

void ImagePane::setImage(wxBitmap &image)
{
	this->image = image;
}

void ImagePane::paintEvent(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

	if(image.Ok())
	{
		dc.DrawBitmap(image, 0, 0, false);
	}
}