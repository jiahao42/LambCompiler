#ifndef SYMSEG_H_
#define SYMSEG_H_

/*
 * This is actually the format of GDB symbol table data.
 * According to the limit of this lexer, not every data in this symbol is used.
 */
 
enum language {language_c};

struct symbol_root
{
  int format;			/* Data format version */
  int length;			/* # bytes in this symbol segment */
  int ldsymoff;			/* Offset in ld symtab of this file's syms */
  int textrel;			/* Relocation for text addresses */
  int datarel;			/* Relocation for data addresses */
  int bssrel;			/* Relocation for bss addresses */
  char *filename;		/* Name of main source file compiled */
  char *filedir;		/* Name of directory it was reached from */
  struct blockvector *blockvector; /* Vector of all symbol-naming blocks */
  struct typevector *typevector; /* Vector of all data types */
  enum language language;	/* Code identifying the language used */
  char *version;		/* Version info.  Not fully specified */
  char *compilation;		/* Compilation info.  Not fully specified */
  int databeg;			/* Address within the file of data start */
  int bssbeg;			/* Address within the file of bss start */
  struct sourcevector *sourcevector; /* Vector of line-number info */
};




#endif /* end of SYMSEG_H_ */