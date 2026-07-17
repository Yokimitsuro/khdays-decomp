/*
 * func_ov268_020d36e4 -- x3. Node update entry: apply a motion, fire an optional callback, tick.
 * Receives the target vec by value; passes &v to 020c5c54. If bit1 of self[0x40] is set and the
 * callback self[0xc] is non-null, invoke it as cb(self, 0). Always run 0203c7ac(self[0x384], 0). If
 * self[0x50] == 1, forward the trailing vec (a,b,c) by value to 020d3cc8(self[0x214], abc).
 */
struct vec3 { int x, y, z; };
extern void func_ov107_020c5c54(int self, struct vec3 *v);
extern void func_0203c7ac(int a, int b);
extern void func_ov268_020d3cec(int p, struct vec3 abc);

void func_ov268_020d36e4(int self, struct vec3 v, struct vec3 abc) {
    int *s = (int *)self;

    func_ov107_020c5c54(self, &v);
    if (s[0x10] << 30 >> 31 && s[3] != 0) {
        ((void (*)(int, int))s[3])(self, 0);
    }
    func_0203c7ac(s[0xe1], 0);
    if (s[0x14] == 1) {
        func_ov268_020d3cec(s[0x85], abc);
    }
}
