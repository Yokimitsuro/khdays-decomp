/* Attack sweep of the ov169 enemy (x2: ov169/170). Collects the hits of the +0x38c item either
 * from a query (func_ov107_020c8f44) or a sphere (func_ov107_020c8eb8; neither = nothing hit);
 * every victim whose kind bit is not yet in the +0x48 mask is pushed away (flat direction from the
 * actor scaled to 0x800, raised to 0x1000) with mode 0, and on success the +8 position is
 * published to the item (mode 2), reaction 0/0x53 fires there and the bit is recorded. When
 * anything was hit reaction 0x13f mode 6 fires and 1 is returned. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vecx32 { int x, y, z; };

struct Ov169Hit {
    char pad000[2];
    u16 nKind;
    char pad004[0x70];
    struct Vecx32 vPos74;
};

extern int func_ov107_020c8f44(void *item, void *query, void *out);
extern int func_ov107_020c8eb8(void *item, void *sphere, void *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern int func_ov107_020ca918(struct Ov169Hit *hit, int actor, void *item, int mode, void *push, int z);
extern void func_ov107_020c0b90(void *item, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);

int func_ov169_020ce424(int *state, void *sphere, void *query)
{
    struct Ov169Hit *hits[4];
    struct Vecx32 push;
    int i;
    int n;
    u8 bit;
    int pushed;

    pushed = 0;
    if (query != 0) {
        n = func_ov107_020c8f44(*(void **)(*state + 0x38c), query, hits);
    } else if (sphere != 0) {
        n = func_ov107_020c8eb8(*(void **)(*state + 0x38c), sphere, hits);
    } else {
        return pushed;
    }
    i = 0;
    if (n > 0) {
        do {
            bit = (u8)(1 << hits[i]->nKind);
            if ((*(u8 *)((char *)state + 0x48) & bit) == 0) {
                VEC_Subtract(&hits[i]->vPos74, (void *)(*state + 0x74), &push);
                push.y = 0;
                func_01ff8d18(&push, &push);
                func_01ffa724(0x800, &push, &push);
                push.y = 0x1000;
                if (func_ov107_020ca918(hits[i], *state, *(void **)(*state + 0x38c), 0, &push, 0) != 0) {
                    func_ov107_020c0b90(*(void **)(*state + 0x38c), 2, *(struct Vecx32 *)state[2], 0);
                    func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
                    pushed = 1;
                    *(u8 *)((char *)state + 0x48) |= bit;
                }
            }
            i++;
        } while (i < n);
    }
    if (pushed != 0) {
        func_ov107_020c5af8(*state, 0x13f, 6, (void *)state[2]);
    }
    return pushed;
}
