#ifndef BUFFER_HH
#define BUFFER_HH

class Buffer
{
private:
	char* buffer1;
	char* buffer2;
	short begin;
	short forward;
	short bsize;
	char* text;
public:
	Buffer(const char*);
	char get_char();
	char check_char(short);
	void proceed();
	void back();
	const char* get_text() const;
};

#endif
