#include <iostream>
#include "Trie.h"

Trie::TrieNode::TrieNode() : endOfWord(false), children() {}

Trie::TrieNode::TrieNode(bool eow) : endOfWord(eow), children() {}

Trie::TrieNode::TrieNode(const TrieNode& toCopy) {
    this->endOfWord = toCopy.endOfWord;
    this->children = toCopy.children;
}

Trie::TrieNode::~TrieNode() {
    std::cout<<"TrieNode destructor called\n";
    /*for(auto& it : this->children) {
        delete it.second;
    }*/
}

bool Trie::TrieNode::isEndOfWord() const {
    return this->endOfWord;
}

void Trie::TrieNode::setEndOfWord(bool eow) {
    this->endOfWord = eow;
}

Trie::TrieNode* Trie::TrieNode::getChild(char symbol) {
	auto it  = this->children.find(symbol);
	TrieNode* res;

	if (it != this->children.end()) {
		res = it->second;
	}
	else {
		res = nullptr;
	}

	return res;
}

Trie::TrieNode* Trie::TrieNode::addChild(char symbol, bool isEOW) {
	// only insert child if it's not present, otherwise don't do anything
	if (this->children.find(symbol) == this->children.end()) {
	    // get the newly-inserted node from directly from the return value
		TrieNode* res = this->children.insert({symbol, new TrieNode(isEOW)}).first->second;
		return res;
	}

	return nullptr;
}

const std::map<char, Trie::TrieNode*>& Trie::TrieNode::getChildren() const {
	return this->children;
}

int Trie::TrieNode::numChildren() {
    return this->children.size();
}

void Trie::TrieNode::removeChild(char symbol) {
    this->children.erase(symbol);
}

std::ostream& operator<<(std::ostream& out, const Trie::TrieNode& node) {
    out<< "EOW: " << node.endOfWord << std::endl;
    out<< "NODE HAS " << node.children.size() << " CHILDREN" <<std::endl;
    out<< "{ ";

    if(!node.children.empty()) {
        auto it = node.children.begin();
        auto secondLast = std::prev(node.children.end(), 1);
        for (; it != secondLast; it++)
            out << it->first << ", ";
        out<< it->first;
    }

    out << " }";

    return out;
}

