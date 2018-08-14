#ifndef PROGRAM4_H
#define PROGRAM4_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef struct char_freq{
  char c;
  double freq;

  char_freq(char c, double freq)
    :c(c),
     freq(freq)
  {}
} CFreq;

typedef struct char_code{
  char c;
  std::string code;
  char_code(char c, std::string code)
    :c(c),
     code(code)
  {}
} CCode;

typedef struct cf_Node {
    char c;
    double freq;
    cf_Node* leftChild;
    cf_Node* rightChild;

    cf_Node(char c,double freq, cf_Node* leftChild, cf_Node* rightChild)
            :c(c),
            freq(freq),
              leftChild(leftChild),
              rightChild(rightChild)
    {}
    bool operator<(const cf_Node& other) const {return freq > other.freq;}
}   cf_Node;

void traverseTree(const cf_Node* currentNode, std::vector<CCode> &hCodes, std::string code) {

    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
        CCode currentCode(currentNode->c, code);

        hCodes.push_back(currentCode);
    }

    if (currentNode->leftChild != NULL) {
        traverseTree(currentNode->leftChild, hCodes, code + "0");
    }

    if (currentNode->rightChild != NULL) {
        traverseTree(currentNode->rightChild, hCodes, code + "1");
    }

    //process current node

}

//input: vector of CFreqs 
//returns: vector of CCodes
std::vector<CCode> getHuffCodes(std::vector<CFreq > cfs){

  //can define in separate .cpp file (make this into declaration) 
  //or define everything here (nothing in targetgtest.cpp)

  //following is for compilation purposes

    std::vector<CCode> codes;

    std::priority_queue <cf_Node> huffmanTree;

    for(int i=0; i<cfs.size(); i++)
    {
        cf_Node htNode(cfs[i].c,cfs[i].freq, NULL, NULL);
        huffmanTree.push(htNode);
    }

    cf_Node* realNode;

    //will be used to delete pointers
    std::vector <cf_Node*> nodePointers;

    while(huffmanTree.size()>1)
    {
        cf_Node smallNode1 = huffmanTree.top();
        cf_Node* snPointer1 = new cf_Node(smallNode1.c,smallNode1.freq,smallNode1.leftChild,smallNode1.rightChild);
        huffmanTree.pop();

        nodePointers.push_back(snPointer1);

        cf_Node smallNode2 = huffmanTree.top();
        cf_Node* snPointer2 = new cf_Node(smallNode2.c,smallNode2.freq,smallNode2.leftChild,smallNode2.rightChild);
        huffmanTree.pop();

        nodePointers.push_back(snPointer2);

        realNode = new cf_Node('!', (smallNode1.freq + smallNode2.freq), snPointer1, snPointer2);

        nodePointers.push_back(realNode);

        huffmanTree.push(*realNode);

    }

    traverseTree(&huffmanTree.top(), codes, "");

    //deleting pointers to prevent memory leak
    for(int i=0; i<nodePointers.size(); i++){
        delete nodePointers[i];
    }

    return codes;
}

#endif //PROGRAM4_H
