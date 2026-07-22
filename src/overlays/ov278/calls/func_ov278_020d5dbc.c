/* func_ov278_020d5dbc -- spawn the 0xc-byte task that drives this reaction (step
 * func_ov278_020d5e1c, completion func_ov278_020d5eb0, priority 0x64) and seed its three-word
 * payload with (self, a, b). RETURNS the task handle: the ROM leaves r0 untouched from the spawn
 * call to the `pop`, and declaring the function `void` frees r0 so mwcc reuses it for the payload
 * pointer -- one register off, nothing else.
 * The payload pointer is re-read from the stack before each store because its address escaped into
 * the spawn call, so the stores could alias it; that is the ROM's three `ldr r1,[sp,#8]`. */
extern int func_0203c5c0(int owner, int a, int b, void *step, void *done, int **out);
extern void func_ov278_020d5eb0(void);
extern void func_ov278_020d5e1c(void);

int func_ov278_020d5dbc(int obj, int a, int b) {
    int *out;
    int r = func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, (void *)func_ov278_020d5e1c,
                          (void *)func_ov278_020d5eb0, &out);
    out[0] = obj;
    out[1] = a;
    out[2] = b;
    return r;
}
