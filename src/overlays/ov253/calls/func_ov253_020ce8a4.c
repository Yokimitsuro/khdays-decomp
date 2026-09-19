/* func_ov253_020ce8a4 -- message hook for kind 5 messages, by slot: 0 / 3 spawn the +0x3b0
 * block's first / fourth effect child (020c08cc, kind 5, scale 1.0, payload at byte 5); 1
 * spawns the handle child (020d1114); 2 / 7 spawn the third / fifth effect at the +0x3ac item's
 * +4 (020c09a0, kinds 0xd / 5); 4 spawns the item child (020d182c); 5 looks the +4 handle up
 * (020c9b68) and, when its +0x18c rider is not 0x10000-flagged and belongs to the current
 * player (02030788), links it as +0x3c0 (020d1b2c); 6 releases +0x3c0. Then the base hook. */
extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov107_020c09a0(int list, int parent, int kind, void *pos, int a, int b);
extern int func_ov107_020c7500(int self, unsigned char *msg, int extra);
extern int func_ov253_020d1114(int self);
extern int func_ov253_020d182c(int self);
extern int func_ov107_020c9b68(unsigned short handle);
extern int func_02030788(void);
extern int func_ov253_020d1b2c(int self, int target);
extern void func_0203c650(int scene, int object);

struct Ov253Pair { int pEffect; int pChild; };

int func_ov253_020ce8a4(int self, unsigned char *msg, int extra) {
    int target;
    int rider;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 1:
            (*(struct Ov253Pair **)(self + 0x3b0))[1].pChild = func_ov253_020d1114(self);
            break;
        case 2:
            (*(struct Ov253Pair **)(self + 0x3b0))[2].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3b0))[2].pEffect, 0xd, (void *)(*(int *)(self + 0x3ac) + 4), 0, 1);
            break;
        case 0:
            (*(struct Ov253Pair **)(self + 0x3b0))[0].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3b0))[0].pEffect, 5, 0, 0x1000, msg + 5);
            break;
        case 3:
            (*(struct Ov253Pair **)(self + 0x3b0))[3].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3b0))[3].pEffect, 5, 0, 0x1000, msg + 5);
            break;
        case 7:
            (*(struct Ov253Pair **)(self + 0x3b0))[4].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x3b0))[4].pEffect, 5, (void *)(*(int *)(self + 0x3ac) + 4), 0, 0);
            break;
        case 4:
            func_ov253_020d182c(self);
            break;
        case 5:
            target = func_ov107_020c9b68(*(unsigned short *)(msg + 4));
            if (target != 0) {
                rider = *(int *)(target + 0x18c);
                if ((*(unsigned long long *)rider & 0x10000ULL) == 0) {
                    if (*(unsigned char *)(rider + 8) == func_02030788()) {
                        *(int *)(self + 0x3c0) = func_ov253_020d1b2c(self, target);
                    }
                }
            }
            break;
        case 6:
            func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3c0));
            *(int *)(self + 0x3c0) = 0;
            break;
        }
    }
    return func_ov107_020c7500(self, msg, extra);
}
