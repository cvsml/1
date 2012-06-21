#ifndef IMAGE_PANE_H
#define IMAGE_PANE_H

#include "wx/wx.h"
#include "wx/window.h"

class ImagePane : public wxPanel { 
private:
	wxBitmap image;
	wxColour backgroundColor;
	void init(wxBitmap &image);

public:
    ImagePane(wxFrame *parent, wxString file, wxBitmapType format);
	ImagePane(wxFrame *parent, wxBitmap &image);

	~ImagePane();

	void setImage(wxBitmap &image);
    void paintEvent(wxPaintEvent& evt);
	void setBackgroundColor(wxColour backgroundColor);

    DECLARE_EVENT_TABLE()
};
 
#endif