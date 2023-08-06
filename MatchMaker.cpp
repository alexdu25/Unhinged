#include "MatchMaker.h"
#include <unordered_set>
#include <vector>
#include "provided.h"
#include <algorithm>
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
:memberdb(mdb),translator(at)
{
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	vector<EmailCount> ret;
	PersonProfile pp = *(memberdb.GetMemberByEmail(email));
	AttValPair avp;
	unordered_set<string> allpairs,emailsadded;
	for(int i=0;;i++){
		if(pp.GetAttVal(i,avp)==false) break;
		vector<AttValPair> pairs = translator.FindCompatibleAttValPairs(avp);
		for(int i=0;i<pairs.size();i++) allpairs.insert(pairs[i].attribute+","+pairs[i].value);
	}
	for(unordered_set<string>::iterator itr=allpairs.begin();itr!=allpairs.end();itr++){
		string tempstr = *itr;
		AttValPair tempavp;
		for(int i=0;i<tempstr.length();i++){
			if(tempstr[i]==','){
				tempavp.attribute = tempstr.substr(0,i);
				tempavp.value = tempstr.substr(i+1,tempstr.length()-i-1);
				break;
			}
		}
		vector<string> allemails = memberdb.FindMatchingMembers(tempavp);
		for(int i=0;i<allemails.size();i++){
			PersonProfile person = *(memberdb.GetMemberByEmail(allemails[i]));
			AttValPair avp2;
			int counter = 0;
			for(int j=0;;j++){
				if(person.GetAttVal(j,avp2)==false) break;
				if(allpairs.find(avp2.attribute+","+avp2.value)!=allpairs.end()) counter++;
			}
			if(counter>=threshold){
				if(emailsadded.find(allemails[i])==emailsadded.end()){
					emailsadded.insert(allemails[i]);
					EmailCount ec = EmailCount(allemails[i],counter);
					ret.push_back(ec);
				}
			}
		}
	}
	sort(ret.begin(),ret.end(),comp);
	return ret;
}