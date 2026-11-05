/* Record filter: true when the record kind (+0x23) is 0. */

int Ov026_RecordFilter_StoryRow(unsigned char *p) {
    return p[0x23] == 0;
}
