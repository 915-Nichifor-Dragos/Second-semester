#include "DynamicVector.h"
#include <stdlib.h>
#include "Offer.h"
#include <assert.h>

DynamicVector* create_dynamic_vector(int capacity, destroyFct destroy)
{
	/*
	The function that creates a structure of type DynamicVector, a dynamic vector used to store offers

	capacity - the maximum capacity of the dynamic vector
	destroy - the function used to destroy each element of the vector (destroy_offer)

	return: returns the created dynamic vector
	*/
	DynamicVector* v = malloc(sizeof(DynamicVector));
	if (v == NULL)
		return NULL;
	v->capacity = capacity;
	v->size = 0;
	v->elems = malloc(sizeof(TElem) * v->capacity);
	if (v->elems == NULL)
	{
		free(v);
		return NULL;
	}

	v->destroy = destroy;

	return v;
}

void destroy_dynamic_vector(DynamicVector* v)
{
	/*
	This function destroys all the contents of the vector, as well as the vector itself.

	v - the vector we want to destroy

	return:
	*/
	if (v == NULL)
		return;
	for (int i = 0; i < v->size; i++)
		v->destroy(v->elems[i]);
	free(v->elems);
	free(v);
}

void resize(DynamicVector* v)
{
	/*
	In case the capacity of the vector v is exceeded, it doubles the size of the vector

	v - the vector

	return:
	*/
	if (v == NULL)
		return;
	v->capacity *= 2;
	TElem* new_elems = malloc(sizeof(TElem) * v->capacity);
	for (int i = 0; i < v->size; i++)
		new_elems[i] = v->elems[i];
	free(v->elems);
	v->elems = new_elems;
}

void add_dynamic_vector(DynamicVector* v, TElem p)
{
	/*
	Adds a new offer in the dynamic vector v

	v - the dynamic vector
	p - the offer we add

	return:
	*/
	if (v == NULL)
		return;
	if (v->size == v->capacity)
	{
		int old_capacity = v->capacity;
		resize(v);
		if (old_capacity == v->capacity)
			return;
	}
	v->elems[v->size++] = p;
}

void remove_dynamic_vector(DynamicVector* v, TElem p)
{
	/*
	Removes an offer element in the dynamic vector v

	v - the dynamic vector
	p - the offer we remove

	return:
	*/
	if (v == NULL)
		return;
	for (int i = 0; i < v->size; i++)
	{
		if (v->elems[i] == p)
		{
			v->destroy(v->elems[i]);
			for (int j = i + 1; j < v->size; j++)
				v->elems[j - 1] = v->elems[j];
			v->size--;
			return;
		}
	}
}

DynamicVector* make_a_copy_dynamic_undo_redo(DynamicVector* vector)
{
	/*
	Creates a copy of the dynamic array 'vector'

	vector - the array we want to copy

	return: the copy of the array
	*/
	DynamicVector* copy = create_dynamic_vector(vector->capacity, vector->destroy);
	for (int i = 0; i < vector->size; i++)
	{
		Offer* offer = create_offer(vector->elems[i]->type, vector->elems[i]->destination, vector->elems[i]->departure_date, vector->elems[i]->price);
		add_dynamic_vector(copy, offer);
	}
	return copy;
}

void test_dynamic_vector()
{
	DynamicVector* vector = create_dynamic_vector(1, &destroy_offer);
	Offer* offer1 = create_offer("Seaside", "Barcelona", "2020/10/14", 300);
	Offer* offer2 = create_offer("City break", "Atena", "2020/11/17", 210);
	assert(vector->capacity == 1);
	assert(vector->size == 0);
	add_dynamic_vector(vector, offer1);
	add_dynamic_vector(vector, offer2);
	assert(vector->capacity == 2);
	assert(vector->size == 2);
	remove_dynamic_vector(vector, offer1);
	assert(vector->size == 1);

	DynamicVector* vector2 = make_a_copy_dynamic_undo_redo(vector);
	assert(vector2->size == 1);
	assert(vector->capacity == 2);

	destroy_dynamic_vector(vector2);
	destroy_dynamic_vector(vector);
}