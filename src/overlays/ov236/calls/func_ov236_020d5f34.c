/* func_ov236_020d5f34 -- spawn the 0xc-byte task for this reaction (step func_ov236_020d6068,
 * completion func_ov236_020d5f9c, priority 0x64) and seed its payload with (self, hit.x, hit.z)
 * read from the collision record at +0x3b0. Returns the task handle -- see the sibling
 * func_ov236_020d5e08 for why the return type is load-bearing. */
extern int func_0203c5c0(int owner, int a, int b, void *step, void *done, int **out);
extern void func_ov236_020d5f9c(void);
extern void func_ov236_020d6068(void);

int func_ov236_020d5f34(int obj) {
    int *out;
    int r = func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, (void *)func_ov236_020d6068,
                          (void *)func_ov236_020d5f9c, &out);
    out[0] = obj;
    out[1] = *(int *)(*(int *)(obj + 0x3b0) + 0x40);
    out[2] = *(int *)(*(int *)(obj + 0x3b0) + 0x48);
    return r;
}
