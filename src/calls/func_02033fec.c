/* Indexes the table that lives 0xb44bc bytes into the block held by data_0204c234 and
 * tail-calls func_0201cb64 with the element pointer.
 *
 * The second parameter is never touched here, but it must exist: it is forwarded to
 * func_0201cb64 in r1, which is what keeps r1 out of the scratch pool and shifts the
 * pool/pointer temporaries up to r2/r3 exactly as the ROM does. */
extern char *data_0204c234;
extern void *func_0201cb64();

void *func_02033fec(int i, int b) {
    return func_0201cb64((int *)(data_0204c234 + 0xb44bc) + i, b);
}
