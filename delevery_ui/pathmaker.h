#ifndef PATHMAKER_H
#define PATHMAKER_H

/**
 * @brief The PathMaker class
 * Base class used as transformer
 * Tranforms an object I in an object O easier to manipulate as a path
 */
template<typename I, typename O>
class PathMaker{
public:
    /**
     * @brief create
     * Creates the O path object
     * @param in
     * @return
     */
    virtual O create(I in) = 0;
};

#endif // PATHMAKER_H
