/* Reset the stream cursor at +0x2c20 and put the decoder back into state 10.
 *
 * The same address is reached two ways -- once through the full expression for
 * the cursor store and once through a held pointer for the state byte -- which
 * is why the ROM decomposes 0x2c20 differently in each. Same shape as
 * func_ov022_02096964. */
void func_ov022_0209be44(int self) {
    char *p = (char *)(self + 0x2c20);

    *(int *)(self + 0x2c20) = 0;
    p[4] = 10;
}
