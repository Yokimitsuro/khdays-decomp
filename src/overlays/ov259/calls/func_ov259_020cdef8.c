/* func_ov259_020cdef8 -- ov259's move dispatcher. Two things set it apart from the rest of the
 * family:
 *
 *  - the cooldown at ctx+0x94 is 0x32 or 0x1e depending on the flag at ctx+0x4c, so whatever that
 *    flag is, it makes the object slower to act;
 *  - there is a SECOND switch before the dispatch: moves 10..17 clear ctx+0x48 and everything else
 *    sets it to 1. It is written out as eight case labels because the ROM builds a full jump table
 *    for it -- a range test (`move >= 10 && move <= 17`) collapses to three instructions instead.
 *
 * Cases 1, 5, 6 and 7 are absent from the move switch; 15 dispatches the same handler as 3.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the field at +8 of
 * *(ctx[0]+0x404) is a byte-in-word. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov259_020ce2a8(void);
extern void func_ov259_020ce34c(void);
extern void func_ov259_020ce898(void);
extern void func_ov259_020ce988(void);
extern void func_ov259_020cea14(void);
extern void func_ov259_020ceb38(void);
extern void func_ov259_020cef8c(void);
extern void func_ov259_020cf040(void);
extern void func_ov259_020cf508(void);
extern void func_ov259_020cf6d0(void);
extern void func_ov259_020cfaa8(void);
extern void func_ov259_020cfe64(void);
extern void func_ov259_020d0338(void);
extern void func_ov259_020d0dbc(void);

void func_ov259_020cdef8(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x86;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x404) + 8))->f |= 1;
        *(unsigned char *)((char *)ctx + 0xae) = 0;
        ctx[0x25] = ctx[0x13] != 0 ? 0x32 : 0x1e;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            ctx[0x12] = 0;
            break;
        default:
            ctx[0x12] = 1;
            break;
        }

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov259_020ce2a8);
            break;
        case 2:
            func_0203c634(self, 1, func_ov259_020ce34c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov259_020cef8c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov259_020cfaa8);
            break;
        case 8:
            func_0203c634(self, 1, func_ov259_020ce898);
            break;
        case 9:
            func_0203c634(self, 1, func_ov259_020ce988);
            break;
        case 10:
            func_0203c634(self, 1, func_ov259_020cea14);
            break;
        case 11:
            func_0203c634(self, 1, func_ov259_020ceb38);
            break;
        case 12:
            func_0203c634(self, 1, func_ov259_020cf040);
            break;
        case 13:
            func_0203c634(self, 1, func_ov259_020cf508);
            break;
        case 14:
            func_0203c634(self, 1, func_ov259_020cf6d0);
            break;
        case 15:
            func_0203c634(self, 1, func_ov259_020cfaa8);
            break;
        case 16:
            func_0203c634(self, 1, func_ov259_020cfe64);
            break;
        case 17:
            func_0203c634(self, 1, func_ov259_020d0338);
            break;
        case 18:
            func_0203c634(self, 1, func_ov259_020d0dbc);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
