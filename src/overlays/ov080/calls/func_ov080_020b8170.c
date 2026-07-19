/* func_ov080_020b8170 -- overlay boot: builds the enemy rig object and publishes it.
 *
 * Grabs the current root heap block as the object, latches it in the overlay global, copies the
 * three identity fields out of the caller's config (type, slot id, bit index), opens the slot
 * with func_0202b850 (the 3-word parameter block is {1, 0x1f00, 0x900}), binds the animation
 * table -- ...4bfc when the config's alt flag is set, ...4be8 otherwise -- fills the ten-entry
 * handler vtable at +0x664, attaches the scene node, invalidates the five bone handles at
 * +0x514 and then resolves four of them by name, and finally folds three optional capability
 * bits into the 64-bit flag word before handing the object to func_ov022_0209f6e0.
 *
 * Head of a 16-member family (ov038/040/041/042/...); the members differ only in the vtable
 * entries and the four bone-name descriptors.
 *
 * Dos formas del fuente que NO son cosmeticas y sin las cuales no casa:
 *   - El bucle va con `goto` explicito. Escrito como `for`, mwcc lo ROTA (entra directo al
 *     cuerpo porque puede probar 0 < 5) y el ROM salta antes al test. Ninguna grafia de
 *     for/while/do lo evita; el goto reproduce el orden de bloques exacto.
 *   - `params` tiene CINCO campos y solo se escriben tres. Los dos muertos son los 8 bytes de
 *     pila que separan `sub sp,#0x18` (ROM) de `sub sp,#0x10`, y son ademas los que obligan a
 *     mwcc a empujar el r3 de relleno en el `push`. Un campo de mas que nadie lee no es ruido:
 *     es la unica prueba que queda de como era la estructura original.
 *   - `i * sizeof(int)` en vez de `i * 4`: con `* 4` mwcc crea una variable de induccion y gasta
 *     un callee-saved de mas; con el sizeof recalcula el desplazamiento como hace el ROM.
 */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(int id, unsigned short mask, int a, void *params, int b);
extern void func_0202b914(int id, void *tbl, int n, int p);
extern int  func_0202bfcc(int id);
extern void func_0202d968(void *dst, int src);
extern int  func_02016f10(void *node, void *desc);
extern void func_ov022_0209f6e0(void *obj);

extern void func_ov080_020b8410(void);
extern void func_ov080_020b8508(void);
extern void func_ov080_020b854c(void);
extern void func_ov080_020b8384(void);
extern void func_ov080_020b83f0(void);
extern void func_ov080_020b85d8(void);
extern void func_ov080_020b8578(void);
extern void func_ov080_020b92d8(void);

extern void *data_ov080_020b9be0;
extern int data_ov080_020b9b54;
extern int data_ov080_020b9b68;
extern int data_ov080_020b9afc;
extern int data_ov080_020b9b1c;
extern int data_ov080_020b9b0c;
extern int data_ov080_020b9aec;

/* The rig hangs off the scene node at +0x28; each bone block starts 0x40 further in. */
typedef struct { int pad[1]; int f4; } RigHdr;

static inline int bone(char *obj) {
    int p = ((RigHdr *)(*(int *)(obj + 0x20) + 0x24))->f4;
    return p != 0 ? p + 0x40 : 0;
}

void func_ov080_020b8170(int *cfg) {
    struct { int a, b, c, d, e; } params;
    char *obj = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int b;

    data_ov080_020b9be0 = obj;
    obj[9] = (char)cfg[0];
    obj[0x4bc] = (char)cfg[1];
    obj[8] = *(unsigned char *)((char *)cfg + 8);
    *(int *)(obj + 0xc) = 11;
    *(long long *)obj = 0;

    params.a = 1;
    params.c = 9 << 8;
    params.b = 0xf << 8;
    func_0202b850(*(signed char *)(obj + 0x4bc),
                  (unsigned short)(1 << *(unsigned char *)(obj + 8)), 0, &params, 0);

    if (cfg[6] == 0) {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov080_020b9b54, 1, cfg[0] + 7);
    } else {
        func_0202b914(*(signed char *)(obj + 0x4bc), &data_ov080_020b9b68, 1, cfg[0] + 7);
    }

    *(void **)(obj + 0x664 + 0x00) = (void *)&func_ov080_020b8410;
    *(void **)(obj + 0x664 + 0x04) = (void *)&func_ov080_020b8508;
    *(void **)(obj + 0x664 + 0x08) = (void *)&func_ov080_020b854c;
    *(void **)(obj + 0x664 + 0x0c) = 0;
    *(void **)(obj + 0x664 + 0x10) = 0;
    *(void **)(obj + 0x664 + 0x14) = (void *)&func_ov080_020b8384;
    *(void **)(obj + 0x664 + 0x18) = (void *)&func_ov080_020b83f0;
    *(void **)(obj + 0x664 + 0x20) = (void *)&func_ov080_020b85d8;
    *(void **)(obj + 0x664 + 0x28) = (void *)&func_ov080_020b8578;
    *(void **)(obj + 0x664 + 0x24) = (void *)&func_ov080_020b92d8;

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
    *(int *)(obj + 0x520) = b != 0 ? func_02016f10((void *)b, &data_ov080_020b9afc) : -1;
    b = bone(obj);
    *(int *)(obj + 0x518) = b != 0 ? func_02016f10((void *)b, &data_ov080_020b9b1c) : -1;
    b = bone(obj);
    *(int *)(obj + 0x51c) = b != 0 ? func_02016f10((void *)b, &data_ov080_020b9b0c) : -1;
    b = bone(obj);
    *(int *)(obj + 0x524) = b != 0 ? func_02016f10((void *)b, &data_ov080_020b9aec) : -1;

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
