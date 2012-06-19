#ifndef CONSOLE_DIALOG_H
#define CONSOLE_DIALOG_H

#include "wx/wx.h"

class ConsoleDialog : public wxDialog 
{
	private:
	
	protected:
	
	public:
		ConsoleDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ConsoleDialog();

		wxTextCtrl* txt;
};

#endif