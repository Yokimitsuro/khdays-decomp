/* func_ov238_020d0c68 -- ov238's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means
 * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is
 * cleared on every path.
 *
 * The reset drops 0xc6 from the hw60 hi-byte and bits 0-1 of the halfword at +0x1ae, then sets bit
 * 0 on the sub-object at ctx[0]+0x38c.
 *
 * Notably case 3 is in its natural position here -- the only dispatcher so far where it is. Cases
 * 8 and 7 are swapped instead.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the +8 field is
 * byte-in-word. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov238_020d0f9c(void);
extern void func_ov238_020d1058(void);
extern void func_ov238_020d107c(void);
extern void func_ov238_020d1258(void);
extern void func_ov238_020d14a4(void);
extern void func_ov238_020d178c(void);
extern void func_ov238_020d1860(void);
extern void func_ov238_020d1ea8(void);
extern void func_ov238_020d1fe0(void);
extern void func_ov238_020d24d0(void);

void func_ov238_020d0c68(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x38c) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov238_020d0f9c);
            break;
        case 1:
            func_0203c634(self, 1, func_ov238_020d1058);
            break;
        case 2:
            func_0203c634(self, 1, func_ov238_020d107c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov238_020d1258);
            break;
        case 4:
            func_0203c634(self, 1, func_ov238_020d14a4);
            break;
        case 5:
            func_0203c634(self, 1, func_ov238_020d178c);
            break;
        case 6:
            func_0203c634(self, 1, func_ov238_020d1860);
            break;
        case 8:
            func_0203c634(self, 1, func_ov238_020d1fe0);
            break;
        case 7:
            func_0203c634(self, 1, func_ov238_020d1ea8);
            break;
        case 9:
            func_0203c634(self, 1, func_ov238_020d24d0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
