#include "utility.h"
#include <vector>
#include <string>
using namespace std;

bool comp(EmailCount ec1,EmailCount ec2){
    return ec1.count>ec2.count || (ec1.count==ec2.count && ec1.email < ec2.email);
}

void parsestring(string str,string &firstatt,string &firstval,string &secondatt,string &secondval){
    for(int i=0;i<str.size();i++){
        if(str[i]==','){
            firstatt = str.substr(0,i);
            str = str.substr(i+1,str.size()-i-1);
            break;
        }
    }
    for(int i=0;i<str.size();i++){
        if(str[i]==','){
            firstval = str.substr(0,i);
            str = str.substr(i+1,str.size()-i-1);
            break;
        }
    }
    for(int i=0;i<str.size();i++){
        if(str[i]==','){
            secondatt = str.substr(0,i);
            str = str.substr(i+1,str.size()-i-1);
            break;
        }
    }
    secondval = str;
}