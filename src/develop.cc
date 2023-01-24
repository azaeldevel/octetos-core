
#include <iostream>

#include "lexer.hh"

struct Person_test1
{
	const char* name;
	const char* ap;
	const char* am;
	int age;

	bool operator < (const Person_test1& obj) const 
	{
		size_t i = 0;
		while(true)
		{			
			if(name[i] == '\0' or obj.name[i] == '\0') return false; 
			
			if(name[i] < obj.name[i]) 
			{
				return true;
			}
			else if(name[i] > obj.name[i]) 
			{
				size_t j = 0;
				while(true)
				{
					if(ap[j] < obj.ap[j]) 
					{
						return true;
					}
					else if(ap[j] > obj.ap[j]) 
					{
						return false;
					}
					j++;
				}
				return false;
			}	
			i++;
		}
		
		return false;
	}
	bool operator > (const Person_test1& obj) const 
	{
		size_t i = 0;
		{			
			if(name[i] == '\0' or obj.name[i] == '\0') return false; 
			
			if(name[i] > obj.name[i]) 
			{
				return true;
			}
			else if(name[i] < obj.name[i]) 
			{
				size_t j = 0;
				while(true)
				{
					if(ap[j] > obj.ap[j]) 
					{
						return true;
					}
					else if(ap[j] < obj.ap[j]) 
					{
						return false;
					}
					j++;
				}
				return false;
			}			
		}
		
		return true;
	}
	void print(std::ostream& out)const
	{
		out << name;
		if(ap) out << " " << ap;
		if(am) out << " " << am;		
		out << " " << age;
		out << "\n";
	}
};

Person_test1 persons_array[] {
	{"Azael","Reyes","Martinez",36},
	{"Juan","Reyes","Prado",60},
	{"Ines","Lopez","martinez",36},
	{"Juan","Muños","Prado",50},
	{"Zaul","Muños","Muriarte",50},	
	{"Maria","Rosass","Muriarte",50},
	{"Juan","Muños","Prado",60},
	{"Juan","Valdez","Prado",60},
};
/*oct::core::Wrapper<testRow_1> rows_array2{
	{"Azael","Reyes","Martinez",36},
	{"Juan","Reyes","Prado",60},
	{"Ines","Lopez","martinez",36},
	{"Juan","Muños","Prado",50},
	
};*/
enum class semver_tokes : int
{
	none,
	major,
	minor,
	patch,
	stage,
	build,
	
	minus,
	puls,
	dot,
};


int main(int argc, char* argv[])
{
	OCTETOS_CORE_DECLSPCE_DLL
	
	return EXIT_SUCCESS;
}
