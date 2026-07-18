/*
 * func_ov271_020d34fc -- x3 (ov200/...). Fill the next ring-buffer slot and advance the write index.
 * slot = *(*param1+0x90) + index*0x38 (index = param1[1]). Set slot[0]=0x3000, copy the vec3 at param2
 * into slot+0x2c. For the orientation block at slot+8: if param3 is null, load the const at
 * data_020420f8; otherwise build a look-at via 0202ed60(slot+8, &data_02042258, param3). Finally wrap
 * the index: {ret, param1[1]} = divmod(index+1, capacity=*(*param1+0x8c)) and return the quotient.
 */
struct vec3 { int x, y, z; };
struct vec4 { int a, b, c, d; };
extern void func_0202ed60(unsigned int *out, void *basis, int *v);
extern long long func_02020400(int num, int den);
extern int data_02042258;
extern struct vec4 data_020420f8;

int func_ov271_020d34fc(int *param1, int *param2, int *param3) {
    int slot = *(int *)(*param1 + 0x90) + param1[1] * 0x38;
    unsigned long long r;

    *(int *)(*(int *)(*param1 + 0x90) + param1[1] * 0x38) = 0x3000;
    *(struct vec3 *)(slot + 0x2c) = *(struct vec3 *)param2;
    if (param3 != 0) {
        func_0202ed60((unsigned int *)(slot + 8), &data_02042258, param3);
    } else {
        *(struct vec4 *)(slot + 8) = data_020420f8;
    }
    r = func_02020400(param1[1] + 1, *(int *)(*param1 + 0x8c));
    param1[1] = (int)(r >> 32);
    return (int)r;
}
