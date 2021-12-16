#ifndef FIELDELEMENTTRACKER_H
#define FIELDELEMENTTRACKER_H

#include "fieldelement.h"


class FieldElementTracker{
private:
    FieldElement* element;
    FieldElementTracker* parent;
    int distance;
    float value;
public:
    FieldElementTracker(FieldElement* element, float value, FieldElementTracker* parent = nullptr){
        this->element=element;
        this->parent = parent;
        distance = 0;
        this->value=value;
    };
    int getDistance(){
        return distance;
    };
    float getValue(){
        return value;
    };
    void setDistance(int d){
        distance=d;
    };
    void setValue(float v){
        value= v;
    };
    FieldElement* getElement()
    {
        return element;
    };
    void setParent(FieldElementTracker* parent)
    {
        this->parent=parent;
    };
    FieldElementTracker* getParent()
    {
        return parent;
    };
};

#endif // FIELDELEMENTTRACKER_H
