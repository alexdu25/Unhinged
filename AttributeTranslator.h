#ifndef ATTRIBUTETRANSLATORH
#define ATTRIBUTETRANSLATORH

#include "RadixTree.h"
#include "provided.h"
#include <set>

class AttributeTranslator{
    public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    private:
    RadixTree<std::set<std::string>>* rt;
};

#endif