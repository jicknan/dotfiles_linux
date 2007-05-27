/*
 * loader.c - ELF programing
 * http://tw.jollen.org/elf-programming/
 *
 * Created at:  Sat 10 Mar 2007 03:55:41 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int elf_ident(char *ident)
{
	if (*(ident+EI_MAG0) != EI_MAG0) return 0;
	if (*(ident+EI_MAG1) != EI_MAG1) return 0;
	if (*(ident+EI_MAG2) != EI_MAG2) return 0;
	if (*(ident+EI_MAG3) != EI_MAG3) return 0;

	return -1;
}

void parse_ident(char *ident)
{
	printf("ELF Identification\n");

	printf("  Class: ");
	switch(*(ident+EI_CLASS)) {
		case ELFCLASSNONE: printf("Invalid class\n"); break;
		case ELFCLASS32: printf("32-bit objects\n"); break;
		case ELFCLASS64: printf("64-bit objects\n"); break;
	}

	printf("  Data: ");
	switch(*(ident+EI_DATA)) {
		case ELFDATANONE: printf("Invalid data encoding\n"); break;
		case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
		case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
	}

	printf("  OS ABI: ");
	switch(*(ident+EI_OSABI)) {
		case ELFOSABI_SYSV: printf("Unix System V ABI\n"); break;
		case ELFOSABI_HPUX: printf("HP-UX\n"); break;
		case ELFOSABI_NETBSD: printf("NetBSD\n"); break;
		case ELFOSABI_LINUX: printf("Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("Sun Solaris\n"); break;
		case ELFOSABI_AIX: printf("IBM AIX\n"); break;
		case ELFOSABI_IRIX: printf("SCI Irix\n"); break;
		case ELFOSABI_FREEBSD: printf("FreeBSD\n"); break;
		case ELFOSABI_OPENBSD: printf("OpenBSD\n"); break;
		case ELFOSABI_ARM: printf("ARM\n"); break;
		case ELFOSABI_STANDALONE: printf("Standalone (embedded) application\n"); break;
	}
}

void parse_type(Elf32_Half type)
{
	printf("Type: ");
	switch(type) {
		case ET_NONE: printf("No file type\n"); break;
		case ET_REL: printf("Relocatable file\n"); break;
		case ET_EXEC: printf("Executable file\n"); break;
		case ET_DYN: printf("Shared object file\n"); break;
		case ET_CORE: printf("Core file\n"); break;
		case ET_NUM: printf("Number of defined types\n"); break;
		default: printf("Unknow\n");
	}
}

void parse_machine(Elf32_Half machine)
{
	printf("Machine: ");
	switch(machine) {
		case EM_NONE: printf("No michine\n"); break;
		case EM_M32: printf("AT&T WE 32100\n"); break;
		case EM_SPARC: printf("SUN SPARC\n"); break;
		case EM_386: printf("Intel 80386\n"); break;
		case EM_68K: printf("Motorola m68k family\n"); break;
		case EM_88K: printf("Motorola m88k family\n"); break;
		case EM_860: printf("Intel 80860\n"); break;
		case EM_MIPS: printf("MIPS RS3000 big-endian\n"); break;
		case EM_S370: printf("IBM System/370\n"); break;
		case EM_MIPS_RS3_LE: printf("MIPS R3000 little-endian\n"); break;
		case EM_960: printf("Intel 80960\n"); break;
		case EM_PPC: printf("PowerPC\n"); break;
		case EM_PPC64: printf("PowerPC 64-bit\n"); break;
		case EM_S390: printf("IBM S390\n"); break;
		case EM_ARM: printf("ARM\n"); break;
		case EM_SH: printf("Hitachi SH\n"); break;
		case EM_IA_64: printf("Intel Merced\n"); break;
		default: printf("Unknow\n");
	}
}

void parse_sections(Elf32_Ehdr *hdr, int fd)
{
	int i;
	Elf32_Shdr header_ent[40];
	Elf32_Shdr *sh_strtab; /* point to section name string table header */
	char strtab[65525]; /* point to section name string table */

	/* file offset of section header_ent table */
	lseek(fd, hdr->e_shoff, SEEK_SET);

	for (i = 0; i <= hdr->e_shnum; i++) {
		read(fd, &header_ent[i], sizeof(Elf32_Shdr));

		if (i == hdr->e_shstrndx) {
			sh_strtab = &header_ent[i];
		}
	}

	/* Read "String Table" */
	lseek(fd, sh_strtab->sh_offset, SEEK_SET);
	read(fd, strtab, sh_strtab->sh_size);

	printf("Idx      Name             Size  Offset\n");
	/* Index 0: undefined */
	for (i = 1; i < hdr->e_shnum; i++) {
		printf("[%02d] %-16s%8d%8d\n", i, &strtab[header_ent[i].sh_name], 
				header_ent[i].sh_size, header_ent[i].sh_offset);
	}
}

int main(int argc, char *argv[])
{
	int fd;
	Elf32_Ehdr f_header;

	if (argc != 2) {
		printf("Usage: loader [filename]\n");
		return -1;
	}

	fd = open(argv[1], S_IRUSR);
	if ( fd < 0) {
		printf("open file faild.\n");
		return -1;
	}

	printf("sizeof Elf32_Ehdr: %d\n", sizeof(Elf32_Ehdr));
	/* Read ELF header */
	read(fd, &f_header, sizeof(Elf32_Ehdr));

	/* Parse header information */
	if (elf_ident(f_header.e_ident)) {
		printf("Not a ELF file.\n");
		return -1;
	}
	parse_ident(f_header.e_ident);
	parse_type(f_header.e_type);
	parse_machine(f_header.e_machine);
	parse_sections(&f_header, fd);

	close(fd);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

