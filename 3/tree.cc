
#include <stdexcept>

#include "tree.hh"

namespace oct::core::v3
{

    Branch::Branch() : childs(NULL),size(0)
    {
    }
    Branch::Branch(size_t s) : childs(new Node*[s]),size(s)
    {
    }
    Branch::~Branch()
    {
        if(childs) delete[] childs;
    }

    Node*& Branch::operator [](size_t i)
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }
    /*const Node*& Branch::operator [](size_t i) const
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }*/
    Node*& Branch::at(size_t i)
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }
    /*const Node*& Branch::at(size_t i) const
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }*/



    Root::Root(size_t size) : Branch(size)
    {
    }
}
