#include <exception>
#include <iostream>
#include "nodeTree.h"
#include "mapTree.h"


using namespace std;

mapTree::mapTree(){
    this->treeHead = new nodeTree(DUMMY_KEY, nullptr);
    this->elements = 0;
};

nodeTree* mapTree::find(int key) const{
    nodeTree* root = this->treeHead->leftSon;
    if(root == nullptr){
        return nullptr;
    }
    nodeTree* found = findInTree(key, root);
    if(found->key != key){
        return nullptr;
    }
    return found;
};

nodeTree* mapTree::findInTree(int key, nodeTree* next) const{
    if(next->key == key) return next;
    if (next->key < key){
        if(next->rightSon == nullptr){
            return next;
        }
       else{
            findInTree(key, next->rightSon);
        }
    }
    else if (next->key > key) {
        if(next->leftSon == nullptr){
            return next;
        }
        else{
            findInTree(key, next->leftSon);
        }
    }
};

void mapTree::inorderPrint(nodeTree* next){
    if(next == nullptr) {
        return;
    }
    inorderPrint(next->leftSon);
    cout<<next->key<<",";
    inorderPrint(next->rightSon);
};




void mapTree::print(){
    nodeTree* root = this->treeHead->leftSon;
    if (root == nullptr) return;
    inorderPrint(root);
};
void mapTree::rollLR(nodeTree* node){
    nodeTree* myleftSon = node->leftSon;
    myleftSon->rollMeLeft();
    node->rollMeRight();
};
void mapTree::rollRL(nodeTree* node){
    nodeTree* myrightSon = node->rightSon;
    myrightSon->rollMeRight();
    node->rollMeLeft();
};
void mapTree::rollLL(nodeTree* node){
    node->rollMeRight();
};
void mapTree::rollRR(nodeTree* node){
    node->rollMeLeft();
};

void mapTree::fixPostInsert(nodeTree* newnode){
    nodeTree* father = newnode->father;
    nodeTree* current = newnode;
    while (father != treeHead){
        if(father->height >= current->height+1){
            break;
        }
        father->height = current->height+1;
        if (father->calculateMyBF() == 2){
           /* if (current != father->leftSon){
                throw  problemOccur();
            }*/
            if(current->calculateMyBF() == -1){
                rollLR(father);
                break;
            }
            if(current->calculateMyBF() >= 0){
                rollLL(father);
                break;
            }
        }
        if (father->calculateMyBF() == -2){
           /* if (current != father->rightSon) {
                throw problemOccur();
            }*/
            if(current->calculateMyBF() == 1){
                rollRL(father);
                break;
            }
            if(current->calculateMyBF() <= 0){
                rollRR(father);
                break;
            }
        }
        current= father;
        father=father->father;
    }
};
nodeTree* mapTree::insert(int key, void* value){
    if(this->treeHead->leftSon == nullptr){
        this->treeHead->leftSon = new nodeTree(key, value);
        this->treeHead->leftSon->father = this->treeHead;
        elements++;
        return this->treeHead->leftSon;
    }
    nodeTree* fatherNode = findInTree(key ,this->treeHead->leftSon);

    if (fatherNode->key == key){
        throw keyAlreadyExist();
    }
    nodeTree* newnode ;
    if (key < fatherNode->key){
        /*if(fatherNode->leftSon != nullptr){
            throw problemOccur();
        }*/
        newnode = new nodeTree(key, value);
        fatherNode->leftSon=newnode;
        newnode->father=fatherNode;
    }
    if (key > fatherNode->key){
       /* if(fatherNode->rightSon != nullptr){
            throw problemOccur();
        }*/
        newnode = new nodeTree(key, value);
        fatherNode->rightSon=newnode;
        newnode->father=fatherNode;
    }

    fixPostInsert(newnode);
    elements++;
    return newnode ;
};

void mapTree::remove(int key){
    nodeTree* toRemove = find(key);
    if (toRemove == nullptr) {
        throw keyNotFound();
    }
    nodeTree* parent = deleteNode(toRemove);
    fixPostRemoval(parent);
    elements--;
};
nodeTree* mapTree::deleteNodeIfEdge(nodeTree* toDelete){
    nodeTree* theFather = toDelete->father;
    if(toDelete->leftSon == nullptr && toDelete->rightSon == nullptr){
        if(theFather->isMyRightSon(toDelete)){
            theFather->rightSon = nullptr;
        }
        else{
            theFather->leftSon = nullptr;
        }
        delete toDelete;
        return theFather;
    }
    if(toDelete->leftSon == nullptr && toDelete->rightSon != nullptr){
        if(theFather->isMyRightSon(toDelete)){
            theFather->rightSon = toDelete->rightSon;
            toDelete->rightSon->father = theFather;
        }
        else{
            theFather->leftSon= toDelete->rightSon;
            toDelete->rightSon->father = theFather;
        }
        delete toDelete;
        return theFather;
    }
    if(toDelete->leftSon != nullptr && toDelete->rightSon == nullptr){
        if(theFather->isMyRightSon(toDelete)){
            theFather->rightSon = toDelete->leftSon;
            toDelete->leftSon->father = theFather;
        }
        else{
            theFather->leftSon= toDelete->leftSon;
            toDelete->leftSon->father = theFather;
        }
        delete toDelete;
        return theFather;
    }
    return nullptr;
};

