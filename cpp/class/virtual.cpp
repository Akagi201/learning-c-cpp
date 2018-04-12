#include <iostream>
#include <stdint.h>
#include <stdio.h>

class shape {
public:
    shape() { };

    virtual void draw() {
        printf("shape\n");
    }
};

class rectangle : public shape {
public:
    rectangle() { };

    void draw() {
        printf("rectangle\n");
    }
};

class round : public shape {
public:
    round() { };

    void draw() {
        printf("round\n");
    }
};

int main() {
    shape *s;

    s = new rectangle();
    s->draw();

    s = new round();
    s->draw();
    return 0;
}
