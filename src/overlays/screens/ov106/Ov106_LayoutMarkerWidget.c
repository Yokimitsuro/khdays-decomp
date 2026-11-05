/* Lay out the ov106 scene's +0x8bc4 widget: it is placed on the loaded +0x8b48 resource's second half
 * (texture word) at data_ov106_020b8a6c (depth 5.0x, style 5), enabled, given full alpha, bound to its
 * +0xe0 child on layer 4 and refreshed. */

#include "nitro/fx_types.h"
#include "game/archive.h"

extern char *data_ov106_020b8b60;
extern const VecFx32 data_ov106_020b8a6c;
extern void Ov106_PlaceWidget(void *self, unsigned int owner, const VecFx32 *pos, int depth, int style);
extern void SceneNode_SetFlag40(void *pWidget, int nValue);
extern void Widget_SetTagWord(void *pWidget, int nValue);
extern void BindAnimTrack(void *a, int b, void *c, int d);
extern void SceneNode_Enable(void *node);

void Ov106_LayoutMarkerWidget(void)
{
    VecFx32 pos = data_ov106_020b8a6c;

    Ov106_PlaceWidget(data_ov106_020b8b60 + 0x8bc4,
                        ARCHIVE_HANDLE(*(int *)(data_ov106_020b8b60 + 0x8b48), 2),
                        &pos, 0xa000, 5);
    SceneNode_SetFlag40(data_ov106_020b8b60 + 0x8bc4, 1);
    Widget_SetTagWord(data_ov106_020b8b60 + 0x8bc4, 0x7fff);
    BindAnimTrack(data_ov106_020b8b60 + 0x8bc4, 4, (void *)((int)(data_ov106_020b8b60 + 0x8bc4) + 0xe0), 0);
    SceneNode_Enable(data_ov106_020b8b60 + 0x8bc4);
}
