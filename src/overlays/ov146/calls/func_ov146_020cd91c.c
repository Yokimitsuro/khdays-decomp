/* Charge decision of the ov146 actor: it looks for a live, unshielded entity of the scene list (other
 * than itself and its partner) within 48.0. Without one bit 0 of +0x1ae clears, the next move is 2 and
 * the node ends. With one the charge timer (+0x3c) and stage (+0x50) reset, both play pose 3, the
 * partner is grabbed (020ce2b4), effect 4 plays at the actor, sound 0x125/4 at its +0xc point and the
 * node moves on to 020cdaa4. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov146_020ce2b4(int partner);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov146_020cdaa4(void);

void func_ov146_020cd91c(int *node)
{
    int *state = (int *)node[1];
    int found = 0;
    int grid = *(int *)(*state + 4);
    int *it;
    char *e;
    Vec3 d;

    it = func_01fffd70((void *)(grid + 0x80));
    e = it == 0 ? 0 : (char *)*it;
    while (e != 0) {
        if (e != (char *)*state && e != (char *)state[2] && (((flags16 *)(e + 0x60))->lo & 1) &&
            !(*(u16 *)(e + 0x1ac) & 6)) {
            VEC_Subtract((Vec3 *)(*state + 0x74), (Vec3 *)(e + 0x74), &d);
            if (func_01ff8d18(&d, &d) <= 0x30000) {
                found = 1;
                break;
            }
        }
        it = func_01fffd8c((void *)(grid + 0x80));
        e = it == 0 ? 0 : (char *)*it;
    }
    if (found == 0) {
        *(u16 *)(*state + 0x1ae) &= ~1;
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xf] = 0;
    *((u8 *)state + 0x50) = 0;
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c9264(state[2], 3, 0);
    func_ov146_020ce2b4(state[2]);
    func_ov107_020c0b90(*state, 4, *(Vec3 *)(*state + 0x74), 0);
    func_ov107_020c5af8(*state, 0x125, 4, (void *)state[3]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020cdaa4);
}
