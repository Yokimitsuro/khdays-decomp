/* func_ov049_020b32fc -- overlay boot of the ov049 enemy (x4: ov049/068/087/104): the ov042 shape (see
 * func_ov042_020b327c for the load-bearing forms): grabs the root heap block as the object, latches
 * it in the overlay global, copies the identity fields from the caller's config, opens the slot
 * with the {1, 0xf00, 0x900} parameter block, binds the animation table -- the alternate one when the config's flag at +0x18 is set, fills the handler vtable
 * at +0x664, attaches the scene node, invalidates the five bone handles and resolves 5 of them by
 * name, folds the three optional capability bits into the 64-bit flag word and hands the object
 * over. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(int id, unsigned short mask, int a, void *params, int b);
extern void func_0202b914(int id, void *tbl, int n, int p);
extern int  func_0202bfcc(int id);
extern void func_0202d968(void *dst, int src);
extern int  func_02016f10(void *node, void *desc);
extern void func_ov022_0209f6e0(void *obj);

extern void func_ov049_020b3728(void);
extern void func_ov049_020b3884(void);
extern void func_ov049_020b3970(void);
extern void func_ov049_020b3538(void);
extern void func_ov049_020b35ec(void);
extern void func_ov049_020b35f0(void);
extern void func_ov049_020b4518(void);
extern void func_ov049_020b45d0(void);
extern void *data_ov049_020b4d00;
extern int data_ov049_020b4c70;
extern int data_ov049_020b4c84;
extern int data_ov049_020b4af4;
extern int data_ov049_020b4b34;
extern int data_ov049_020b4b24;
extern int data_ov049_020b4b04;
extern int data_ov049_020b4b14;

/* The rig hangs off the scene node at +0x28; each bone block starts 0x40 further in. */
typedef struct { int pad[1]; int f4; } RigHdr;

static inline int bone(char *obj) {
    int p = ((RigHdr *)(*(int *)(obj + 0x20) + 0x24))->f4;
    return p != 0 ? p + 0x40 : 0;
}

void func_ov049_020b32fc(int *cfg) {
    struct { int a, b, c, d, e; } params;
    char *obj = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int b;

    data_ov049_020b4d00 = obj;
    obj[9] = (char)cfg[0];
    obj[0x4bc] = (char)cfg[1];
    obj[8] = *(unsigned char *)((char *)cfg + 8);
    *(int *)(obj + 0xc) = 19;
    *(long long *)obj = 0;

    params.a = 1;
    params.c = 9 << 8;
    params.b = 0xf00;
    func_0202b850(*(signed char *)(obj + 0x4bc),
                  (unsigned short)(1 << *(unsigned char *)(obj + 8)), 0, &params, 0);

    if (cfg[6] == 0) {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov049_020b4c70, 1, cfg[0] + 7);
    } else {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov049_020b4c84, 1, cfg[0] + 7);
    }
    *(void **)(obj + 0x664 + 0x00) = (void *)&func_ov049_020b3728;
    *(void **)(obj + 0x664 + 0x04) = (void *)&func_ov049_020b3884;
    *(void **)(obj + 0x664 + 0x08) = (void *)&func_ov049_020b3970;
    *(void **)(obj + 0x664 + 0x0c) = 0;
    *(void **)(obj + 0x664 + 0x10) = 0;
    *(void **)(obj + 0x664 + 0x14) = (void *)&func_ov049_020b3538;
    *(void **)(obj + 0x664 + 0x18) = (void *)&func_ov049_020b35ec;
    *(void **)(obj + 0x664 + 0x20) = (void *)&func_ov049_020b35f0;
    *(void **)(obj + 0x664 + 0x28) = (void *)&func_ov049_020b4518;
    *(void **)(obj + 0x664 + 0x24) = (void *)&func_ov049_020b45d0;

    func_0202d968(obj + 0x20, func_0202bfcc(*(signed char *)(obj + 0x4bc)));

    i = 0;
    goto test;
body:
    *(int *)(obj + i * sizeof(int) + 0x514) = -1;
    i++;
test:
    if (i < 5) {
        goto body;
    }

    b = bone(obj);
    *(int *)(obj + 0x520) = b != 0 ? func_02016f10((void *)b, &data_ov049_020b4af4) : -1;
    b = bone(obj);
    *(int *)(obj + 0x518) = b != 0 ? func_02016f10((void *)b, &data_ov049_020b4b34) : -1;
    b = bone(obj);
    *(int *)(obj + 0x514) = b != 0 ? func_02016f10((void *)b, &data_ov049_020b4b24) : -1;
    b = bone(obj);
    *(int *)(obj + 0x51c) = b != 0 ? func_02016f10((void *)b, &data_ov049_020b4b04) : -1;
    b = bone(obj);
    *(int *)(obj + 0x524) = b != 0 ? func_02016f10((void *)b, &data_ov049_020b4b14) : -1;
    if (cfg[3] != 0) {
        *(long long *)obj |= 0x20;
    }
    if (cfg[4] != 0) {
        *(long long *)obj |= 0x10000;
    }
    if (cfg[5] != 0) {
        *(long long *)obj |= 0x1000000000LL;
    }
    func_ov022_0209f6e0(obj);
}
