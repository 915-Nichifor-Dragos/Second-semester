#define _CRT_SECURE_NO_WARNINGS
#include "Controller.h"
#include "Repository.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Controller* create_controller(Repository* repo)
{
	/*
	The function that creates a structure of type Controller

	repo - the repository associated

	return: returns the created controller
	*/
	Controller* c = malloc(sizeof(Controller));
	if (c != NULL)
		c->repo = repo;
	return c;
}

void destroy_controller(Controller* c)
{
	/*
	This function destroys the controller.

	c - the controller we want to destroy

	return:
	*/
	if (c == NULL)
		return;
	destroy_repository(c->repo);
	free(c);
}

int add_controller(Controller* c, char* type, char* destination, char* departure_date, int price)
{
	/*
	Adds a new offer -> will call repository function, which is more detailed

	c - the current controller
	type - the type of the offer
	destination - the destination of the offer
	departure_date - the departure_date of the offer
	price - the price of the offer

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	Offer* offer = create_offer(type, destination, departure_date, price);
	return add_repository(c->repo, offer);
}

int remove_controller(Controller* c, char* destination, char* departure_date)
{
	/*
	Removes an offer -> will call repository function, which is more detailed

	c - the current controller
	destination - the destination of the offer
	departure_date - the departure_date of the offer

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	return remove_repository(c->repo, destination, departure_date);
}

int update_controller(Controller* c, char* destination, char* departure_date, char* type, int price)
{
	/*
	Updates an offer -> will call repository function, which is more detailed

	c - the current controller
	destination - the destination of the offer
	departure_date - the departure_date of the offer
	type - the new type
	price - the new price

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	return update_repository(c->repo, destination, departure_date, type, price);
}

DynamicVector* print_search_string_destination_controller(Controller* c, char* string)
{
	/*
	Creates a vector of offers that contain the string 'string'. If 'string' is empty, all the offers will be considered

	c - the current controller
	string - the string

	return: returns the dynamic vector of offers that satisfies the conditions
	*/
	DynamicVector* vector = create_dynamic_vector(c->repo->offers->size, &destroy_offer);
	int ok = 0;
	for (int i = 0; i < strlen(string); i++)
		if (string[i] != ' ')
			ok = 1;
	if (strlen(string) == 0 || ok == 0)
	{
		for (int i = 0; i < c->repo->offers->size; i++)
			add_dynamic_vector(vector, c->repo->offers->elems[i]);
	}
	else
	{
		for (int i = 0; i < c->repo->offers->size; i++)
		{
			if (strstr(c->repo->offers->elems[i]->destination, string) != NULL)
				add_dynamic_vector(vector, c->repo->offers->elems[i]);
		}
	}
	for (int i = 0; i < vector->size - 1; i++)
		for (int j = i + 1; j < vector->size; j++)
		{
			if (vector->elems[i]->price > vector->elems[j]->price)
			{
				Offer* offer = vector->elems[i];
				vector->elems[i] = vector->elems[j];
				vector->elems[j] = offer;
			}
		}
	return vector;
}

DynamicVector* print_search_string_type_date_controller(Controller* c, char* type, char* date)
{
	/*
	Creates a vector of offers that are of type 'type' and have the departure date after 'date'

	c - the current controller
	type - the type of the offer that are valid
	date - the date after which the offers are valid

	return: returns the dynamic vector of offers that satisfies the conditions
	*/
	DynamicVector* vector = create_dynamic_vector(c->repo->offers->size, &destroy_offer);

	for (int i = 0; i < c->repo->offers->size; i++)
	{
		if (strcmp(type, c->repo->offers->elems[i]->type) == 0)
		{
			if (strcmp(c->repo->offers->elems[i]->departure_date, date) > 0)
				add_dynamic_vector(vector, c->repo->offers->elems[i]);
		}
	}
	return vector;
}

void test_controller()
{
	DynamicVector* vector = create_dynamic_vector(100, &destroy_offer);
	Repository* repo = create_repository(vector);
	Controller* c = create_controller(repo);

	add_controller(c, "abc", "abcd", "2020/10/14", 150);
	assert(c->repo->offers->size == 1);
	assert(strcmp(repo->offers->elems[0]->type, "abc") == 0);
	assert(strcmp(repo->offers->elems[0]->destination, "abcd") == 0);
	assert(strcmp(repo->offers->elems[0]->departure_date, "2020/10/14") == 0);
	assert(repo->offers->elems[0]->price == 150);

	add_controller(c, "abcdef", "abcdef", "2021/03/10", 300);
	assert(c->repo->offers->size == 2);

	remove_controller(c, "abcdef", "2021/03/10");
	assert(c->repo->offers->size == 1);
	add_controller(c, "abcdef", "abcdef", "2021/03/10", 300);
	assert(c->repo->offers->size == 2);

	update_controller(c, "abcd", "2020/10/14", "NEW", 0);
	assert(strcmp(repo->offers->elems[0]->type, "NEW") == 0);
	assert(strcmp(repo->offers->elems[0]->destination, "abcd") == 0);
	assert(strcmp(repo->offers->elems[0]->departure_date, "2020/10/14") == 0);
	assert(repo->offers->elems[0]->price == 0);

	DynamicVector* v2 = print_search_string_destination_controller(c, "a");
	assert(v2->size == 2);
	free(v2->elems);
	free(v2);

	DynamicVector* v3 = print_search_string_type_date_controller(c, "NEW", "2020/09/11");
	assert(v3->size == 1);
	free(v3->elems);
	free(v3);

	destroy_controller(c);
}