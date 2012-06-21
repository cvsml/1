#ifndef MY_FRAME_H
#define MY_FRAME_H

#include "wx/wx.h"
#include "BasicDrawPane.h"
#include "ImagePane.h"
#include "RenderTimer.h"
#include "FMod.h"

class MyFrame : public wxFrame
{
private:
    RenderTimer *timer;

	wxBitmap gestureLookLeftImage;
	wxBitmap gestureLookRightImage;
	wxBitmap gestureEyeLeftImage;
	wxBitmap gestureEyeRightImage;
	wxBitmap gestureDefaultImage;

	ImagePane *gestureLookLeft;
	ImagePane *gestureLookRight;
	ImagePane *gestureEyeLeft;
	ImagePane *gestureEyeRight;
	
	FMOD::Sound *lookLeftSound;
	FMOD::Sound *lookRightSound;
	FMOD::Sound *eyeLeftSound;
	FMOD::Sound *eyeRightSound;

protected:
	wxPanel *guiPanel;

	BasicDrawPane *drawPane;
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenu *helpMenu;
	wxMenu *optionsMenu;
		
	// Event handlers
	virtual void menuOnNewGame( wxCommandEvent& event );
	virtual void menuOnExit( wxCommandEvent& event );
	virtual void menuOnInstructions( wxCommandEvent& event );
	virtual void menuOnAbout( wxCommandEvent& event );
	virtual void menuOnOptions( wxCommandEvent& event );
	virtual void OnClose(wxCloseEvent& evt);

	ImagePane* getGesturePane(GESTURE gesture);
	wxBitmap* getGestureBitmap(GESTURE gesture);

public:
    MyFrame();
    ~MyFrame();

	void render(GESTURE gesture);
	void setGestureBorder(GESTURE gesture, wxColour color);

	ImagePane *turn;
	wxBitmap turnComputer;
	wxBitmap turnPlayer;

	FMOD::Sound* getGestureSound(GESTURE gesture);
};

#endif