#ifndef WX_APP
#define WX_APP

#include "wx/wx.h"

class MyApp : public wxApp
{
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Quit = 1,
    ID_About,
};

#endif