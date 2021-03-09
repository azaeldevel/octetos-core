
#ifndef MUPOSYS_MAIL_HH
#define MUPOSYS_MAIL_HH

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

namespace octetos::core
{

class Message
{
public:
	Message();
	static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
private:
	
};

class SMTP
{
private:
	CURL *curl;
	std::string server;
	int port;
	std::string username;
	std::string password;
	static const char *payload_text[];
public:
	//
	SMTP();
	~SMTP();
	void send(const Message* msg = NULL);
	static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);
};


} 

#endif