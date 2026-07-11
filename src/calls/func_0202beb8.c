/* Dispatch veneer: indexes the 0x184-byte-stride table at data_0204c208
 * (field at +0xc4) by `index` and tail-calls func_0202bedc, forwarding arg2. */
extern void *func_0202bedc();
extern int data_0204c208;

void *func_0202beb8(int index, int arg2) {
    return func_0202bedc(data_0204c208 + 0xc4 + 0x184 * index, arg2);
}
