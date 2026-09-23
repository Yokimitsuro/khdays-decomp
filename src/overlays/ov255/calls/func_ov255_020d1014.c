/* Spawn of the ov255 trail helper (0x14-byte state, kind 100): its tick is func_ov255_020d1074 and
 * its second callback func_ov255_020d1184; the helper keeps the two parts and the source pose. */
extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov255_020d1074(void);
extern void func_ov255_020d1184(void);

int func_ov255_020d1014(int self, int a, int b, int c)
{
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x14, func_ov255_020d1074, func_ov255_020d1184, &out);
    out[0] = a;
    out[1] = b;
    out[2] = c;
    return rc;
}
