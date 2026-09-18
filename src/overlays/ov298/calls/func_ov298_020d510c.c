/* Turn entry of the ov298 enemy: half the time the +0x28 turn is rolled (0x1922 to 0x3243), the
 * target gap measured and the +0x30 target yaw aimed from the actor at its +0x394 target plus
 * the turn; animation 8 plays, the +0x90 flag is set, bit 0 of the +0x38c part's +8 word is set,
 * reaction 0 mode 0x43 fires at the +8 point and the tick hands off to d51fc. */
typedef struct { int x, y, z; } VecFx32;
struct LowByte32 { unsigned bits : 8; };

extern int func_02023eb4(int range);
extern unsigned int func_02023e80(unsigned int range);
extern int func_ov298_020d404c(void *node);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int func_01ff8d18(VecFx32 *v, VecFx32 *d);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov298_020d51fc(int *node);

void func_ov298_020d510c(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if ((unsigned int)func_02023eb4(0x64) < 0x32) {
        state[10] = func_02023e80(0x1922) + 0x1922;
        func_ov298_020d404c(node);
        VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x74), (void *)(*state + 0x74), &d);
        func_01ff8d18(&d, &d);
        state[0xc] = func_020050b4(d.x, d.z);
        state[0xc] += state[10];
    }
    func_ov107_020c9264(*state, 8, 0);
    state[0x24] = 1;
    ((struct LowByte32 *)(*(int *)(*state + 0x38c) + 8))->bits |= 1;
    func_ov107_020c5af8(*state, 0, 0x43, (void *)state[2]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov298_020d51fc);
}
