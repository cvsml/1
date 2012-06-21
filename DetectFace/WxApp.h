#ifndef WX_APP
#define WX_APP

#include "wx/wx.h"
#include "wx/window.h"

#define _USE_MATH_DEFINES

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

#include "MyFrame.h"
#include "ConsoleDialog.h"

//#define APP_DEBUG 1

class MyApp : public wxApp {
private:
	virtual void OnClose(wxCloseEvent& evt);
    bool OnInit();
    MyFrame *frame;
	ConsoleDialog *console;

public:
	DECLARE_EVENT_TABLE()

};

#endif