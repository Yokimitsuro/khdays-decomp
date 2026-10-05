#include "game/engine.h"

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern char data_0204c270[];
extern char gOv002EName[];
/* Format the day counter (game field 0x2080/5) into the shared string buffer. */
void Ov002_FormatDayCounter(void) {
    int day = GameState_GetField(0x2080, 5);
    OS_SPrintf(data_0204c270, gOv002EName, day);
}
