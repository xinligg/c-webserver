//#ifndef WEBSERVER_UTILS_H
//#define WEBSERVER_UTILS_H

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

std::string &ltrim(string &);

std::string &rtrim(string &);

std::string &trim(string &);

int setnonblocking(int fd);
void handle_for_sigpipe();

int check_base_path(char *basePath);

std::vector<std::string> split(std::string str,std::string pattern);
std::string genrandomstring(int length);

//#endif //WEBSERVER_UTILS_H
