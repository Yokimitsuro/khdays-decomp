// Read-only integrity check for the standalone MobiClip Ghidra program.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

public class MobiclipAudit extends GhidraScript {
    @Override
    public void run() throws Exception {
        long instructionCount = 0;
        long instructionBytes = 0;
        long dataBytes = 0;
        long functionCount = 0;

        for (Instruction instruction : currentProgram.getListing().getInstructions(true)) {
            ++instructionCount;
            instructionBytes += instruction.getLength();
        }
        for (Data data : currentProgram.getListing().getDefinedData(true))
            dataBytes += data.getLength();
        for (Function ignored : currentProgram.getFunctionManager().getFunctions(true))
            ++functionCount;

        println("language=" + currentProgram.getLanguageID());
        println("imageBase=" + currentProgram.getImageBase());
        println("memoryMin=" + currentProgram.getMemory().getMinAddress());
        println("memoryMax=" + currentProgram.getMemory().getMaxAddress());
        println("instructions=" + instructionCount);
        println("instructionBytes=" + instructionBytes);
        println("dataBytes=" + dataBytes);
        println("functions=" + functionCount);
        String[] names = {
            "MobiClip_DecodeFrameCore",
            "MobiClip_ReadUnsignedExpGolomb",
            "MobiClip_DecodeRunLevelCoefficients",
            "MobiClip_AddCoefficients4x4",
            "MobiClip_AddPFrameBlockCoefficients",
        };
        for (String name : names) {
            if (getGlobalFunctions(name).isEmpty())
                throw new IllegalStateException("missing function " + name);
        }
        if (!"0208c8c4".equals(currentProgram.getMemory().getMinAddress().toString()) ||
            !"02092e5f".equals(currentProgram.getMemory().getMaxAddress().toString()) ||
            instructionCount != 5899 || instructionBytes != 23596 ||
            dataBytes != 2416)
            throw new IllegalStateException("saved program does not match inventory totals");
        println("mobiclipAudit=PASS");
    }
}
