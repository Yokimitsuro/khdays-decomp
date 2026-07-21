/* Base constructor for every AI behaviour node: reset flags (bit 0 set), assign a unique id from
 * the global counter, install the four default vtable callbacks, zero the working fields, clear
 * the low 3 bits of the state word at +0x40, and link into the manager list. */

typedef unsigned short u16;

struct StateFlags {
    unsigned int f0 : 1;
    unsigned int f1 : 1;
    unsigned int f2 : 1;
    unsigned int rest : 29;
};

extern int data_ov107_020cbb00;
extern void func_ov107_020c0d74(void);
extern void func_ov107_020c0cfc(void);
extern void func_ov107_020c0d14(void);
extern void func_ov107_020c0d94(void);
extern void func_ov107_020c9ac0(u16 *node);

void func_ov107_020c0c94(u16 *node) {
    node[0] = 0;
    node[0] |= 1;
    node[1] = (u16)data_ov107_020cbb00++;
    *(int *)((char *)node + 4) = 0;
    *(void **)((char *)node + 8) = (void *)func_ov107_020c0d74;
    *(int *)((char *)node + 0xc) = 0;
    *(int *)((char *)node + 0x10) = 0;
    *(void **)((char *)node + 0x14) = (void *)func_ov107_020c0cfc;
    *(void **)((char *)node + 0x18) = (void *)func_ov107_020c0d14;
    *(int *)((char *)node + 0x1c) = 0;
    *(int *)((char *)node + 0x20) = 0;
    *(void **)((char *)node + 0x24) = (void *)func_ov107_020c0d94;
    *(int *)((char *)node + 0x28) = 0;
    *(int *)((char *)node + 0x2c) = 0;
    *(int *)((char *)node + 0x30) = 0;
    *(int *)((char *)node + 0x34) = 0;
    *(int *)((char *)node + 0x38) = 0;
    *(int *)((char *)node + 0x3c) = 0;
    {
        struct StateFlags *sf = (struct StateFlags *)((char *)node + 0x40);
        sf->f0 = 0;
        sf->f1 = 0;
        sf->f2 = 0;
    }
    func_ov107_020c9ac0(node);
}
