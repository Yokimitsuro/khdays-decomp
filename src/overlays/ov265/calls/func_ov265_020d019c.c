/* Effect message hook of the ov265 enemy. A "spawned" message (kind 5) picks
 * the +0x3b8 pair named by byte 3: slots 0/2 spawn at the packed position (bytes 5..) with mode 5
 * (slot 0) or 1 and weight 0x1ec6 / 0x1119; the other slots first finish the pending slot-6 effect
 * and then anchor on the +0x3dc point with kind 0x15 (slot 4) or 5, looping for slot 6. The base
 * hook always runs. */
typedef unsigned char u8;
struct Pair { void *res; void *handle; };

extern int FX_Inv(int num, int den);
extern void *func_ov107_020c08cc(void *taskList, void *subitem, u8 mode, int blend, int weight, void *payload);
extern void *func_ov107_020c09a0(void *taskList, void *subitem, u8 kind, void *at, int a, int b);
extern void func_0203c650(void *taskList, void *handle);
extern void func_ov107_020c7500(char *actor, u8 *msg, int param);

void func_ov265_020d019c(char *actor, u8 *msg, int param)
{
    int weight;

    if (msg[2] == 5) {
        weight = FX_Inv(0x1ec6, 0x1119);
        switch (msg[3]) {
        case 0:
        case 2:
            (*(struct Pair **)(actor + 0x3b8))[msg[3]].handle =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(struct Pair **)(actor + 0x3b8))[msg[3]].res,
                                    msg[3] == 0 ? 5 : 1, 0, weight, msg + 5);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            {
                u8 kind = msg[3] == 4 ? 0x15 : 5;
                if ((*(struct Pair **)(actor + 0x3b8))[6].handle != 0) {
                    func_0203c650(*(void **)(actor + 0x3c), (*(struct Pair **)(actor + 0x3b8))[6].handle);
                    (*(struct Pair **)(actor + 0x3b8))[6].handle = 0;
                }
                (*(struct Pair **)(actor + 0x3b8))[msg[3]].handle =
                    func_ov107_020c09a0(*(void **)(actor + 0x3c), (*(struct Pair **)(actor + 0x3b8))[msg[3]].res,
                                        kind, actor + 0x3dc, 0, msg[3] == 6);
            }
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
