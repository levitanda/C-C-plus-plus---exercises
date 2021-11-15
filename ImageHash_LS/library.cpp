//
// Created by HP on 07/01/2019.
//

#include "library.h"
#include "ImageTagger.h"

void * Init(int pixels){
    if(pixels<=0){
        return nullptr;
    }
 ImageTagger* ds = new ImageTagger(pixels);
 return (void*)ds;
}

StatusType AddImage(void *DS, int imageID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->insertImage(imageID);
};

StatusType DeleteImage(void *DS, int imageID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->removeImage(imageID);
};

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->setLabelScore(imageID, pixel, label, score);
};

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->resetLabelScore(imageID, pixel, label);
};

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){
    if(DS == nullptr || label== nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->maxScoredLabel(imageID,pixel,label);
};

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ImageTagger* ImgTagger = (ImageTagger*)DS;
    return ImgTagger->mergeSPixels(imageID, pixel1, pixel2);
};


void Quit(void** DS){
    ImageTagger* ImgTagger = (ImageTagger*)*DS;
    delete ImgTagger;
    *DS = nullptr;
};