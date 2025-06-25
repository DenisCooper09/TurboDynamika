MEMORY
{
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 512k
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128k
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .vectors : { KEEP(*(.vectors)) } > flash
    .text    : { *(.text*)         } > flash
    .rodata  : { *(.rodata*)       } > flash
    
    .data :
    {
        _sdata = .;
        *(.first_data)
        *(.data SORT(.data.*))
        _edata = .;
    }
    
    _sidata = LOADADDR(.data);
    
    .bss :
    {
        _sbss = .;
        *(.bss SORT(.bss.*) COMMON)
        _ebss = .;
    }
}
