/* func_ov260_020cd8c8 -- ov260's move dispatcher.
 *
 * Moves 7 and 8 run the SAME handler (func_ov260_020cf0e8) and differ only in the byte they park
 * at ctx+0x78 afterwards -- 1 for one, 3 for the other. So that field is the handler's parameter,
 * and the two moves are one behaviour with a variant selector.
 *
 * The "nothing queued" case RETURNS outright (a predicated `popeq`) rather than falling into the
 * shared -1 store. Case 1 is absent from the switch; case 3 is out of order (last) as everywhere.
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
extern void func_ov260_020cdb8c(void);
extern void func_ov260_020cdc80(void);
extern void func_ov260_020cdd04(void);
extern void func_ov260_020ce27c(void);
extern void func_ov260_020ce7cc(void);
extern void func_ov260_020cf0e8(void);
extern void func_ov260_020cfbac(void);
extern void func_ov260_020cfe20(void);
extern void func_ov260_020d0230(void);
extern void func_ov260_020d05ec(void);
extern void func_ov260_020d07a0(void);
extern void func_ov260_020d0978(void);

void func_ov260_020cd8c8(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }

    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
    ((B8 *)(*(int *)(ctx[0] + 0x418) + 8))->f |= 1;

    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov260_020cdb8c);
        break;
    case 2:
        func_0203c634(self, 1, func_ov260_020cdc80);
        break;
    case 4:
        func_0203c634(self, 1, func_ov260_020cdd04);
        break;
    case 5:
        func_0203c634(self, 1, func_ov260_020ce27c);
        break;
    case 6:
        func_0203c634(self, 1, func_ov260_020ce7cc);
        break;
    case 7:
        func_0203c634(self, 1, func_ov260_020cf0e8);
        *(unsigned char *)((char *)ctx + 0x78) = 1;
        break;
    case 8:
        func_0203c634(self, 1, func_ov260_020cf0e8);
        *(unsigned char *)((char *)ctx + 0x78) = 3;
        break;
    case 9:
        func_0203c634(self, 1, func_ov260_020cfbac);
        break;
    case 10:
        func_0203c634(self, 1, func_ov260_020cfe20);
        break;
    case 11:
        func_0203c634(self, 1, func_ov260_020d0230);
        break;
    case 12:
        func_0203c634(self, 1, func_ov260_020d05ec);
        break;
    case 13:
        func_0203c634(self, 1, func_ov260_020d07a0);
        break;
    case 3:
        func_0203c634(self, 1, func_ov260_020d0978);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
