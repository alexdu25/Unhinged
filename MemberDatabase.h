#ifndef MEMBERDATABASE
#define MEMBERDATABASE

#include "RadixTree.h"
#include "PersonProfile.h"
#include "provided.h"
#include <set>
#include <vector>

class MemberDatabase{
    public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    private:
    RadixTree<std::vector<std::string>>* pairToEmail;
    RadixTree<PersonProfile*>* emailToProfile;
    std::vector<PersonProfile*> tbd;
};

#endif