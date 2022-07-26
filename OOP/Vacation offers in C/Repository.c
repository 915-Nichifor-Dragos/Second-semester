#define _CRT_SECURE_NO_WARNINGS
#include "Offer.h"
#include "Repository.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Repository* create_repository(DynamicVector* v)
{
	/*
	The function that creates a structure of type Repository, the 'storage' of our application.

	v - the dynamic vector associated as a storage

	return: returns the created repository
	*/
	if (v == NULL)
		return NULL;

	Repository* repo = malloc(sizeof(Repository));

	if (repo == NULL)
		return NULL;

	repo->offers = v;
	return repo;
}

void destroy_repository(Repository* repo)
{
	/*
	This function destroys the repository.

	repo - the repository we want to destroy

	return:
	*/
	if (repo == NULL)
		return;
	else
	{
		destroy_dynamic_vector(repo->offers);
		free(repo);
	}
}

int add_repository(Repository* repo, Offer* p)
{
	/*
	Adds a new offer in the repository

	repo - the repository
	p - the offer

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	for (int i = 0; i < repo->offers->size; i++)
	{
		if (strcmp(p->destination, repo->offers->elems[i]->destination) == 0 && strcmp(p->departure_date, repo->offers->elems[i]->departure_date) == 0)
		{
			return 0;
		}
	}
	add_dynamic_vector(repo->offers, p);
	return 1;
}

int remove_repository(Repository* repo, char* destination, char* departure_date)
{
	/*
	Removes an offer in the repository

	repo - the repository
	destination - the destination of the offer we want to remove
	departure_date - the departure_date of the offer we want to remove

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	for (int i = 0; i < repo->offers->size; i++)
	{
		if (strcmp(destination, repo->offers->elems[i]->destination) == 0 && strcmp(departure_date, repo->offers->elems[i]->departure_date) == 0)
		{
			remove_dynamic_vector(repo->offers, repo->offers->elems[i]);
			return 1;
		}
	}
	return 0;
}

int update_repository(Repository* repo, char* destination, char* departure_date, char* type, int price)
{
	/*
	Updates an offer that is in the repository

	repo - the repository
	destination - the destination of the offer we want to remove
	departure_date - the departure_date of the offer we want to remove
	type - the new type
	price - the new price

	return: 0 if the operation fails, 1 if the operation doesn't fail
	*/
	for (int i = 0; i < repo->offers->size; i++)
	{
		if (strcmp(destination, repo->offers->elems[i]->destination) == 0 && strcmp(departure_date, repo->offers->elems[i]->departure_date) == 0)
		{
			update_offer(repo->offers->elems[i], type, price);
			return 1;
		}
	}
	return 0;
}

void test_repository()
{
	DynamicVector* vector = create_dynamic_vector(100, &destroy_offer);
	Repository* repo = create_repository(vector);

	Offer* offer1 = create_offer("Seaside", "Barcelona", "2020/10/14", 300);
	add_repository(repo, offer1);
	assert(repo->offers->size == 1);

	update_repository(repo, offer1->destination, offer1->departure_date, "ABC", -1);
	assert(strcmp(repo->offers->elems[0]->type, "ABC") == 0);
	assert(strcmp(repo->offers->elems[0]->destination, "Barcelona") == 0);
	assert(strcmp(repo->offers->elems[0]->departure_date, "2020/10/14") == 0);
	assert(repo->offers->elems[0]->price == 300);

	remove_repository(repo, offer1->destination, offer1->departure_date);
	assert(repo->offers->size == 0);

	destroy_repository(repo);
}