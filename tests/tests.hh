
#include <iostream>

#define CU_ASSERT(T) if(not T) std::cout << "Fail on " << __FILE__ << ":" << __LINE__ << "\n";
