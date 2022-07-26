#pragma once
#include <exception>
#include <string>

using namespace std;

class inputException: public exception{

private:

	string message;

public:
	inputException(const string message) { this->message = message + string("\nPlease enter a valid input!\n\n"); };

	~inputException() {};

	virtual string what() { return this->message; };

};


class addException: public exception
{
private:
	string message;

public:
	addException(const string message) { this->message = message + string("\nYou can not add the same element twice!\n\n"); }

	~addException() {};

	virtual string what() { return this->message; };
};


class updateRemoveException : public exception
{
private:
	string message;

public:
	updateRemoveException(const string message) { this->message = message + string("\nYou can remove or update an event that already exists!\n\n"); };

	~updateRemoveException() {};

	virtual string what() { return this->message; };
};


class commandException : public exception
{
private:
	string message;

public:
	commandException(const string message) { this->message = message; };

	~commandException() {};

	virtual string what() { return this->message; };
};


class FileException : public exception
{
private:
	string message;

public:
	FileException(const string message) { this->message = message; };

	~FileException() {};

	virtual string what() { return this->message; };
};


class inputFileException: public exception{

private:

	string message;

public:
	inputFileException(const string message) { this->message = message + string("\nPlease enter a valid input in your file!\n\n"); };

	~inputFileException() {};

	virtual string what() { return this->message; };

};

class startException : public exception {

private:

	string message;

public:
	startException(const string message) { this->message = message + string("\nThe program could not start! Please try again!\n\n"); };

	~startException() {};

	virtual string what() { return this->message; };

};

// remove function with find in repo