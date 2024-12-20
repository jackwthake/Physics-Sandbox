#ifndef TEST_H
#define TEST_H

#include "Object.h"

class Test_Obj : public Object {
public:
    Test_Obj();

    void update(double delta);
};

#endif