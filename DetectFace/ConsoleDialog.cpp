#include "ConsoleDialog.h"

ConsoleDialog::ConsoleDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetModal(false);
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	txt = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txt->SetMinSize( wxSize( 640,480 ) );
	txt->SetMaxSize( wxSize( 640,480 ) );
	
	bSizer1->Add( txt, 0, wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

ConsoleDialog::~ConsoleDialog()
{

}