/* Dispatch to Ov004_WalkRecordsAppendMatching with handler Ov004_RecordFilter_MissionModeEntry. */
extern unsigned short Ov004_WalkRecordsAppendMatching(int a, int b, int c, void *handler);
extern void Ov004_RecordFilter_MissionModeEntry(void);
int Ov004_AppendRecordsKindNonZero(int param_1, int param_2, int param_3) {
    return Ov004_WalkRecordsAppendMatching(param_1, param_2, param_3, (void *)&Ov004_RecordFilter_MissionModeEntry);
}
