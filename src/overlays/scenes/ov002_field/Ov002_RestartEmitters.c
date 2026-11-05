
#include "nitro/fx_types.h"
#include "game/archive.h"

extern int data_ov002_0207f628;

extern void Tween_Clear(int pTarget);
extern void Ov002_PlaceWidget(int pTarget, unsigned int nParam, const VecFx32 *pOffset,
                                int nId, int nFlags);

/* Restart the two effect emitters and re-arm the third with its fixed offset. */
void Ov002_RestartEmitters(void)
{
    VecFx32 vOffset;
    int pOwner;

    pOwner = *(int *)&data_ov002_0207f628;

    Tween_Clear(pOwner + 0x100c);
    Tween_Clear(pOwner + 0xff0);

    vOffset.x = 0xbb8;
    vOffset.y = 0xfffffc18;
    vOffset.z = 0;

    Ov002_PlaceWidget(pOwner + 0xec8,
                        ARCHIVE_HANDLE(*(int *)(pOwner + 0x40), 0),
                        &vOffset, 0x614, 0xf);
}
