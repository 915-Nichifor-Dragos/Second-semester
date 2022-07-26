#pragma once
#include "DynamicVector.h"

typedef DynamicVector* URElem;

typedef void(*destroyFct)(void*);

typedef struct {
	int capacity, size;
	URElem* elems;
	destroyFct destroy;
}DynamicUndoRedo;

DynamicUndoRedo* create_dynamic_undo_redo(int capacity, destroyFct destroy);

void free_dynamic_undo_redo(DynamicUndoRedo* v);

void add_dynamic_undo_redo(DynamicUndoRedo* v, URElem p);

void test_dynamic_undo_redo();