/* func_ov005_020533a8 -- how many rows fit in the list window: 0x2bc divided by (row height at
 * +0x4c00 of the ov005 context, plus the 7-pixel gap), truncated to a signed byte.
 * func_02020400 is the runtime signed divide and returns quotient in r0 / remainder in r1, which
 * C sees as a packed `long long`; only the quotient is wanted here. */
extern long long func_02020400(int a, int b);
extern int data_ov005_0205b80c;

int func_ov005_020533a8(void) {
    return (signed char)(int)func_02020400(0x2bc,
        *(int *)(*(int *)&data_ov005_0205b80c + 0x4c00) + 7);
}
