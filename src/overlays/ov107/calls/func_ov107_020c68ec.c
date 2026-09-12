typedef struct Self68ec {
    char pad00[0x3c];
    void *field_3c;
    char pad40[0x1a8 - 0x40];
    void *field_1a8;
    char pad1ac[0x214 - 0x1ac];
    int field_214;
    char pad218[0x22c - 0x218];
    char list_22c[0x260 - 0x22c];
    char list_260[0x350 - 0x260];
    void *arr350[8];
} Self68ec;

extern void func_0203c7e8(void *obj);
extern void *func_0203c6a4(void *this_, int arg1);
extern void func_0203c640(void *p);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void WM_EndKeySharing_0x020c3190(void *obj);
extern void func_0203d194(void *p);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c3d84(void *self);

void func_ov107_020c68ec(Self68ec *self)
{
    void **entry;
    int i;

    func_0203c7e8(self->field_1a8);

    if (self->field_214 != 0) {
        void *r = func_0203c6a4(self->field_3c, self->field_214);
        func_0203c640(r);
        self->field_214 = 0;
    }

    entry = (void **)func_01fffd70(self->list_22c);
    if (entry != 0) {
        do {
            void *elem = *entry;
            if (elem != 0)
                WM_EndKeySharing_0x020c3190(elem);
            entry = (void **)func_01fffd8c(self->list_22c);
        } while (entry != 0);
    }

    NNSi_FndDestroyDoubleList(self->list_22c);
    NNSi_FndDestroyDoubleList(self->list_260);

    for (i = 0; i < 8; i++) {
        void *node = self->arr350[i];
        if (node != 0) {
            void *f14 = *(void **)((char *)node + 0x14);
            if (f14 != 0)
                func_0203c7e8(f14);
            func_0203d194(node);
        }
    }

    func_ov107_020c3d84(self);
}
