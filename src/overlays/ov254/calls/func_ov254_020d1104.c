/* Stop entry: the +0xc velocity resets, the actor plays pose 7 (aggressive, +0x78) or 0x10 and is
 * knocked back in place (mode 5). When not aggressive, every shape of the ten +0x4ac items' +0x22c
 * lists gains bit 1 and the +0x45c partner is released (020d206c). The +0x70 flag clears and the
 * node moves to 020d121c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
struct Items4ac { char pad[0x4ac]; int item[10]; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);
extern void func_ov254_020d206c(int partner);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d121c(void);

void func_ov254_020d1104(int *node)
{
    int *state = (int *)node[1];
    Vec3 zero = data_02041dc8;
    int i;
    int shape;

    *(Vec3 *)(state + 3) = data_02041dc8;
    func_ov107_020c9264(*state, state[0x1e] != 0 ? 7 : 0x10, 0);
    func_ov107_020c0b90(*state, 5, zero, 0);
    if (state[0x1e] == 0) {
        for (i = 0; i < 10; i++) {
            for (shape = func_01fffd70((void *)(((struct Items4ac *)*state)->item[i] + 0x22c)); shape != 0;
                 shape = func_01fffd8c((void *)(((struct Items4ac *)*state)->item[i] + 0x22c))) {
                ((B8 *)(shape + 8))->f |= 2;
            }
        }
        func_ov254_020d206c(*(int *)(*state + 0x45c));
    }
    *((u8 *)state + 0x70) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d121c);
}
