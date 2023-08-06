#ifndef MATCHMAKERH
#define MATCHMAKERH

#include "MemberDatabase.h"
#include "RadixTree.h"
#include "AttributeTranslator.h"
#include <vector>
#include <set>

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase &memberdb;
    const AttributeTranslator &translator;
};

#endif