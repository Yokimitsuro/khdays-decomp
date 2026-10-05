/* Ov025_DrawMenuEntry -- Ov008_DrawMenuEntry (124 B, 4 relocs).
 * Draws menu entry arg1 (with value arg2) onto the surface at arg0+0x124. Copies the 6-entry text
 * table data_ov025_020b3ce0 to a local, opens the surface (Obj_InvokeInnerVtable4), builds a cell from the
 * table's arg1-th id via Ov025_VariadicMapForward(arg0+0x28c, (int)(tbl[arg1]), work, 0x80, arg2) into a 0x100
 * work buffer, and renders it with Text_DrawWithShadow(arg0+0x124, 0, 0, 0xf3, cell, 1). */

#include "nitro/types.h"

typedef struct Buf18 { int entries[6]; } Buf18;

extern Buf18 data_ov025_020b3ce0;
extern void Obj_InvokeInnerVtable4(void *surface);
extern void *Ov025_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);
extern void Text_DrawWithShadow(void *surface, int a, int b, int c, int d, int e);

void Ov025_DrawMenuEntry(void *arg0, int arg1, int arg2)
{
    char *ctx = (char *)arg0;
    Buf18 tbl = data_ov025_020b3ce0;
    u8 work[0x100];

    Obj_InvokeInnerVtable4(ctx + 0x124);
    Text_DrawWithShadow(ctx + 0x124, 0, 0, 0xf3,
                  (int)Ov025_VariadicMapForward(ctx + 0x28c, (int)tbl.entries[arg1], work, 0x80, arg2), 1);
}
