/* Constructs a full actor AI node: base-init, set flag bit 5, install the twelve behaviour
 * callbacks, seed the two scale fields to 0x1000, init the transform at +0xa0, zero the three
 * position vectors (+0xcc/+0xd8/+0xe4), set the team index (1 for local player 0, else 2), attach a
 * fresh sub-object at +0x9c (with its own flag bit 1), set hw60 bit 15, and init the child list.
 */

typedef unsigned short u16;

typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

extern void func_ov107_020c0c94(u16 *node);
extern void func_0203c960(int *transform);
extern short func_02030788(void);
extern void *func_0203bf44(void);
extern void func_01fffc24(void *list);
extern void func_ov107_020c3d84(void);
extern void func_ov107_020c41e4(void);
extern void func_ov107_020c4924(void);
extern void func_ov107_020c49b8(void);
extern void func_ov107_020c4bf0(void);
extern void func_ov107_020c4e30(void);
extern void func_ov107_020c4d9c(void);
extern void func_ov107_020c4e9c(void);
extern void func_ov107_020c4eb4(void);
extern void func_ov107_020c3dc8(void);
extern void func_ov107_020c3e50(void);
extern void func_ov107_020c518c(void);
extern const VecFx32 data_02041dc8;

void func_ov107_020c3c74(u16 *node) {
    func_ov107_020c0c94(node);
    *node |= 0x20;
    *(void **)(node + 4) = (void *)func_ov107_020c3d84;
    *(void **)(node + 6) = (void *)func_ov107_020c41e4;
    *(void **)(node + 8) = (void *)func_ov107_020c4924;
    *(void **)(node + 0xe) = (void *)func_ov107_020c49b8;
    *(void **)(node + 0x12) = (void *)func_ov107_020c4bf0;
    *(void **)(node + 0xc) = (void *)func_ov107_020c4e30;
    *(void **)(node + 0x1a) = (void *)func_ov107_020c4d9c;
    *(void **)(node + 0x14) = (void *)func_ov107_020c4e9c;
    *(void **)(node + 0x16) = (void *)func_ov107_020c4eb4;
    *(void **)(node + 0x22) = (void *)func_ov107_020c3dc8;
    *(void **)(node + 0x24) = (void *)func_ov107_020c3e50;
    *(void **)(node + 0x26) = (void *)func_ov107_020c518c;
    *(int *)((char *)node + 0x54) = 0x1000;
    *(int *)((char *)node + 0x58) = 0;
    *(int *)((char *)node + 0x5c) = 0x1000;
    func_0203c960((int *)(node + 0x50));
    *((char *)node + 0x179) = 0;
    *(VecFx32 *)((char *)node + 0xe4) = data_02041dc8;
    *(VecFx32 *)((char *)node + 0xd8) = *(VecFx32 *)((char *)node + 0xe4);
    *(VecFx32 *)((char *)node + 0xcc) = *(VecFx32 *)((char *)node + 0xd8);
    *(int *)((char *)node + 0x50) = func_02030788() == 0 ? 1 : 2;
    *(void **)((char *)node + 0x9c) = func_0203bf44();
    *(unsigned int *)(*(int *)((char *)node + 0x9c) + 0x5c) |= 2;
    node[0x30] = (u16)((node[0x30] & 0xffff00ff) |
                 ((((unsigned int)node[0x30] << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    func_01fffc24(node + 0xa2);
}
