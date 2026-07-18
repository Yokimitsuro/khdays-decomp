/*
 * func_ov228_020d238c -- x3. Scan entities near the owner and react to each not-yet-handled one.
 * Query the owner's list (*(self[0]+0x38c)) for entities near the owner position (self[0]+0x74) ->
 * results[count]. For each result, form a per-entity bit = (1 << *(u16)(result+2)) & 0xff; skip it if
 * self[0x34] already has that bit. Otherwise compute dir = normalise(flatten_y(result(+0x74) -
 * self[0]+0x74)) and run the reaction check 020ca918(result, self[0], *(self[0]+0x38c), 3, dir, 0);
 * if it succeeds, set the bit in self[0x34] and remember that something fired. Return that flag.
 */
struct v4 { int w[4]; };
extern int  func_ov107_020c8eb8(int list, void *pos, void *results);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_ov107_020ca918(int a, int b, int c, int d, void *e, int f);

int func_ov228_020d238c(int self) {
    int results[4];
    struct v4 pos;
    int v[3];
    int count, i;
    int found = 0;

    pos = *(struct v4 *)(*(int *)self + 0x74);
    count = func_ov107_020c8eb8(*(int *)(*(int *)self + 0x38c), &pos, results);
    for (i = 0; i < count; i++) {
        int bit = (1 << *(unsigned short *)(results[i] + 2)) & 0xff;
        if (!(*(unsigned char *)(self + 0x34) & bit)) {
            VEC_Subtract((void *)(results[i] + 0x74), (void *)(*(int *)self + 0x74), v);
            v[1] = 0;
            func_01ff8d18(v, v);
            if (func_ov107_020ca918(results[i], *(int *)self, *(int *)(*(int *)self + 0x38c), 3, v, 0)
                != 0) {
                *(unsigned char *)(self + 0x34) |= bit;
                found = 1;
            }
        }
    }
    return found;
}
