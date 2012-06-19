#ifndef WX_APP
#define WX_APP

#include "wx/wx.h"
#include "wx/window.h"

#define _USE_MATH_DEFINES

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

#include "MyFrame.h"
 
class MyApp : public wxApp {
private:
    bool OnInit();
    MyFrame *frame;

public:

};

#endif