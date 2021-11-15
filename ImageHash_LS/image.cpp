#include "image.h"

image::image(int pixels, int imageId){
    this->imageId = imageId;
    this->numPixels = pixels;
    this->parent= new int[pixels]();
    this->size=new int[pixels]();
    this->pointer_max_score= new PixelLabel*[pixels];
    this->superPixels = new mapTree*[pixels];
    for (int i = 0; i < pixels ; ++i) {
        this->size[i]=1;
        this->parent[i]=-1;
        this->pointer_max_score[i]= nullptr;
        this->superPixels[i]= nullptr;

    }
};

image::~image(){
    delete[] this->parent;
    delete[] this->size;
    delete[] this->pointer_max_score;
    for (int i = 0; i <this->numPixels ; ++i) {
        if(this->superPixels[i]!= nullptr){
            inorderFree(this->superPixels[i]->treeHead->leftSon);
        }
        delete superPixels[i];
    }
    delete[] this->superPixels;
};

int image::PixelFind(int px) {
    int r = px;
    while(parent[r] >= 0){
        r = parent[r];
    }
    return r;
}


bool image::PixelUnion(int x, int y) {
   int  p1 = PixelFind(x);
   int  p2 = PixelFind(y);
    if(p1 != p2) {
        if(size[p1] > size[p2]) {
            size[p1] += size[p2];
            parent[p2] = p1;
            size[p2]=0;
            unionLabelsData(p1, p2);
            return true;
        }
        else {
            size[p2] += size[p1];
            parent[p1] = p2;
            size[p1]=0;
            unionLabelsData(p2, p1);
            return true;
        }

    }
    return false;
}

int image::mergeLabels(void** merged, int pixFather, int pixFatherSize, void** pixFatherLabels, int pixSonSize, void** pixlSonLabels){
    int index1 = 0;
    int index2 = 0;
    int indexmerg = 0;
    int mergedSumElements= 0;
    while (index1 < pixFatherSize && index2 < pixSonSize)
    {
        PixelLabel* p1 = (PixelLabel*) pixFatherLabels[index1];
        PixelLabel* p2 = (PixelLabel*) pixlSonLabels[index2];

        if ( p1->label < p2->label )
        {
            merged[indexmerg] = pixFatherLabels[index1];
            index1++;
            mergedSumElements++;

        } else {
            if ( p1->label > p2->label )
            {
                merged[indexmerg] = pixlSonLabels[index2];
                index2++;
                mergedSumElements++;

            } else
            if ( p1->label == p2->label ){

                p1->score = p1->score + p2->score;
                merged[indexmerg]= p1 ;
                delete p2;
                if(this->pointer_max_score[pixFather]->score < p1->score){
                    this->pointer_max_score[pixFather]= p1;
                } else{
                    if(this->pointer_max_score[pixFather]->score == p1->score){
                        if(this->pointer_max_score[pixFather]->label < p1->label){
                            this->pointer_max_score[pixFather]= p1;
                        }
                    }
                }
                index1++;
                index2++;
                mergedSumElements++;
            }
        }

        indexmerg++;
    }

    while(index1 < pixFatherSize){
        merged[indexmerg]= pixFatherLabels[index1];
        index1++;
        indexmerg++;
        mergedSumElements++;
    }
    while(index2 < pixSonSize){
        merged[indexmerg]= pixlSonLabels[index2];
        index2++;
        indexmerg++;
        mergedSumElements++;
    }

    return mergedSumElements;
}

void image::unionLabelsData(int pixelfather, int pixelson){
    mapTree* tree1 = this->superPixels[pixelfather];
    mapTree* tree2 = this->superPixels[pixelson];
    if(tree2 == nullptr){
        return;
    }
    if(tree1 == nullptr){
        this->superPixels[pixelfather]=this->superPixels[pixelson];
        this->pointer_max_score[pixelfather]=this->pointer_max_score[pixelson];
        this->superPixels[pixelson] = nullptr;
        this->pointer_max_score[pixelson]= nullptr;
        this->size[pixelson]=0;
        return;
    }

    if(pointer_max_score[pixelfather]->score < pointer_max_score[pixelson]->score){
        pointer_max_score[pixelfather]= pointer_max_score[pixelson];
    } else{
        if(pointer_max_score[pixelfather]->score == pointer_max_score[pixelson]->score){
            if(pointer_max_score[pixelfather]->label< pointer_max_score[pixelson]->label)
                pointer_max_score[pixelfather]= pointer_max_score[pixelson];
        }
    }
    void** data1 = new void*[tree1->size()]();
    void** data2 = new void*[tree2->size()]();
    Print2Array(tree1,data1);
    Print2Array(tree2,data2);
    void** data3 = new void*[tree1->size()+tree2->size()]();
    int effSize = mergeLabels(data3, pixelfather, tree1->size(), data1, tree2->size(), data2);
    mapTree* tree3 = almostFullemptyTree(effSize);
    fillEmptyTree(tree3, data3, effSize);
    delete tree1;
    delete tree2;
    delete[] data1;
    delete[] data2;
    delete[] data3;
    this->superPixels[pixelfather] = tree3;
    this->superPixels[pixelson]= nullptr;
    this->pointer_max_score[pixelson]= nullptr;
    this->size[pixelson]=0;


    PostorderFixLabelsMaxTree(this->superPixels[pixelfather]->treeHead->leftSon);
    PixelLabel* updattedMax =(PixelLabel*) (this->superPixels[pixelfather]->treeHead->leftSon->value);
    this->pointer_max_score[pixelfather]= updattedMax->nextMax;
}




