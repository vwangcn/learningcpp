#pragma once
#include <string>
#include <iostream>
#include <regex>

#include <SFML/Network.hpp>

#include "newsstory.h"


std::string& trim(std::string &s);
NewsStories do_fetch(const std::string& header, const std::string& uri);
NewsStories fetch();