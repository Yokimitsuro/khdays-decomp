/* Relocate a loaded font (NFTR) resource: walk its section list (count at +0xe,
 * first section at base + *(u16*)(base+0xc), each advanced by its own size word
 * [1]) and add `base` to the internal offsets inside each FINF/CWDH/CMAP block so
 * they become absolute pointers. CGLP blocks carry no pointers (empty case). */
void func_02014874(int base) {
    unsigned int *p = (unsigned int *)(base + *(unsigned short *)(base + 0xc));
    int i = 0;
    if (i < (int)(unsigned int)*(unsigned short *)(base + 0xe)) {
        do {
            switch (*p) {
            case 0x46494e46:  /* FINF */
                p[4] += base;
                if (p[5] != 0) p[5] += base;
                if (p[6] != 0) p[6] += base;
                break;
            case 0x43574448:  /* CWDH */
                if (p[3] != 0) p[3] += base;
                break;
            case 0x434d4150:  /* CMAP */
                if (p[4] != 0) p[4] += base;
                break;
            case 0x43474c50:  /* CGLP */
                break;
            }
            i++;
            p = (unsigned int *)((int)p + p[1]);
        } while (i < (int)(unsigned int)*(unsigned short *)(base + 0xe));
    }
}