bool image::setLabelScore(int pixel, int label, int score){
    if(pixel<0 || pixel>this->numPixels-1){
        return false;
    }
    int superpixel = PixelFind(pixel);
    mapTree* labelsDS = this->superPixels[superpixel];
    if(labelsDS == nullptr){
        this->superPixels[superpixel]= new mapTree();
        labelsDS = this->superPixels[superpixel];
        PixelLabel* newLabel = new PixelLabel(label, score);
        newLabel->nextMax = newLabel;
        labelsDS->insert(label,newLabel);
        this->pointer_max_score[superpixel]=newLabel;

        return true;
    }
    nodeTree* foundLabel = labelsDS->find(label);
    if(foundLabel== nullptr){
        PixelLabel* newLabel = new PixelLabel(label, score);
        foundLabel =  labelsDS->insert(label,newLabel);
        PixelLabel* foundLabelFather =(PixelLabel*)(foundLabel->father->value);
        if(foundLabelFather->nextMax->score < newLabel->score){
            foundLabelFather->nextMax = newLabel;
        }
        else if(foundLabelFather->nextMax->score == newLabel->score && foundLabelFather->nextMax->label < newLabel->score){
            foundLabelFather->nextMax = newLabel;
        }

    } else{
        PixelLabel* fp = (PixelLabel*)(foundLabel->value);
        fp->score=score;
        if(fp->nextMax->score < fp->score){
            fp->nextMax = fp;
        }
        else if(fp->nextMax->score == fp->score && fp->nextMax->label > fp->nextMax->label){
            fp->nextMax = fp;
        }
    }
    FixLabelsMaxTree(foundLabel->father, superpixel);
    PixelLabel* updateMaxscore = ( PixelLabel*)(this->superPixels[superpixel]->treeHead->leftSon->value);
    updateMaxscore= updateMaxscore->nextMax;
    this->pointer_max_score[superpixel]= updateMaxscore;
    return true;
}


bool image::resetLabelScore(int pixel, int label){
    if(pixel<0 || pixel>this->numPixels-1){
        return false;
    }
    int superpixel = PixelFind(pixel);
    mapTree* labelsDS = this->superPixels[superpixel];
    if(labelsDS == nullptr){
        return false;
    }
    nodeTree* foundLabel = labelsDS->find(label);
    if(foundLabel== nullptr){
        return false;

    }
    PixelLabel* fp = (PixelLabel*)(foundLabel->value);
    fp->score=0;
    nodeTree* foundLabelFather = foundLabel->father;
    nodeTree* SecondSubTree ;
    if(foundLabelFather == this->superPixels[superpixel]->treeHead){      ///// case reset score in the first node in tree
            nodeTree* resetfirstNode = this->superPixels[superpixel]->treeHead->leftSon;
            PixelLabel* updatemaxLabel =(PixelLabel*)(resetfirstNode->value);
            updatemaxLabel = updatemaxLabel->nextMax;
            if(updatemaxLabel == fp){
                if(resetfirstNode->leftSon != nullptr && resetfirstNode->rightSon!= nullptr){
                    PixelLabel* Lsubtree = (PixelLabel*)(resetfirstNode->leftSon->value);
                    PixelLabel* Rsubtree = (PixelLabel*)(resetfirstNode->rightSon->value);
                    updatemaxLabel->nextMax = Rsubtree->nextMax;
                    if(Lsubtree->nextMax->score > Rsubtree->nextMax->score){
                        updatemaxLabel->nextMax = Lsubtree->nextMax;
                    }
                    if(Lsubtree->nextMax->score == Lsubtree->nextMax->score && Lsubtree->nextMax->label > Rsubtree->nextMax->label){
                        updatemaxLabel->nextMax = Lsubtree->nextMax;
                    }
                }else{
                    if( resetfirstNode->leftSon == nullptr && resetfirstNode->rightSon == nullptr){
                        updatemaxLabel->nextMax = updatemaxLabel;
                    }
                    if(resetfirstNode->leftSon == nullptr && resetfirstNode->rightSon != nullptr){
                        updatemaxLabel->nextMax = (PixelLabel*)(resetfirstNode->rightSon->value);
                        updatemaxLabel->nextMax = updatemaxLabel->nextMax->nextMax;
                    }
                    if(resetfirstNode->rightSon == nullptr && resetfirstNode->leftSon != nullptr){
                        updatemaxLabel->nextMax = (PixelLabel*)(resetfirstNode->leftSon->value);
                        updatemaxLabel->nextMax = updatemaxLabel->nextMax->nextMax;
                    }

                }
            }
            this->pointer_max_score[superpixel]=updatemaxLabel;
            return true;
    }
        if(foundLabel==foundLabelFather->leftSon){
            SecondSubTree = foundLabelFather->leftSon;
        } else
        {
            SecondSubTree = foundLabelFather->rightSon;
        }
        PixelLabel* pixelSubtree = (PixelLabel*)(SecondSubTree->value);
        PixelLabel* pixelFather = (PixelLabel*)(foundLabelFather->value);
        if(pixelFather->nextMax->score < pixelSubtree->nextMax->score){
            pixelFather->nextMax = pixelSubtree;
        } else{
            if(pixelFather->nextMax->score == pixelSubtree->nextMax->score && pixelFather->nextMax->label>pixelSubtree->nextMax->label )
                pixelFather->nextMax = pixelSubtree;
        }
        FixLabelsMaxTree(foundLabelFather, superpixel);
        PixelLabel* updateMaxscore = ( PixelLabel*)(this->superPixels[superpixel]->treeHead->leftSon->value);
        this->pointer_max_score[superpixel]= updateMaxscore->nextMax;

    return true;
}





