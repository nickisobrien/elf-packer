#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "section.h"
#include "elf.h"

static void
print_section_headers(section_header **hdrs, uint16_t shnum)
{
	int i;

	printf("\nSection headers:\n");
	for (i = 0; i < shnum; i++)
	{
		printf("Sect: Type:%08x\n",
			hdrs[i]->sh_type);
	}
}

section_header **
get_section_headers(FILE *fp, uint16_t e_shnum)
{
	section_header **hdrs = (section_header **)malloc(sizeof(section_header *) * e_shnum);

	for (int i = 0; i < e_shnum; i++)
	{
		hdrs[i] = (section_header *)malloc(sizeof(section_header) + 1);
		for (size_t j = 0; j < sizeof(section_header); j++)
			((char *)(hdrs[i]))[j] = fgetc(fp);
	}
	print_section_headers(hdrs, e_shnum);
	return hdrs;
}
