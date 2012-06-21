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

#include "Logger.h"
#include "FMod.h"

using namespace std;
using namespace cv;
 
IMPLEMENT_APP(MyApp)
 
BEGIN_EVENT_TABLE(MyApp, wxApp)
EVT_CLOSE(MyApp::OnClose)
END_EVENT_TABLE()

bool MyApp::OnInit()
{
	frame = 0;
	console = 0;
	sound = new Sound();

    frame = new MyFrame();
    frame->Show();

	console = new ConsoleDialog(frame, -1, wxT("Console"));

#ifdef APP_DEBUG
		console->Show();
#endif

	logger = new Logger(console->txt);

    return true;
} 

void MyApp::OnClose(wxCloseEvent& evt)
{
	if(logger)
	{
		delete logger;
		logger = 0;
	}

	if(sound)
	{
		delete sound;
		sound = 0;
	}
}
