/* Sort the list at param_1+0x1414 by field 6, then field 0x18 (Ov008_MergeSortList through its
 * veneer, with Ov008_CompareByField6ThenField18).
 *
 * The branch target is the pool word loaded into r12, which the original fills
 * with 0x0205697c; Ov008_CompareByField6ThenField18 is the second pool word and arrives in r1
 * as the comparison argument. */
extern int Ov008_VeneerTo_Ov008_MergeSortList(int obj, int callback);
extern void Ov008_CompareByField6ThenField18(void);

int Ov008_SortListByKey(int param_1) {
    return Ov008_VeneerTo_Ov008_MergeSortList(param_1 + 0x1414, (int)&Ov008_CompareByField6ThenField18);
}
