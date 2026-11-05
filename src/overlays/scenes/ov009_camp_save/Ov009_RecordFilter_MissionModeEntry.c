/* Record filter: true when the record kind (+0x23) is not 0. */

int Ov009_RecordFilter_MissionModeEntry(unsigned char *r0)
{
    return r0[0x23] != 0;
}
