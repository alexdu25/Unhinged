#include "PersonProfile.h"
#include <string>
#include <vector>
#include <iterator>
#include <unordered_set>
using namespace std;

PersonProfile::PersonProfile(std::string name,std::string email){
    pname = name;
    pemail = email;
}

PersonProfile::~PersonProfile(){}
    
std::string PersonProfile::GetName() const{
    return pname;
}

std::string PersonProfile::GetEmail() const{
    return pemail;
}

void PersonProfile::AddAttValuePair(const AttValPair& attval){
    string tempstr = attval.attribute + "," + attval.value;
    pairs.insert(tempstr);
}

int PersonProfile::GetNumAttValPairs() const{
    return pairs.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if(attribute_num>=pairs.size()||attribute_num<0) return false;
    int counter = 0;
    for(unordered_set<string>::const_iterator itr=pairs.begin();itr!=pairs.end();itr++){
        if(counter==attribute_num){
            string tot = *itr;
            int ind = -1;
            for(int i=0;i<tot.length();i++){
                if(tot[i]==','){
                    ind = i;
                    break;
                }
            }
            string tempatt = tot.substr(0,ind);
            string tempval = "";
            for(int i=ind+1;i<tot.length();i++) tempval += tot[i];
            AttValPair tempavp = AttValPair(tempatt,tempval);
            attval = tempavp;
            return true;
        }
        counter++;
    }
    return false;
}