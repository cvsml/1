#include "MyFrame.h"
#include "Logger.h"
#include "FMod.h"

MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Simon"), wxPoint(50,50), wxSize(640, 480))
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	wxInitAllImageHandlers();

	wxBoxSizer* frameSizer;
	frameSizer = new wxBoxSizer( wxVERTICAL );
	
	wxColour bg = wxColour(255, 255, 255);

	SetBackgroundColour(bg);

	wxBoxSizer* guiSizer;
	guiSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridSizer* leftSizer;
	leftSizer = new wxGridSizer( 0, 2, 0, 0 );
	
	leftSizer->SetMinSize(wxSize(100, -1 )); 
	guiSizer->Add( leftSizer, 0, 0, 5 );

	//guiPanel = new wxPanel( this, wxID_ANY, wxPoint(65, 0), wxSize(310, 310), wxTAB_TRAVERSAL );
	//guiPanel->SetBackgroundColour(bg);
	
	gestureDefaultImage.LoadFile(wxT("resources\\images\\empty.bmp"), wxBITMAP_TYPE_ANY);
	gestureLookLeftImage.LoadFile(wxT("resources\\images\\lookLeft.bmp"), wxBITMAP_TYPE_ANY);
	gestureLookRightImage.LoadFile(wxT("resources\\images\\lookRight.bmp"), wxBITMAP_TYPE_ANY);
	gestureEyeLeftImage.LoadFile(wxT("resources\\images\\eyeLeft.bmp"), wxBITMAP_TYPE_ANY);
	gestureEyeRightImage.LoadFile(wxT("resources\\images\\eyeRight.bmp"), wxBITMAP_TYPE_ANY);
	turnComputer.LoadFile(wxT("resources\\images\\pc.bmp"), wxBITMAP_TYPE_ANY);
	turnPlayer.LoadFile(wxT("resources\\images\\player.bmp"), wxBITMAP_TYPE_ANY);

	wxGridSizer* imagesSizer;
	imagesSizer = new wxGridSizer( 2, 2, 0, 0 );
	imagesSizer->SetMinSize(310, 310);
	imagesSizer->SetDimension(0, 0, 310, 310);

	gestureLookLeft = new ImagePane(this, gestureDefaultImage);
	gestureLookLeft->SetSize(160, 160);
	gestureLookLeft->setBackgroundColor(bg);
    imagesSizer->Add(gestureLookLeft, 1, wxALL);
	gestureLookLeft->SetWindowStyle(wxBORDER_SUNKEN);

	gestureLookRight = new ImagePane(this, gestureDefaultImage);
	gestureLookRight->SetSize(160, 160);
	gestureLookRight->setBackgroundColor(bg);
    imagesSizer->Add(gestureLookRight, 1, wxALL);
	gestureLookRight->SetWindowStyle(wxBORDER_THEME);

	gestureEyeLeft = new ImagePane(this, gestureDefaultImage);
	gestureEyeLeft->SetSize(160, 160);
	gestureEyeLeft->setBackgroundColor(bg);
    imagesSizer->Add(gestureEyeLeft, 1, wxALL);
	gestureEyeLeft->SetWindowStyle(wxBORDER_THEME);

	gestureEyeRight = new ImagePane(this, gestureDefaultImage);
	gestureEyeRight->SetSize(160, 160);
	gestureEyeRight->setBackgroundColor(bg);
    imagesSizer->Add(gestureEyeRight, 1, wxALL);
	gestureEyeRight->SetWindowStyle(wxBORDER_THEME);

	guiSizer->Add( imagesSizer, 0, wxALIGN_CENTER|wxALIGN_TOP, 5 );

	wxGridSizer* rightSizer;
	rightSizer = new wxGridSizer(0, 1, 0, 0);
	
	rightSizer->SetMinSize(wxSize(100,-1)); 
	turn = new ImagePane(this, turnComputer);
	turn->SetSize(170, 170);
	turn->setBackgroundColor(bg);
	rightSizer->Add(turn, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 0);
	
	guiSizer->Add( rightSizer, 0, wxALIGN_CENTER_VERTICAL, 0 );
	
	frameSizer->Add(guiSizer, 0, wxEXPAND, 5);
	
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

	if(sound)
	{
		lookLeftSound	= sound->loadSound("resources\\sounds\\1.wav");
		lookRightSound	= sound->loadSound("resources\\sounds\\2.wav");
		eyeLeftSound	= sound->loadSound("resources\\sounds\\3.wav");
		eyeRightSound	= sound->loadSound("resources\\sounds\\4.wav");
	}

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
	drawPane->newGame();
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

void MyFrame::render(GESTURE gesture)
{
	gestureLookLeft->setImage(gestureDefaultImage);
	gestureLookRight->setImage(gestureDefaultImage);
	gestureEyeLeft->setImage(gestureDefaultImage);
	gestureEyeRight->setImage(gestureDefaultImage);

	ImagePane *pane = getGesturePane(gesture);
	wxBitmap *bitmap = getGestureBitmap(gesture);

	if(pane && bitmap)
		pane->setImage(*bitmap);

	gestureLookLeft->Refresh();
	gestureLookRight->Refresh();
	gestureEyeLeft->Refresh();
	gestureEyeRight->Refresh();
}

wxBitmap* MyFrame::getGestureBitmap(GESTURE gesture)
{
	switch(gesture)
	{
		case GESTURE_LEFT:
			return &gestureLookLeftImage;
		break;

		case GESTURE_RIGHT:
			return &gestureLookRightImage;
		break;

		case GESTURE_LEFT_EYE:
			return &gestureEyeLeftImage;
		break;

		case GESTURE_RIGHT_EYE:
			return &gestureEyeRightImage;
		break;

		default:
			return &gestureDefaultImage;
		break;
	}
}

ImagePane* MyFrame::getGesturePane(GESTURE gesture)
{
	switch(gesture)
	{
		case GESTURE_LEFT:
			return gestureLookLeft;
		break;

		case GESTURE_RIGHT:
			return gestureLookRight;
		break;

		case GESTURE_LEFT_EYE:
			return gestureEyeLeft;
		break;

		case GESTURE_RIGHT_EYE:
			return gestureEyeRight;
		break;

		default:
			return NULL;
		break;
	}
}

FMOD::Sound* MyFrame::getGestureSound(GESTURE gesture)
{
	switch(gesture)
	{
		case GESTURE_LEFT:
			return lookLeftSound;
		break;

		case GESTURE_RIGHT:
			return lookRightSound;
		break;

		case GESTURE_LEFT_EYE:
			return eyeLeftSound;
		break;

		case GESTURE_RIGHT_EYE:
			return eyeRightSound;
		break;

		default:
			return NULL;
		break;
	}
}

void MyFrame::setGestureBorder(GESTURE gesture, wxColour color)
{
	ImagePane *pane = getGesturePane(gesture);

	if(pane)
	{
		pane->setBackgroundColor(color);
	}
}