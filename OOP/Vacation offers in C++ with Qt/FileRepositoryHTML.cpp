#include "FileRepositoryHTML.h"

void FileRepositoryHTML::open()
{
	cout << "HTML file opening...\n\n";
	wstring op = wstring(this->outputfile.begin(), this->outputfile.end());
	LPCWSTR outputFilename = op.c_str();
	LPCWSTR command = L"open";
	ShellExecute(NULL, command, outputFilename, NULL, NULL, SW_SHOWNORMAL);
	//string op = string(this->outputfile.begin(), this->outputfile.end());
	//LPCSTR output = op.c_str();
	//ShellExecuteA(NULL, NULL, "chrome.exe",output , NULL, SW_SHOWMAXIMIZED);
}

void FileRepositoryHTML::write()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->data)
	{
		file << s;
	}
	file.close();

	ofstream out(this->outputfile);
	string htmlFormat = convertToHTMLFile();
	out << htmlFormat;
}

string FileRepositoryHTML::convertToHTMLFile()
{
	string str;
	str = str + "<!DOCTYPE html>\n<html>\n<head>\n<title>Event list</title>\n</head>\n";
	str = str + "<body>\n<table border=\"1\">\n<tr>\n<td>Title</td>\n<td>Description</td>\n<td>Date</td>\n<td>Hour</td>\n<td>Number of participants</td>\n<td>Link</td>\n</tr>\n";

	for (auto ev : this->data)
	{
		stringstream ss;
		ss << ev.getNumberOfPeople();
		str = str + "<tr>\n<td>" + ev.getTitle() + "</td>\n<td>" + ev.getDescription() + "</td>\n<td>" + ev.getEventDate().getDate() + "</td>\n<td>" +
			ev.getEventDate().getTime() + "</td>\n<td>" + ss.str() + "</td>\n<td>" + ev.getLink() + "</td>\n</tr>\n";
	}

	str = str + "</table>\n</body>\n</html>";
	return str;
}

FileRepositoryHTML::~FileRepositoryHTML()
{
	this->write();
}
