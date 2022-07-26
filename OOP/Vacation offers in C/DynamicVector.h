#pragma once
#include "Offer.h"

typedef Offer* TElem;

typedef void(*destroyFct)(void*);

typedef struct {
	int capacity, size;
	TElem* elems;
	destroyFct destroy;
}DynamicVector;

DynamicVector* create_dynamic_vector(int capacity, destroyFct destroy);

void destroy_dynamic_vector(DynamicVector* v);

void add_dynamic_vector(DynamicVector* v, TElem p);

void remove_dynamic_vector(DynamicVector* v, TElem p);

DynamicVector* make_a_copy_dynamic_undo_redo(DynamicVector* vector);

void test_dynamic_vector();