nodeTree* mapTree::deleteNode(nodeTree* toDelete){
    nodeTree* father = deleteNodeIfEdge(toDelete);
    if (father != nullptr) {
        return father;
    }
    nodeTree* theWnode = toDelete->rightSon;
   /* if(theWnode == nullptr){
        throw problemOccur();
    }*/
    while(theWnode->leftSon != nullptr){
        theWnode = theWnode->leftSon;
    }
    nodeTree* tmp1 = theWnode->leftSon;
    nodeTree* tmp2 = theWnode->rightSon;
    nodeTree* tmp3 = theWnode->father;
    nodeTree* tmp4 = toDelete->leftSon;
    nodeTree* tmp5 = toDelete->rightSon;
    nodeTree* tmp6 = toDelete->father;
    theWnode->leftSon = tmp4;
    theWnode->rightSon = tmp5;
    theWnode->father = tmp6;
    toDelete->leftSon = tmp1;
    toDelete->rightSon = tmp2;
    toDelete->father = tmp3;

    if(toDelete->father==toDelete){ //////////////////////
        toDelete->father=theWnode;
        theWnode->rightSon=toDelete;
        if(tmp6->isMyRightSon(toDelete)){theWnode->father->rightSon=theWnode;}
        else theWnode->father->leftSon=theWnode;
        if(theWnode->leftSon!= nullptr) theWnode->leftSon->father=theWnode;
        if(toDelete->leftSon!= nullptr) toDelete->leftSon->father=theWnode;
        if(toDelete->rightSon!= nullptr) toDelete->rightSon->father=theWnode;
    }
    else{
        if(tmp3->isMyRightSon(theWnode)){
            tmp3->rightSon=toDelete;
        }
        if(tmp3->isMyLeftSon(theWnode)){
            tmp3->leftSon=toDelete;
        }
        if(tmp1!= nullptr){
            tmp1->father=toDelete;
        }
        if(tmp2!= nullptr){
            tmp2->father=toDelete;
        }
        tmp4->father=theWnode;
        tmp5->father=theWnode;
        if(tmp6->isMyRightSon(toDelete)){
            tmp6->rightSon=theWnode;
        }else{
            tmp6->leftSon=theWnode;
        }

    }
    theWnode->height = toDelete->height;
    father = deleteNodeIfEdge(toDelete);
   /* if(father == nullptr){
        throw problemOccur();
    }*/
    return father;

};
void mapTree::fixPostRemoval(nodeTree* parent){
    if (parent == this->treeHead) return;
   /* if (parent->leftSon != nullptr && parent->rightSon != nullptr){
        throw problemOccur();
    }*/
    nodeTree* current = parent->rightSon;
    if (current == nullptr){
        current = parent->leftSon;
    }
    int leftheight = 0;
    int rightheight = 0;
    int preRollParentHeight = parent->height;
    nodeTree* grandpa = parent->father;
    bool wasItRighttSon = grandpa->isMyRightSon(parent);
    bool isrolles = false;
    while (parent != treeHead){
        if (parent->leftSon != nullptr ) {
            leftheight = parent->leftSon->height;
        } else {
            leftheight = -1;
        }
        if (parent->rightSon != nullptr ) {
            rightheight = parent->rightSon->height;
        } else {
            rightheight = -1;
        }
        parent->height = std::max(leftheight, rightheight)+1;
        preRollParentHeight = parent->height;
        isrolles = false;
        grandpa = parent->father;
        if(grandpa!= nullptr){
            wasItRighttSon = grandpa->isMyRightSon(parent);
        }

        if (parent->calculateMyBF() == 2){

            if(current->calculateMyBF() == -1){
                rollLR(parent);
                isrolles = true;
            }
           else if(current->calculateMyBF() >= 0){
                rollLL(parent);
                isrolles = true;
            }
        }
       else if (parent->calculateMyBF() == -2){

            if(current->calculateMyBF() == 1){
                rollRL(parent);
                isrolles = true;
            }
           else if(current->calculateMyBF() <= 0){
                rollRR(parent);
                isrolles = true;
            }
        }
        if (isrolles == true && wasItRighttSon == true){
            if (grandpa->rightSon->height == preRollParentHeight){
                break;
            }
            current=grandpa->rightSon;
            parent = grandpa;
            continue;

        }
        if (isrolles == true && wasItRighttSon == false){
            if (grandpa->leftSon->height == preRollParentHeight){
                break;
            }
            current=grandpa->leftSon;
            parent = grandpa;
            continue;
        }
        current = parent;
        parent = parent->father;
    }
};

int mapTree::size() const {
    return  this->elements;
};

void mapTree::removeByPointer(nodeTree* toRemove){
    if(toRemove == nullptr){
        throw invalidPointer();
    }
    int keyToDelete = (*toRemove).key;
    remove(keyToDelete);
};


mapTree::~mapTree(){
    nodeTree* root = this->treeHead->leftSon;
    destruct(root);
    delete treeHead;
};

void mapTree::destruct (nodeTree* root){
    if(root == nullptr){
        return;
    }
    destruct(root->leftSon);
    destruct(root->rightSon);
    delete root;
};



