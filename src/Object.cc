#include <iostream>
//#include <iostream>
//#include <cstdlib>
//#include <cstring>
//#include <string.h>
//#include <string>

#include "Object.hh"


namespace octetos
{
namespace core
{	
        Object::~Object()
        {
#ifdef COLLETION_ASSISTANT
                if(parent != NULL)
                {
                        parent->removeChild(this);
                }
                if(countChilds > 0)
                {
                        std::cerr << "Una instacia de '" << typeid(*this).name() << "' termino sin que todos sus hijos terminaran  primero" << std::endl;
                } 
#endif
        }
        
        Object::Object()
        {
#ifdef COLLETION_ASSISTANT
                countChilds = 0;
                parent = NULL;
#endif
        }
        
#ifdef COLLETION_ASSISTANT
        unsigned int Object::getCountChilds()
        {
                return countChilds;
        }
        void Object::addChild(Object* child)
        {
                countChilds++;
                child->parent = this;
        }
        void Object::removeChild(Object* child)
        {
                countChilds--;
                child->parent = NULL;
        }
#endif

}
}
