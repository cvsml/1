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

using namespace std;
using namespace cv;
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
    frame = new MyFrame();
    frame->Show();

    return true;
} 
