#include "MemberDatabase.h"
#include <fstream>
#include <set>
using namespace std;

MemberDatabase::MemberDatabase() {
	pairToEmail = new RadixTree<vector<string>>();
	emailToProfile = new RadixTree<PersonProfile*>();
}

MemberDatabase::~MemberDatabase() {
	delete pairToEmail;
	delete emailToProfile;
	for(int i=0;i<tbd.size();i++){
		delete tbd[i];
	}
}

bool MemberDatabase::LoadDatabase(std::string filename) {
	ifstream fin(filename);
	if (fin.fail()) return false;
	string name,email,str;
	while (getline(fin, name)) {
		getline(fin, email);
		int n=0;
		string tempn;
		getline(fin, tempn);
		while (tempn != "") {
			n *= 10;
			n += tempn[0] - '0';
			tempn = tempn.substr(1, tempn.size() - 1);
		}
		PersonProfile* pp = new PersonProfile(name, email);
		tbd.push_back(pp);
		for (int i = 0; i < n; i++) {
			getline(fin, str);
			AttValPair avp;
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == ',') {
					avp.attribute = str.substr(0, j);
					avp.value = str.substr(j + 1, str.length() - j - 1);
					break;
				}
			}
			pp->AddAttValuePair(avp);
			if (pairToEmail->search(str) == nullptr) {
				vector<string> v;
				v.push_back(email);
				pairToEmail->insert(str, v);
			}
			else {
				(*(pairToEmail->search(str))).push_back(email);
			}
		}
		if (emailToProfile->search(email) == nullptr) {
			emailToProfile->insert(email, pp);
		}
		else {
			return false;
		}
		getline(fin,str);
	}
	return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
	vector<string> ret;
	if (pairToEmail->search(input.attribute + "," + input.value) == nullptr){
		return ret;
	}
	ret = *(pairToEmail->search(input.attribute + "," + input.value));
	return ret;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
	if(emailToProfile->search(email)==nullptr) return nullptr;
	return *(emailToProfile->search(email));
}