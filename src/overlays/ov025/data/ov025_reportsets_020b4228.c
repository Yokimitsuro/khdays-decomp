/* ov025 report sets, 0x020b4228-0x020b4234 (.rodata): the archive members of the
 * reports page per mode (0 = reports, 1 = enemy profiles), picked by the mode word
 * at +0x258 of the page: the background (Ov025_Reports_LoadResources 0209eb28), the
 * layout, the tag tracker and the entries (Ov025_Reports_SetupEntries 0209ebb4).
 * Two 5-byte records and two bytes of padding; the letters are the members' tags.
 *
 * Readers: 0209eb28, 0209ebb4.
 */

typedef unsigned char u8;

typedef struct Ov025ReportsSet {
    u8   nBgMember;           /* 0x00: the background archive member */
    u8   nLayoutMember;       /* 0x01 */
    u8   nTrackerMember;      /* 0x02 */
    u8   nEntriesMember;      /* 0x03 */
    u8   nField04;            /* 0x04 */
} Ov025ReportsSet;

const Ov025ReportsSet data_ov025_020b4228[2] = {
    { 'G', 'J', 'F', 'I', 'M' },
    { 'O', 'R', 'N', 'Q', 'U' },
};
