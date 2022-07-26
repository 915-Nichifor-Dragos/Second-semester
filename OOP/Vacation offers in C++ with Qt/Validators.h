#pragma once

#include <string>
#include "Exceptions.h"

using namespace std;

class inputValidator {

public:

	static void checkDate(string date);

	static void checkHour(string hour);
};