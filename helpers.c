//
// Created by felix on 27.01.2022.
//

#include "helpers.h"
#include "types.h"
#include <stdlib.h>

/**
 * @return new random point
 */
point getNewRandomPoint(){
    point p;
    int randomNumber = (rand() % 9);
    p.x = randomNumber;
    randomNumber = (rand() % 9);
    p.y = randomNumber;
    return p;
}