#include "DynamicUndoRedo.h"
#include "DynamicVector.h"
#include <stdlib.h>
#include <assert.h>

DynamicUndoRedo* create_dynamic_undo_redo(int capacity, destroyFct destroy)
{
	/*
	The function that creates a structure of type DynamicUndoRedo, a dynamic vector used to store undo and redo operations

	capacity - the maximum capacity of the dynamic vector
	destroy - the function used to destroy each element of the vector

	return: returns the created dynamic vector
	*/
	DynamicUndoRedo* v = malloc(sizeof(DynamicUndoRedo));
	if (v == NULL)
		return NULL;
	v->capacity = capacity;
	v->size = 0;
	v->elems = malloc(sizeof(URElem) * v->capacity);
	if (v->elems == NULL)
	{
		free(v);
		return NULL;
	}

	v->destroy = destroy;

	return v;
}

void free_dynamic_undo_redo(DynamicUndoRedo* v)
{
	/*
	This function destroys all the contents of the vector.
	
	v - the vector we want to empty

	return:
	*/
	if (v == NULL)
		return;
	for (int i = 0; i < v->size; i++)
		 v->destroy(v->elems[i]);
	v->size = 0;
}

void resize_undo_redo(DynamicUndoRedo* v)
{
	/*
	In case the capacity of the vector v is exceeded, it doubles the size of the vector

	v - the vector

	return:
	*/
	if (v == NULL)
		return;
	v->capacity *= 2;
	URElem* new_elems = malloc(sizeof(URElem) * v->capacity);
	for (int i = 0; i < v->size; i++)
		new_elems[i] = v->elems[i];
	free(v->elems);
	v->elems = new_elems;
}

void add_dynamic_undo_redo(DynamicUndoRedo* v, URElem p)
{
	/*
	Adds a new element in the dynamic vector v

	v - the dynamic vector
	p - the element we want to add

	return:
	*/
	if (v == NULL)
		return;
	if (v->size == v->capacity)
	{
		int old_capacity = v->capacity;
		resize_undo_redo(v);
		if (old_capacity == v->capacity)
			return;
	}
	v->elems[v->size++] = p;
}

void test_dynamic_undo_redo()
{
	DynamicUndoRedo* vector = create_dynamic_undo_redo(1, &destroy_dynamic_vector);

	DynamicVector* v1 = create_dynamic_vector(100, &destroy_offer);
	assert(vector->capacity == 1);
	DynamicVector* v2 = create_dynamic_vector(100, &destroy_offer);
	add_dynamic_undo_redo(vector, v1);
	add_dynamic_undo_redo(vector, v2);
	assert(vector->capacity == 2);
	assert(vector->size == 2);

	free_dynamic_undo_redo(vector);

	assert(vector->size == 0);
	free(vector->elems);
	free(vector);
}