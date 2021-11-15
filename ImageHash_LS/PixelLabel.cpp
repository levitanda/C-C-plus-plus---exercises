//
// Created by HP on 04/01/2019.
//

#include "PixelLabel.h"

PixelLabel::PixelLabel(int label, int score){
    this->label=label;
    this->score=score;
    this->nextMax= nullptr;
}

PixelLabel::~PixelLabel(){};
