/* Enter the aim/track state (x3: ov212/266/267). Clear the phase counter (ctx+0x20),
 * raise bit 0 of the hw60 hi byte, then seed the current point (ctx+0x34) and all 3
 * history slots (ctx+0x40..) from the live anchor at ctx[1], kick the tracker and
 * advance state.
 *
 * Same array-in-a-struct point as func_ov212_020ce36c: 0x40 is not a multiple of the
 * 12-byte element, so `arr[i]` must come off a struct member. The ROM walks the ctx
 * base and re-adds +0x40 each iteration; a pre-offset walking pointer is 1 instruction
 * short. */
struct vec3 { int x, y, z; };
struct Ctx2 { char pad[0x40]; struct vec3 arr[3]; };

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020d1294(void);

void func_ov212_020d1200(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i = 0;
    unsigned short v;

    ctx[8] = 0;
    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    *(struct vec3 *)((char *)ctx + 0x34) = *(struct vec3 *)ctx[1];
    for (; i < 3; i++) {
        ((struct Ctx2 *)ctx)->arr[i] = *(struct vec3 *)ctx[1];
    }
    func_ov107_020c9264(*ctx, 0, 1);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov212_020d1294);
}
