/* Latch entry of an ov259 helper: +0x34 and the +0x38 flag clear, the +0x18 point resets, the +0x38c
 * shape shows, the +0x394 owner is knocked back at the helper's +0x74 position (mode 5) and the node
 * moves on to 020d23c4. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d23c4(void);
extern const Vec3 data_02041dc8;

void func_ov259_020d2328(int *node)
{
    int *state = (int *)node[1];

    state[0xd] = 0;
    *((u8 *)state + 0x38) = 0;
    *(Vec3 *)(state + 6) = data_02041dc8;
    ((B8 *)(*(int *)(*state + 0x38c) + 8))->f |= 1;
    func_ov107_020c0b90(*(int *)(*state + 0x394), 5, *(Vec3 *)(*state + 0x74), 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d23c4);
}
