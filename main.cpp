#include <stdio.h>

const int SIZE = 10;
const int LEFT = 1;
const int RIGHT = -1;
const int UP = SIZE;
const int DOWN = -SIZE;
int map[SIZE * SIZE];
#include <omp.h>

void initialize() {
    for(int i = 0; i < SIZE * SIZE; ++i) {
        if(i % 2 == 0) { map[i] = 1; }
    }
}

void display() {
    for(int i = 0; i < SIZE * SIZE; ++i) {
        if(i % SIZE == 0) { printf("\n"); }
        printf("[%d]", map[i]);
    }
};

int getLeft(int origin) {
    // Move Left, Mod to X Position + Multiple of Original Y Position
    // e.g 
    //      (39 + 1) % 10 + 10 * (39 / 10)
    //      40 % 10 + 10 * 3
    //      0 + 30
    //      Result: 39 + 1 -> wrap to 30
    return (origin + 1) % SIZE + SIZE * (origin / SIZE);
}
bool isFish(int v) {return v == 1;}
bool isOcean(int v) { return v == 0; }

void moveLeft() {
    // SIZE * 3,    X = 8, Row = 0, 10 (x is really 38)
    // (X + 1) % SIZE <-- X Value, but we also need to add Y which is X % SIZE == 8, X % 

    // X = (3)9 + 1 -> 39
    // X = X % SIZE -> X
    // Y = X / SIZE -> 3 
    for(int i = 0; i < SIZE * SIZE; ++i) {
        // if left is free
        int left = getLeft(i);
        if(isOcean(map[left]) && isFish(map[i])) {
            map[left] = map[i];
            map[i] = 0;
        }
    }
}



void countFish() {
    int fish = 0;
    for(int i = 0; i < SIZE * SIZE; ++i) {
        fish += map[i];
    }
    printf("\nFish: %d\n", fish);
}


int main() {
    initialize();
    display();
    countFish();
    moveLeft();
    display();
    countFish();
    printf("\n");
}
