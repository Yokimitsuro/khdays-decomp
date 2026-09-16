/* ov008 scene parameter table data_ov008_0208e9c4, 0x0208e9c4-0x0208edd4 (.rodata).
 *
 * One 52-byte entry per scene id: the two-letter code that 0205a138 prints
 * into the resource name (data_ov008_02090278), and the two dictionary
 * names 0205a1fc looks up (02016f10) for the panels when they are set.
 */

typedef struct Ov008SceneParam {
    const char *pCode;        /* 0x00: two-letter scene code, formatted into the resource name */
    char aNameLeft[16];       /* 0x04: dictionary entry for the left panel, empty when none */
    char aNameRight[16];      /* 0x14: dictionary entry for the right panel */
    char aReserved[16];       /* 0x24 */
} Ov008SceneParam;

extern char data_ov008_02090214;
extern char data_ov008_02090218;
extern char data_ov008_0209021c;
extern char data_ov008_02090220;
extern char data_ov008_02090224;
extern char data_ov008_02090228;
extern char data_ov008_0209022c;
extern char data_ov008_02090230;
extern char data_ov008_02090234;
extern char data_ov008_02090238;
extern char data_ov008_0209023c;
extern char data_ov008_02090240;
extern char data_ov008_02090244;
extern char data_ov008_02090248;
extern char data_ov008_0209024c;
extern char data_ov008_02090250;
extern char data_ov008_02090254;
extern char data_ov008_02090258;
extern char data_ov008_0209025c;
extern char data_ov008_02090260;

const Ov008SceneParam data_ov008_0208e9c4[20] = {
    { &data_ov008_02090260, "ro_w_tg_L", "ro_w_tg_R", "" },
    { &data_ov008_0209025c, "ax_h_L", "ax_h_R", "" },
    { &data_ov008_02090258, "xig_h_L", "xig_h_R", "" },
    { &data_ov008_02090254, "sa_h_L", "sa_h_R", "" },
    { &data_ov008_02090250, "", "", "xaldin_R" },
    { &data_ov008_0209024c, "so_left_dummy", "so_w_tg00", "" },
    { &data_ov008_02090248, "", "", "demyx_R" },
    { &data_ov008_02090244, "la_h_L", "la_h_R", "" },
    { &data_ov008_02090240, "", "le_h_R", "" },
    { &data_ov008_0209023c, "", "", "luxord_R" },
    { &data_ov008_02090238, "", "ma_h_R", "" },
    { &data_ov008_02090234, "", "ri_h_R", "" },
    { &data_ov008_02090230, "", "", "ve_w_tg" },
    { &data_ov008_0209022c, "xe_h_L", "xe_h_R", "" },
    { &data_ov008_02090228, "", "xo_h_R", "" },
    { &data_ov008_02090224, "", "", "zexion_R" },
    { &data_ov008_02090220, "", "mi_w_tg_R", "" },
    { &data_ov008_0209021c, "", "do_h_R", "" },
    { &data_ov008_02090218, "", "go_h_R", "" },
    { &data_ov008_02090214, "ro_h_L", "ro_h_R", "" },
};
