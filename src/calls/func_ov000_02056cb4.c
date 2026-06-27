extern int NNS_FndAppendListObject();
extern int NNS_FndGetNextListObject();
extern int NNSi_FndAllocFromDefaultExpHeap();

struct info_s {
    int f0;
    int pad04[5];
    int field18;
    int field1c;
    int field20;
    unsigned char field24;
};

struct node_s {
    int f0;
    int f4;
    int f8;
    int fc;
    int f10;
    int f14;
};

struct local_s {
    struct info_s *info;
    char pad04[0x20 - 4];
    int field20;
};

struct obj_s {
    char pad00[0x14];
    int list;
    char pad18[0x30 - 0x18];
    int f30;
    int f34;
    char padmid[0xf8 - 0x38];
    void (*fn0)(struct local_s *, int, int, int);
    void (*fn1)(struct local_s *);
};

void func_ov000_02056cb4(struct obj_s *obj, int arg1, int arg2, int arg3)
{
    struct local_s local;
    struct node_s *node;

    local.info = 0;
    obj->fn0(&local, 0x13, arg1, 0xe);

    if (arg1 == 0x59)
        obj->f30 = 1;
    if (arg1 == 0x42)
        obj->f34 = 1;

    node = (struct node_s *)NNS_FndGetNextListObject(&obj->list, 0);
    if (node) {
        do {
            if (node->f0 == arg1) {
                if (local.info->field18 != 0)
                    node->f4 = node->f4 + arg2;
                else
                    node->f4 = -1;
                node->f8 = node->f8 + arg3;
                node->fc = node->fc | local.field20;
                node->f14 = local.info->field1c;
                break;
            }
            node = (struct node_s *)NNS_FndGetNextListObject(&obj->list, node);
        } while (node);
    }

    if (node == 0) {
        node = (struct node_s *)NNSi_FndAllocFromDefaultExpHeap(0x24);
        node->f0 = arg1;
        if (local.info->field18 == 0)
            arg2 = -1;
        node->f4 = arg2;
        node->f8 = arg3;
        node->fc = local.field20;
        node->f10 = 0;
        node->f14 = local.info->field1c;
        NNS_FndAppendListObject(&obj->list, node);
    }

    if (local.info->field18 != 0) {
        if (node->f4 > local.info->field24)
            node->f4 = local.info->field24;
    }
    if (node->f0 == 0x5a) {
        if (node->f8 > 0xc)
            node->f8 = 0xc;
    }

    obj->fn1(&local);
}
