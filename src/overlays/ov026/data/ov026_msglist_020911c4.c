/* ov026 .rodata 0x020911c4-0x020911d0: message-list initialiser. */

/* Message-list set initialiser: the language-templated message archive path
 * ("UI/cm/msl_&.msi.z", '&' = language code), a start index and the list capacity. */
typedef struct MsgListInit {
    const char *pszArchive;  /* 0x00 */
    int nFirst;              /* 0x04 */
    int nCapacity;           /* 0x08 */
} MsgListInit;

extern char data_ov026_02091340;  /* "UI/cm/msl_&.msi.z" */

/* Read by func_ov026_0208cd44. */
const MsgListInit data_ov026_020911c4 = { &data_ov026_02091340, 0, 5 };
