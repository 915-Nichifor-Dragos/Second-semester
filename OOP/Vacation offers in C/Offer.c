#define _CRT_SECURE_NO_WARNINGS
#include "Offer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Offer* create_offer(char* type, char* destination, char* departure_date, int price)
{
	/*
	The function that creates a structure of type Offer

	type - the type of the offer
	destination - the destination of the offer
	departure_date - the departure date of the offer
	price - the price of the offer

	return: returns the created offer
	*/
	Offer* p = malloc(sizeof(Offer));
	if (p != NULL)
	{
		p->type = malloc(sizeof(char) * (strlen(type) + 1));
		if (p->type == NULL)
		{
			free(p);
			return NULL;
		}
		strcpy(p->type, type);
		p->destination = malloc(sizeof(char) * (strlen(destination) + 1));
		if (p->destination == NULL)
		{
			free(p->type);
			free(p);
			return NULL;
		}
		strcpy(p->destination, destination);
		p->departure_date = malloc(sizeof(char) * (strlen(departure_date) + 1));
		if (p->departure_date == NULL)
		{
			free(p->type);
			free(p->destination);
			free(p);
			return NULL;
		}
		strcpy(p->departure_date, departure_date);
		p->price = price;
		return p;
	}
	else
		return NULL;
}

void update_offer(Offer* p, char* type, int price)
{
	/*
	Updates an offer's type or price

	type - the new type
	price - the new price

	return:
	*/
	char str[20] = "-1";
	if (price != -1)
		p->price = price;
	if (strcmp(str, type) != 0)
	{
		p->type = realloc(p->type, sizeof(char) * (strlen(type) + 1));
		if (p->type != 0)
			strcpy(p->type, type);
	}

}

void destroy_offer(Offer* p)
{
	/*
	Destoryes the allocated memory for offer

	p - the offer we destroy

	return:A
	*/
	if (p == NULL)
		return;
	else
	{
		free(p->type);
		free(p->destination);
		free(p->departure_date);
		free(p);
		p = NULL;
	}
}

void test_offer()
{
	Offer* offer1 = create_offer("Seaside", "Barcelona", "2020/10/14", 300);
	assert(strcmp(offer1->type, "Seaside") == 0);
	assert(strcmp(offer1->destination, "Barcelona") == 0);
	assert(strcmp(offer1->departure_date, "2020/10/14") == 0);
	assert(offer1->price == 300);

	update_offer(offer1, "ABC", 500);

	assert(strcmp(offer1->type, "ABC") == 0);
	assert(offer1->price == 500);

	destroy_offer(offer1);
}