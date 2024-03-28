/// \file
/// GameObjectStruct.h


#ifndef SRC_GAMEOBJECTSTRUCT_H
#define SRC_GAMEOBJECTSTRUCT_H

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

#endif // SRC_GAMEOBJECTSTRUCT_H
