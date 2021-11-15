#include "ImageTagger.h"

ImageTagger::ImageTagger(int PixelPerImage){
    this->Images = new HashImages(100);
    this->PixelPerImage=PixelPerImage;
}
ImageTagger::~ImageTagger() {
    delete this->Images;
}
StatusType ImageTagger::insertImage(int imageId){
    if(imageId<=0){
        return  INVALID_INPUT;
    }
    bool res = this->Images->insertImage(imageId, this->PixelPerImage);
    if(res){
        return SUCCESS;
    }
    return FAILURE;
};
StatusType ImageTagger::removeImage(int imageId){
    if(imageId<=0){
        return  INVALID_INPUT;
    }
    bool res = this->Images->removeImage(imageId);
    if(res){
        return SUCCESS;
    }
    return FAILURE;
}
StatusType ImageTagger::setLabelScore(int imageID, int pixel, int label, int score){
    if(imageID<=0 || score<=0 || label<=0|| pixel<0 || pixel>=this->PixelPerImage  ){
        return  INVALID_INPUT;
    }
    HashNode* foundImg = this->Images->findImage(imageID);
    if(foundImg == nullptr){
        return FAILURE;
    }
    bool res = foundImg->Img->setLabelScore(pixel,label,score);
    if(res){
        return SUCCESS;
    }
    return FAILURE;
}
StatusType ImageTagger::resetLabelScore(int imageID, int pixel, int label){
    if(imageID<=0 || label<=0|| pixel<0 || pixel>=this->PixelPerImage  ){
        return  INVALID_INPUT;
    }
    HashNode* foundImg = this->Images->findImage(imageID);
    if(foundImg == nullptr){
        return FAILURE;
    }
    bool res = foundImg->Img->resetLabelScore(pixel,label);
    if(res){
        return SUCCESS;
    }
    return FAILURE;
}
StatusType ImageTagger::maxScoredLabel(int imageID, int pixel, int* maxLabel){
    if(imageID<=0 ||  pixel<0 || pixel>=this->PixelPerImage){
        return  INVALID_INPUT;
    }
    HashNode* foundImg = this->Images->findImage(imageID);
    if(foundImg == nullptr){
        return FAILURE;
    }
    PixelLabel* max  = foundImg->Img->maxScoredLabel(pixel);
    if(max!= nullptr){
        *maxLabel=max->label;
        if(max->score == 0){
            return FAILURE;
        }
        return SUCCESS;
    }
    return FAILURE;
}

StatusType ImageTagger::mergeSPixels(int imageID, int pixel1, int pixel2){
    if(imageID<=0 ||  pixel1<0 || pixel1>=this->PixelPerImage || pixel2<0 || pixel2>=this->PixelPerImage){
        return  INVALID_INPUT;
    }
    HashNode* foundImg = this->Images->findImage(imageID);
    if(foundImg == nullptr){
        return FAILURE;
    }
    bool res = foundImg->Img->PixelUnion(pixel1,pixel2);
    if(res){
        return SUCCESS;
    }
    return FAILURE;
}