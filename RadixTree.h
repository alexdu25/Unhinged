#ifndef RADIXTREEH
#define RADIXTREEH

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "utility.h"
#include "PersonProfile.h"

class PersonProfile;
template <typename ValueType>
struct Node{
    bool hasVal;
    std::string str;
    ValueType val;
    Node* children[128];
    ~Node(){
        for(int i=0;i<128;i++){
            if(children[i]!=nullptr) delete children[i];
        }
    }
};

template<typename ValueType>
class RadixTree {
public:
 RadixTree();
 ~RadixTree();
 void insert(std::string key, const ValueType& value);
 ValueType* search(std::string key) const;
private:
 Node<ValueType>* root;
};

template<typename ValueType> RadixTree<ValueType>::RadixTree(){
    root = new Node<ValueType>();
    root->hasVal = false;
    for(int i=0;i<128;i++){
        root->children[i]=nullptr;
    }
}

template<typename ValueType> RadixTree<ValueType>::~RadixTree(){
    delete root;
}

template<typename ValueType> void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
    Node<ValueType>* curnode = root;
    std::string query = key;
    while(query!=""){
        if(curnode->children[query[0]]==nullptr){
            Node<ValueType>* newnode = new Node<ValueType>();
            newnode->hasVal = true;
            newnode->str = query;
            newnode->val = value;
            curnode->children[query[0]] = newnode;
            return;
        }
        else{
            std::string curstring = curnode->children[query[0]]->str;
            if(query==curstring){
                curnode->children[query[0]]->val = value;
                curnode->children[query[0]]->hasVal = true;
                return;
            }
            int ind = -1;
            for(int i=curstring.size();i>0;i--){
                if(i<=query.size() && query.substr(0,i)==curstring.substr(0,i)){
                    ind = i;
                    break;
                }
            }
            if(ind==query.size()){//query is ABC, curstring is ABCD, so need to make a new node ABC and put D as new child
                std::string remstr = "";
                for(int i=ind;i<curstring.size();i++) remstr += curstring[i];
                Node<ValueType>* newnode = new Node<ValueType>();
                Node<ValueType>* temp = curnode->children[query[0]];
                newnode->hasVal = true;
                newnode->val = value;
                newnode->str = query;
                newnode->children[remstr[0]] = curnode->children[query[0]];
                curnode->children[query[0]] = newnode;
                temp->str = remstr;
                return;
            }
            else if(ind==curstring.size()){//ind==curstring.size()){//query is ABCD, curstring is ABC, so need to recurse with query D
                std::string remstr = "";
                for(int i=ind;i<query.size();i++) remstr += query[i];
                Node<ValueType>* newcur = curnode->children[query[0]];
                query = remstr;
                curnode = newcur;
            }
            else{//query is ABCDE, curstring is ABDC, need AB, 2 branches CDE and DC
                std::string rem1 = query.substr(ind,query.size()-ind);//CDE
                std::string rem2 = curstring.substr(ind,curstring.size()-ind);//DC
                Node<ValueType>* newnode = new Node<ValueType>();
                Node<ValueType>* newnode1 = new Node<ValueType>();//CDE
                newnode1->str = rem1;
                newnode1->hasVal = true;
                newnode1->val = value;
                newnode->str = query.substr(0,ind);//AB
                newnode->hasVal = false;
                newnode->children[rem1[0]] = newnode1;
                newnode->children[rem2[0]] = curnode->children[query[0]];
                newnode->children[rem2[0]]->str = rem2;
                curnode->children[query[0]] = newnode;
                return;
            }
        }
    }
}

template<typename ValueType> ValueType* RadixTree<ValueType>::search(std::string key) const{
    ValueType* ret = nullptr;
    std::string tempstr = key;
    Node<ValueType>* curnode = root;
    while(tempstr.length()>0){
        if(curnode->children[tempstr[0]]==nullptr) return nullptr;
        std::string curstring = curnode->children[tempstr[0]]->str;
        if(tempstr.size()<curstring.size()) return nullptr;
        if(tempstr.substr(0,curstring.size())!=curstring) return nullptr;
        if(tempstr==curstring) return &(curnode->children[tempstr[0]]->val);
        if(tempstr.length()>0) curnode = curnode->children[tempstr[0]];
        tempstr = tempstr.substr(curstring.size(),tempstr.size()-curstring.size());
    }
    if(curnode->hasVal==true) ret = &(curnode->val);
    return ret;
}

#endif