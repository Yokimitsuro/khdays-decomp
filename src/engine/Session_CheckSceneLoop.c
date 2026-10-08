/* When the session changed tick or the scene may be interrupted, runs the scene loop (unless
 * blocked); returns 0. */

#include "game/engine.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern unsigned short WH_GetBitmap(void);

typedef struct {
    char _00[0x20];
    unsigned short h20;
    char _22[0x2c - 0x22];
    unsigned short bit0 : 1;
    unsigned short rest : 15;
} Obj02030570;

int Session_CheckSceneLoop(void)
{
    Obj02030570 *obj = (Obj02030570 *)NNSi_FndGetCurrentRootHeap();
    int flag = 0;

    if (Session_IsActive() != 0 && Session_IsReady() != 0) {
        if (obj->h20 != WH_GetBitmap())
            flag = 1;
    }
    if (Session_IsSceneInterruptible() != 0)
        flag = 1;

    if (flag != 0 && obj->bit0 == 0)
        Game_RunSceneLoop();

    return 0;
}
