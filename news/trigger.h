#pragma once

#include <vector>
#include <string>

#include <stdexcept>
#include <chrono>

#include "newsstory.h"

using std::chrono::system_clock;

class Trigger
{
private:
    virtual bool doevaluate(const NewsStory&) const = 0;

public:
    bool evaluate(const NewsStory& story)
    {
        return doevaluate(story);
    }
};

using TriggerList = std::vector<Trigger*>;

class PhraseTrigger: public Trigger
{
public:
    PhraseTrigger(const std::string& phrase)
    : phrase_{phrase} 
    {}

protected:
   bool is_phrase_in(const std::string& text) const;

private:
    bool doevaluate(const NewsStory&) const
    {
        return true;
    }

private:
    std::string phrase_;
};


class TitleTrigger: public PhraseTrigger
{
public:
    TitleTrigger(const std::string phrase)
    : PhraseTrigger(phrase)
    {}
private:
    bool doevaluate(const NewsStory& story) const
    {
        return is_phrase_in(story.Title());
    }
};

class DescriptionTrigger: public PhraseTrigger
{
public:
    DescriptionTrigger(const std::string phrase)
    : PhraseTrigger(phrase)
    {}
private:
    bool doevaluate(const NewsStory& story) const
    {
        return is_phrase_in(story.Description());
    }
};


class TimeTrigger:public Trigger
{
public:
    TimeTrigger(const std::string str);
    
private:
    bool doevaluate(const NewsStory& story) const
    {
        return true;
    }

protected:
    system_clock::time_point tm_;
};

class BeforeTrigger: public TimeTrigger
{
public:
    BeforeTrigger(const std::string str)
    : TimeTrigger(str)
    {}

private:
    bool doevaluate(const NewsStory& story) const
    {
        return story.Pubdate() > tm_;
    }
};

class AfterTrigger: public TimeTrigger
{
public:
    AfterTrigger(const std::string tstr)
    : TimeTrigger(tstr)
    {}

private:
    bool doevaluate(const NewsStory& story) const
    {
        return story.Pubdate() < tm_;
    }
};


class NotTrigger: public Trigger
{
public:
    NotTrigger(Trigger* t)
    : t_{t}
    {}

private:
    bool doevaluate(const NewsStory& story) const
    {
        return not t_->evaluate(story);
    }
private:
    Trigger* t_;
};

class AndTrigger: public Trigger
{
public:
    AndTrigger(Trigger *a, Trigger *b)
    : a_{a}, b_{b}
    {}

private:
    bool doevaluate(const NewsStory& story) const
    {
        return a_->evaluate(story) && b_->evaluate(story);
    }
private:
    Trigger *a_, *b_;
};

class OrTrigger: public Trigger
{
public:
    OrTrigger(Trigger *a, Trigger *b)
    : a_{a}, b_{b}
    {}

private:
    bool doevaluate(const NewsStory& story) const
    {
        return a_->evaluate(story) || b_->evaluate(story);
    }
private:
    Trigger *a_, *b_;
};

