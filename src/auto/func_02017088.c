/* Resolve a sub-block pointer inside a resource at obj: `blk = obj + obj[0xc]`.
 * If obj[0xe]==1 it's a BTX0 archive — return obj + *blk when the magic matches,
 * else NULL; otherwise return obj + *(blk+4). */
void *func_02017088(unsigned char *obj) {
    unsigned char *blk = obj + *(unsigned short *)(obj + 0xc);
    if (*(unsigned short *)(obj + 0xe) == 1) {
        if (*(unsigned int *)obj == 0x30585442) {
            return obj + *(int *)blk;
        }
        return 0;
    }
    return obj + *(int *)(blk + 4);
}
