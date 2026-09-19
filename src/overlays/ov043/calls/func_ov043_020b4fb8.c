/* Arms request `slot` of the node's +0x12c rows (stride 0x240): the first time a row is used
 * its 2 animations (+4, stride 0x108) get channels 0 and 2 bound to their +0xe0 tables and
 * rewound, then the row is marked live, its +0xa8 / +0x224 vectors copied from the two
 * arguments and its +0x1b0 vector computed from the slot's world position (4ef0). */
typedef struct { int x, y, z; } Vec3;

extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern void func_ov043_020b4ef0(char *self, int slot, Vec3 *out);

void func_ov043_020b4fb8(char *self, char *node, int slot, Vec3 *a, Vec3 *b)
{
    char *row = node + 0x12c + slot * 0x240;
    int i;
    char *anim;
    Vec3 pos;

    if (*(int *)row == 0) {
        anim = row + 4;
        for (i = 0; i < 2; i++) {
            func_0202accc(anim, 0, anim + 0xe0, 0);
            func_0202accc(anim, 2, anim + 0xe0, 0);
            func_01fff774(anim, 0, 0);
            func_01fff774(anim, 2, 0);
            anim += 0x108;
        }
    }
    *(int *)row = 1;
    *(Vec3 *)(row + 0xa8) = *a;
    *(Vec3 *)(row + 0x224) = *b;
    func_ov043_020b4ef0(self, slot, &pos);
    *(Vec3 *)(row + 0x1b0) = pos;
}
