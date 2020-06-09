#include <map>
#include <cassert>
#include <algorithm>

#include "utils.h"

static std::map<std::string, Trigger*> triggers;

bool contain(const std::string& name)
{
    auto iter = triggers.find(name);
    return iter != end(triggers);
}

void insert(const std::string& name, Trigger* ptr)
{
    triggers[name] = ptr;
}

Trigger* lookup(const std::string& name)
{
    auto iter = triggers.find(name);
    
    if (iter != end(triggers))
    {
        return (*iter).second;
    };
    return nullptr;
}


std::istream& read_trigger_config(std::istream& is, TriggerList& list)
{
    list.clear();
    std::string line;
    while(std::getline(is, line))
    {
        if (line.size() == 0 || (line[0] == '#')|| (line[0]=='/' && line[1] == '/') ) continue;

        std::vector<std::string> words = split(line);
        if (words[0] == "ADD")
        {
            for(size_t idx = 1; idx<words.size(); ++idx)
            {
                std::string name = words[idx];
                assert(contain(name));
                list.push_back(lookup(name));
            }
        } else {
            std::string name{words[0]}, tclass{words[1]}, param{words[2]};
            Trigger* trigger = nullptr;
            if (tclass == "TITLE")
                trigger = new TitleTrigger(param);
            else if (tclass == "DESCRIPTION")
                trigger = new DescriptionTrigger(param);
            else if (tclass == "AFTER")
                trigger = new AfterTrigger(param);
            else if (tclass == "BEFORE")
                trigger = new BeforeTrigger(param);
            else if (tclass == "AND" || tclass == "OR" )
            {
                Trigger *a = lookup(param), *b = lookup(words[3]);
                if (tclass == "AND")
                    trigger = new AndTrigger(a, b);
                else
                    trigger = new OrTrigger(a, b);
            }
            else if (tclass == "not")
            {
                Trigger* p_trigger = triggers[param];
                trigger = new NotTrigger(p_trigger);
            }
            if (trigger != nullptr){
                triggers[name] = trigger;
            }
        }
    }
    return is;
}

// helper

time_t string_to_datetime(const std::string &str)
{
    char *cha = (char *)str.data();                                                 // 将string转换成char*。
    tm tm_;                                                                         // 定义tm结构体。
    int year, month, day, hour, minute, second;                                     // 定义时间的各个int临时变量。
    sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second); // 将string存储的日期时间，转换为int临时变量。
    tm_.tm_year = year - 1900;                                                      // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month - 1;                                                         // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
    tm_.tm_mday = day;                                                              // 日。
    tm_.tm_hour = hour;                                                             // 时。
    tm_.tm_min = minute;                                                            // 分。
    tm_.tm_sec = second;                                                            // 秒。
    tm_.tm_isdst = 0;                                                               // 非夏令时。
    time_t t_ = mktime(&tm_);                                                       // 将tm结构体转换成time_t格式。
    return t_;                                                                      // 返回值。
}

system_clock::time_point convert_ts(const std::string &str)
{
    time_t tt = string_to_datetime(str);
    return system_clock::from_time_t(tt);
}

std::string calc_guid(std::string &title, std::string &description)
{
    std::string guid;
    std::size_t h1 = std::hash<std::string>{}(title);
    std::size_t h2 = std::hash<std::string>{}(description);

    guid = std::to_string(h1 ^ (h2 << 1));

    return guid;
}

// split 
static bool space(char c)
{
	return isspace(c) || c==',';
}

static bool not_space(char c)
{
	return !space(c);
}
std::vector<std::string> split(const std::string& s){
    std::vector<std::string> ret;
    using sz_type = std::string::size_type;

    sz_type i = 0;

    while(i!=s.size()){

        while(i != s.size() && space(s[i]))
            ++i;

        sz_type j= i;
        while(j != s.size() && not_space(s[j]))
            ++j;

        if(i!=j){
            ret.push_back(s.substr(i,j-i));
            i=j;
        }
    }

    return ret;
}
