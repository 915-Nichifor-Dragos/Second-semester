#pragma once
#include "IdeaRepository.h"

#include <assert.h>

void testAdd()
{
	IdeaRepository ir("");
	ir.addElement(Idea{ "abc", "abcd", "abcde", 3 });

	assert(ir.getList()[0].getDescription() == "abc");
	assert(ir.getList()[0].getStatus() == "abcd");
	assert(ir.getList()[0].getCreator() == "abcde");
	assert(ir.getList()[0].getAct() == 3);

	ir.addElement(Idea{ "123", "1234", "12345", 2 });

	assert(ir.getList()[0].getDescription() == "123");
	assert(ir.getList()[0].getStatus() == "1234");
	assert(ir.getList()[0].getCreator() == "12345");
	assert(ir.getList()[0].getAct() == 2);
}

void testUpdate()
{
	IdeaRepository ir("");
	ir.addElement(Idea{ "abc", "abcd", "abcde", 3 });
	
	assert(ir.getList()[0].getStatus() == "abcd");
	ir.updateElement(0);
	assert(ir.getList()[0].getStatus() == "Accepted");
}