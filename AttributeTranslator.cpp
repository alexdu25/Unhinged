#include <fstream>
#include "AttributeTranslator.h"
#include <cassert>
using namespace std;

AttributeTranslator::AttributeTranslator(){
    rt = new RadixTree<set<string>>();
}

AttributeTranslator::~AttributeTranslator(){
    delete rt;
}

bool AttributeTranslator::Load(std::string filename){
    ifstream fin(filename);
    if(fin.fail()) return false;
    string inp,firstatt,firstval,secondatt,secondval;
    while(getline(fin,inp)){
        parsestring(inp,firstatt,firstval,secondatt,secondval);
        if(rt->search(firstatt+","+firstval)==nullptr){
            set<string> temps;
            temps.insert(secondatt+","+secondval);
            rt->insert(firstatt+","+firstval,temps);
        }
        else{
            ( *(rt->search(firstatt+","+firstval)) ).insert(secondatt+","+secondval);
        }
        if(rt->search(secondatt+","+secondval)==nullptr){
            set<string> temps;
            rt->insert(secondatt+","+secondval,temps);
        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    vector<AttValPair> ret;
    string str = source.attribute + "," + source.value;
    auto temps = rt->search(str);
    if(temps==nullptr) return ret;
    for(auto itr=(*temps).begin();itr!=temps->end();itr++){
        string s = *itr;
        string tempatt,tempval;
        for(int i=0;i<s.length();i++){
            if(s[i]==','){
                tempatt=s.substr(0,i);
                s=s.substr(i+1,s.size()-i-1);
                break;
            }
        }
        tempval = s;
        AttValPair avp = AttValPair(tempatt,tempval);
        ret.push_back(avp);
    }
    return ret;
}

