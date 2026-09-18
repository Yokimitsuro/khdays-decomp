/* func_ov245_020d09ec -- message hook for kind-5 messages: slots 0 and 2 spawn the slot's
 * +0x394 effect child (020c08cc, kind 5 -- or 0x15 for slot 2 -- scale 1.0, payload at byte 5),
 * slot 1 spawns a kind-0x11 child at the actor's +0xa0 placement (020c09a0, flags 0/1); all
 * land in +0x398. Then the state filter (020cc8a4). */
struct Ov245Slots { char pad[0x394]; struct { int pEffect; int pChild; } slots[3]; };

extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov107_020c09a0(int list, int parent, int kind, void *at, int a, int b);
extern int func_ov245_020cc8a4(int self, unsigned char *msg, int extra);

int func_ov245_020d09ec(int self, unsigned char *msg, int extra) {
    switch (msg[2]) {
    case 5:
        switch (msg[3]) {
        case 0:
        case 2:
            ((struct Ov245Slots *)self)->slots[msg[3]].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Ov245Slots *)self)->slots[msg[3]].pEffect,
                                    (unsigned char)((msg[3] == 2 ? 0x10 : 0) | 5), 0, 0x1000, msg + 5);
            break;
        case 1:
            ((struct Ov245Slots *)self)->slots[msg[3]].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov245Slots *)self)->slots[msg[3]].pEffect, 0x11,
                                    (void *)(self + 0xa0), 0, 1);
            break;
        }
        break;
    }
    return func_ov245_020cc8a4(self, msg, extra);
}
