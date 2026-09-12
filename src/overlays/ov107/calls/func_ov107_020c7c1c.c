typedef struct {
    char pad_00[0x14];
    int field_14;
} Entry;

typedef struct {
    char pad_00[0x3c];
    int field_3c;
    char pad_40[0x214 - 0x40];
    int field_214;
    char pad_218[0x260 - 0x218];
    char list_260[0xc];
    char pad_26c[0x350 - 0x26c];
    Entry *slots[8];         /* +0x350 */
} Obj;

typedef struct {
    char pad_00[0x104];
    int field_104;
} Param1;

extern void *func_0203c6a4(int this_, int arg1);
extern void func_0203c640(void *p);
extern void func_0203bfe8(int a, int b);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void func_ov107_020c4eb4(void *obj, void *param1);

void func_ov107_020c7c1c(Obj *obj, Param1 *param1) {
    if (obj->field_214 != 0) {
        func_0203c640(func_0203c6a4(obj->field_3c, obj->field_214));
        obj->field_214 = 0;
    }

    func_0203bfe8(param1->field_104, *(int *)((char *)obj + 0x1a8));

    {
        void *node = func_01fffd70(obj->list_260);
        while (node != 0) {
            func_0203bfe8(param1->field_104, *(int *)node);
            node = func_01fffd8c(obj->list_260);
        }
    }

    {
        int i;
        for (i = 0; i < 8; i++) {
            Entry *e = obj->slots[i];
            if (e != 0 && e->field_14 != 0) {
                func_0203bfe8(param1->field_104, e->field_14);
            }
        }
    }

    func_ov107_020c4eb4(obj, param1);
}
