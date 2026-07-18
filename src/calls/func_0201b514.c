/* GetSectionEntryPtr: resolve a section entry pointer by index. The resource is
 * *data_0204ad4c; its section base is at +0x8c; the entry table sits at
 * base + *(base+0x14). Returns base + table->entries[idx], or 0 when the table
 * is absent, idx is out of range, or the entry offset is 0. */
extern int *data_0204ad4c;

typedef struct EntryTable {
    int count;         /* +0x0 */
    int entries[1];    /* +0x4 */
} EntryTable;

int func_0201b514(unsigned int idx)
{
    int *res = data_0204ad4c;
    int section = res[0x23];                       /* *(res + 0x8c) */
    int off = *(int *)(section + 0x14);
    EntryTable *table = (off == 0) ? 0 : (EntryTable *)(section + off);
    int entry;

    if (table == 0) return 0;
    if ((int)idx < 0) return 0;
    if (idx >= (unsigned int)table->count) return 0;
    entry = table->entries[idx];
    section = res[0x23];
    return (entry == 0) ? 0 : section + entry;
}
