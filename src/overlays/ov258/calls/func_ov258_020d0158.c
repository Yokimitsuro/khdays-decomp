/* Hand follow of the ov258 held item: the item's pose takes the transform of the owner's (+0x390)
 * left (+0x43c) or right (+0x448) hand by its +0x38c side flag and the item moves to that hand's
 * +0x14 point. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c9d0(void *srt, void *from);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);

void func_ov258_020d0158(int *node)
{
    int *state = (int *)node[1];
    int hand;

    if (*(u8 *)(*state + 0x38c) == 0) {
        hand = *(int *)(*(int *)(*state + 0x390) + 0x43c);
        func_0203c9d0((void *)(*state + 0xa0), (void *)(hand + 4));
    } else {
        hand = *(int *)(*(int *)(*state + 0x390) + 0x448);
        func_0203c9d0((void *)(*state + 0xa0), (void *)(hand + 4));
    }
    func_ov107_020c5c54(*state, (Vec3 *)(hand + 0x14));
}
