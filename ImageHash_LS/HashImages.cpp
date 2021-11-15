
#include "HashImages.h"


HashImages::HashImages(int n) {
    this->hasharr = new HashNode*[n]();
    this->capacity = n;
    this->size = 0;
    for (int i = 0; i <this->capacity ; ++i) {
        this->hasharr[i]= nullptr;
    }

};
int HashImages::hashing(int imgId){

    int cell = imgId%this->capacity;
    return cell;
};

HashNode* HashImages::findImage(int imageId){
    if(this->hasharr == nullptr){
        return nullptr;
    }
    int cell = hashing(imageId);
    if (cell > this->capacity || cell < 0 ){
        return nullptr;
    }
    HashNode* currentHashnode = this->hasharr[cell];
    while(currentHashnode!= nullptr){
        if(currentHashnode->Img->imageId == imageId){
            return  currentHashnode;
        }
        currentHashnode= currentHashnode->nextImg;
    }
    return nullptr;
};

bool HashImages::insertImage(int imageId, int pixelsPerimage){
    HashNode* currentHashnode = findImage(imageId);
    if (currentHashnode!= nullptr){
        return false;
    }
    image* newImg = new image(pixelsPerimage, imageId);
    int cell = hashing(imageId);
    if (cell > this->capacity || cell < 0 ){
        return false;
    }
    currentHashnode = this->hasharr[cell];
    if(currentHashnode == nullptr){
        this->hasharr[cell] =  new HashNode(newImg);
        this->hasharr[cell]->Img = newImg;
        this->size++;
        return true;
    }
    if(currentHashnode!= nullptr){
        this->hasharr[cell]= new HashNode(newImg);
        this->hasharr[cell]->Img = newImg;
        this->hasharr[cell]->nextImg= currentHashnode;
        currentHashnode->prevImg = this->hasharr[cell];
        this->size++;
        return true;
    }

};
bool HashImages::removeImage(int imageId){
    HashNode* currentHashnode = findImage(imageId);
    if (currentHashnode== nullptr){
        return false;
    }
    if(currentHashnode->prevImg != nullptr){
        currentHashnode->prevImg->nextImg = currentHashnode->nextImg;
    }
    if(currentHashnode->nextImg != nullptr) {
        currentHashnode->nextImg->prevImg = currentHashnode->prevImg;
    }
    if(this->hasharr[hashing(imageId)]==currentHashnode){
        this->hasharr[hashing(imageId)]= nullptr;
    }
    image* imgtodelete = currentHashnode->Img;
    delete imgtodelete;
    delete currentHashnode;
    this->size--;
    return true;
};

void HashImages::deleteallcell(HashNode* hashnode){
        if (hashnode== nullptr) {
            return;
        }
        HashNode* next = hashnode->nextImg;
        delete hashnode->Img;
        delete hashnode;
        deleteallcell(next);
};

void HashImages::deleteAllImages(){
    for (int i = 0; i <this->capacity ; ++i) {
        deleteallcell(this->hasharr[i]);
    }
};
HashImages::~HashImages() {
    deleteAllImages();
    delete[] this->hasharr;
}