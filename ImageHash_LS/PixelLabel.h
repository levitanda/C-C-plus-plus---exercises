//
// Created by HP on 04/01/2019.
//

#ifndef WET2_PIXELLABEL_H
#define WET2_PIXELLABEL_H


class PixelLabel {
public:
    int label;
    int score;
    PixelLabel* nextMax;

    PixelLabel(int label, int score);
    ~PixelLabel();
};




#endif //WET2_PIXELLABEL_H
