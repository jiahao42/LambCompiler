// LambLexer
// by James 2017/04/06

#ifndef LAMB_COMPILER_SYMBOL_TABLE_H_
#define LAMB_COMPILER_SYMBOL_TABLE_H_

#include "token.h"

/*
 * This is actually the format of GDB symbol table data.
 * According to the limit of this lexer, not every data in this symbol is used.
 * The unused data has been all commentted.
 */

struct type;
struct source;
struct field;
struct c_token;
// struct block;

enum language { language_c };

struct symbol_root {
    int format;                    /* Data format version */
    int length;                    /* # bytes in this symbol segment */
    std::string filename;          /* Name of main source file compiled */
    std::string filedir;           /* Name of directory it was reached from */
    std::vector<type> type_vector; /* Vector of all data types */
    // std::unordered_map<
    enum language language;            /* Code identifying the language used */
    std::string version;               /* Version info.  Not fully specified */
    std::vector<source> source_vector; /* Vector of source files */

    // int ldsymoff;						/* Offset in ld symtab of this file's syms
    // */  int textrel;						/* Relocation for text addresses */
    // int datarel;						/* Relocation for data addresses */
    // int bssrel;						/* Relocation for bss addresses */
    // std::vector<block> blockvector; 	/* Vector of all symbol-naming blocks */
    // std::string compilation;			/* Compilation info.  Not fully specified
    // */
    // int databeg;						/* Address within the file of data start
    // */
    // int bssbeg;						/* Address within the file of bss start
    // */
};

/* All data types of symbols in the compiled program
 * are represented by `struct type' objects.
 * All of these objects are pointed to by the typevector.
 * The type vector may have empty slots that contain zero.
 */

enum type_code {
    TYPE_CODE_UNDEF,  /* Not used; catches errors */
    TYPE_CODE_PTR,    /* Pointer type */
    TYPE_CODE_ARRAY,  /* Array type, lower bound zero */
    TYPE_CODE_STRUCT, /* C struct or Pascal record */
    TYPE_CODE_UNION,  /* C union or Pascal variant part */
    TYPE_CODE_ENUM,   /* Enumeration type */
    TYPE_CODE_FUNC,   /* Function type */
    TYPE_CODE_INT,    /* Integer type */
    TYPE_CODE_FLT,    /* Floating type */
    TYPE_CODE_VOID,   /* Void type (values zero length) */
    TYPE_CODE_RANGE,  /* Range (integers within spec'd bounds) */
                      // TYPE_CODE_SET,			/* Pascal sets */
    // TYPE_CODE_PASCAL_ARRAY,	/* Array with explicit type of index */
};

struct type {
    /*
     * Code for kind of type
     */
    enum type_code code;
    /*
     * Name of this type, or zero if none.
     * This is used for printing only.
     */
    std::string name;
    /*
     * Length in bytes of storage for a value of this type
     */
    int length;
    /*
     * For a pointer type, describes the type of object pointed to.
     * For an array type, describes the type of the elements.
     * For a function type, describes the type of the value.
     * Unused otherwise.
     */
    type *target_type;
    /*
     * Type that is a pointer to this type.
     * Zero if no such pointer-to type is known yet.
     */
    type *pointer_type;
    /*
     * Type that is a function returning this type.
     * Zero if no such function type is known here.
     */
    type *function_type;
    /*
     * Flags about this type.
     */
    short flags;
    /*
     * vector of fields described for this type
     */
    std::vector<field> field_vector;
};

/*
 * For structure and union types, a description of each field.
 * For range types, there are two "fields",
 * the minimum and maximum values (both inclusive).
 * For enum types, each possible value is described by one "field".
 * For range types, there are two "fields", that record constant values
 * (inclusive) for the minimum and maximum.
 *
 * Using a pointer to a separate array of fields
 * allows all types to have the same size, which is useful
 * because we can allocate the space for a type before
 * we know what to put in it.
 */
struct field {
    /*
     * Position of this field, counting in bits from start of
     * containing structure.  For a function type, this is the
     * position in the argument list of this argument.
     * For a range bound or enum value, this is the value itself.
     */
    int bitpos;
    /*
     * Size of this field, in bits, or zero if not packed.
     * For an unpacked field, the field's type's length
     * says how many bytes the field occupies.
     */
    int bitsize;
    /*
     * In a struct or enum type, type of this field.
     * In a function type, type of this argument.
     * In an array type, the domain-type of the array.
     */
    struct type *type;
    /*
     * Name of field, value or argument.
     * Zero for range bounds and array domains.
     */
    std::string name;
};

#if 0 
/* Not used yet, leave it for syntax analyze */

