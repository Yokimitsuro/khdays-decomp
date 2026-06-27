typedef unsigned int u32;

extern void DC_FlushRange(const void *addr, u32 size);
extern void GX_LoadOAM(const void *src, u32 offset, u32 size);
extern void GXS_LoadOAM(const void *src, u32 offset, u32 size);
extern void GFXi_EnqueueCommand(u32 engine, u32 zero, void *oam, u32 size);

struct OamCtrl {
    char pad0[0x608];
    u32 engine;          // 0x608
    char pad1[0x20];
    int count;           // 0x62c
    int dirty;           // 0x630
};

struct OamObj {
    u32 attr0;
    u32 attr1;
};

void func_02031930(char *self, int flag) {
    int i;
    struct OamObj *p;

    i = ((struct OamCtrl *)(self + 0x4000))->dirty;
    if (i < ((struct OamCtrl *)(self + 0x4000))->count) {
        p = (struct OamObj *)(self + 0x238 + 0x4400) + i;
        do {
            p->attr0 = (p->attr0 & ~0x300u) | 0x200u;
            p++;
            i++;
        } while (i < ((struct OamCtrl *)(self + 0x4000))->count);
    }
    ((struct OamCtrl *)(self + 0x4000))->dirty = 0;

    if (flag) {
        DC_FlushRange(self + 0x238 + 0x4400, 0x400);
        if (((struct OamCtrl *)(self + 0x4000))->engine == 0x12) {
            GX_LoadOAM(self + 0x238 + 0x4400, 0,
                       ((struct OamCtrl *)(self + 0x4000))->count * 8);
        } else {
            GXS_LoadOAM(self + 0x238 + 0x4400, 0,
                        ((struct OamCtrl *)(self + 0x4000))->count * 8);
        }
    } else {
        GFXi_EnqueueCommand(((struct OamCtrl *)(self + 0x4000))->engine, 0,
                      self + 0x238 + 0x4400,
                      ((struct OamCtrl *)(self + 0x4000))->count * 8);
    }
}
