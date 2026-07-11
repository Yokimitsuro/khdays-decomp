/* Locate the keyframe segment in a curve whose value range brackets `val`. Look up
 * the curve descriptor (func_020171f0), start from a fixed-point estimate
 * (slope[2]*val >> 12), then clamp down while the entry value exceeds `val` and up
 * while the next entry is still <= `val`. Entries are {u16 value; u16 pad} pairs at
 * base + descriptor[3]; returns the address of the chosen entry. */
extern int func_020171f0(int base, unsigned int key);
typedef struct { unsigned short v; unsigned short pad; } Entry;
int func_0201717c(int base, unsigned int key, unsigned int val) {
    unsigned short *p = (unsigned short *)func_020171f0(base, key);
    Entry *tbl = (Entry *)(base + p[3]);
    unsigned int i = (int)(short)p[2] * val >> 0xc;
    while (i != 0 && tbl[i].v >= val) i--;
    while (i + 1 < (unsigned int)*p && tbl[i + 1].v <= val) i++;
    return (int)(tbl + i);
}
