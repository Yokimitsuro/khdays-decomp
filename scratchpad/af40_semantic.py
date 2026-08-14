"""Semantic receipt for func_ov002_0205af40."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelFindGroupSlot"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205af40. Busca el indice del slot que sirve a un "
     "grupo y una clave, o -1. Recorre los cuatro registros de 16 bytes en "
     "+0x440 de la sesion; un slot solo cuenta si su nGroup coincide, y "
     "entonces el grupo 3 compara nKey contra el nKey literal del slot mientras "
     "el grupo 8 lo compara contra el primer byte detras de pKeyRef. Cualquier "
     "otro grupo no puede casar nunca, asi que responde -1. Su resultado es el "
     "indice de estilo que Ov002_PanelRepaintRow, casada en la vuelta anterior, "
     "usa para indexar sus dos tablas de traduccion."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad DOS, confirmada en el desensamblado: solo r0 y r1 se leen antes de "
     "escribirse. Renombrados a nGroup y nKey. El primero no es un indice sino "
     "un discriminador: se compara contra el campo del slot y ademas contra las "
     "constantes 3 y 8, que son los dos unicos grupos con semantica de clave."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es solo push {r4,lr} sin sub sp. El "
     "indice del bucle vive en r4, el puntero de sesion en lr y la direccion "
     "del slot en r12. Read-back LOCALS 0, asi que no hay nada que renombrar. "
     "El push existe justamente porque el indice necesita un registro "
     "callee-saved: la version sin marco, con el indice en un caller-saved, "
     "sale ocho bytes mas corta y no es la del ROM."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_PanelFindGroupSlot(int nGroup, int nKey). Devuelve el indice o "
     "-1: las dos salidas de exito hacen mov r0,r4 y la de fallo mvn r0,#0. El "
     "caller compara el resultado contra cero con cmp y ldrge, es decir lo trata "
     "como entero CON SIGNO, lo que confirma que -1 es un valor de retorno real "
     "y no un 0xffffffff sin signo."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "Layout nuevo. La region +0x440..+0x480 de Ov002PanelSession estaba SIN "
     "definir: el read-back previo no listaba ningun componente entre +0x430 y "
     "+0x480, y el primero era lists en +0x480. El ROM la recorre con "
     "add r12,lr,r4 lsl #4, es decir paso de DIECISEIS bytes, y con indice "
     "acotado por cmp r4,#4, es decir CUATRO entradas, lo que cubre exactamente "
     "los 64 bytes hasta lists. Creado Ov002PanelGroupSlot de 16 bytes con "
     "nGroup ushort en +0x00 (ldrh), pKeyRef uchar * en +0x04 (ldr seguido de "
     "ldrb) y nKey ushort en +0x0c (ldrh); el resto queda como relleno porque el "
     "ROM no lo toca. Aplicado como aGroups Ov002PanelGroupSlot[4] en +0x440, y "
     "el read-back confirma que la sesion sigue midiendo 1572 y que lists "
     "conserva su sitio en +0x480. Se comprobo antes de crear si servia un tipo "
     "existente: Ov002DisplaySlot tambien mide 16 bytes y sus offsets no "
     "contradicen a estos, pero es un HUERFANO, sin padres y sin aplicar en "
     "ningun dato ni variable del programa, y su unico campo comun estaria en "
     "+0x0c, asi que no describe esta tabla y extenderlo habria sido inventar."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los dos parametros int en r0 y r1, "
     "Ov002PanelGroupSlot len=16 con sus tres campos con nombre, el campo "
     "aGroups Ov002PanelGroupSlot[4] de 64 bytes en +0x440 y lists intacto en "
     "+0x480 con la sesion en 1572 bytes, y el pool slot "
     "arm9_ov002.bss::0207f620 como Ov002PanelSession *. Ademas se re-decompilo "
     "tras aplicar: ahora lee pOVar2->aGroups[iVar1].nGroup, .nKey y .pKeyRef, "
     "asi que el tipo esta en uso y no ha roto el decompilador."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los cuatro scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el que "
     "crea el tipo y hace replaceAtOffset sobre 64 bytes."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista "
     "Ov002PanelGroupSlot ni Ov002PanelSession con variantes en conflicto. El "
     "tipo nuevo ocupa una region que estaba sin definir, asi que no desplaza "
     "ni sombrea ningun campo existente."),
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
