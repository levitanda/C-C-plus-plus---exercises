#ifndef WET2_IMAGE_H
#define WET2_IMAGE_H

#include <math.h>
#include "mapTree.h"
#include "PixelLabel.h"

class image {
public:
    int imageId;
    int numPixels;
    PixelLabel** pointer_max_score;
    int* size;
    int* parent;
    mapTree** superPixels;


    image(int pixels, int imageId);
    ~image();
    int PixelFind(int px);
    bool PixelUnion(int x, int y);
    bool setLabelScore(int pixel, int label, int score);
    bool resetLabelScore(int pixel, int label);
    PixelLabel* maxScoredLabel(int pixel);
    void FixLabelsMaxTree(nodeTree* current, int superPixel);
    void unionLabelsData(int pixelfather, int pixelson);
    int mergeLabels(void** merged, int pixFather, int pixFatherSize, void** pixFatherLabels, int pixSonSize, void** pixlSonLabels);
    void PostorderFixLabelsMaxTree(nodeTree* current);

};

///non member functions for building almost full empty tree and fill it

nodeTree* buildEmptyTree (nodeTree* root , int h) ;
void inorderAlmostFul(mapTree* fultree, nodeTree* next, int wanted_nodes);
int fultreeheight (int wanted_nodes);
mapTree* almostFullemptyTree (int wanted_nodes);
void inorderfillEmptyTree (nodeTree* next,  void** orderedElementsArray, int* index);
void fillEmptyTree (mapTree* emptytree,  void** orderedElementsArray, int realSize);
void inorderPrint2Array(nodeTree* next, void** dataArr, int* index);
void Print2Array(mapTree* fultree, void** dataArr);
void inorderFree(nodeTree* next);


#endif //WET2_IMAGE_H
