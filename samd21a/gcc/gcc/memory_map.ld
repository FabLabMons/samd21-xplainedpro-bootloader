/* Memory Spaces Definitions */
MEMORY
{
  bootrom  (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00004000
  rom      (rx)  : ORIGIN = 0x00004000, LENGTH = 0x0003C000
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

__bootrom_start__ = ORIGIN(bootrom);
__bootrom_size__ = LENGTH(bootrom);
__rom_start__ = ORIGIN(rom);
__rom_size__ = LENGTH(rom);