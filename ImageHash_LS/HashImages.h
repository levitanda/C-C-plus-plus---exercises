#ifndef WET2_HASHIMAGES_H
#define WET2_HASHIMAGES_H


#include "image.h"

class HashNode {
public:
image* Img;
HashNode* nextImg;
HashNode* prevImg;

HashNode(image* img) {
    this->Img = img;
    this->nextImg = nullptr;
    this->prevImg = nullptr;
}
~HashNode(){};

};

class HashImages {
public:
    HashNode** hasharr ;
    int capacity;
    int size;

HashImages(int n);
~HashImages();
HashNode* findImage(int imageId);
bool insertImage(int imageId, int pixelsPerimage);
bool removeImage(int imageId);
void deleteAllImages();
void deleteallcell(HashNode* hashnode);
int hashing(int imgId);
};




#endif //WET2_HASHIMAGES_H
