
#include <iostream>

#include "Mail.hh"


int main()
{
	std::cout << "Sending ...";
	octetos::core::Message msg;
	octetos::core::SMTP smtp;
	smtp.send();
	std::cout << " sended.\n";
}
