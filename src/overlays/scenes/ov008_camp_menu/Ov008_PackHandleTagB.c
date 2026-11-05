/* Twin of Ov008_PackHandleTag; the handle slot is at global+0x96b8. */

#include "game/archive.h"
extern int data_ov008_02090f04;

int Ov008_PackHandleTagB(int param_1) {
    int g = *(int *)((char *)&data_ov008_02090f04 + 4);
    int handle = *(int *)(g + 0x96b8);
    if (handle == 0) return 0;
    return ARCHIVE_HANDLE(handle, param_1 & 0x1ff);
}
