/* func_ov278_020d5ee8 -- spawn the 0xc-byte task for this reaction (step func_ov278_020d5f50,
 * completion func_ov278_020d601c, priority 0x64) and seed its payload with (self, hit.x, hit.z)
 * read from the collision record at +0x3b0. Returns the task handle -- see the sibling
 * func_ov236_020d5e08 for why the return type is load-bearing. */
extern int func_0203c5c0(int owner, int a, int b, void *step, void *done, int **out);
extern void func_ov278_020d5f50(void);
extern void func_ov278_020d601c(void);

int func_ov278_020d5ee8(int obj) {
    int *out;
    int r = func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, (void *)func_ov278_020d5f50,
                          (void *)func_ov278_020d601c, &out);
    out[0] = obj;
    out[1] = *(int *)(*(int *)(obj + 0x3b0) + 0x40);
    out[2] = *(int *)(*(int *)(obj + 0x3b0) + 0x48);
    return r;
}
