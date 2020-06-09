#include "newsstory.h"
#include "utils.h"
#include "feedparser.h"

Stories *Stories::instance_ = nullptr;

NewsStory::NewsStory(const std::string& guid, const std::string& title, const std::string& link, const std::string& description, const std::string& str)
:  title_{title}, link_{link}, description_{description}, pub_date_{ convert_ts(str)}
{
    guid_ = calc_guid(title_, description_);
}

void NewsStory::set(const std::string& title, const std::string& link, const std::string& description, const std::string& str)
{
    title_ = title;
    link_ = link;
    description_ = description;
    pub_date_ = convert_ts(str);

    guid_ = calc_guid(title_, description_);
}

std::ostream &operator<<(std::ostream &os, const NewsStory &story)
{
    os << story.Guid() << " "
       << story.Title() << " "
       << story.Link();

    return os;
}

std::istream &operator>>(std::istream &is, NewsStory &story)
{
    std::string title, link, description, pubdate;
    is >> title >> link >> description;
    std::getline(is, pubdate);

    story.set(title, link, description, pubdate);

    return is;
}

Stories *Stories::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new Stories();
    return instance_;
}

inline void Stories::doFectch()
{
    stories_ = fetch();
}

