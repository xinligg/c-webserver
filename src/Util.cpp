//
// Created by marvinle on 2019/2/1 12:18 PM.
//

#include "../include/Util.h"

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <sys/stat.h>


std::string& ltrim(std::string &str) {
    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(" \t"));
    return str;
}

std::string& rtrim(std::string &str) {
    if (str.empty()) {
        return str;
    }
    str.erase(str.find_last_not_of(" \t")+1);
    return str;
}

std::string& trim(std::string& str) {
    if (str.empty()) {
        return str;
    }

    ltrim(str);
    rtrim(str);
    return str;
}

int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}


void handle_for_sigpipe()
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if(sigaction(SIGPIPE, &sa, NULL))
        return;
}


int check_base_path(char *basePath) {
    struct stat file;
    if (stat(basePath, &file) == -1) {
        return -1;
    }
    // 不是目录 或者不可访问
    if (!S_ISDIR(file.st_mode) || access(basePath, R_OK) == -1) {
        return -1;
    }
    return 0;
}

std::vector<std::string> split(std::string str,std::string pattern = " ")
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str+=pattern;//扩展字符串以方便操作
  int size=str.size();
 
  for(int i=0; i<size; i++)
  {
    pos=str.find(pattern,i);
    if(pos<size)
    {
      std::string s=str.substr(i,pos-i);
      result.push_back(s);
      i=pos+pattern.size()-1;
    }
  }
  return result;
}

std::string genrandomstring(int length = 10)
{
	char ch;
	int flag;
    std::string string;
    srand((unsigned) time(NULL));

	for(int i=0; i<length; i++)
	{
		flag = rand()%3;
		switch (flag)
		{
			case 0:
				ch = 'A' + rand() % 26;
				break;
			 case 1:
				ch = 'a' + rand() % 26;
				break;
			 case 2:
			default:
				ch = '0' + rand() % 10;
				break;
		}
		string.push_back(ch);
	}
    return string;
}

