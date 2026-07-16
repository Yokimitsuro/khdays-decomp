/* func_ov282_020d07dc -- ov210's move dispatcher: play whatever move is queued at ctx[0]+0x1c7 and
 * clear the slot. Third of its kind after func_ov228_020cf47c and func_ov231_020cd2b4, and the
 * same shape: -1 means nothing queued, the id is copied to +0x1c6 and it is that copy the switch
 * reads, and the slot is cleared on every path.
 *
 * The reset before dispatching: hw60 hi loses 0xce, bit 0 of the halfword at +0x1ae is cleared,
 * and bit 0 of the byte field at *(ctx[0]+0x3b0)+8 is set.
 *
 * Source case order is 0,1,2,4,5,6,7,8,9,10,11,12,13,14,15,16,3,17,18 -- the order the ROM lays
 * the bodies out, which with a jump table IS the source order (the table itself is index-ordered).
 * Case 3 sitting late is the third dispatcher in a row to do this, so whatever move id 3 is, it
 * was added to all of them after the fact.
 *
 * The hw60 write HAS the `lsl#0x10 ; lsr#0x10` trunc pair -> bitfield form; the field at +8 is a
 * byte-in-word. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov282_020d0b54(void);
extern void func_ov282_020d0c24(void);
extern void func_ov282_020d0cd4(void);
extern void func_ov282_020d0f68(void);
extern void func_ov282_020d1158(void);
extern void func_ov282_020d1594(void);
extern void func_ov282_020d1760(void);
extern void func_ov282_020d1b04(void);
extern void func_ov282_020d1fe4(void);
extern void func_ov282_020d204c(void);
extern void func_ov282_020d2600(void);
extern void func_ov282_020d29ac(void);
extern void func_ov282_020d2aec(void);
extern void func_ov282_020d2e04(void);
extern void func_ov282_020d311c(void);
extern void func_ov282_020d32b4(void);
extern void func_ov282_020d38c8(void);
extern void func_ov282_020d3990(void);
extern void func_ov282_020d3c64(void);

void func_ov282_020d07dc(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(ctx[0] + 0x3b0) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov282_020d0b54);
            break;
        case 1:
            func_0203c634(self, 1, func_ov282_020d0c24);
            break;
        case 2:
            func_0203c634(self, 1, func_ov282_020d0cd4);
            break;
        case 4:
            func_0203c634(self, 1, func_ov282_020d0f68);
            break;
        case 5:
            func_0203c634(self, 1, func_ov282_020d1158);
            break;
        case 6:
            func_0203c634(self, 1, func_ov282_020d1594);
            break;
        case 7:
            func_0203c634(self, 1, func_ov282_020d1760);
            break;
        case 8:
            func_0203c634(self, 1, func_ov282_020d1b04);
            break;
        case 9:
            func_0203c634(self, 1, func_ov282_020d1fe4);
            break;
        case 10:
            func_0203c634(self, 1, func_ov282_020d2600);
            break;
        case 11:
            func_0203c634(self, 1, func_ov282_020d29ac);
            break;
        case 12:
            func_0203c634(self, 1, func_ov282_020d2aec);
            break;
        case 13:
            func_0203c634(self, 1, func_ov282_020d2e04);
            break;
        case 14:
            func_0203c634(self, 1, func_ov282_020d311c);
            break;
        case 15:
            func_0203c634(self, 1, func_ov282_020d32b4);
            break;
        case 16:
            func_0203c634(self, 1, func_ov282_020d204c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov282_020d38c8);
            break;
        case 17:
            func_0203c634(self, 1, func_ov282_020d3990);
            break;
        case 18:
            func_0203c634(self, 1, func_ov282_020d3c64);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
