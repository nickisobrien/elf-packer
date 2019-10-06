#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "program.h"
#include "elf.h"

static void
print_program_headers(program_header **hdrs, uint16_t phnum)
{
	int i;

	printf("\nProgram headers:\n");
	for (i = 0; i < phnum; i++)
	{
		printf("Type:%#08x, "
				"Offset:%#08lx, "
				"Filesz:%#08lx, "
				"Memsz:%#08lx, "
				"Align:%#08lx, "
				"Paddr:%#08lx, "
				"Vaddr:%#08lx, "
				"Flags:%#08x\n",
				hdrs[i]->p_type,
				hdrs[i]->p_offset,
				hdrs[i]->p_filesz,
				hdrs[i]->p_memsz,
				hdrs[i]->p_align,
				hdrs[i]->p_paddr,
				hdrs[i]->p_vaddr,
				hdrs[i]->p_flags);
	}
}

program_header **
get_program_headers(FILE *fp, uint16_t e_phnum)
{
	program_header **hdrs = (program_header **)malloc(sizeof(program_header *) * e_phnum);

	for (int i = 0; i < e_phnum; i++)
	{
		hdrs[i] = (program_header *)malloc(sizeof(program_header) + 1);
		for (size_t j = 0; j < sizeof(program_header); j++)
			((char *)(hdrs[i]))[j] = fgetc(fp);
	}
	print_program_headers(hdrs, e_phnum);
	return hdrs;
}
