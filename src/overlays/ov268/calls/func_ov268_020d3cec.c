/*
 * func_ov268_020d3cec -- x3 (ov208/209/268). Set the target position and orient toward it.
 * Store the incoming vec3 into self[6..8], build the look-at matrix at self[0xc..] via
 * 0202ed60(self+0xc, &data_02042258, &v), then raise the "aim dirty" flag *(*self+0x1c7)=1.
 */
struct vec3 { int x, y, z; };
extern void func_0202ed60(unsigned int *out, void *basis, struct vec3 *v);
extern int data_02042258;

void func_ov268_020d3cec(int *self, struct vec3 v) {
    *(struct vec3 *)(self + 6) = v;
    func_0202ed60((unsigned int *)(self + 0xc), &data_02042258, &v);
    *(unsigned char *)(*self + 0x1c7) = 1;
}
