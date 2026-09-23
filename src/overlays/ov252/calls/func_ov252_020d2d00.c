/* Shed entry of the ov252 actor: bits 0-1 of +0x1ae are set, the nine +0x4e8 armour shapes hide, sound
 * 0/0x4a plays at its +0x74 position and the node moves on to 020d2d88. */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;
struct Ov252Armour { char pad[0x4e8]; int shapes[9]; };

extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d2d88(void);

void func_ov252_020d2d00(int *node)
{
    int *state = (int *)node[1];
    int i;

    *(u16 *)(*state + 0x1ae) |= 3;
    for (i = 0; i < 9; i++) {
        ((B8 *)(((struct Ov252Armour *)*state)->shapes[i] + 8))->f &= ~1;
    }
    func_ov107_020c5af8(*state, 0, 0x4a, (void *)(*state + 0x74));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d2d88);
}
