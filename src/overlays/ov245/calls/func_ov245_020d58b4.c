/* func_ov245_020d58b4 -- message hook for kind-5 messages on the +0x3a4 slot list: takes a copy
 * of the actor's +0xa0 placement scaled by 0.6 (0203ca9c); sub-kind 0 spawns a kind-0x17 child
 * under slot msg[4] (flag 2 for slot 1, scale 1.5, payload msg+5); sub-kind 1 spawns a kind-5
 * child under slot 2 at scale 0.6; sub-kinds 2/3 spawn a kind-5 child under slot msg[3]+1 at the
 * scaled placement (020c0794). Each child lands in its slot's +4. Then the base hook (020c7500). */
typedef struct { int m[11]; } Pose44;
struct Ov245Slot { int pEffect; int pChild; };

extern void func_0203ca9c(void *srt, int scale);
extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov107_020c0794(int list, int parent, int kind, int a, Pose44 *pose);
extern int func_ov245_020d59f8(int self, unsigned char *msg, int extra);
extern int func_ov107_020c7500(int self, unsigned char *msg, int extra);

int func_ov245_020d58b4(int self, unsigned char *msg, int extra) {
    Pose44 pose;

    if (msg[2] == 5) {
        pose = *(Pose44 *)(self + 0xa0);
        func_0203ca9c(&pose, 0x999);
        switch (msg[3]) {
        case 0:
            (*(struct Ov245Slot **)(self + 0x3a4))[msg[4]].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov245Slot **)(self + 0x3a4))[msg[4]].pEffect,
                                    0x17, (unsigned char)(msg[4] == 1 ? 2 : 0), 0x1800, msg + 5);
            break;
        case 1:
            (*(struct Ov245Slot **)(self + 0x3a4))[2].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov245Slot **)(self + 0x3a4))[2].pEffect,
                                    5, 0, 0x999, msg + 5);
            break;
        case 2:
        case 3:
            (*(struct Ov245Slot **)(self + 0x3a4))[msg[3] + 1].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov245Slot **)(self + 0x3a4))[msg[3] + 1].pEffect,
                                    5, 0, &pose);
            break;
        }
    }
    return func_ov107_020c7500(self, msg, extra);
}
