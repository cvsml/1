#include "Logger.h"

Logger *logger = 0;

Logger::Logger(wxTextCtrl *txtBox)
{
	this->txtBox = txtBox;
}

Logger::~Logger()
{

}

void Logger::print(string text)
{
	if(txtBox)
		txtBox->AppendText(wxString(text.c_str(), wxConvUTF8));
}

void Logger::printLine(string text)
{
	print(text);
	print(string("\n"));
}