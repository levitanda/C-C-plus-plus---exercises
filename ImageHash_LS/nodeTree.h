#ifndef DS_HW1_NODETREE_H
#define DS_HW1_NODETREE_H
#include <exception>
#include <iostream>
using namespace std;

class leftSonIsNull : public std::exception{};
class rightSonIsNull : public std::exception{};

class nodeTree {

public:
    void* value;
    int key;
    int height;
    nodeTree* leftSon;
    nodeTree* rightSon;
    nodeTree* father;

    nodeTree();
    ~nodeTree();
    nodeTree(int key, void* value);
    bool isMyRightSon(nodeTree* son) const;
    bool isMyLeftSon(nodeTree* son) const;
    void rollMeRight();
    void rollMeLeft();
    int calculateMyBF();


};
#endif //DS_HW1_NODETREE_H
