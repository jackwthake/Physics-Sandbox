#include "test.h"

#include <iostream>

Test_Obj::Test_Obj() : Object() {
    this->position = { 1, 1 };
    this->bounds = { 1, 1 }; // 1 meter x 1 meter
    this->color = { 255, 255, 0 };
    this->mass = 2.5; // 2.5 kg
}

void Test_Obj::update(double dt) {
    using namespace std;
    cout << this->position << endl;
}