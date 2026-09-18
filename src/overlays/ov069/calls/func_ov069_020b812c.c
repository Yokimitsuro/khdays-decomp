/* Whether the save block's +0x10e0 bit array has bit `id` set (ids from 0x400 up are never set). */
extern int func_02025694(void *bits, unsigned int bit);
extern char *data_0204be18;

int func_ov069_020b812c(unsigned int id)
{
    if (id >= 0x400) {
        return 0;
    }
    if (func_02025694(data_0204be18 + 0x10e0, id) != 0) {
        return 1;
    }
    return 0;
}
