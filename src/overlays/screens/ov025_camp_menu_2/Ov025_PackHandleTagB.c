/* Twin of Ov008_PackHandleTag; the handle slot is at global+0x96b8. */

#include "game/archive.h"
extern int data_ov025_020b5744;

int Ov025_PackHandleTagB(int param_1) {
    int g = *(int *)((char *)&data_ov025_020b5744 + 4);
    int handle = *(int *)(g + 0x96b8);
    if (handle == 0) return 0;
    return ARCHIVE_HANDLE(handle, param_1 & 0x1ff);
}
