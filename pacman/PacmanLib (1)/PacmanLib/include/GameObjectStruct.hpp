/// \file
/// GameObjectStruct.h


#ifndef SRC_GAMEOBJECTSTRUCT_H
#define SRC_GAMEOBJECTSTRUCT_H

#include <vector>

/// These enum values denote the sprite sets available for items on screen.
enum Type {
    PACMAN,
    BLINKY,
    PINKY,
    INKY,
    CLYDE,
    SCARED,
    SCAREDINV,
    CHERRY,
    STRAWBERRY,
    ORANGE,
    LEMON,
    APPLE,
    GRAPES,
    DOT,
    ENERGIZER,
    WALL,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

/// An enum to denote the direction of an item on screen.
enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

/// This represents an item that is drawn onto the screen.
struct GameObjectStruct {
    /// x-position of the item.
    int x;
    /// y-position of the item.
    int y;
    /// The appearance of the item (sprite set).
    Type type;
    /// The direction of the item (sprite selection).
    Direction dir;

    bool operator==(const GameObjectStruct& other) const {
        return (x == other.x && y== other.y); // Compare the 'type' members for equality
    }
};

class Ghost : public GameObjectStruct {
public:
    Type originalType; // To remember the ghost's type 

    // Constructor to initialize a Ghost object 
    Ghost(int x, int y, Type type, Direction dir)
        : GameObjectStruct{x, y, type, dir}, originalType(type) {}

    // Method to reset the ghost to its original state
    void reset() {
        this->x = 12; 
        this->y = 13; 
        this->type = originalType; // Reset to original type
    }
};

#endif // SRC_GAMEOBJECTSTRUCT_H
