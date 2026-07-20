/* Constructs an AI node of one behaviour type: base-init, set flag bit 3, install the eight
 * callback function pointers into the node's vtable slots, and init its child list at +0x44. */

typedef unsigned short u16;

extern void func_ov107_020c0c94(u16 *node);
extern void func_01fffc24(void *list);
extern void func_ov107_020c2c44(void);
extern void func_ov107_020c2c94(void);
extern void func_ov107_020c2cec(void);
extern void func_ov107_020c2d84(void);
extern void func_ov107_020c2e0c(void);
extern void func_ov107_020c2e4c(void);
extern void func_ov107_020c2b94(void);
extern void func_ov107_020c2bd4(void);

void func_ov107_020c2a9c(u16 *node) {
    func_ov107_020c0c94(node);
    *node |= 8;
    *(void **)(node + 4) = (void *)func_ov107_020c2c44;
    *(void **)(node + 6) = (void *)func_ov107_020c2c94;
    *(void **)(node + 8) = (void *)func_ov107_020c2cec;
    *(void **)(node + 0x10) = (void *)func_ov107_020c2d84;
    *(void **)(node + 0x1a) = (void *)func_ov107_020c2e0c;
    *(void **)(node + 0xc) = (void *)func_ov107_020c2e4c;
    *(void **)(node + 0x38) = (void *)func_ov107_020c2b94;
    *(void **)(node + 0x3a) = (void *)func_ov107_020c2bd4;
    func_01fffc24(node + 0x22);
}
