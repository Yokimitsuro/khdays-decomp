/* Push this enemy's attack event(s): event 5 at each attack anchor (Ov039_GetAttackAnchor)
 * with range 0x1000, the enemy's facing (angle at +0x80 of its +0x20 node, biased by 0x8000)
 * and a per-band flag read from a table by the progress band ((+0x7b0 - 0x9000) / 0x3000, 15
 * bands, wrapping to 0). While the shared rig's +0x2cd4 flag is clear one event is pushed from
 * the single-row table; once it is set both anchors get one, each from its own row. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int v[15]; } Ov039BandRow;

extern void func_ov039_020b4050(char *self, int side, Vec3 *out);              /* Ov039_GetAttackAnchor */
extern void func_ov022_020ad208(char *self, int event, Vec3 *pos, int range, int angle, int flag);
extern char *data_ov039_020b5600;
extern const Ov039BandRow data_ov039_020b53c8;      /* the single-anchor per-band flags */

void func_ov039_020b46b0(char *self)
{
    Vec3 vAnchor;
    char *rig = data_ov039_020b5600 + 0xd4 + 0x2c00;
    int band;
    int angle;

    angle = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    angle = (unsigned short)(angle + 0x8000);
    band = (*(int *)(self + 0x7b0) - 0x9000) / 0x3000;
    if (band >= 15) band = 0;
    if (*(int *)rig == 0) {
        Ov039BandRow single = data_ov039_020b53c8;
        func_ov039_020b4050(self, 0, &vAnchor);
        func_ov022_020ad208(self, 5, &vAnchor, 0x1000, angle, single.v[band]);
        return;
    }
    {
        int table[2][15] = {
            { 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0 },
            { 2, 2, 2, 0, 0, 0, 2, 2, 2, 1, 1, 1, 0, 0, 0 },
        };
        func_ov039_020b4050(self, 0, &vAnchor);
        func_ov022_020ad208(self, 5, &vAnchor, 0x1000, angle, table[0][band]);
        func_ov039_020b4050(self, 1, &vAnchor);
        func_ov022_020ad208(self, 5, &vAnchor, 0x1000, angle, table[1][band]);
    }
}
