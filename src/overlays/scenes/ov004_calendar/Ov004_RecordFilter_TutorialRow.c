/* Record filter: true for kind 4 records with id 10. */

int Ov004_RecordFilter_TutorialRow(unsigned char *p) {
    if (p[0x23] != 4) {
        return 0;
    }
    return *(unsigned short *)(p + 2) == 0xa;
}
