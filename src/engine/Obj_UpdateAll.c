/*
 * Obj_UpdateAll - run one frame of the object registry (gObjSystem, head at [3]). Each object
 * is published as the current one ([1]) while it runs. An update callback of -2 marks an object
 * to destroy (Obj_Destroy, unless it is protected by flag 1), -1 an idle one; any other callback
 * runs inside the object's allocator arena (obj[7]) when the registry is not paused or the object
 * runs while paused (flag 4), and a non-zero return replaces the callback. The walk continues from
 * the current object's successor ([3]). Afterwards the current object is cleared and, unless
 * paused, the frame counter ([2]) advances.
 */

#include "game/engine.h"

extern int  gObjSystem[];

void Obj_UpdateAll(int paused)
{
    int *obj;
    int next;

    gObjSystem[1] = gObjSystem[3];
    obj = (int *)gObjSystem[1];
    while (obj != 0) {
        switch (obj[5]) {
        case -2:
            next = obj[3];
            if (!(obj[0] & 1)) {
                next = Obj_Destroy(obj);
            }
            break;
        case -1:
            next = obj[3];
            break;
        default:
            if (paused == 0 || (obj[0] & 4)) {
                GameHeap *arena = Heap_SetCurrent((GameHeap *)obj[7]);
                int cb = ((int (*)(void))((int *)gObjSystem[1])[5])();

                Heap_SetCurrent(arena);
                if (cb != 0) {
                    ((int *)gObjSystem[1])[5] = cb;
                }
            }
            next = ((int *)gObjSystem[1])[3];
            break;
        }
        gObjSystem[1] = next;
        obj = (int *)next;
    }
    gObjSystem[1] = 0;
    if (paused == 0) {
        gObjSystem[2]++;
    }
}
