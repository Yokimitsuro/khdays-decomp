/* func_ov056_020b5a80 -- overlay boot of the ov037 enemy (x4: ov037/055/075/092): the ov042 shape (see
 * func_ov042_020b327c for the load-bearing forms): grabs the root heap block as the object, latches
 * it in the overlay global, copies the identity fields from the caller's config, opens the slot
 * with the {1, 0x1700, 0x900} parameter block, binds the animation table -- the alternate one when the config's flag at +0x18 is set, fills the handler vtable
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

extern void func_ov056_020b5d5c(void);
extern void func_ov056_020b5e28(void);
extern void func_ov056_020b5f30(void);
extern void func_ov056_020b5cc8(void);
extern void func_ov056_020b5d34(void);
extern void func_ov056_020b5ff8(void);
extern void func_ov056_020b623c(void);
extern void func_ov056_020b5f68(void);
extern void func_ov056_020b6470(void);
extern void *data_ov056_020b7620;
extern int data_ov056_020b75a8;
extern int data_ov056_020b75bc;
extern int data_ov056_020b7544;
extern int data_ov056_020b7554;
extern int data_ov056_020b7524;
extern int data_ov056_020b7534;
extern int data_ov056_020b7564;

/* The rig hangs off the scene node at +0x28; each bone block starts 0x40 further in. */
typedef struct { int pad[1]; int f4; } RigHdr;

static inline int bone(char *obj) {
    int p = ((RigHdr *)(*(int *)(obj + 0x20) + 0x24))->f4;
    return p != 0 ? p + 0x40 : 0;
}

void func_ov056_020b5a80(int *cfg) {
    struct { int a, b, c, d, e; } params;
    char *obj = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int b;

    data_ov056_020b7620 = obj;
    obj[9] = (char)cfg[0];
    obj[0x4bc] = (char)cfg[1];
    obj[8] = *(unsigned char *)((char *)cfg + 8);
    *(int *)(obj + 0xc) = 7;
    *(long long *)obj = 0;

    params.a = 1;
    params.c = 9 << 8;
    params.b = 0x1700;
    func_0202b850(*(signed char *)(obj + 0x4bc),
                  (unsigned short)(1 << *(unsigned char *)(obj + 8)), 0, &params, 0);

    if (cfg[6] == 0) {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov056_020b75a8, 1, cfg[0] + 7);
    } else {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov056_020b75bc, 1, cfg[0] + 7);
    }
    *(void **)(obj + 0x664 + 0x00) = (void *)&func_ov056_020b5d5c;
    *(void **)(obj + 0x664 + 0x04) = (void *)&func_ov056_020b5e28;
    *(void **)(obj + 0x664 + 0x08) = (void *)&func_ov056_020b5f30;
    *(void **)(obj + 0x664 + 0x0c) = 0;
    *(void **)(obj + 0x664 + 0x10) = 0;
    *(void **)(obj + 0x664 + 0x14) = (void *)&func_ov056_020b5cc8;
    *(void **)(obj + 0x664 + 0x18) = (void *)&func_ov056_020b5d34;
    *(void **)(obj + 0x664 + 0x20) = (void *)&func_ov056_020b5ff8;
    *(void **)(obj + 0x664 + 0x1c) = (void *)&func_ov056_020b623c;
    *(void **)(obj + 0x664 + 0x28) = (void *)&func_ov056_020b5f68;
    *(void **)(obj + 0x664 + 0x24) = (void *)&func_ov056_020b6470;

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
    *(int *)(obj + 0x520) = b != 0 ? func_02016f10((void *)b, &data_ov056_020b7544) : -1;
    b = bone(obj);
    *(int *)(obj + 0x518) = b != 0 ? func_02016f10((void *)b, &data_ov056_020b7554) : -1;
    b = bone(obj);
    *(int *)(obj + 0x514) = b != 0 ? func_02016f10((void *)b, &data_ov056_020b7524) : -1;
    b = bone(obj);
    *(int *)(obj + 0x51c) = b != 0 ? func_02016f10((void *)b, &data_ov056_020b7534) : -1;
    b = bone(obj);
    *(int *)(obj + 0x524) = b != 0 ? func_02016f10((void *)b, &data_ov056_020b7564) : -1;
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
