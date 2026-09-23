/* Spawns an ov235 helper object through func_0203c5c0 (scene +0x3c, kind 100, 0x18 bytes, update
 * func_ov235_020d1d48, teardown func_ov235_020d1e5c) and fills it with the owner and the three
 * arguments; returns the spawner's result. */
extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov235_020d1d48(void);
extern void func_ov235_020d1e5c(void);

int func_ov235_020d1cdc(int self, int a, int b, int c)
{
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x18, func_ov235_020d1d48, func_ov235_020d1e5c, &out);
    out[0] = self;
    out[1] = a;
    out[2] = b;
    out[3] = c;
    return rc;
}
