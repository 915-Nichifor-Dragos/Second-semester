#include "Matrix.h"
#include <exception>
#include <iostream>
#include <string.h>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	this->lines = nrLines;
	this->columns = nrCols;
	this->size = 0;
	this->capacity = 1;
	vectorLines = new TElem[nrLines + 1];
	vectorColumns = new TElem[this->capacity];
	vectorValues = new TElem[this->capacity];
	for (int i = 0; i <= nrLines; i++)
		vectorLines[i] = 0;
	// Time complexity: BC = WC = AC: theta(this->lines + 1) ; we have to initialise the 'vectorLines' with 0's on each position
	// Space complexity -> theta(1) ; does not use auxiliary space
}


Matrix::~Matrix() {
	delete[] this->vectorLines;
	delete[] this->vectorColumns;
	delete[] this->vectorValues;
	// Time complexity: BC = WC = AC: theta(1)
	// Space complexity -> theta(1) ; does not use auxiliary space
}

void Matrix::resize()
{
	this->capacity = this->capacity * 2;
	TElem* colVect = new TElem[this->capacity];
	TElem* valVect = new TElem[this->capacity];

	for (int i = 0; i < this->size; i++)
	{
		colVect[i] = this->vectorColumns[i];
		valVect[i] = this->vectorValues[i];
	}

	delete[] this->vectorColumns;
	delete[] this->vectorValues;
	this->vectorColumns = colVect;
	this->vectorValues = valVect;
}

int Matrix::nrLines() const {
	return this->lines;
	// Time complexity: BC = WC = AC: theta(1) ; no loops, only returns the value
	// Space complexity -> theta(1) ; does not use auxiliary space
}


int Matrix::nrColumns() const {
	return this->columns;
	// Time complexity: BC = WC = AC: theta(1) ; no loops, only returns the value
	// Space complexity -> theta(1) ; does not use auxiliary space
}


TElem Matrix::element(int i, int j) const {
	if (i < 0 or i > nrLines() - 1)
		throw exception();
	if (j < 0 or j > nrColumns() - 1)
		throw exception();
	
	for (int column = vectorLines[i]; column < vectorLines[i + 1]; column++)
	{
		if (vectorColumns[column] == j)
		{
			return vectorValues[column];
		}
	}
	return NULL_TELEM;
	// Time complexity : theta(this->lines) / best case -> theta(1) ; the element is the 1st element different than 0 on that line
	//                                        worst case -> theta(this->lines) ; all the elements before the element are different than 0 
	//                                                                           and the element is the last on that line
	//                                        average case -> theta(((this->lines)*(this->lines + 1))/this->lines) ; the element could be on any column in 
	//																												 the given line
	// Total time complexity: theta(this->lines)
	// Space complexity -> theta(1) ; does not use auxiliary space
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 or i > this->lines - 1)
		throw exception();
	if (j < 0 or j > this->columns - 1)
		throw exception();

	TElem previous = element(i, j);
	int current_position = vectorLines[i + 1];
	bool found = false;

	for (int column = vectorLines[i]; column < vectorLines[i + 1]; column++)
	{
		if (j == vectorColumns[column])
		{
			found = true;
			current_position = column;
			break;
		}
		if (j < vectorColumns[column])
		{
			current_position = column;
			break;
		}
	}

	if (found == false)
	{
		this->size += 1;
		if (this->size == this->capacity)
			resize();

		for (int aux = vectorLines[nrLines()]; aux > current_position; aux--)
		{
			vectorColumns[aux] = vectorColumns[aux - 1];
			vectorValues[aux] = vectorValues[aux - 1];
		}

		for (int aux = i + 1; aux <= nrLines(); aux++)
			vectorLines[aux] += 1;
		vectorColumns[current_position] = j;
		vectorValues[current_position] = e;
	}
	else if (found == true)
	{	
		vectorValues[current_position] = e;
	}

	return previous;
	// Time complexity : theta() / best case -> theta(1) ; the element on position i and j already exists and only needs to be modified, so we 
	//													   do not have to move all the elements in the 'vectorLines' one position to the right
	//							   worst case -> theta(this->lines * this->columns - 1) ; if all the elements in the matrix are different than 0, 
	//                                                                                    except the one on position (0, 0) and we want to modify 
	//                                                                                    this one, we must move (this->lines * this->columns) - 1 elements to 
	//                                                                                    the right in the 'vectorColumns' and 'vectorValues' vectors
	// Total time complexity: theta(this->lines * this->columns - 1)
	// Space complexity -> theta(sizeof(TElem)) ~ theta(sizeof(1)) ~ theta(1) if TElem is an integer ; we hold the previous element on position                                                                                              i and j in order to return it
}

void Matrix::setElemsOnCol(int col, TElem elem)
{
	if (col < 0 or col > this->columns - 1)
		throw exception();
	
	for (int i = 0; i < nrLines(); i++)
		this->modify(i, col, elem);
}