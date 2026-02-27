ENTRY(_start)

SECTIONS
{
	. = 2M;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* 읽기 전용 데이터. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* 읽기-쓰기 데이터 (초기화된 데이터) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* 읽기-쓰기 데이터 (초기화되지 않은 데이터) 및 스택 */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
