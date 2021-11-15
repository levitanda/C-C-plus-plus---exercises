//
// Created by HP on 02/01/2019.
//

#ifndef WET2_IMAGETAGGER_H
#define WET2_IMAGETAGGER_H

#include "mapTree.h"
#include "HashImages.h"
#include "PixelLabel.h"
#include "image.h"
#include "library.h"

class ImageTagger {
public:
    HashImages* Images;
    int PixelPerImage;

    ImageTagger(int PixelPerImage);
    ~ImageTagger();
    StatusType insertImage(int imageId);
    StatusType removeImage(int imageId);
    StatusType setLabelScore(int imageID, int pixel, int label, int score);
    StatusType resetLabelScore(int imageID, int pixel, int label);
    StatusType maxScoredLabel(int imageID, int pixel, int* maxLabel);
    StatusType mergeSPixels(int imageID, int pixel1, int pixel2);

};


#endif //WET2_IMAGETAGGER_H
