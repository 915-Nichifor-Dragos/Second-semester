#pragma once
#include "Controller.h"

typedef struct {
	Controller* c;
}UI;

UI* create_ui(Controller*);

void destroy_ui(UI*);

void start_ui(UI*);
