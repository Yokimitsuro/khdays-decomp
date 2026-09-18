/* func_ov245_020d3b24 -- message hook for kind-5 messages: slot 0 spawns a kind-5 child under
 * the slot's +0x3b8 parent at the +0x3b0 item's +4 transform (020c09a0); slot 1 spawns the
 * slot's +0x3b8 effect child (020c08cc, kind 0x15, scale 1.0, payload at byte 5) and then
 * re-links the actor (020c0b14 with 0); both land in +0x3bc. Then the state filter (020cc8a4). */
struct Ov245Slots { char pad[0x3b8]; struct { int pParent; int pChild; } slots[2]; };

extern int func_ov107_020c09a0(int list, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern void func_ov107_020c0b14(int self, int a);
extern int func_ov245_020cc8a4(int self, unsigned char *msg, int extra);

int func_ov245_020d3b24(int self, unsigned char *msg, int extra) {
    switch (msg[2]) {
    case 5:
        switch (msg[3]) {
        case 0:
            ((struct Ov245Slots *)self)->slots[msg[3]].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov245Slots *)self)->slots[msg[3]].pParent, 5,
                                    (void *)(*(int *)(self + 0x3b0) + 4), 0, 0);
            break;
        case 1:
            ((struct Ov245Slots *)self)->slots[msg[3]].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Ov245Slots *)self)->slots[msg[3]].pParent, 0x15, 0, 0x1000, msg + 5);
            func_ov107_020c0b14(self, 0);
            break;
        }
        break;
    }
    return func_ov245_020cc8a4(self, msg, extra);
}
