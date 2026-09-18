/* Carry-release tick of the ov171 enemy (and its byte-identical twins). Needs a +0xc carried
 * target; while the target's 64-bit flags at +0x464 lack bit 15 the +0x4c timer accumulates the
 * frame-time and past 0x2a7 the state ends (sub-state 0). Once the bit is set, the +0x10 drop
 * point and the +0x38c item's +0x74 position are both settled on the ground by the sibling
 * settle routine (each with the other's radius holder), the target is moved to the settled item
 * position (its +0x4ec rider too, with the rider's +0x40 bit-1 hook), the target is released via
 * func_ov022_020ad8e0, the item is moved to the settled drop point (same hook), and the state
 * ends with sub-state 0. */
typedef unsigned char u8;
typedef unsigned long long u64;
typedef struct { int x, y, z; } VecFx32;
typedef void (*Hook)(int obj, int a);

extern void func_ov171_020ce3cc(int scene, VecFx32 *pos, int actor);
extern void func_0202b450(void *obj, VecFx32 *pos);
extern void func_ov107_020c5c54(int obj, VecFx32 *at);
extern void func_ov022_020ad8e0(int target, int a);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov171_020ced14(int *node)
{
    int *state = (int *)node[1];
    VecFx32 drop;
    VecFx32 at;
    int scene;
    int rider;
    int item;

    if (state[3] == 0) {
        return;
    }
    if ((*(u64 *)((char *)state[3] + 0x464) & 0x8000) != 0) {
        scene = *(int *)(*state + 4);
        drop = *(VecFx32 *)(state + 4);
        at = *(VecFx32 *)(*(int *)(*state + 0x38c) + 0x74);
        func_ov171_020ce3cc(scene, &drop, *(int *)(*state + 0x38c) + 0x74);
        func_ov171_020ce3cc(scene, &at, (int)(state + 4));
        func_0202b450(*(void **)(state[3] + 0x20), &at);
        rider = *(int *)(state[3] + 0x4ec);
        if (rider != 0) {
            *(VecFx32 *)(rider + 0x190) = at;
            func_ov107_020c5c54(rider, (VecFx32 *)(rider + 0x190));
            rider = *(int *)(state[3] + 0x4ec);
            if (((*(int *)(rider + 0x40) << 30) >> 31) != 0 && *(Hook *)(rider + 0xc) != 0) {
                (*(Hook *)(rider + 0xc))(rider, 0);
            }
        }
        func_ov022_020ad8e0(state[3], 0);
        func_ov107_020c5c54(*(int *)(*state + 0x38c), &drop);
        item = *(int *)(*state + 0x38c);
        if (((*(int *)(item + 0x40) << 30) >> 31) != 0 && *(Hook *)(item + 0xc) != 0) {
            (*(Hook *)(item + 0xc))(item, 0);
        }
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        state[0x13] += *(int *)(*node + 0x2c);
        if (state[0x13] >= 0x2a8) {
            *(u8 *)(*state + 0x1c7) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        }
    }
}
