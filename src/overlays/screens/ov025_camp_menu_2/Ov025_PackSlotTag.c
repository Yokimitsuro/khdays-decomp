/* Pack a 32-bit tag from the handle at global+0x96b0 and the low 9 bits of
 * param_1 (no empty-slot check; see Ov008_PackHandleTag for the checked twin). */

#include "game/archive.h"
extern int data_ov025_020b5744;

int Ov025_PackSlotTag(int param_1) {
    int g = *(int *)((char *)&data_ov025_020b5744 + 4);
    int index = param_1 & 0x1ff;
    int handle = *(int *)(g + 0x96b0);
    return ARCHIVE_HANDLE(handle, index);
}
