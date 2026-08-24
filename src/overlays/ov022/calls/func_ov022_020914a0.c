extern void func_02014dc4(void *tracks, int handle);
extern void func_0202accc(void *anim, unsigned short slot, void *block, short arg);
extern int *func_01fff774(void *anim, unsigned short slot, int arg);

struct Ov022Rig {
    char _pad0[0x28];
    char anim[0x34 - 0x28];
    int slots[5];
    char tracks[0x108 - 0x48];
    char block[0x130 - 0x108];
    int pShared;
};

void func_ov022_020914a0(struct Ov022Rig *obj, int arg1) {
    unsigned int i = 0;

    do {
        if (obj->pShared != 0) {
            int slot = obj->slots[i];
            if (slot != 0) {
                func_02014dc4(obj->tracks, slot);
                obj->slots[i] = 0;
            }
            func_0202accc(obj->anim, i, (void *)obj->pShared, (short)arg1);
        } else {
            func_0202accc(obj->anim, i, obj->block, (short)arg1);
        }
        func_01fff774(obj->anim, i, 0);
        i = i + 1;
    } while ((int)i < 5);
}
