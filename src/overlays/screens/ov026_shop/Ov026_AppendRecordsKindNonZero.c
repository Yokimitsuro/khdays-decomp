/* Dispatch to Ov026_WalkRecordsAppendMatching with handler Ov026_RecordFilter_MissionModeEntry. */
extern unsigned short Ov026_WalkRecordsAppendMatching(int a, int b, int c, void *handler);
extern void Ov026_RecordFilter_MissionModeEntry(void);
int Ov026_AppendRecordsKindNonZero(int param_1, int param_2, int param_3) {
    return Ov026_WalkRecordsAppendMatching(param_1, param_2, param_3, (void *)&Ov026_RecordFilter_MissionModeEntry);
}
