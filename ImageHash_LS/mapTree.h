#ifndef DS_HW1_MAPTREE_H
#define DS_HW1_MAPTREE_H

#include <exception>
#include <iostream>
#include "nodeTree.h"
#define DUMMY_KEY 0



using namespace std;


class keyNotFound : public std::exception{};
class keyAlreadyExist : public std::exception{};
class invalidPointer : public std::exception{};
//class problemOccur : public std::exception{};

class mapTree{
public:
    nodeTree* treeHead;
    int elements;

    mapTree();
    ~mapTree();
    nodeTree* find(int key) const;
    void remove(int key);
    nodeTree* insert(int key, void* value);
    int size() const;
    void removeByPointer(nodeTree* toRemove);
    void print();


private:
    nodeTree* findInTree(int key, nodeTree* next) const;
    void inorderPrint(nodeTree* next);
    void rollLR(nodeTree* node);
    void rollRL(nodeTree* node);
    void rollLL(nodeTree* node);
    void rollRR(nodeTree* node);
    void fixPostInsert(nodeTree* newnode);
    nodeTree* deleteNode(nodeTree* toDelete);
    nodeTree* deleteNodeIfEdge(nodeTree* toDelete);
    void fixPostRemoval(nodeTree* parent);
    void destruct (nodeTree* root);

};


#endif //DS_HW1_MAPTREE_H
