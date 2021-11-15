#include <exception>
#include <iostream>
#include "nodeTree.h"
using namespace std;

nodeTree::nodeTree(int key, void* value):value(value), key(key), height(0), leftSon(nullptr),
rightSon(nullptr), father(nullptr){};

nodeTree::~nodeTree(){};

bool nodeTree::isMyRightSon(nodeTree* son) const {
    return (this->rightSon == son);
};

bool nodeTree::isMyLeftSon(nodeTree* son) const {
    return (this->leftSon == son);
};

int nodeTree::calculateMyBF(){
    int balanceFactor = 0;
    if (this->leftSon != nullptr){
        balanceFactor = this->leftSon->height;
    }else {
        balanceFactor = -1;
    }
    if (this->rightSon != nullptr){
        balanceFactor = balanceFactor - this->rightSon->height;
    }else {
        balanceFactor = balanceFactor + 1;
    }
    return  balanceFactor;
};

void nodeTree::rollMeRight(){
    nodeTree* leftNode = this->leftSon;
    if(leftNode == nullptr){
        throw leftSonIsNull();
    }
    nodeTree* leftRightNode = leftNode->rightSon;
    nodeTree* fatherNode = this->father;
    if(fatherNode->isMyRightSon(this)){
        fatherNode->rightSon = leftNode;
    } else {
        fatherNode->leftSon = leftNode;
    }
    leftNode->father=fatherNode;
    leftNode->rightSon=this;
    this->father=leftNode;
    this->leftSon=leftRightNode;
    if(leftRightNode!= nullptr){
        leftRightNode->father=this;
    }
    int leftH=-1, rightH=-1;
    if(this->leftSon != nullptr){
        leftH = this->leftSon->height;
    }
    if (this->rightSon!= nullptr){
        rightH=this->rightSon->height;
    }
    this->height=std::max(leftH +1, rightH+1);
    leftH=-1;
    rightH=-1;
    if(leftNode->leftSon != nullptr){
        leftH = leftNode->leftSon->height;
    }
    if (leftNode->rightSon!= nullptr){
        rightH=leftNode->rightSon->height;
    }
    leftNode->height=std::max(leftH +1, rightH+1);
};

void nodeTree::rollMeLeft(){
    nodeTree* rightNode = this->rightSon;
    if(rightNode == nullptr){
        throw rightSonIsNull();
    }
    nodeTree* rightLeftNode = rightNode->leftSon;
    nodeTree* fatherNode = this->father;
    if(fatherNode->isMyRightSon(this)){
        fatherNode->rightSon = rightNode;
    } else {
        fatherNode->leftSon = rightNode;
    }
    rightNode->father=fatherNode;
    rightNode->leftSon=this;
    this->father=rightNode;
    this->rightSon=rightLeftNode;
    if(rightLeftNode!= nullptr){
        rightLeftNode->father=this;
    }

    int leftH=-1, rightH=-1;
    if(this->leftSon != nullptr){
        leftH = this->leftSon->height;
    }
    if (this->rightSon!= nullptr){
        rightH=this->rightSon->height;
    }
    this->height=std::max(leftH +1, rightH+1);
    leftH=-1;
    rightH=-1;
    if(rightNode->leftSon != nullptr){
        leftH = rightNode->leftSon->height;
    }
    if (rightNode->rightSon!= nullptr){
        rightH=rightNode->rightSon->height;
    }
    rightNode->height=std::max(leftH +1, rightH+1);

};



