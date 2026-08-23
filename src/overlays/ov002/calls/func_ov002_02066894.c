/*
 * Ov002_ShowPairFocus - run the highlight cue for one half of the active pair.
 *
 * Kinds 0 and 1 own a fixed pair of cue ids, one for gaining focus and one for
 * losing it, and are looked up and played straight away. Any other kind
 * restyles the node the caller passes - 0xd focused, 0xc not - and replays it.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

extern int func_ov002_02053558(u16 nCue);
extern void func_ov002_020535a4(int hCue);
extern void func_ov002_02053610(int hCue, u8 nStyle);

void func_ov002_02066894(int nKind, int hNode, int bOn)
{
    switch (nKind) {
    case 0:
        func_ov002_020535a4(func_ov002_02053558((u16)(bOn ? 0x460 : 0x44c)));
        break;
    case 1:
        func_ov002_020535a4(func_ov002_02053558((u16)(bOn ? 0x461 : 0x44d)));
        break;
    default:
        func_ov002_02053610(hNode, (u8)(bOn ? 0xd : 0xc));
        func_ov002_020535a4(hNode);
        break;
    }
}
