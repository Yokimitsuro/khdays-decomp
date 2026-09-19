/* func_ov253_020d24f8 -- message hook: a kind 0 message stores its four +0x24..+0x2a halfwords
 * into +0x398 / +0x38c / +0x390 / +0x394; a kind 5 message aimed at slot 0 spawns the +0x3e8
 * block's first effect child (020c09a0, kind 5, at the actor's +0xa0) into its +4 and the
 * position child at +0xb0 (020d31a0) into +0x3d0, aimed at slot 1 spawns the second one
 * (020c08cc, kind 5, scale 1.0, payload at byte 5) into its +0xc. Then the base hook (020c7500). */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov107_020c09a0(int list, int parent, int kind, void *pos, int a, int b);
extern int func_ov107_020c7500(int self, unsigned char *msg, int extra);
extern int func_ov253_020d31a0(int self, const Vec3 *pos);

struct Ov253Pair { int pEffect; int pChild; };

int func_ov253_020d24f8(int self, unsigned char *msg, int extra) {
    if (msg[2] == 0) {
        *(int *)(self + 0x398) = *(short *)(msg + 0x24);
        *(int *)(self + 0x38c) = *(short *)(msg + 0x26);
        *(int *)(self + 0x390) = *(short *)(msg + 0x28);
        *(int *)(self + 0x394) = *(short *)(msg + 0x2a);
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(struct Ov253Pair **)(self + 0x3e8))[0].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3e8))[0].pEffect, 5, (void *)(self + 0xa0), 0, 0);
            *(int *)(self + 0x3d0) = func_ov253_020d31a0(self, (Vec3 *)(self + 0xb0));
            break;
        case 1:
            (*(struct Ov253Pair **)(self + 0x3e8))[1].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3e8))[1].pEffect, 5, 0, 0x1000, msg + 5);
            break;
        }
    }
    return func_ov107_020c7500(self, msg, extra);
}
