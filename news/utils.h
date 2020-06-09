#pragma once
#include <string>
#include <vector>
#include <chrono>

#include "trigger.h"


time_t string_to_datetime(const std::string &str);
std::chrono::system_clock::time_point convert_ts(const std::string &str);
std::string calc_guid(std::string& title, std::string& description);

std::vector<std::string> split(const std::string&);
std::istream& read_trigger_config(std::istream& is, TriggerList& list);
