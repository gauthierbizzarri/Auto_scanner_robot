#ifndef PATHMAKER_H
#define PATHMAKER_H

template<typename I, typename O>
class PathMaker{
public:
    virtual O create(I in) = 0;
};

#endif // PATHMAKER_H
