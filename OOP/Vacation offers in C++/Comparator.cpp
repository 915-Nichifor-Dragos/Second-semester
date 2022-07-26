#include "Comparator.h"
#include <assert.h>
#include <vector>
#include "Utilities.h"

bool ComparatorAscendingByNumberOfPeople::compare(Event first, Event second)
{
    if (first.getNumberOfPeople() < second.getNumberOfPeople())
        return true;
    return false;
}

bool ComparatorAscendingByTitle::compare(Event first, Event second)
{
    if (first.getTitle()[0] < second.getTitle()[0])
        return true;
    return false;
}

void testComparator()
{
    DateTime data1 = DateTime{ "2021/11/30", "21:40" };
    DateTime data2 = DateTime{ "2021/01/06", "20:30" };
    DateTime data3 = DateTime{ "2021/01/19", "08:30" };

    Event e1 = Event { "Treasure Hunt in Carol Park", "Entertainment", data1, 500, "https://shop.secretromania.com/product/treasure-hunt-in-parcul-carol-din-bucuresti/" };
    Event e2 = Event { "Sports Festival", "Sports", data2, 200, "https://www.sportsfestival.com/" };
    Event e3 = Event { "Form Days 2022", "Music", data3, 100, "https://www.songkick.com/festivals/3298258-form-days/id/39465933-form-days-festival-2022" };

    vector<Event> events;
    events.push_back(e1);
    events.push_back(e2);
    events.push_back(e3);

    Comparator<Event>* c1 = new ComparatorAscendingByNumberOfPeople{};
    Comparator<Event>* c2 = new ComparatorAscendingByTitle{};

    customSort(events, c1);

    assert(events[0].getNumberOfPeople() == 100);
    assert(events[1].getNumberOfPeople() == 200);
    assert(events[2].getNumberOfPeople() == 500);

    customSort(events, c2);

    assert(events[0].getTitle() == "Form Days 2022");
    assert(events[1].getTitle() == "Sports Festival");
    assert(events[2].getTitle() == "Treasure Hunt in Carol Park");
}
