#ifndef IMAGE_PANE_H
#define IMAGE_PANE_H

#include "wx/wx.h"
#include "wx/window.h"

class ImagePane : public wxPanel { 
private:
	wxBitmap image;

public:
    ImagePane(wxPanel *parent, wxString file, wxBitmapType format);
	ImagePane(wxPanel *parent, wxBitmap &image);
	~ImagePane();

	void setImage(wxBitmap &image);

    void paintEvent(wxPaintEvent& evt);

    DECLARE_EVENT_TABLE()
};
 
#endif