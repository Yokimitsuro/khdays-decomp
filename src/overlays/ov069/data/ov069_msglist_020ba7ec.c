/* ov069 .rodata 0x020ba7ec-0x020ba7f8: message-list initialiser. */

/* Message-list set initialiser: the language-templated message archive path
 * ("UI/cm/msl_&.msi.z", '&' = language code), a start index and the list capacity. */
typedef struct MsgListInit {
    const char *pszArchive;  /* 0x00 */
    int nFirst;              /* 0x04 */
    int nCapacity;           /* 0x08 */
} MsgListInit;

extern char data_ov069_020baab4;  /* "UI/cm/msl_&.msi.z" */

/* Read by func_ov069_020b876c. */
const MsgListInit data_ov069_020ba7ec = { &data_ov069_020baab4, 0, 4 };
