#pragma once
#include "Repository.h"

typedef struct {
	Repository* repo;

}Controller;

Controller* create_controller(Repository*);

void destroy_controller(Controller*);

int add_controller(Controller*, char*, char*, char*, int);

int remove_controller(Controller*, char*, char*);

int update_controller(Controller*, char*, char*, char*, int);

DynamicVector* print_search_string_destination_controller(Controller*, char*);

DynamicVector* print_search_string_type_date_controller(Controller*, char*, char*);

void test_controller();