/* Publish the landing: copy the pending anchor into the live slot and ask the placement helper
 * where the object ends up. If it reports a spot, send the canned 4-byte event to the notify
 * hook, latch the returned height and go to action 7. If not, wait unless the ready bit at
 * +0x17a is set, in which case clear the counter, drop 0x06 from the hw60 high byte and continue.
 *
 * Matched byte-exact 2026-07-23, closing an old park filed as a "2-halfword read-order tie".
 * It is not a tie: bind a pointer to the DESTINATION inside the block and copy the HIGH halfword
 * first through it. That is what makes mwcc read +0xa before +8 and reuse the table base register
 * for the second load, exactly as the ROM does. A struct assignment reads +8 first and keeps the
 * base alive, which is the four-instruction residue the park recorded. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Vec4;
struct bit0 { unsigned char b : 1; };
typedef struct { unsigned short a, b; } Pair;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov107_020c8eb8(int owner, int src, Vec4 *out);
extern void func_0203c634(int *self, int action, void *cb);
extern void func_ov117_020cd594(void);
extern Pair data_ov117_020cdc28[];

void func_ov117_020cd494(int *self) {
    int *ctx = (int *)self[1];
    Vec4 out;
    Pair p;
    void (*cb)(int owner, Pair *p, int n);

    *(Vec3 *)((char *)ctx + 0x2c) = *(Vec3 *)((char *)ctx + 0x64);

    if (func_ov107_020c8eb8(*ctx, *ctx + 0x74, &out) != 0) {
        Pair *pp = &p;
        pp->b = data_ov117_020cdc28[2].b;
        pp->a = data_ov117_020cdc28[2].a;
        cb = *(void (**)(int, Pair *, int))(*ctx + 0x24);
        if (cb != 0) {
            cb(*ctx, pp, 4);
        }
        ctx[0x1d] = out.w[0];
        *(signed char *)(*ctx + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    if (((struct bit0 *)(*ctx + 0x17a))->b == 0) {
        return;
    }
    ctx[0xe] = 0;
    ((struct hw60 *)(*ctx + 0x60))->hi &= ~6;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov117_020cd594);
}
