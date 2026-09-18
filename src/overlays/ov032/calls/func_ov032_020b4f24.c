/* Hover step of the ov032 enemy (and its byte-identical twins): on the local player both 64-bit
 * flag words get bit 16, bit 7 of +0x24 is cleared and the +0x668 hook decides the fired bit
 * (bit 49, node shown, bit 1 of +0x464 on the local session). Once fired: with the +0x22f8
 * emitter idle the state becomes 0x23; otherwise the mission root's +0x2e80 turn accumulates the
 * +0x2aba rate, the +0x1a input's bit 5/4 steer the heading +-0xfff (resetting it), the node is
 * turned through 020ad4e8 unless locked and a +0x1c stick of 5/6 records the emitter's 95554
 * value in the root's +0x2e78 and goes to state 0x24; with nothing chosen an input carrying bit
 * 1 of +0x18 goes to 0x23. Without bit 2 of +0x24 the actor is marked unrestricted (bit 46) with
 * a cleared +0x58. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef unsigned short u16;

extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_0202af1c(void *node);
extern int func_ov022_02095524(char *emitter);
extern int func_ov022_02095554(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern int func_ov022_020ad4e8(char *self, u16 heading);
extern int data_ov032_020b58c0;

void *func_ov032_020b4f24(char *self)
{
    void *next = 0;
    int *block = (int *)(*(int *)&data_ov032_020b58c0 + 0x278 + 0x2c00);
    int r;
    unsigned int *node;
    int heading;
    int left;
    int right;
    int a;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    *(int *)(self + 0x24) &= ~0x80;
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2;
        }
    }
    if (((Flags *)(self + 0x694))->b1) {
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            next = func_ov022_020a35f4(self, 0x23);
        } else {
            heading = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
            block[2] += *(short *)(self + 0x2a00 + 0xba);
            left = 0;
            right = 0;
            if ((*(u16 *)(self + 0x1a) & 0x20) != 0) {
                left = 1;
            } else if ((*(u16 *)(self + 0x1a) & 0x10) != 0) {
                right = 1;
            }
            if (left != 0) {
                heading += 0xfff;
                block[2] = 0;
            } else if (right != 0) {
                heading -= 0xfff;
                block[2] = 0;
            }
            a = func_ov022_020ad4e8(self, heading);
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
            if ((u16)(*(u16 *)(self + 0x1c) + 0xfffb) <= 1) {
                block[0] = func_ov022_02095554(self + 0x2f8 + 0x2000);
                next = func_ov022_020a35f4(self, 0x24);
            }
        }
        if (next == 0 && (*(u16 *)(self + 0x18) & 2) == 2) {
            next = func_ov022_020a35f4(self, 0x23);
        }
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    return next;
}
