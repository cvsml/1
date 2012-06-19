#include "MyFrame.h"

MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Simon"), wxPoint(50,50), wxSize(640, 480))
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	wxInitAllImageHandlers();

	wxBoxSizer* frameSizer;
	frameSizer = new wxBoxSizer( wxVERTICAL );
	
	guiPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 640,-1 ), wxTAB_TRAVERSAL );
	guiPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	gestureDefaultImage.LoadFile(wxT("resources\\images\\empty.bmp"), wxBITMAP_TYPE_ANY);
	gestureLookLeftImage.LoadFile(wxT("resources\\images\\lookLeft.bmp"), wxBITMAP_TYPE_ANY);
	gestureLookRightImage.LoadFile(wxT("resources\\images\\lookRight.bmp"), wxBITMAP_TYPE_ANY);
	gestureEyeLeftImage.LoadFile(wxT("resources\\images\\eyeLeft.bmp"), wxBITMAP_TYPE_ANY);
	gestureEyeRightImage.LoadFile(wxT("resources\\images\\eyeRight.bmp"), wxBITMAP_TYPE_ANY);

	wxGridSizer* imagesSizer;
	imagesSizer = new wxGridSizer( 2, 2, 0, 0 );

	gestureLookLeft = new ImagePane(guiPanel, gestureDefaultImage);
    imagesSizer->Add(gestureLookLeft, 1, wxEXPAND);

	gestureLookRight = new ImagePane(guiPanel, gestureDefaultImage);
    imagesSizer->Add(gestureLookRight, 1, wxEXPAND);

	gestureEyeLeft = new ImagePane(guiPanel, gestureDefaultImage);
    imagesSizer->Add(gestureEyeLeft, 1, wxEXPAND);

	gestureEyeRight = new ImagePane(guiPanel, gestureDefaultImage);
    imagesSizer->Add(gestureEyeRight, 1, wxEXPAND);

	guiPanel->SetSizer( imagesSizer );
	guiPanel->Layout();
	frameSizer->Add( guiPanel, 1, wxEXPAND | wxALL, 5 );
	
	drawPane = new BasicDrawPane(this);
	frameSizer->Add( drawPane, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( frameSizer );
	this->Layout();
	frameSizer->Fit( this );
	menuBar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* newGameMenuItem;
	newGameMenuItem = new wxMenuItem( fileMenu, wxID_NEW, wxString( wxT("New Game") ) + wxT('\t') + wxT("N"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( newGameMenuItem );
	
	wxMenuItem* exitMenuItem;
	exitMenuItem = new wxMenuItem( fileMenu, wxID_EXIT, wxString( wxT("Exit") ) + wxT('\t') + wxT("E"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( exitMenuItem );
	
	menuBar->Append( fileMenu, wxT("File") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* instructionsMenuItem;
	instructionsMenuItem = new wxMenuItem( helpMenu, wxID_HELP, wxString( wxT("Instructions") ) , wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( instructionsMenuItem );
	
	wxMenuItem* aboutMenuItem;
	aboutMenuItem = new wxMenuItem( helpMenu, wxID_ABOUT, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( aboutMenuItem );
	
	menuBar->Append( helpMenu, wxT("Help") ); 
	
	optionsMenu = new wxMenu();
	wxMenuItem* optionsMenuItem;
	optionsMenuItem = new wxMenuItem( optionsMenu, wxID_PREFERENCES, wxString( wxT("Options") ) + wxT('\t') + wxT("O"), wxEmptyString, wxITEM_NORMAL );
	optionsMenu->Append( optionsMenuItem );
	
	menuBar->Append( optionsMenu, wxT("Options") ); 
	
	this->SetMenuBar( menuBar );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( this->GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame::OnClose));
	this->Connect( newGameMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnNewGame ) );
	this->Connect( exitMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnExit ) );
	this->Connect( instructionsMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnInstructions ) );
	this->Connect( aboutMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnAbout ) );
	this->Connect( optionsMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnOptions ) );

	timer = new RenderTimer(drawPane);
    Show();
    timer->start();
}

MyFrame::~MyFrame()
{
    delete timer;

	// Disconnect Events
	this->Disconnect(GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame::OnClose));
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnNewGame ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnExit ) );
	this->Disconnect( wxID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnInstructions ) );
	this->Disconnect( wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnAbout ) );
	this->Disconnect( wxID_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::menuOnOptions ) );
}

void MyFrame::OnClose(wxCloseEvent& evt)
{
    timer->Stop();
	drawPane->Close();
	evt.Skip();
}

void MyFrame::menuOnNewGame( wxCommandEvent& event )
{

}

void MyFrame::menuOnExit( wxCommandEvent& event )
{
	Close();
}

void MyFrame::menuOnInstructions( wxCommandEvent& event )
{

}

void MyFrame::menuOnAbout( wxCommandEvent& event )
{
	wxMessageBox(wxT("Simon 2012 by Assaf Muller, Noam Slomianko and Tomer Levin"), wxT("About"), wxOK | wxICON_INFORMATION);
}

void MyFrame::menuOnOptions( wxCommandEvent& event )
{

}