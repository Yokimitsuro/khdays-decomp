/* Message handler (rider form): a kind-0 message copies its +0x28 bit 0 into the actor's
 * +0x3c0 bit 0 and its +0x24 / +0x26 halfwords into the +0x3bc / +0x3be rider counters. A
 * "spawned" message (kind 5) dispatches on its slot byte: 0 builds the first +0x3b8 sub-item via
 * 020d5e08 with mode 1 / 2 / 0 by which counter is empty; 1 starts the two +0x3b8 sub-items
 * (kind 0x17, at the +0xa0 pose) whose counters are non-zero; 2 / 3 run the 020cda7c hook;
 * 4 / 5 start the +0x18 / +0x20 sub-items at the +0x3ac / +0x3a8 items' transforms; 6 starts
 * effect 0x166 (kind 0xa) at the +0xa0 pose into +0x3c4. The base handler always runs. */
typedef unsigned char u8;
struct Bits3c0 { unsigned int b0 : 1; };
struct Bits28 { u8 b0 : 1; };
struct Ov278SubSlot { int pItem; int pChild; };

extern int func_ov278_020d5dbc(char *self, int item, int mode);
extern int func_ov107_020c09a0(int list, int parent, int kind, void *at, int a, int b);
extern void func_ov278_020cda7c(char *self);
extern int func_ov107_020cb040(char *self, int id, int a3, int a4, void *xform);
extern void func_ov107_020c7500(char *self, u8 *cmd, void *arg3);

void func_ov278_020cd5a0(char *self, u8 *cmd, void *arg3)
{
    if (cmd[2] == 0) {
        ((struct Bits3c0 *)(self + 0x3c0))->b0 = ((struct Bits28 *)(cmd + 0x28))->b0;
        *(short *)(self + 0x300 + 0xbc) = *(short *)(cmd + 0x24);
        *(short *)(self + 0x300 + 0xbe) = *(short *)(cmd + 0x26);
    } else if (cmd[2] == 5) {
        switch (cmd[3]) {
        case 0: {
            int mode;
            if (*(short *)(self + 0x300 + 0xbc) == 0) {
                mode = 1;
            } else if (*(short *)(self + 0x300 + 0xbe) == 0) {
                mode = 2;
            } else {
                mode = 0;
            }
            (*(struct Ov278SubSlot **)(self + 0x3b8))[0].pChild =
                func_ov278_020d5dbc(self, (*(struct Ov278SubSlot **)(self + 0x3b8))[0].pItem, mode);
            break;
        }
        case 1: {
            signed char i;
            for (i = 0; i < 2; i++) {
                if (((short *)(self + 0x300 + 0xbc))[i] != 0) {
                    (*(struct Ov278SubSlot **)(self + 0x3b8))[i + 1].pChild =
                        func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov278SubSlot **)(self + 0x3b8))[i + 1].pItem,
                                            0x17, self + 0xa0, 0, 1);
                }
            }
            break;
        }
        case 2:
        case 3:
            func_ov278_020cda7c(self);
            break;
        case 4:
            (*(struct Ov278SubSlot **)(self + 0x3b8))[3].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov278SubSlot **)(self + 0x3b8))[3].pItem,
                                    0x17, *(char **)(self + 0x3ac) + 4, 0, 0);
            break;
        case 5:
            (*(struct Ov278SubSlot **)(self + 0x3b8))[4].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov278SubSlot **)(self + 0x3b8))[4].pItem,
                                    0x17, *(char **)(self + 0x3a8) + 4, 0, 0);
            break;
        case 6:
            *(int *)(self + 0x3c4) = func_ov107_020cb040(self, 0x166, 0xa, 0, self + 0xa0);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}
