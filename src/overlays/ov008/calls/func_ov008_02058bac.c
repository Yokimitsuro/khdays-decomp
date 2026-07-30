/* func_ov008_02058bac -- Ov008_HandleCancelFlags (116 B, 5 relocs).
 * Reacts to the menu's flag halfword at ctx+0x5c6. If bit 7 is set the request is suppressed and
 * it returns immediately. Otherwise, when bit 5 is set it plays the cancel feedback
 * (func_ov008_02057c78(0)) and posts event (0, 3); when bit 5 is clear it looks up object 0x200c
 * (func_02023588), resolves its node (func_ov008_0204ed20), and if present sets bit 2 of the
 * node's byte flags before signalling func_ov008_0205714c(8). The two flag tests read single
 * bitfield members so the compiler emits the lsl/lsr bit extracts. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008Flags5c6 {
    u16 pad0 : 5;
    u16 bit5 : 1;   /* 0x20 */
    u16 pad6 : 1;
    u16 bit7 : 1;   /* 0x80 */
    u16 pad8 : 8;
} Ov008Flags5c6;

typedef struct EdObj {
    u8 pad_0000[2];
    u8 flags2;      /* 0x2 */
} EdObj;

extern void   func_ov008_02057c78(int a);
extern void   func_02033b78(int a, int b);
extern void  *func_02023588(int id);
extern EdObj *func_ov008_0204ed20(void *x);
extern void   func_ov008_0205714c(int a);

void func_ov008_02058bac(void *ctx)
{
    Ov008Flags5c6 *f = (Ov008Flags5c6 *)((char *)ctx + 0x5c6);
    void *x;
    EdObj *y;

    if (f->bit7) {
        return;
    }
    if (f->bit5) {
        func_ov008_02057c78(0);
        func_02033b78(0, 3);
        return;
    }
    x = func_02023588(0x200c);
    if (x == 0) {
        return;
    }
    y = func_ov008_0204ed20(x);
    if (y == 0) {
        return;
    }
    y->flags2 |= 4;
    func_ov008_0205714c(8);
}
