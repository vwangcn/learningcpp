#include <iostream>
#include "trigger.h"
#include "newsstory.h"
#include "feedparser.h"


void test_trigger()
{
    //1 title trigger
    TitleTrigger trigger{"上海"};

    //2 stories
    NewsStories stories = fetch();

    //
}


int main()
{
    test_trigger();

    return 0;
}