/* c634 init: points the state's +0x1c at the actor's +0xb0 pose, seeds the +4 pose block from
 * data_020420f8, resets the actor's +0x1c6 kind and +0x1c7 request, clears bit 0 of the +0x60
 * high byte and bit 0 of +0x1ae, then installs the three slot handlers (0: 020cd904,
 * 1: 020cd9c8, 2: 020cd998). */
typedef unsigned short u16;
struct vec4 { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern const struct vec4 data_020420f8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov244_020cd904(void);
extern void func_ov244_020cd9c8(void);
extern void func_ov244_020cd998(void);

void func_ov244_020cd844(int self) {
    int *obj = *(int **)(self + 4);
    int zero;
    obj[7] = *obj + 0xb0;
    *(struct vec4 *)(obj + 1) = data_020420f8;
    zero = 0;
    *(signed char *)(*obj + 0x1c6) = zero;
    *(signed char *)(*obj + 0x1c7) = zero - 1;
    ((struct hw60 *)(*obj + 0x60))->hi &= ~1;
    *(u16 *)(*obj + 0x100 + 0xae) &= ~1;
    func_0203c634(self, 0, &func_ov244_020cd904);
    func_0203c634(self, 1, &func_ov244_020cd9c8);
    func_0203c634(self, 2, &func_ov244_020cd998);
}
