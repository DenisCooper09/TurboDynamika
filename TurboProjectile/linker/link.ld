MEMORY
{
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 512k
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128k
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .rovectors : { KEEP(*(.rovectors)) } > flash
    .text      : { *(.text*)           } > flash
    .rodata    : { *(.rodata*)         } > flash
    
    .data :
    {
        _sdata = .;
        *(.first_data)
        *(.data SORT(.data.*))
        _edata = .;
    } > flash AT > SRAM
    
    _sidata = LOADADDR(.data);
    
    .vectors (NOLOAD) : ALIGN(128)
    {
        _svectors = .;
        . = . + 408;
        _evectors = .;
    } > SRAM
    
    .bss :
    {
        _sbss = .;
        *(.bss SORT(.bss.*) COMMON)
        _ebss = .;
    } > SRAM
}
