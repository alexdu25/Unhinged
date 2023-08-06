#ifndef PERSONPRO
#define PERSONPRO

#include "RadixTree.h"
#include "provided.h"
#include <unordered_set>

class PersonProfile{
    public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValuePair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    private:
    std::string pname;
    std::string pemail;
    std::unordered_set<std::string> pairs;
};

#endif