#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <iostream>

class NewsStory
{
public:
    NewsStory(): guid_{""}, title_{""}, link_{""}, description_{""} { }
    NewsStory(const std::string& guid, const std::string& title, const std::string& link, const std::string& description, const std::string& str);
public:
    void set(const std::string& title, const std::string& link, const std::string& description, const std::string& str);

public:
    // getter & setter
    std::string Guid() const
    {
        return guid_;
    }

    void Guid(std::string guid)
    {
        guid_ = guid;
    }
    std::string Title() const
    {
        return title_;
    }

    void Title(std::string title)
    {
        title_ = title;
    }

    std::string Link() const
    {
        return link_;
    }

    void Link(std::string link)
    {
        link_ = link;
    }

    std::string Description() const
    {
        return description_;
    }

    void Description(std::string description)
    {
        description_ = description;
    }

    std::chrono::system_clock::time_point Pubdate() const
    {
        return pub_date_;
    }

    void Pubdate(std::chrono::system_clock::time_point pub_date)
    {
        pub_date_ = pub_date;
    }

private:
    std::string guid_;
    std::string title_;
    std::string link_;
    std::string description_;
    std::chrono::system_clock::time_point pub_date_;
};

std::ostream &operator<<(std::ostream &os, const NewsStory &story);
std::istream &operator>>(std::istream &is, NewsStory &story);

using NewsStories = std::vector<NewsStory>;

class Stories{
public:
    static Stories* getInstance();

    void doFectch();

private:
    Stories() {};
    static Stories* instance_;

private:
    NewsStories stories_;
};
