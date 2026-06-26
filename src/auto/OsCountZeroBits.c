int OsCountZeroBits(unsigned int x){ int r; __asm { clz r, x } return r; }
