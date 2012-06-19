#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "wx/wx.h"

using namespace std;

class Logger {
private:
	wxTextCtrl *txtBox;

public:
	Logger(wxTextCtrl *txtBox);
	~Logger();

	void print(string text);
	void printLine(string text);
};

extern Logger *logger;

#endif