#pragma once
#include "Offer.h"
#include "DynamicVector.h"

typedef struct
{
	DynamicVector* offers;
}Repository;

Repository* create_repository();

void destroy_repository(Repository*);

int add_repository(Repository*, Offer*);

int remove_repository(Repository*, char*, char*);

int update_repository(Repository*, char*, char*, char*, int);

void test_repository();