#pragma once

typedef struct {
	char* type;
	char* destination;
	char* departure_date;
	int price;
}Offer;

Offer* create_offer(char*, char*, char*, int);

void update_offer(Offer*, char*, int);

void destroy_offer(Offer*);

void test_offer();