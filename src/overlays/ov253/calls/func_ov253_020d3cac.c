/* func_ov253_020d3cac -- message hook: a kind 5 message aimed at slot 0 spawns the +0x398
 * block's first effect child (020c08cc, kind 5, scale 1.0, payload at byte 5) into its +4;
 * aimed at slot 1 it spawns the second one into its +0xc and pushes the payload's three 24-bit
 * coordinates (bytes 5..13) as a 4.0 ring entry on the +0x388 item's +0x464 ring (020d1e38).
 * Then the base hook (020c7500). */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, unsigned char *payload);
extern int func_ov107_020c7500(int self, unsigned char *msg, int extra);
extern void func_ov253_020d1e38(int *ring, const VecFx32 *v, int arg);

struct Ov253Pair { int pEffect; int pChild; };

int func_ov253_020d3cac(int self, unsigned char *msg, int extra) {
    VecFx32 pos;
    int rawZ;
    int rawY;
    int rawX;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(struct Ov253Pair **)(self + 0x398))[0].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x398))[0].pEffect, 5, 0, 0x1000, msg + 5);
            break;
        case 1:
            (*(struct Ov253Pair **)(self + 0x398))[1].pChild =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Ov253Pair **)(self + 0x398))[1].pEffect, 5, 0, 0x1000, msg + 5);
            ((char *)&rawX)[3] = msg[5];
            ((char *)&rawX)[2] = msg[6];
            ((char *)&rawX)[1] = msg[7];
            pos.x = rawX >> 8;
            ((char *)&rawY)[3] = msg[8];
            ((char *)&rawY)[2] = msg[9];
            ((char *)&rawY)[1] = msg[10];
            pos.y = rawY >> 8;
            ((char *)&rawZ)[3] = msg[11];
            ((char *)&rawZ)[2] = msg[12];
            ((char *)&rawZ)[1] = msg[13];
            pos.z = rawZ >> 8;
            func_ov253_020d1e38(*(int **)(*(int *)(self + 0x388) + 0x464), &pos, 0x4000);
            break;
        }
    }
    return func_ov107_020c7500(self, msg, extra);
}
