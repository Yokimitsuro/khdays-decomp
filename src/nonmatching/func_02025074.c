/* NONMATCHING (redundant-cast-fold tie): mwcc 139 folds the record index
 * (param_1 & 0x1ff) << 16 >> 14 into param_1<<23>>21 (dropping the mask), whereas the
 * ROM keeps `and rec,mask,lsr#15` then `<<16>>14`. Reloc-free 72B; semantics exact.
 * Archive_SubfileIsCompressed: return desc[k] & 0x80000000 (bit31=compressed) from the
 * container directory at 0x01ff8000; handle>>7&0xfffffc = dir off, handle&0x1ff = k. */
unsigned int func_02025074(unsigned int param_1) {
    unsigned int uVar1 = 0xfffffc & param_1 >> 7;
    return *(unsigned int *)(uVar1 +
             (((((unsigned int)*(unsigned short *)(0x1ff8000 + uVar1 + 2) & 0xfffffc >> 0xf) + 1) / 2
               << 0x11) >> 0xf) +
             (((param_1 & 0xfffffc >> 0xf) << 0x10) >> 0xe) + 0x1ff8010) & 0x80000000;
}
