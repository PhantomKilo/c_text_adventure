#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"

bool executeLookAround(void)
{
    if (isLit(player->location))
    {
        printf("You are in %s.\n", player->location->description);
    }
    else
    {
        printf("It is very dark in here.\n");
    }
    
    listObjectsAtLocation(player->location);
    return true;
}

bool executeLook(void) 
{
    OBJECT *obj = getVisible("What do you want to look at", params[0]);
    switch (getDistance(player, obj)) 
    {
        case distHereContained:
            printf("Hard to see, try to get it first.\n");
            break;
        case distOverThere:
            printf("Too far away, move closer please.\n");
            break;
        case distNotHere:
            printf("You don't see and %s here.\n", params[0]);
            break;
        case distUnknownObject:
            // already handled by getVisible
            break;
        default:
            printf("%s\n", obj->details);
            listObjectsAtLocation(obj);                
    }    
    return true;
}

static void movePlayer(OBJECT *passage) 
{
    printf("%s\n", passage->textGo);
    if (passage->destination != NULL)
    {
        player->location = passage->destination;
        printf("\n");
        executeLookAround();
    }
}

bool executeGo(void)
{
    OBJECT *obj = getVisible("where you want to go", params[0]);
    switch (getDistance(player, obj)) 
    {
        case distOverThere:
            movePlayer(getPassage(player->location, obj));
            break;
        case distNotHere:
            printf("You dont see any %s here.\n", params[0]);
            break;
        case distUnknownObject:
            // already handled by getVisible
            break;
        default:
            movePlayer(obj);
    }
    return true;
}