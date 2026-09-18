/* func_ov245_020cea80 -- message hook for kind 5 messages aimed at slot 0: spawns the slot's
 * +0x394 effect child (020c08cc, kind 0x15, scale 1.0, payload at message byte 5) into +0x398,
 * then hands the message to the state filter (020cc8a4). Codegen: the kind test is a `switch`
 * so the slot test stays a separate branch. */
extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov245_020cc8a4(int self, unsigned char *msg, int extra);

struct Ov245Slots { char pad[0x394]; struct { int pEffect; int pChild; } slots[1]; };

int func_ov245_020cea80(int self, unsigned char *msg, int extra) {
    switch (msg[2]) {
    case 5:
        if (msg[3] == 0) {
            ((struct Ov245Slots *)self)->slots[msg[3]].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Ov245Slots *)self)->slots[msg[3]].pEffect, 0x15, 0, 0x1000, msg + 5);
        }
        break;
    }
    return func_ov245_020cc8a4(self, msg, extra);
}