PixelLabel* image::maxScoredLabel(int pixel){
    int superpixel = PixelFind(pixel);
    PixelLabel* res = this->pointer_max_score[superpixel];
    return  res;
};


void image::FixLabelsMaxTree(nodeTree* current, int superPixel ){
    if(current == this->superPixels[superPixel]->treeHead ) {
        return;
    }
    PixelLabel* currentPixelLabel = (PixelLabel*)(current->value);
    if(current->rightSon== nullptr && current->leftSon == nullptr){
        return;
    }
    if(current->rightSon== nullptr || current->leftSon == nullptr){
        nodeTree* pixelLabel = current->leftSon;
        if(pixelLabel== nullptr){
            pixelLabel=current->rightSon;
        }
        PixelLabel* LSpixelLabel =(PixelLabel*)(pixelLabel->value);
        if(LSpixelLabel->score > currentPixelLabel->score){
            currentPixelLabel->nextMax = LSpixelLabel;
        }
        else {
            if(LSpixelLabel->score== currentPixelLabel->score && LSpixelLabel->label> currentPixelLabel->label){
                currentPixelLabel->nextMax = LSpixelLabel;
            } else {
                currentPixelLabel->nextMax = currentPixelLabel;
            }
        }
        FixLabelsMaxTree(current->father, superPixel);
    }
    else{
        PixelLabel* RSpixelLabel =  (PixelLabel*)(current->rightSon->value);
        PixelLabel* LSpixelLabel =  (PixelLabel*)(current->leftSon->value);
        if(RSpixelLabel->nextMax->score > LSpixelLabel->nextMax->score){
            currentPixelLabel->nextMax = RSpixelLabel->nextMax;
        }else{
            if(RSpixelLabel->nextMax->score == LSpixelLabel->nextMax->score && RSpixelLabel->nextMax->label>LSpixelLabel->nextMax->label) {
                currentPixelLabel->nextMax = RSpixelLabel->nextMax;
            }
            else {
                currentPixelLabel->nextMax = LSpixelLabel->nextMax;
            }
        }
        FixLabelsMaxTree(current->father, superPixel);
    }
};

