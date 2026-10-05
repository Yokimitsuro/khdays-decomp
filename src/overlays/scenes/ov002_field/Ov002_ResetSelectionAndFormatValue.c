/* Reset the two-word selection state to {0, 1}, then format setting 0x2080's
 * value (query kind 5) into the shared text buffer and close the dialog. */

#include "game/engine.h"

extern int OS_SPrintf(char *dst, const char *fmt, ...);

extern int data_0204c270[];
extern char data_0204c278[];
extern char gOv002MName[];

void Ov002_ResetSelectionAndFormatValue(void) {
    data_0204c270[0] = 0;
    data_0204c270[1] = 1;
    OS_SPrintf(data_0204c278, gOv002MName, GameState_GetField(0x2080, 5));
    SetGameMode(0);
}
