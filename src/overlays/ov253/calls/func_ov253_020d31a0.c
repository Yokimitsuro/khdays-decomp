/* func_ov253_020d31a0 -- spawn the 0x20-byte sub-object of kind 0x64 (tick 020d3210, finish
 * 020d3388) linked to the actor and its +0x3a0 item, seeded with the given position. */
typedef struct { int x, y, z; } Vec3;
struct Ov253Child { int pOwner; int pItem; Vec3 pos; };

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, struct Ov253Child **out);
extern void func_ov253_020d3210(void);
extern void func_ov253_020d3388(void);

int func_ov253_020d31a0(int self, const Vec3 *pos) {
    struct Ov253Child *out;
    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x20, func_ov253_020d3210, func_ov253_020d3388, &out);
    out->pOwner = self;
    out->pItem = *(int *)(self + 0x3a0);
    out->pos = *pos;
    return rc;
}
