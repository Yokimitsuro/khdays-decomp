/* Constructs a container-type AI node: base behaviour init, set flags bit 4 and vtable slot bit 1,
 * install three callbacks, allocate and init a 0x28-byte child list at +0xb0, clear the tracking
 * fields, and attach a fresh object at +0x3c. */

typedef unsigned short u16;

extern void func_ov107_020c2a9c(u16 *node);
extern void *func_0203d15c(int size);
extern void func_01fffc24(void *list);
extern void *func_0203c400(void);
extern void func_ov107_020c9730(void);
extern void func_ov107_020c9784(void);
extern void func_ov107_020c980c(void);

void func_ov107_020c96c8(u16 *node) {
    func_ov107_020c2a9c(node);
    *node |= 0x10;
    *(void **)(node + 4) = (void *)func_ov107_020c9730;
    *(void **)(node + 6) = (void *)func_ov107_020c9784;
    *(void **)(node + 8) = (void *)func_ov107_020c980c;
    *(unsigned int *)(node + 0x20) |= 2;
    *(void **)(node + 0x58) = func_0203d15c(0x28);
    func_01fffc24(*(void **)(node + 0x58));
    *(int *)((char *)node + 0xac) = 0;
    *(int *)((char *)node + 0x94) = 0;
    *(int *)((char *)node + 0x9c) = 0;
    *(int *)((char *)node + 0xa0) = 0;
    *(void **)(node + 0x1e) = func_0203c400();
}
