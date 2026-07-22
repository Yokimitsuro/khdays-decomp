/* func_ov023_02082ec0 -- ov023 scene poll: hand back the next state function only once bit 1 of
 * the status halfword at +0x8758c of the scene root is set; until then stay put (0). */
extern int data_ov023_0208a784;
extern void func_ov023_02082ee4(void);

void *func_ov023_02082ec0(void) {
    if ((*(unsigned short *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x8758c) & 2) != 0) {
        return (void *)func_ov023_02082ee4;
    }
    return 0;
}
