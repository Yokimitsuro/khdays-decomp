/* func_ov236_020cf4b4 -- the mount's move dispatcher. A pending move (+0x1c7 != -1) becomes current
 * (+0x1c6): bits 1-2 and 6-7 of the +0x60 high byte and bits 0-1 of +0x1ae clear, the +0x3a4 /
 * +0x3a8 shapes are armed (bit 0) with only the first flagged (bit 1), +0x54 clears, and the
 * move's handler is registered. Moves 2 and 4-8 also hand moves 2-7 to each rider controller
 * (+0x3b4 front / +0x3b8 rear) that is free (its +0x1ac bit 1 clear) and present (+0x3c0 / +0x3d4
 * bit 0); move 9 instead sends each free, absent rider move 8 with +0x1ae bit 0 set. The pending
 * slot is always reset to -1. */
typedef unsigned short u16;
typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;
typedef struct {
    unsigned f : 8;
} B8;
typedef struct {
    int b0 : 1;
} Flag1;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov236_020cfa88(void);
extern void func_ov236_020cfb2c(void);
extern void func_ov236_020cfb9c(void);
extern void func_ov236_020cfdb4(void);
extern void func_ov236_020cfff8(void);
extern void func_ov236_020d03ec(void);
extern void func_ov236_020d04d0(void);
extern void func_ov236_020d0860(void);
extern void func_ov236_020d0b20(void);
extern void func_ov236_020d11e8(void);
extern void func_ov236_020d13d0(void);
extern void func_ov236_020d144c(void);
extern void func_ov236_020d1748(void);

void func_ov236_020cf4b4(int self) {
    int *ctx;
    int front;
    int rear;
    int frontFree;
    int rearFree;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        front = *(int *)(ctx[0] + 0x3b4);
        rear = *(int *)(ctx[0] + 0x3b8);
        frontFree = (*(u16 *)(front + 0x1ac) & 2) == 0;
        rearFree = (*(u16 *)(rear + 0x1ac) & 2) == 0;
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(u16 *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x3a4) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3a8) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3a4) + 8))->f |= 2;
        ((B8 *)(*(int *)(ctx[0] + 0x3a8) + 8))->f &= ~2;
        *(int *)(ctx[0] + 0x54) = 0;
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov236_020cfa88);
            break;
        case 1:
            func_0203c634(self, 1, func_ov236_020cfb2c);
            break;
        case 2:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 2;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 2;
            }
            func_0203c634(self, 1, func_ov236_020cfb9c);
            break;
        case 4:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 3;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 3;
            }
            func_0203c634(self, 1, func_ov236_020cfdb4);
            break;
        case 5:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 4;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 4;
            }
            func_0203c634(self, 1, func_ov236_020cfff8);
            break;
        case 6:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 5;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 5;
            }
            func_0203c634(self, 1, func_ov236_020d144c);
            break;
        case 7:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 6;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 6;
            }
            func_0203c634(self, 1, func_ov236_020d1748);
            break;
        case 8:
            if (frontFree && ((Flag1 *)(front + 0x3c0))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 7;
            }
            if (rearFree && ((Flag1 *)(rear + 0x3d4))->b0) {
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 7;
            }
            func_0203c634(self, 1, func_ov236_020d03ec);
            break;
        case 10:
            func_0203c634(self, 1, func_ov236_020d04d0);
            break;
        case 9:
            if (frontFree && !((Flag1 *)(front + 0x3c0))->b0) {
                *(u16 *)(*(int *)(ctx[0] + 0x3b4) + 0x1ae) |= 1;
                *(signed char *)(*(int *)(ctx[0] + 0x3b4) + 0x1c7) = 8;
            }
            if (rearFree && !((Flag1 *)(rear + 0x3d4))->b0) {
                *(u16 *)(*(int *)(ctx[0] + 0x3b8) + 0x1ae) |= 1;
                *(signed char *)(*(int *)(ctx[0] + 0x3b8) + 0x1c7) = 8;
            }
            func_0203c634(self, 1, func_ov236_020d0860);
            break;
        case 11:
            func_0203c634(self, 1, func_ov236_020d0b20);
            break;
        case 12:
            func_0203c634(self, 1, func_ov236_020d11e8);
            break;
        case 3:
            func_0203c634(self, 1, func_ov236_020d13d0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
