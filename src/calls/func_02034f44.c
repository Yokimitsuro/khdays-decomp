/* P2_ExtractString: fetch string sub-index `param_4` from message-db `param_3`'s
 * offset-table buffer (entry[4] = {u32 count; u32 offsets[count]; u16 data[]}).
 * data base = buf + (count+1)*4. String = data[offset[k] .. offset[k+1]],
 * len_u16 = (offset[k+1]-offset[k])>>1. keep<0: return the in-place pointer (out
 * count = N); keep>=0: copy into a fresh heap block (out count = len). */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern int data_0204c238;
int func_02034f44(unsigned short **out_ptr, unsigned int *out_count, int db, int k, int keep) {
    unsigned int count;
    unsigned int *buf = *(unsigned int **)(data_0204c238 + db * 0x14 + 4);
    count = *buf;
    unsigned int len = (buf[k + 1] - (k == 0 ? 0 : buf[k])) >> 1;
    unsigned short *sp = (unsigned short *)((int)buf + ((count + 1) * 4 + (k == 0 ? 0 : buf[k])));
    unsigned short *dst;
    unsigned int i;
    *out_ptr = 0;
    *out_count = 0;
    if (keep < 0) {
        *out_ptr = sp;
        *out_count = count;
    } else {
        dst = (unsigned short *)NNSi_FndAllocFromDefaultExpHeap(len << 1);
        if (dst == 0) {
            return 0;
        }
        *out_ptr = dst;
        *out_count = len;
        for (i = 0; i < len; i++) {
            *dst++ = *sp++;
        }
    }
    return 1;
}
