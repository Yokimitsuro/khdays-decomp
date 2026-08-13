/*
 * Post a cursor request to the ov002 scene context and refresh the view.
 *
 * The context is the second entry of the ov002 pointer table. A request carries a kind whose
 * low byte selects the entry and whose high byte carries flags: below 12 the kind and its value
 * replace the pair at +0x84/+0x86, at 12 or above only the flag byte is swapped in and the
 * stored entry byte is preserved. The extra halfword and the selection index are written on
 * every path, then 020646c0 rebuilds the display.
 *
 * Field names live on Ov002SceneContext in Ghidra (wCursorA, wCursorB, wCursorExtra, nSelected);
 * the raw offsets here are what reproduces the original codegen.
 */

typedef unsigned char u8;
typedef unsigned short u16;

extern char *data_ov002_0207f62c[];
extern void func_ov002_020646c0(void);

void func_ov002_020631b8(u16 kind, u16 value, u16 extra, int selected) {
    char *ctx = data_ov002_0207f62c[1];

    if ((kind & 0xff) >= 0xc) {
        *(u16 *)(ctx + 0x84) = (u16)((u8)*(u16 *)(ctx + 0x84) | (kind & 0xff00));
    } else {
        *(u16 *)(ctx + 0x84) = kind;
        *(u16 *)(ctx + 0x86) = value;
    }
    *(u16 *)(ctx + 0x88) = extra;
    *(int *)(ctx + 0xac) = selected;
    func_ov002_020646c0();
}
