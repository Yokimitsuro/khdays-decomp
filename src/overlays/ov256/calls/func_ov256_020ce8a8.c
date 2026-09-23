/* Leap entry tick of the ov256 actor: it re-picks its target (020ccd54) and the +0x10 velocity is the
 * +0x450 owner's +0x2c vector turned by its heading (020cd054) at triple length. Once the partner
 * holds no queued move, or on the fourth +0x17a flag, +0x4c clears, bits 1-2 and 7 of the +0x60 high
 * byte are set on both claws (+0x434, +0x438) and the actor, the +0x428 shape hides and is flagged
 * (bit 1), the actor is knocked back at the +0xc point (mode 6) and the node moves on to 020cea18. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; };

extern int func_ov256_020ccd54(int *node);
extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cea18(void);

static inline void HighByteOr(char *obj, int bits)
{
    u16 hw = *(u16 *)(obj + 0x60);
    *(u16 *)(obj + 0x60) = (hw & ~0xff00) | ((((((unsigned int)hw << 0x10) >> 0x18) | bits) << 0x18) >> 0x10);
}

void func_ov256_020ce8a8(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020ccd54(node);
    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    func_01ffa724(0x3000, &v, (Vec3 *)(state + 4));
    if (*(u8 *)(state[1] + 0xad) != 0 && !((struct Flag17a *)(*state + 0x17a))->b3) {
        return;
    }
    state[0x13] = 0;
    HighByteOr(*(char **)(*state + 0x434), 0x86);
    HighByteOr(*(char **)(*state + 0x438), 0x86);
    ((B8 *)(*(int *)(*state + 0x428) + 8))->f &= ~1;
    HighByteOr((char *)*state, 0x86);
    ((B8 *)(*(int *)(*state + 0x428) + 8))->f |= 2;
    func_ov107_020c0b90(*state, 6, *(Vec3 *)state[3], 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cea18);
}
