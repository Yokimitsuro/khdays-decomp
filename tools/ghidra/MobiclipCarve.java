// Import and classify the standalone ov024 MobiClip payload from its generated
// inventory. Intended for analyzeHeadless on an isolated raw-binary program.

import java.io.FileReader;
import java.math.BigInteger;
import java.util.LinkedHashSet;
import java.util.Set;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.ByteDataType;
import ghidra.program.model.data.DWordDataType;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.symbol.SourceType;

public class MobiclipCarve extends GhidraScript {
    private static long parseAddress(JsonElement value) {
        return Long.decode(value.getAsString());
    }

    private Address address(long value) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(value);
    }

    private void collectTableTargets(JsonArray tables, Set<Long> seeds) {
        if (tables == null)
            return;
        for (JsonElement tableElement : tables) {
            JsonObject table = tableElement.getAsJsonObject();
            JsonArray entries = table.getAsJsonArray("entries");
            if (entries == null)
                continue;
            for (JsonElement entryElement : entries) {
                JsonObject entry = entryElement.getAsJsonObject();
                if (entry.has("target") && !entry.get("target").isJsonNull())
                    seeds.add(parseAddress(entry.get("target")));
            }
        }
    }

    private void collectAddresses(JsonArray values, Set<Long> seeds) {
        if (values == null)
            return;
        for (JsonElement value : values)
            seeds.add(parseAddress(value));
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1)
            throw new IllegalArgumentException("expected mobiclip_inventory.json path");
        JsonObject inventory;
        try (FileReader reader = new FileReader(args[0])) {
            inventory = JsonParser.parseReader(reader).getAsJsonObject();
        }

        long base = parseAddress(inventory.get("payload_base"));
        long end = base + inventory.get("payload_size").getAsLong() - 1;
        Register tMode = currentProgram.getProgramContext().getRegister("TMode");
        if (tMode != null && getInstructionAt(address(base)) == null)
            currentProgram.getProgramContext().setValue(
                tMode, address(base), address(end), BigInteger.ZERO);

        createLabel(address(base), "MobiClip_PayloadStart", true,
                    SourceType.USER_DEFINED);
        setPlateComment(address(base),
            "Position-independent ARMv5TE payload copied from ov024 to ITCM at runtime.");

        JsonArray dataRegions = inventory.getAsJsonArray("embedded_data_regions");
        for (JsonElement element : dataRegions) {
            JsonObject region = element.getAsJsonObject();
            long start = parseAddress(region.get("start"));
            int size = region.get("size").getAsInt();
            Address at = address(start);
            clearListing(at, address(start + size - 1));
            if ((size & 3) == 0) {
                createData(at, new ArrayDataType(DWordDataType.dataType,
                                                 size / 4, 4));
            }
            else {
                createData(at, new ArrayDataType(ByteDataType.dataType,
                                                 size, 1));
            }
            createLabel(at, "MobiClip_Data_" + region.get("name").getAsString(),
                        true, SourceType.USER_DEFINED);
            setPlateComment(at, "Embedded payload DATA; size 0x" +
                                  Integer.toHexString(size) + ".");
        }

        JsonArray ranges = inventory.getAsJsonArray("ranges");
        for (JsonElement element : ranges) {
            JsonObject range = element.getAsJsonObject();
            if (!"arm_code".equals(range.get("classification").getAsString()))
                continue;
            long start = parseAddress(range.get("start"));
            long rangeEnd = parseAddress(range.get("end"));
            for (long cursor = start; cursor < rangeEnd; cursor += 4)
                disassemble(address(cursor));
        }

        Set<Long> seeds = new LinkedHashSet<>();
        seeds.add(base);
        collectAddresses(inventory.getAsJsonArray("validated_entries"), seeds);
        collectAddresses(inventory.getAsJsonArray("computed_continuations"), seeds);
        collectTableTargets(inventory.getAsJsonArray("relative_tables"), seeds);
        collectTableTargets(inventory.getAsJsonArray("signed_relative_tables"), seeds);
        collectTableTargets(inventory.getAsJsonArray("inferred_relative_tables"), seeds);

        for (long seed : seeds) {
            Address at = address(seed);
            if (getInstructionAt(at) == null)
                continue;
            String name = String.format("MobiClip_Sub_%08x", seed);
            if (seed == 0x0208dfb4L)
                name = "MobiClip_DecodeFrameCore";
            else if (seed == 0x0208e8f8L)
                name = "MobiClip_ReadUnsignedExpGolomb";
            else if (seed == 0x02090860L)
                name = "MobiClip_DecodeRunLevelCoefficients";
            else if (seed == 0x0208e8a8L)
                name = "MobiClip_AddCoefficients4x4";
            else if (seed == 0x0208e6f0L)
                name = "MobiClip_AddPFrameBlockCoefficients";
            if (getFunctionAt(at) == null)
                createFunction(at, name);
            else
                getFunctionAt(at).setName(name, SourceType.USER_DEFINED);
        }

        analyzeAll(currentProgram);
        println("MobiClip carve complete: 0x" + Long.toHexString(base) +
                "..0x" + Long.toHexString(end) + ", " + seeds.size() +
                " explicit function seeds, " + dataRegions.size() +
                " DATA regions.");
    }
}
