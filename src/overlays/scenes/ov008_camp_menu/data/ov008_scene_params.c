/* ov008 camp's records by character, gOv008CampCharacterRecords, 0x0208e9c4-0x0208edd4 (.rodata).
 *
 * One 52-byte entry per character (the camp's member 0): its data folder's code (ba/ch/<code>/)
 * that 0205a138 prints into the resource name (gOv008BaChWPathFmt), and the two dictionary
 * names 0205a1fc looks up (02016f10) for the panels when they are set.
 */

typedef struct Ov008CampCharacterRecord {
    const char *pCode;        /* 0x00: the character's data folder code, formatted into the resource name */
    char aNameLeft[16];       /* 0x04: a weapon node, the left panel's, empty when none */
    char aNameRight[16];      /* 0x14: a weapon node, the right panel's */
    char aReserved[16];       /* 0x24 */
} Ov008CampCharacterRecord;

extern char gOv008R2Name;
extern char gOv008GoName;
extern char gOv008DoName;
extern char gOv008MiName;
extern char gOv008ZeName;
extern char gOv008XoName;
extern char gOv008XeName;
extern char gOv008VeName;
extern char gOv008RiName;
extern char gOv008MaName;
extern char gOv008LuName;
extern char gOv008LeName;
extern char gOv008LaName;
extern char gOv008DeName;
extern char gOv008SoName;
extern char gOv008XaName;
extern char gOv008SaName;
extern char gOv008XiName;
extern char gOv008AxName;
extern char gOv008RoName;

const Ov008CampCharacterRecord gOv008CampCharacterRecords[20] = {
    { &gOv008RoName, "ro_w_tg_L", "ro_w_tg_R", "" },
    { &gOv008AxName, "ax_h_L", "ax_h_R", "" },
    { &gOv008XiName, "xig_h_L", "xig_h_R", "" },
    { &gOv008SaName, "sa_h_L", "sa_h_R", "" },
    { &gOv008XaName, "", "", "xaldin_R" },
    { &gOv008SoName, "so_left_dummy", "so_w_tg00", "" },
    { &gOv008DeName, "", "", "demyx_R" },
    { &gOv008LaName, "la_h_L", "la_h_R", "" },
    { &gOv008LeName, "", "le_h_R", "" },
    { &gOv008LuName, "", "", "luxord_R" },
    { &gOv008MaName, "", "ma_h_R", "" },
    { &gOv008RiName, "", "ri_h_R", "" },
    { &gOv008VeName, "", "", "ve_w_tg" },
    { &gOv008XeName, "xe_h_L", "xe_h_R", "" },
    { &gOv008XoName, "", "xo_h_R", "" },
    { &gOv008ZeName, "", "", "zexion_R" },
    { &gOv008MiName, "", "mi_w_tg_R", "" },
    { &gOv008DoName, "", "do_h_R", "" },
    { &gOv008GoName, "", "go_h_R", "" },
    { &gOv008R2Name, "ro_h_L", "ro_h_R", "" },
};