/* All of the name-scope contours of the program
 * are represented by `struct block' objects.
 * All of these objects are pointed to by the blockvector.
 *
 * Each block represents one name scope.
 * Each lexical context has its own block.
 *
 * The first two blocks in the blockvector are special.
 * The first one contains all the symbols defined in this compilation
 * whose scope is the entire program linked together.
 * The second one contains all the symbols whose scope is the
 * entire compilation excluding other separate compilations.
 * In C, these correspond to global symbols and static symbols.
 *
 * Each block records a range of core addresses for the code that
 * is in the scope of the block.  The first two special blocks
 * give, for the range of code, the entire range of code produced
 * by the compilation that the symbol segment belongs to.
 *
 * The blocks appear in the blockvector
 * in order of increasing starting-address,
 * and, within that, in order of decreasing ending-address.
 *
 * This implies that within the body of one function
 * the blocks appear in the order of a depth-first tree walk.  
 */

struct block
{
   /* Addresses in the executable code that are in this block.
    * Note: in an unrelocated symbol segment in a file,
    * these are always zero.  They can be filled in from the
    * N_LBRAC and N_RBRAC symbols in the loader symbol table.  
	*/
  int startaddr, endaddr;
   /* The symbol that names this block,
    * if the block is the body of a function;
    * otherwise, zero.
    * Note: In an unrelocated symbol segment in an object file,
    * this field may be zero even when the block has a name.
    * That is because the block is output before the name
    * (since the name resides in a higher block).
    * Since the symbol does point to the block (as its value),
    * it is possible to find the block and set its name properly.  
	*/
	struct variable *function;
   /* 
    * The `struct block' for the containing block, or 0 if none.  
	*/
   /* 
    * Note that in an unrelocated symbol segment in an object file
    * this pointer may be zero when the correct value should be
    * the second special block (for symbols whose scope is one compilation).
    * This is because the compiler ouptuts the special blocks at the
    * very end, after the other blocks.   
	*/
	struct block *superblock;
   /* 
	* The local symbols.  
	*/
	std::vector<variable> syms;
};

#endif /* end of block */

/* Represent one symbol name; a variable, constant, function or typedef.  */

/*
 * Different name spaces for symbols.  Looking up a symbol specifies
 * a namespace and ignores symbol definitions in other name spaces.
 *
 * VAR_NAMESPACE is the usual namespace.
 * In C, this contains variables, function names, typedef names
 * and enum type values.
 *
 * STRUCT_NAMESPACE is used in C to hold struct, union and enum type names.
 * Thus, if `struct foo' is used in a C program,
 * it produces a symbol named `foo' in the STRUCT_NAMESPACE.
 *
 * LABEL_NAMESPACE may be used for names of labels (for gotos);
 * currently it is not used and labels are not recorded at all.
 */

struct variable {
    /*
     * Variable name
     */
    std::string name;
    /*
     * Data type of value
     */
    type *var_type;
    /*
     * constant value, or address if static, or register number,
     * or offset in arguments, or offset in stack frame.
     */
    union {
        long value;
        struct block *block; /* for LOC_BLOCK */
        char *bytes;         /* for LOC_CONST_BYTES */
    } value;
};

/*
 * Source-file information.
 * This describes the relation between source files and line numbers
 * and addresses in the program text.
 */

/* Line number and address of one line.  */

typedef struct line {
    line() : linenum(0), address(0) {}
    size_t linenum;
    int address;
    std::string content;
    // post increment
    struct line &operator++(int) {
        linenum++;
        return *this;
    }
    inline void reset() { linenum = 0; }
    inline void set_content(std::string &_content) { content = _content; }
    inline size_t &get_linenum() { return linenum; }
} line;

/* All the information on one single source file.  */

struct source {
    std::string filename;    /* Name of file */
    std::vector<line> lines; /* Information of each line */
    std::vector<c_token> c_token_vector;
    /*
     * Simple wrap of push_back token
     */
    inline void push(c_token c) { c_token_vector.push_back(c); }
    inline c_ttype &get_token_type(size_t idx) {
        return c_token_vector[idx].type;
    }
    inline std::string &get_token_name(size_t idx) {
        return c_token_vector[idx].name;
    }
    inline size_t get_token_size() { return c_token_vector.size(); }
    inline void reset() {
        c_token_vector.clear();
        lines.clear();
    }
    inline void push_line(line &cur_line) { lines.push_back(cur_line); }
    inline std::string &get_line_content(size_t &idx) {
        size_t tmp = idx - 1;
        return lines[tmp].content;
    }
};

#endif /* end of LAMB_COMPILER_SYMBOL_TABLE_H_ */
