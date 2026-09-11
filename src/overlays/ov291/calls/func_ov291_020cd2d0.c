typedef unsigned char u8;
typedef unsigned short u16;

struct Elem16 {
    u8 pad00[0xc];
    int field_0c;
};

extern int func_ov107_020c9f48(int param_1, int param_2);
extern void func_0202f384(void *in_vec, int unused, void *out_vec);
extern int func_0203bec0(int param_1, int param_2);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_01ffa724(int factor, int *src, int *dst);
extern void func_0203c634(int *a, int i, int v);

void func_ov291_020cd2d0(int *node)
{
    int *task = (int *)node[1];
    int local[3];
    int factor;
    int actor;
    u8 phase;

    actor = *(int *)task;
    factor = func_ov107_020c9f48(*(int *)(actor + 0x394), (int)local);

    actor = *(int *)task;
    func_0202f384((void *)local, actor + 0xa0, (void *)local);

    phase = *(u8 *)((char *)task + 0x28);
    if (phase == 0) {
        if (func_0203bec0(*(int *)(*(int *)task + 0x384), 0) >= 0x6000) {
            func_ov107_020c5af8(*(int *)task, 0x16f, 4, task[3]);
            *(u8 *)((char *)task + 0x28) = 1;
        }
    } else if (phase == 1) {
        if (func_0203bec0(*(int *)(*(int *)task + 0x384), 0) >= 0xc000) {
            func_ov107_020c5af8(*(int *)task, 0x16f, 5, task[3]);
            *(u8 *)((char *)task + 0x28) = 2;
        }
    } else if (phase == 2) {
        if (func_0203bec0(*(int *)(*(int *)task + 0x384), 0) < 0xc000) {
            *(u8 *)((char *)task + 0x28) = 0;
        }
    }

    func_01ffa724(factor, local, (int *)((char *)task + 0x10));
    task[7] = 0;

    if (*(u8 *)task[8] != 0) {
        return;
    }

    actor = *(int *)task;
    {
        int idx = task[9];
        struct Elem16 *arr = *(struct Elem16 **)(actor + 0x3a0);
        u16 val = (u16)arr[idx].field_0c;

        if (val == 1) {
            *(u8 *)(actor + 0x1c7) = 4;
        } else if (val == 2) {
            *(u8 *)(actor + 0x1c7) = 7;
        }
    }

    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
