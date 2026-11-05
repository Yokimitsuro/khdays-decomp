/* The record to show over the Preferences page's tabs next, cycled by the page's label timer: while
 * record 0 ("Adjust your settings.") is shown, the tab's title -- 1 (Player-Unique Settings) for
 * Mission Mode's first two tabs, 2 (Universal Settings) for the others -- and record 0 again after
 * it. The story's list (nList 0) has no tab titles and stays on record 0. */

int Ov008_Config_GetTabTitleRecord(int nList, unsigned nTab, int nShownRecord) {
    if (nList != 0 && nShownRecord == 0) {
        return nTab < 2 ? 1 : 2;
    }
    return 0;
}