void image::PostorderFixLabelsMaxTree(nodeTree* current){
    if(current == nullptr) {
        return;
    }
    PostorderFixLabelsMaxTree(current->leftSon);
    PostorderFixLabelsMaxTree(current->rightSon);

    PixelLabel* currentPixelLabel = (PixelLabel*)(current->value);
    if(current->rightSon== nullptr || current->leftSon== nullptr){
        nodeTree* leaf = current->rightSon;
        if(leaf == nullptr){
            leaf =current->leftSon;
        }
        if(leaf == nullptr){
            currentPixelLabel->nextMax=currentPixelLabel;
            return;
        }
        PixelLabel* leafLabel =(PixelLabel*) (leaf->value);
        if(leafLabel->score > currentPixelLabel->score ||(leafLabel->score == currentPixelLabel->score && leafLabel->label > currentPixelLabel->label)){
            currentPixelLabel->nextMax = leafLabel;
        }else{
            currentPixelLabel->nextMax = currentPixelLabel;
        }
        return;
    }
    PixelLabel* RSpixelLabel =  (PixelLabel*)(current->rightSon->value);
    PixelLabel* LSpixelLabel =  (PixelLabel*)(current->leftSon->value);
    if(RSpixelLabel->nextMax->score > LSpixelLabel->nextMax->score){
        currentPixelLabel->nextMax = RSpixelLabel->nextMax;
    } else if (RSpixelLabel->nextMax->score == LSpixelLabel->nextMax->score && RSpixelLabel->nextMax->label > LSpixelLabel->nextMax->label){
        currentPixelLabel->nextMax = LSpixelLabel->nextMax;
    }

    if(currentPixelLabel->score > currentPixelLabel->nextMax->score ){
        currentPixelLabel->nextMax = currentPixelLabel;
    } else if(currentPixelLabel->score == currentPixelLabel->nextMax->score && currentPixelLabel->label > currentPixelLabel->nextMax->label){
        currentPixelLabel->nextMax = currentPixelLabel;
    }

};












///non member functions for building almost full empty tree and fill it

nodeTree* buildEmptyTree (nodeTree* root , int currentHeight, nodeTree* recFather, int height ) {
    if(currentHeight==-1){
        return nullptr;
    }
    nodeTree* curnode = new nodeTree(DUMMY_KEY, nullptr);
    curnode->height= currentHeight;
    curnode->father= recFather;
    if(currentHeight==height){
        root->leftSon=curnode;
        curnode->father=root;
    }
    curnode->leftSon = buildEmptyTree (root, currentHeight-1, curnode, height);
    curnode->rightSon = buildEmptyTree (root, currentHeight-1, curnode, height);
}

int fultreeheight (int wanted_nodes){
    int counter=0;
    int sum =0;
    while(sum<wanted_nodes){  ////////////complexity is right///////////////////////
        sum = sum+ pow(2,counter);
        counter++;
    }
    int fultreenodes = sum;
    int h = (int)(log2(fultreenodes+1)-1);
    return h;
}
mapTree* almostFullemptyTree (int wanted_nodes){
    mapTree* newtree = new mapTree();
    nodeTree* root = new nodeTree(DUMMY_KEY, nullptr);
    int h = fultreeheight(wanted_nodes);
    buildEmptyTree(root, h, nullptr, h);
    newtree->treeHead=root;
    newtree->elements= pow(2, (h+1))-1;
    inorderAlmostFul(newtree ,newtree->treeHead->leftSon, wanted_nodes);
    return newtree;

}
void inorderAlmostFul(mapTree* fultree, nodeTree* next, int wanted_nodes){
    if(next == nullptr){
        return ;
    }
    inorderAlmostFul(fultree, next->rightSon, wanted_nodes);
    if(next->rightSon== nullptr && next->rightSon== nullptr){
        if(fultree->elements>wanted_nodes ){
            if(next->father->rightSon==next){
                next->father->rightSon = nullptr;
            }
            if(next->father->leftSon==next){
                next->father->leftSon = nullptr;
            }
            delete next;
            fultree->elements = fultree->elements -1;
        }
    }
    inorderAlmostFul(fultree, next->leftSon, wanted_nodes);

}

void inorderfillEmptyTree (nodeTree* next,  void** orderedElementsArray, int* index){
    if(next== nullptr){
        return ;
    }
    inorderfillEmptyTree(next->leftSon, orderedElementsArray, index);
    PixelLabel* pl = (PixelLabel*)(orderedElementsArray[*index]);

    next->value= pl ;
    next->key=  pl->label;
    *index = *index +1;
    inorderfillEmptyTree(next->rightSon, orderedElementsArray, index);
}

void fillEmptyTree (mapTree* emptytree,  void** orderedElementsArray, int realSize){
    int* index = new int();
    *index=0;
    inorderfillEmptyTree(emptytree->treeHead->leftSon, orderedElementsArray, index);
    delete index;
    emptytree->elements= realSize;
}

void inorderPrint2Array(nodeTree* next, void** dataArr, int* index){
    if(next == nullptr) {
        return;
    }
    inorderPrint2Array(next->leftSon, dataArr, index);
    dataArr[*index]= next->value;
    *index= *index +1;
    inorderPrint2Array(next->rightSon,  dataArr, index);
};

void Print2Array(mapTree* fultree, void** dataArr){
    int* index= new int();
    *index= 0;
    inorderPrint2Array(fultree->treeHead->leftSon, dataArr, index);
    delete index;

}

void inorderFree(nodeTree* next){
    if(next == nullptr) {
        return;
    }
    inorderFree(next->leftSon);
    delete (PixelLabel*)(next->value);
    inorderFree(next->rightSon);
};

