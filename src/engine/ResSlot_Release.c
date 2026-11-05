/* Drops one reference; at zero releases the resource (packed 'HPAK' group or G3D resource), frees
 * its memory and clears the slot. Returns 1 when freed. */

#include "game/engine.h"

typedef struct ResGroup ResGroup;

extern void ResGroup_Release(ResGroup *state);
extern void NNS_G3dResDefaultRelease(void *pResData);

struct S {
    unsigned short field_00;
    unsigned short field_02;
    unsigned short field_04;
    unsigned short field_06;
    int *field_08;
    ResGroup *field_0c;
    unsigned char field_10;
};

int ResSlot_Release(struct S *p)
{
    p->field_00 = p->field_00 - 1;
    if (p->field_00 == 0) {
        if (p->field_02 != 0) {
            if (*(int *)p->field_0c == 0x4850414B) {
                ResGroup_Release(p->field_0c);
            } else {
                NNS_G3dResDefaultRelease(p->field_0c);
            }
            p->field_02 = 0;
            p->field_04 = 0;
        }
        p->field_10 = 0;
        ExpHeap_Free(p->field_0c, (GameHeap *)p->field_08);
        p->field_0c = 0;
        return 1;
    }
    return 0;
}
