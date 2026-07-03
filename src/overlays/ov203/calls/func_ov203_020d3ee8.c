struct v3 { int x, y, z; };
struct nodeinfo { struct v3 pos; int radius; };
struct pair { int x, y; };
struct tbl8 { struct pair p[4]; };

extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *a, void *out);
extern const struct tbl8 data_ov203_020d6824;

void func_ov203_020d3ee8(int *param_1, int param_2, int param_3, int param_4,
                         int *param_5, int param_6, int *param_7, int param_8) {
    int node;
    int i;
    int scale2, half;
    int newcenter[2];
    struct nodeinfo ni;
    int diff[3];
    struct tbl8 dir;
    struct tbl8 outer;

    node = *(int *)(param_3 + 8);
    if (node != 0) {
        do {
            int obj = *(int *)(node + 0x28);
            if (obj != 0 && *(int *)(obj + 0x158) != 0 &&
                (*(unsigned short *)(node + 0x22) & 0xff) == 0) {
                int dist;
                ni.pos = *(struct v3 *)(node + 0x2c);
                ni.radius = *(int *)(node + 0x38);
                VEC_Subtract(&ni.pos, param_5, diff);
                dist = func_01ff8d18(diff, diff);
                if (dist < param_5[3] + ni.radius) {
                    ((int *)param_8)[*param_7] = node;
                    *param_7 += 1;
                    if (*param_7 >= 4) return;
                }
            }
            node = *(int *)(node + 4);
        } while (node != 0);
    }

    if ((*(unsigned short *)param_3 & 0xf0f0) == 0) return;

    outer = data_ov203_020d6824;
    scale2 = param_2 >> 2;
    half = param_2 >> 1;
    for (i = 0; i < 4; i++) {
        int child;
        dir = outer;
        child = ((int *)param_3)[i + 4];
        if (child != 0) {
            newcenter[0] = param_1[0] + scale2 * dir.p[i].x;
            newcenter[1] = param_1[1] + scale2 * dir.p[i].y;
            func_ov203_020d3ee8(newcenter, half, child, param_4,
                                param_5, param_6, param_7, param_8);
            if (*param_7 >= 4) return;
        }
    }
}
