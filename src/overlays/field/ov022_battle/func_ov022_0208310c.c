/* Runs the frame and picks the next step from the context state: fade out, nothing, or closing the
 * ov106 scene. */

#include "game/engine.h"

extern void func_ov022_02083f0c(void);
extern void Ov022_UpdateCameraAndViews(int arg0);
extern int data_ov022_020b2e60;
extern void Ov022_StepCameraInputThenNextState(void);
extern void Ov022_StateCloseOv106Scene(void);

int func_ov022_0208310c(void) {
    func_ov022_02083f0c();
    Ov022_UpdateCameraAndViews(1);
    switch (*(char *)(*(int *)&data_ov022_020b2e60 + 0x3e)) {
    case 0:
        return (int)Ov022_StepCameraInputThenNextState;
    case 1:
        break;
    case 2:
        return (int)Ov022_StepCameraInputThenNextState;
    case 3:
        StoreToGlobalPtr4Field28(1);
        return (int)Ov022_StateCloseOv106Scene;
    }
    return 0;
}
