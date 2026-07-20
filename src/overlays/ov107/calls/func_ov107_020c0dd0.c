/* Constructs a movement-type AI node: base-init, set flag bit 1, install two callbacks (plus two
 * more only for local player 0), clear the movement fields, seed the scale at +0x118 to 0x1000, and
 * copy the zero vector into the position at +0x104. */

typedef unsigned short u16;

typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

extern void func_ov107_020c0c94(u16 *node);
extern short func_02030788(void);
extern void func_ov107_020c1dd8(int node);
extern void func_ov107_020c1cd4(int node);
extern void func_ov107_020c0e6c(void);
extern void func_ov107_020c1268(void);
extern void func_ov107_020c0ea0(void);
extern void func_ov107_020c1348(void);
extern const VecFx32 data_02041dc8;

void func_ov107_020c0dd0(u16 *node) {
    func_ov107_020c0c94(node);
    *node |= 2;
    *(void **)(node + 4) = (void *)func_ov107_020c0e6c;
    *(void **)(node + 0x1a) = (void *)func_ov107_020c1268;
    if (func_02030788() == 0) {
        *(void **)(node + 6) = (void *)func_ov107_020c0ea0;
        *(void **)(node + 10) = (void *)func_ov107_020c1348;
    }
    *(int *)((char *)node + 0x44) = 0;
    *(int *)((char *)node + 0xf4) = 0;
    node[0x24] = 0;
    *(int *)((char *)node + 0x118) = 0x1000;
    node[0x25] = 0;
    *(VecFx32 *)((char *)node + 0x104) = data_02041dc8;
    *(int *)((char *)node + 0x110) = 0;
    func_ov107_020c1dd8((int)node);
    func_ov107_020c1cd4((int)node);
}
