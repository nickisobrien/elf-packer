#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "section.h"
#include "elf.h"

static void
print_section_headers(section_header **hdrs)
{
	int i;

	printf("Section headers:\n");
	for (i = 0; hdrs[i]; i++)
	{
		printf("Sect: Type:%08x\n",
			hdrs[i]->sh_type);
	}
}

section_header **
get_section_headers(FILE *fp, uint16_t e_shnum)
{
	int i;
	section_header **hdrs = (section_header **)malloc(sizeof(section_header *) * e_shnum);

	for (i = 0; i < e_shnum; i++)
	{
		hdrs[i] = (section_header *)malloc(sizeof(section_header) + 1);
		if (fgets((char *)(hdrs[i]), sizeof(section_header) + 1, fp) == NULL)
			return NULL;
	}
	hdrs[i] = NULL;
	print_section_headers(hdrs);
	return hdrs;
}
