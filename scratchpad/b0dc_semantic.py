"""Semantic receipt for func_ov002_0205b0dc."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelRepaintListRow"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205b0dc. Repinta una fila de panel respaldada por "
     "lista, la contrapartida de Ov002_PanelRepaintRow que case en la vuelta "
     "anterior. Un nIndex negativo significa que no hay fila: el bloque de "
     "glifos cae a 0x3d0 y no se busca entrada. Si no, el bloque es "
     "nIndex*16 + 0x250 y la entrada sale de la lista por ordinal. El rebuild "
     "func_ov002_0205bff4 la llama TRES veces, sobre lists[0] y lists[2]."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad OCHO, confirmada en el desensamblado: r0 a r3 se leen antes de "
     "escribirse y los otros cuatro con ldr desde sp+0x28, sp+0x2c, sp+0x30 y "
     "sp+0x34, justo por encima de los 36 bytes del push mas los 4 del sub sp. "
     "Renombrados a pList, nIndex, nSlot, nEntry, nColumn, bEnabled, "
     "bRightAlign y bAlt. bAlt es un eje NUEVO respecto a la version de fila "
     "normal: alli la paleta era 0xf u 0xe segun bEnabled, y aqui bAlt elige "
     "ademas entre esa pareja y la pareja 0xc / 0x7."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Un unico hueco de pila y NO es una variable del programa: es el area del "
     "quinto argumento saliente de las dos llamadas de cinco argumentos, la "
     "escritura de etiqueta y el contador (str rX,[sp,#0] en 0x0205b16c y "
     "0x0205b208). Renombrado a aOutArgSlot y tipado int; read-back LOCALS 1. "
     "El resto vive en registros: r4 el puntero de sesion, r6 la entrada, r5 el "
     "bloque de glifos, r10 nIndex, r9 nSlot, r8 nColumn y r7 bRightAlign."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelRepaintListRow(NNSFndList *pList, int nIndex, int nSlot, "
     "int nEntry, int nColumn, int bEnabled, int bRightAlign, int bAlt). "
     "Retorno void: el epilogo restaura pc tras las dos marcas de entrada sin "
     "definir r0."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Extiende Ov002PanelEntry de 8 a 12 bytes y tipa dos tablas. La funcion "
     "lee del objeto de lista +0x00 con ldrh (nKey, que pasa al buscador de "
     "grupo), +0x02 con ldrh (nTag, que dibuja) y ademas +0x08 con ldr, un "
     "campo que ninguna funcion anterior habia tocado; anadido como "
     "nField0008 int. ANTES de extender se comprobo donde esta embebido el "
     "tipo, que es exactamente como rompi el struct de sesion en su dia: "
     "Ov002PanelSession solo lo embebe por PUNTERO, en pCachedEntry +0x4a4, y "
     "el unico array por valor, Ov002PanelEntry[551], es un huerfano sin "
     "padres. El read-back lo confirma: entrada 8 -> 12 y sesion todavia en "
     "1572. Ademas se tiparon las dos tablas de traduccion en 0x0207de50 y "
     "0x0207de60, que estaban sin tipo; el ROM las indexa con lsl #2 y "
     "symbols.txt las acota a dieciseis bytes cada una, asi que son int[4], "
     "igual que el par que usa la fila normal."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los ocho parametros con su "
     "almacenamiento, incluido pList como NNSFndList * y los cuatro de pila en "
     "Stack[0x0] a Stack[0xc]; aOutArgSlot int en Stack[-0x28]; "
     "Ov002PanelEntry len=12 con nKey +0x00, nTag +0x02, nState +0x04 y "
     "nField0008 +0x08; Ov002PanelSession en 1572 bytes con nState int en "
     "+0x10 y pCachedEntry Ov002PanelEntry * en +0x4a4; y las dos tablas como "
     "int[4]. El read-back final se hizo con un script de SOLO LECTURA, porque "
     "el primero renombraba el local y por eso informaba CHANGED True al "
     "reejecutarlo."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los cuatro scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el que "
     "extiende el tipo y recrea el dato de las dos tablas."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back de SOLO LECTURA posterior informa CHANGED False, con "
     "ENTRY len=12 y SESSION len=1572."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista Ov002PanelEntry "
     "ni Ov002PanelSession con variantes en conflicto. Se extendio el tipo "
     "existente en vez de crear uno rival, y el unico contenedor por valor que "
     "cambia de tamano es un array huerfano que no usa nadie."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:120]))
print("failures:", fail)
