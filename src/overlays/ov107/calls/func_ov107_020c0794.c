typedef struct { int w[11]; } Xform44;

typedef struct {
    int field_00;
    Xform44 xform;
    char pad[0x5c - 0x30];
    int flags;
} Node;

typedef struct { Node *node; } Entry;

extern int func_0203c5c0(int param_1, unsigned int param_2, unsigned int param_3,
                          int param_4, int param_5, Entry **param_6);
extern void func_0203b9fc(int obj, unsigned short idx, int blend, int zero);
extern void func_0203c7ac(int *ptr, int arg);
extern void func_ov107_020c0894(void);
extern void func_ov107_020c0868(void);

int func_ov107_020c0794(int taskList, Node *node, int mode, int blend, Xform44 *m)
{
    Entry *entry;
    int r = func_0203c5c0(taskList, 100, 4, (int)&func_ov107_020c0868,
                           (int)&func_ov107_020c0894, &entry);
    entry->node = node;
    entry->node->flags |= 2;
    entry->node->xform = *m;
    for (int i = 0; i < 5; i++) {
        if (mode & (1 << i))
            func_0203b9fc((int)node, i, blend, 0);
    }
    func_0203c7ac((int *)node, 0);
    return r;
}
