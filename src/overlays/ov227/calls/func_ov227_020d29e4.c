/* Spawn tick of the ov227 enemy: every 0x2a8 of the +0x5c timer the first of the owner's ten +0x3ec
 * members without a +0x388 item is placed 1.0 above the +0x3ac body's +0x20 point (counting the
 * spawns at +0x60). While the +4 item is busy (+0xad) nothing else happens; otherwise animation
 * 0x19 plays, or after ten spawns animation 0x1a and the tick hands over to func_ov227_020d2ae0. */
typedef struct { int x, y, z; } Vec3;
struct Ov227Family { char pad[0x3ec]; char *aMembers[10]; };

extern void func_ov227_020d3da0(char *obj, Vec3 pos);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov227_020d2ae0(int *node);

void func_ov227_020d29e4(int *node)
{
    int *state = (int *)node[1];

    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] >= 0x2a8) {
        int i;
        struct Ov227Family *owner = (struct Ov227Family *)*state;
        Vec3 pos = *(Vec3 *)(**(int **)((char *)owner + 0x3ac) + 0x20);

        pos.y += 0x1000;
        for (i = 0; i < 0xa; i++) {
            if (owner->aMembers[i] != 0 && *(int *)(owner->aMembers[i] + 0x388) == 0) {
                func_ov227_020d3da0(owner->aMembers[i], pos);
                break;
            }
        }
        state[0x17] = 0;
        state[0x18]++;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x18] < 0xa) {
        func_ov107_020c9264(*state, 0x19, 0);
        return;
    }
    func_ov107_020c9264(*state, 0x1a, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov227_020d2ae0);
}
