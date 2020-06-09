#include <regex>

#include "trigger.h"
#include "utils.h"


bool PhraseTrigger::is_phrase_in(const std::string& text) const
{
    std::string chars;
    for(auto& ch: text)
    {
        if (std::ispunct(ch))
        {
            if (chars[chars.size()-1] != ' ')
                chars += ' ';
        } else {
            chars += ch;
        }
    }
    std::string pattern = phrase_;
    std::regex reg(pattern);
    std::smatch match;
    std::regex_search(chars, match, reg);
    //std::cout << "match " <<phrase_ << ":"  << text << " "<< match.size() << "\n";
    return match.size()>0;
}


TimeTrigger::TimeTrigger(const std::string str)
{
    tm_ =  convert_ts(str);
}

