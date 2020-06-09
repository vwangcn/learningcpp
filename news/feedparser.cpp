#include "feedparser.h"


std::string urls[][2] = {
    {"http://www.chinanews.com/", "rss/scroll-news.xml"},
    {"http://www.chinanews.com/", "rss/importnews.xml"},
    {"http://www.chinanews.com/", "rss/china.xml"},
    {"http://www.chinanews.com/", "rss/world.xml"},
    {"http://www.chinanews.com/", "rss/mil.xml"},
    {"http://www.chinanews.com/", "rss/society.xml"},
    {"http://www.chinanews.com/", "rss/finance.xml"}
};


std::string& trim(std::string &s) 
{
    if (s.empty()) 
    {
        return s;
    }
 
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

NewsStories do_fetch(const std::string& header, const std::string& uri)
{
    std::cout << "fetch: "<<header<<"/"<<uri<<"\n";
    
    NewsStories stories;
    sf::Http http{header};
    
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    request.setUri(uri);
    request.setHttpVersion(1, 1); // HTTP 1.1
    sf::Http::Response response = http.sendRequest(request);

    // 
    std::cout << "status: " << response.getStatus() << std::endl;
    // std::cout << "HTTP version: " << response.getMajorHttpVersion() << "." << response.getMinorHttpVersion() << std::endl;
    // std::cout << "Content-Type header:" << response.getField("Content-Type") << std::endl;
    std::string content=response.getBody();
    // std::cout << "body: " << content << "\n";

    std::regex pattern{"<item><title>([\\s\\S]*?)</title><link>([\\s\\S]*?)</link><description>([\\s\\S]*?)</description><pubDate>([\\s\\S]*?)</pubDate></item>"};
    std::smatch result;
    std::string::const_iterator start = content.begin();
    std::string::const_iterator end = content.end();
    auto count = 1;
    while(std::regex_search(start, end, result, pattern, std::regex_constants::match_any))
    {
        std::string title = result[1];
        std::string link = result[2];
        std::string description = result[3];
        std::string pubdate = result[4];
        description = trim(description);

        NewsStory story;
        story.set(title, link, description, pubdate);
        //std::cout << count << ": "<< story << "\n";
        stories.push_back(story);

        start = result[0].second;
        ++count;
    }

    return stories;
}

NewsStories fetch()
{
    NewsStories stories;
    for(auto idx=0; idx<sizeof(urls)/sizeof(urls[0]); ++idx)
    {
        NewsStories items = do_fetch(urls[idx][0], urls[idx][1]);
        std::copy(items.begin(), items.end(), std::back_inserter(stories));
    }
    return stories;
}