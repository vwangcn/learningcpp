#include <iostream>
#include <fstream>

#include "feedparser.h"
#include "utils.h"

int main()
{
    NewsStories stories = fetch();
    TriggerList triggers;
    std::ifstream fs{"triggers.txt"};
    read_trigger_config(fs, triggers);

    for(auto& story: stories){
        for(auto& ptrigger: triggers)
            if (ptrigger->evaluate(story)){
                std::cout << story << "\n";
                break;
            }
    }

    return 0;
}