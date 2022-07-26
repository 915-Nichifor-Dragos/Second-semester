#include "RepositoryIssues.h"

#include <assert.h>

void testadd()
{
    RepositoryIssues repositoryI("");
    Issue i("abc", "open", "Andrei", "Sebastian");
    repositoryI.addElement(i);

    Issue i2;
    for (auto el : repositoryI.getList())
    {
        i2 = el;
    }

    assert(i2.getDescription() == "abc");
    assert(i2.getStatus() == "open");
    assert(i2.getReporter() == "Andrei");
    assert(i2.getSolver() == "Sebastian");

}

void testupdate()
{
    RepositoryIssues repositoryI("");
    Issue i("abc", "open", "Andrei", "");
    repositoryI.addElement(i);

    repositoryI.updateStatus(0, "Vlad");

    Issue i2;
    for (auto el : repositoryI.getList())
    {
        i2 = el;
    }

    assert(i2.getDescription() == i.getDescription());
    assert(i2.getReporter() == i.getReporter());
    assert(i2.getSolver() == "Vlad");
    assert(i2.getStatus() == "closed");
}