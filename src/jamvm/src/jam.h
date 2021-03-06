/*
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Robert Lougher <rob@jamvm.org.uk>.
 *
 * This file is part of JamVM.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <inttypes.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

/* Configure options */
#include "config.h"

/* Architecture dependent definitions */
#include "arch.h"

#ifndef TRUE
#define         TRUE    1
#define         FALSE   0
#endif

/* These should go in the interpreter file */

#define OPC_NOP                         0
#define OPC_ACONST_NULL                 1
#define OPC_ICONST_M1                   2
#define OPC_ICONST_0                    3
#define OPC_ICONST_1                    4
#define OPC_ICONST_2                    5
#define OPC_ICONST_3                    6
#define OPC_ICONST_4                    7
#define OPC_ICONST_5                    8
#define OPC_LCONST_0                    9
#define OPC_LCONST_1                    10
#define OPC_FCONST_0                    11
#define OPC_FCONST_1                    12
#define OPC_FCONST_2                    13
#define OPC_DCONST_0                    14
#define OPC_DCONST_1                    15
#define OPC_BIPUSH                      16
#define OPC_SIPUSH                      17
#define OPC_LDC                         18
#define OPC_LDC_W                       19
#define OPC_LDC2_W                      20
#define OPC_ILOAD                       21
#define OPC_LLOAD                       22
#define OPC_FLOAD                       23
#define OPC_DLOAD                       24
#define OPC_ALOAD                       25
#define OPC_ILOAD_0                     26
#define OPC_ILOAD_1                     27
#define OPC_ILOAD_2                     28
#define OPC_ILOAD_3                     29
#define OPC_LLOAD_0                     30
#define OPC_LLOAD_1                     31
#define OPC_LLOAD_2                     32
#define OPC_LLOAD_3                     33
#define OPC_FLOAD_0                     34
#define OPC_FLOAD_1                     35
#define OPC_FLOAD_2                     36
#define OPC_FLOAD_3                     37
#define OPC_DLOAD_0                     38
#define OPC_DLOAD_1                     39
#define OPC_DLOAD_2                     40
#define OPC_DLOAD_3                     41
#define OPC_ALOAD_0                     42
#define OPC_ALOAD_1                     43
#define OPC_ALOAD_2                     44
#define OPC_ALOAD_3                     45
#define OPC_IALOAD                      46
#define OPC_LALOAD                      47
#define OPC_FALOAD                      48
#define OPC_DALOAD                      49
#define OPC_AALOAD                      50
#define OPC_BALOAD                      51
#define OPC_CALOAD                      52
#define OPC_SALOAD                      53
#define OPC_ISTORE                      54
#define OPC_LSTORE                      55
#define OPC_FSTORE                      56
#define OPC_DSTORE                      57
#define OPC_ASTORE                      58
#define OPC_ISTORE_0                    59
#define OPC_ISTORE_1                    60
#define OPC_ISTORE_2                    61
#define OPC_ISTORE_3                    62
#define OPC_LSTORE_0                    63
#define OPC_LSTORE_1                    64
#define OPC_LSTORE_2                    65
#define OPC_LSTORE_3                    66
#define OPC_FSTORE_0                    67
#define OPC_FSTORE_1                    68
#define OPC_FSTORE_2                    69
#define OPC_FSTORE_3                    70
#define OPC_DSTORE_0                    71
#define OPC_DSTORE_1                    72
#define OPC_DSTORE_2                    73
#define OPC_DSTORE_3                    74
#define OPC_ASTORE_0                    75
#define OPC_ASTORE_1                    76
#define OPC_ASTORE_2                    77
#define OPC_ASTORE_3                    78
#define OPC_IASTORE                     79
#define OPC_LASTORE                     80
#define OPC_FASTORE                     81
#define OPC_DASTORE                     82
#define OPC_AASTORE                     83
#define OPC_BASTORE                     84
#define OPC_CASTORE                     85
#define OPC_SASTORE                     86
#define OPC_POP                         87
#define OPC_POP2                        88
#define OPC_DUP                         89
#define OPC_DUP_X1                      90
#define OPC_DUP_X2                      91
#define OPC_DUP2                        92
#define OPC_DUP2_X1                     93
#define OPC_DUP2_X2                     94
#define OPC_SWAP                        95
#define OPC_IADD                        96
#define OPC_LADD                        97
#define OPC_FADD                        98
#define OPC_DADD                        99
#define OPC_ISUB                        100
#define OPC_LSUB                        101
#define OPC_FSUB                        102
#define OPC_DSUB                        103
#define OPC_IMUL                        104
#define OPC_LMUL                        105
#define OPC_FMUL                        106
#define OPC_DMUL                        107
#define OPC_IDIV                        108
#define OPC_LDIV                        109
#define OPC_FDIV                        110
#define OPC_DDIV                        111
#define OPC_IREM                        112
#define OPC_LREM                        113
#define OPC_FREM                        114
#define OPC_DREM                        115
#define OPC_INEG                        116
#define OPC_LNEG                        117
#define OPC_FNEG                        118
#define OPC_DNEG                        119
#define OPC_ISHL                        120
#define OPC_LSHL                        121
#define OPC_ISHR                        122
#define OPC_LSHR                        123
#define OPC_IUSHR                       124
#define OPC_LUSHR                       125
#define OPC_IAND                        126
#define OPC_LAND                        127
#define OPC_IOR                         128     
#define OPC_LOR                         129     
#define OPC_IXOR                        130     
#define OPC_LXOR                        131     
#define OPC_IINC                        132
#define OPC_I2L                         133
#define OPC_I2F                         134
#define OPC_I2D                         135
#define OPC_L2I                         136
#define OPC_L2F                         137
#define OPC_L2D                         138
#define OPC_F2I                         139
#define OPC_F2L                         140
#define OPC_F2D                         141
#define OPC_D2I                         142
#define OPC_D2L                         143
#define OPC_D2F                         144
#define OPC_I2B                         145
#define OPC_I2C                         146
#define OPC_I2S                         147
#define OPC_LCMP                        148
#define OPC_FCMPL                       149
#define OPC_FCMPG                       150
#define OPC_DCMPL                       151
#define OPC_DCMPG                       152
#define OPC_IFEQ                        153
#define OPC_IFNE                        154
#define OPC_IFLT                        155
#define OPC_IFGE                        156
#define OPC_IFGT                        157
#define OPC_IFLE                        158
#define OPC_IF_ICMPEQ                   159
#define OPC_IF_ICMPNE                   160
#define OPC_IF_ICMPLT                   161
#define OPC_IF_ICMPGE                   162
#define OPC_IF_ICMPGT                   163
#define OPC_IF_ICMPLE                   164
#define OPC_IF_ACMPEQ                   165
#define OPC_IF_ACMPNE                   166
#define OPC_GOTO                        167
#define OPC_JSR                         168
#define OPC_RET                         169
#define OPC_TABLESWITCH                 170
#define OPC_LOOKUPSWITCH                171
#define OPC_IRETURN                     172
#define OPC_LRETURN                     173
#define OPC_FRETURN                     174
#define OPC_DRETURN                     175
#define OPC_ARETURN                     176
#define OPC_RETURN                      177
#define OPC_GETSTATIC                   178
#define OPC_PUTSTATIC                   179
#define OPC_GETFIELD                    180
#define OPC_PUTFIELD                    181
#define OPC_INVOKEVIRTUAL               182
#define OPC_INVOKESPECIAL               183
#define OPC_INVOKESTATIC                184
#define OPC_INVOKEINTERFACE             185
#define OPC_NEW                         187
#define OPC_NEWARRAY                    188
#define OPC_ANEWARRAY                   189
#define OPC_ARRAYLENGTH                 190
#define OPC_ATHROW                      191
#define OPC_CHECKCAST                   192
#define OPC_INSTANCEOF                  193
#define OPC_MONITORENTER                194
#define OPC_MONITOREXIT                 195
#define OPC_WIDE                        196
#define OPC_MULTIANEWARRAY              197
#define OPC_IFNULL                      198
#define OPC_IFNONNULL                   199
#define OPC_GOTO_W                      200
#define OPC_JSR_W                       201
#define OPC_LDC_QUICK                   203
#define OPC_LDC_W_QUICK                 204
#define OPC_GETFIELD_QUICK              206
#define OPC_PUTFIELD_QUICK              207
#define OPC_GETFIELD2_QUICK             208
#define OPC_PUTFIELD2_QUICK             209
#define OPC_GETSTATIC_QUICK             210
#define OPC_PUTSTATIC_QUICK             211
#define OPC_GETSTATIC2_QUICK            212
#define OPC_PUTSTATIC2_QUICK            213
#define OPC_INVOKEVIRTUAL_QUICK         214
#define OPC_INVOKENONVIRTUAL_QUICK      215
#define OPC_INVOKESUPER_QUICK           216
#define OPC_GETFIELD_QUICK_REF          217
#define OPC_PUTFIELD_QUICK_REF          218
#define OPC_GETSTATIC_QUICK_REF         219
#define OPC_PUTSTATIC_QUICK_REF         220
#define OPC_GETFIELD_THIS_REF           221
#define OPC_INVOKEVIRTUAL_QUICK_W       226
#define OPC_GETFIELD_QUICK_W            227
#define OPC_PUTFIELD_QUICK_W            228
#define OPC_GETFIELD_THIS               229
#define OPC_LOCK                        230
#define OPC_ALOAD_THIS                  231
#define OPC_INVOKESTATIC_QUICK          232
#define OPC_NEW_QUICK                   233
#define OPC_ANEWARRAY_QUICK             235
#define OPC_CHECKCAST_QUICK             238
#define OPC_INSTANCEOF_QUICK            239
#define OPC_MULTIANEWARRAY_QUICK        243
#define OPC_INVOKEINTERFACE_QUICK       244
#define OPC_ABSTRACT_METHOD_ERROR       245
#define OPC_INLINE_REWRITER             246
#define OPC_PROFILE_REWRITER            247

#define CONSTANT_Utf8                   1
#define CONSTANT_Integer                3
#define CONSTANT_Float                  4
#define CONSTANT_Long                   5
#define CONSTANT_Double                 6
#define CONSTANT_Class                  7
#define CONSTANT_String                 8
#define CONSTANT_Fieldref               9
#define CONSTANT_Methodref              10
#define CONSTANT_InterfaceMethodref     11
#define CONSTANT_NameAndType            12

#define CONSTANT_Resolved               20
#define CONSTANT_ResolvedClass          25
#define CONSTANT_ResolvedString         26
#define CONSTANT_Locked                 21

#define ACC_PUBLIC              0x0001
#define ACC_PRIVATE             0x0002
#define ACC_PROTECTED           0x0004
#define ACC_STATIC              0x0008
#define ACC_FINAL               0x0010
#define ACC_SYNCHRONIZED        0x0020
#define ACC_SUPER               0x0020
#define ACC_VOLATILE            0x0040
#define ACC_TRANSIENT           0x0080
#define ACC_NATIVE              0x0100
#define ACC_INTERFACE           0x0200
#define ACC_ABSTRACT            0x0400
#define ACC_SYNTHETIC           0x1000
#define ACC_ANNOTATION          0x2000
#define ACC_ENUM                0x4000
#define ACC_MIRANDA             0x0800

#define T_BOOLEAN               4
#define T_CHAR                  5       
#define T_FLOAT                 6
#define T_DOUBLE                7
#define T_BYTE                  8
#define T_SHORT                 9
#define T_INT                  10
#define T_LONG                 11

/* Class states */

#define CLASS_LOADED            1
#define CLASS_LINKED            2
#define CLASS_BAD               3
#define CLASS_INITING           4
#define CLASS_INITED            5

#define CLASS_ARRAY             6
#define CLASS_PRIM              7

/* Internal primitive type numbers */

#define PRIM_IDX_VOID           0
#define PRIM_IDX_BOOLEAN        1
#define PRIM_IDX_BYTE           2
#define PRIM_IDX_CHAR           3
#define PRIM_IDX_SHORT          4
#define PRIM_IDX_INT            5
#define PRIM_IDX_FLOAT          6
#define PRIM_IDX_LONG           7
#define PRIM_IDX_DOUBLE         8

/* Class flags */

#define CLASS_CLASS             1
#define REFERENCE               2
#define SOFT_REFERENCE          4
#define WEAK_REFERENCE          8
#define PHANTOM_REFERENCE      16
#define FINALIZED              32 
#define CLASS_LOADER           64 
#define CLASS_CLASH           128
#define VMTHROWABLE           256 
#define ANONYMOUS             512
#define VMTHREAD             1024

typedef unsigned char           u1;
typedef unsigned short          u2;
typedef unsigned int            u4;
typedef unsigned long long      u8;

typedef uintptr_t ConstantPoolEntry;

typedef struct constant_pool {
    volatile u1 *type;
    ConstantPoolEntry *info;
} ConstantPool;

typedef struct exception_table_entry {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} ExceptionTableEntry;

typedef struct line_no_table_entry {
    u2 start_pc;
    u2 line_no;
} LineNoTableEntry;

typedef struct object Object;
typedef Object Class;
typedef Class* pClass;
typedef Object* pObject;

struct object {
   uintptr_t lock;
   pClass class;
};

#ifdef DIRECT
typedef union ins_operand {
    uintptr_t u;
    int i;
    struct {
        signed short i1;
        signed short i2;
    } ii;
    struct {
        unsigned short u1;
        unsigned short u2;
    } uu;
    struct {
        unsigned short u1;
        unsigned char u2;
        char i;
    } uui;
    void *pntr;
} Operand;

typedef struct instruction {
#ifdef DIRECT_DEBUG
    unsigned char opcode;
    char cache_depth;
    short bytecode_pc;
#endif
    const void *handler;
    Operand operand;
} Instruction;

typedef struct switch_table {
    int low;
    int high;
    Instruction *deflt;
    Instruction **entries;
} SwitchTable;

typedef struct lookup_entry {
    int key;
    Instruction *handler;
} LookupEntry;

typedef struct lookup_table {
    int num_entries;
    Instruction *deflt;
    LookupEntry *entries;
} LookupTable;

#ifdef INLINING
typedef struct opcode_info {
    unsigned char opcode;
    unsigned char cache_depth;
} OpcodeInfo;

typedef struct profile_info ProfileInfo;

typedef struct basic_block {
    union {
        struct {
            int quickened;
            ProfileInfo *profiled;
        } profile;
        struct {
            char *addr;
            struct basic_block *next;
        } patch;
    } u;
    int length;
    Instruction *start;
    OpcodeInfo *opcodes;
    struct basic_block *prev;
    struct basic_block *next;
} BasicBlock;

typedef struct quick_prepare_info {
    BasicBlock *block;
    Instruction *quickened;
    struct quick_prepare_info *next;
} QuickPrepareInfo;

typedef struct prepare_info {
    BasicBlock *block;
    Operand operand;
} PrepareInfo;

struct profile_info {
    BasicBlock *block;
    int profile_count;
    const void *handler;
    struct profile_info *next;
    struct profile_info *prev;
};
#endif

typedef Instruction *CodePntr;
#else
typedef unsigned char *CodePntr;
#endif

typedef struct annotation_data {
   u1 *data;
   int len;
} AnnotationData;

typedef struct method_annotation_data {
    AnnotationData *annotations;
    AnnotationData *parameters;
    AnnotationData *dft_val;
} MethodAnnotationData;

typedef struct methodblock MethodBlock;
typedef MethodBlock* pMethodBlock;

typedef uintptr_t *(*NativeMethod)(pClass, struct methodblock*, uintptr_t*);

struct methodblock {
   pClass class;
   char *name;
   char *type;
   char *signature;
   u2 access_flags;
   u2 max_stack;
   u2 max_locals;
   u2 args_count;
   u2 throw_table_size;
   u2 exception_table_size;
   u2 line_no_table_size;
   int native_extra_arg;
   NativeMethod native_invoker;
   void *code;
   int code_size;
   u2 *throw_table;
   ExceptionTableEntry *exception_table;
   LineNoTableEntry *line_no_table;
   int method_table_index;
   MethodAnnotationData *annotations;
#ifdef INLINING
   QuickPrepareInfo *quick_prepare_info;
   ProfileInfo *profile_info;
#endif
};

typedef struct fieldblock {
   pClass class;
   char *name;
   char *type;
   char *signature;
   u2 access_flags;
   u2 constant;
   AnnotationData *annotations;
   union {
       union {
           char data[8];
           uintptr_t u;
           long long l;
           void *p;
           int i;
       } static_value; 
       u4 offset;
   } u;
} FieldBlock;
typedef FieldBlock* pFieldBlock;

typedef struct itable_entry {
   pClass interface;
   int *offsets;
} ITableEntry;

typedef struct refs_offsets_entry {
    int start;
    int end;
} RefsOffsetsEntry;

#define CLASS_PAD_SIZE 4

typedef struct classblock {
   uintptr_t pad[CLASS_PAD_SIZE];
   char *name;
   char *signature;
   char *super_name;
   char *source_file_name;
   pClass super;
   u1 state;
   u2 flags;
   u2 access_flags;
   u2 interfaces_count;
   u2 fields_count;
   u2 methods_count;
   u2 constant_pool_count;
   int object_size;
   pFieldBlock fields;
   pMethodBlock methods;
   pClass *interfaces;
   ConstantPool constant_pool;
   int method_table_size;
   pMethodBlock *method_table;
   int imethod_table_size;
   ITableEntry *imethod_table;
   pClass element_class;
   int initing_tid;
   int dim;
   pObject class_loader;
   u2 declaring_class;
   u2 inner_access_flags;
   u2 inner_class_count;
   u2 *inner_classes;
   int refs_offsets_size;
   RefsOffsetsEntry *refs_offsets_table;
   u2 enclosing_class;
   u2 enclosing_method;
   AnnotationData *annotations;
} ClassBlock;

typedef struct frame {
   CodePntr last_pc;
   uintptr_t *lvars;
   uintptr_t *ostack;
   pMethodBlock mb;
   struct frame *prev;
} Frame;

typedef struct jni_frame {
   pObject *next_ref;
   pObject *lrefs;
   uintptr_t *ostack;
   pMethodBlock mb;
   struct frame *prev;
} JNIFrame;

typedef struct exec_env {
    pObject exception;
    char *stack;
    char *stack_end;
    int stack_size;
    Frame *last_frame;
    pObject thread;
    char overflow;
} ExecEnv;

typedef struct prop {
    char *key;
    char *value;
} Property;

typedef struct InitArgs {
    int asyncgc;
    int verbosegc;
    int verbosedll;
    int verboseclass;

    int compact_specified; /* Whether compaction has been given on the
                              command line, and the value if it has */
    int do_compact;

    char *classpath;
    char *bootpath;
    char bootpathopt;

    int java_stack;
    unsigned long min_heap;
    unsigned long max_heap;

    Property *commandline_props;
    int props_count;

    void *main_stack_base;

    /* JNI invocation API hooks */
    
    int (*vfprintf)(FILE *stream, const char *fmt, va_list ap);
    void (*exit)(int status);
    void (*abort)(void);

#ifdef INLINING
    unsigned int codemem;
    int replication_threshold;
    int profile_threshold;
    int branch_patching_dup;
    int branch_patching;
    int print_codestats;
    int join_blocks;
    int profiling;
#endif
} InitArgs;

#define CLASS_CB(classRef)           ((ClassBlock*)(classRef+1))

#define INST_DATA(obj, type, offset) *(type*)&((char*)obj)[offset]
#define INST_BASE(obj, type)         ((type*)(obj+1))

#define ARRAY_DATA(arrayRef, type)   ((type*)(((uintptr_t*)(arrayRef+1))+1)) 
#define ARRAY_LEN(arrayRef)          *(uintptr_t*)(arrayRef+1)

#define IS_CLASS(object)             (object->class && IS_CLASS_CLASS( \
                                                  CLASS_CB(object->class)))

#define IS_INTERFACE(cb)             (cb->access_flags & ACC_INTERFACE)
#define IS_SYNTHETIC(cb)             (cb->access_flags & ACC_SYNTHETIC)
#define IS_ANNOTATION(cb)            (cb->access_flags & ACC_ANNOTATION)
#define IS_ENUM(cb)                  (cb->access_flags & ACC_ENUM)
#define IS_ARRAY(cb)                 (cb->state == CLASS_ARRAY)
#define IS_PRIMITIVE(cb)             (cb->state >= CLASS_PRIM)
 
#define IS_FINALIZED(cb)             (cb->flags & FINALIZED)
#define IS_REFERENCE(cb)             (cb->flags & REFERENCE)
#define IS_SOFT_REFERENCE(cb)        (cb->flags & SOFT_REFERENCE)
#define IS_WEAK_REFERENCE(cb)        (cb->flags & WEAK_REFERENCE)
#define IS_PHANTOM_REFERENCE(cb)     (cb->flags & PHANTOM_REFERENCE)
#define IS_CLASS_LOADER(cb)          (cb->flags & CLASS_LOADER)
#define IS_CLASS_DUP(cb)             (cb->flags & CLASS_CLASH)
#define IS_CLASS_CLASS(cb)           (cb->flags & CLASS_CLASS)
#define IS_VMTHROWABLE(cb)           (cb->flags & VMTHROWABLE)
#define IS_VMTHREAD(cb)              (cb->flags & VMTHREAD)
#define IS_ANONYMOUS(cb)             (cb->flags & ANONYMOUS)
#define IS_SPECIAL(cb)               (cb->flags & (REFERENCE | CLASS_LOADER | \
                                                  VMTHREAD))
#define IS_MEMBER(cb)                cb->declaring_class
#define IS_LOCAL(cb)                 (cb->enclosing_method && !IS_ANONYMOUS(cb))

/* Macros for accessing constant pool entries */

#define CP_TYPE(cp,i)                   cp->type[i]
#define CP_INFO(cp,i)                   cp->info[i]
#define CP_CLASS(cp,i)                  (u2)cp->info[i]
#define CP_STRING(cp,i)                 (u2)cp->info[i]
#define CP_METHOD_CLASS(cp,i)           (u2)cp->info[i]
#define CP_METHOD_NAME_TYPE(cp,i)       (u2)(cp->info[i]>>16)
#define CP_INTERFACE_CLASS(cp,i)        (u2)cp->info[i]
#define CP_INTERFACE_NAME_TYPE(cp,i)    (u2)(cp->info[i]>>16)
#define CP_FIELD_CLASS(cp,i)            (u2)cp->info[i]
#define CP_FIELD_NAME_TYPE(cp,i)        (u2)(cp->info[i]>>16)
#define CP_NAME_TYPE_NAME(cp,i)         (u2)cp->info[i]
#define CP_NAME_TYPE_TYPE(cp,i)         (u2)(cp->info[i]>>16)
#define CP_UTF8(cp,i)                   (char *)(cp->info[i])

#define CP_INTEGER(cp,i)                (int)(cp->info[i])      
#define CP_FLOAT(cp,i)                  *(float *)&(cp->info[i])
#define CP_LONG(cp,i)                   *(long long *)&(cp->info[i])
#define CP_DOUBLE(cp,i)                 *(double *)&(cp->info[i])

#define KB 1024
#define MB (KB*KB)

/* minimum allowable size of object heap */
#define MIN_HEAP 4*KB

/* minimum allowable size of the Java stack */
#define MIN_STACK 2*KB

/* default minimum size of object heap */
#ifndef DEFAULT_MIN_HEAP
#define DEFAULT_MIN_HEAP 16*MB
#endif

/* default maximum size of object heap */
#ifndef DEFAULT_MAX_HEAP
#define DEFAULT_MAX_HEAP 128*MB
#endif

/* default size of the Java stack */
#define DEFAULT_STACK 256*KB

/* size of emergency area - big enough to create
   a StackOverflow exception */
#define STACK_RED_ZONE_SIZE 1*KB

#define JAVA_COMPAT_VERSION "1.5.0"

/* --------------------- Function prototypes  --------------------------- */

/* Alloc */

extern void initialiseAlloc(InitArgs *args);
extern void initialiseGC(InitArgs *args);
extern pClass allocClass();
extern pObject allocObject(pClass class);
extern pObject allocTypeArray(int type, int size);
extern pObject allocArray(pClass class, int size, int el_size);
extern pObject allocMultiArray(pClass array_class, int dim, intptr_t *count);
extern pObject cloneObject(pObject ob);
extern uintptr_t getObjectHashcode(pObject ob);

extern void gc1();
extern void runFinalizers();

extern unsigned long freeHeapMem();
extern unsigned long totalHeapMem();
extern unsigned long maxHeapMem();

extern void *sysMalloc(int n);
extern void sysFree(void *ptr);
extern void *sysRealloc(void *ptr, int n);

extern void *gcMemMalloc(int n);
extern void gcMemFree(void *ptr);
extern void *gcMemRealloc(void *ptr, int n);

extern void registerStaticObjectRef(pObject *ref);
extern void registerStaticObjectRefLocked(pObject *ref, pObject obj);

#define registerStaticClassRef(ref) \
    registerStaticObjectRef(ref);

#define registerStaticClassRefLocked(ref, class) \
    registerStaticObjectRefLocked(ref, class);

extern void gcPendingFree(void *addr);

/* GC support */
extern void markRoot(pObject ob);
extern void markConservativeRoot(pObject ob);
extern void markObject(pObject ob, int mark);
extern void markJNIClearedWeakRef(pObject ob);
extern void markJNIGlobalRef(pObject ob);
extern int isMarkedJNIWeakGlobalRef(pObject ob);
extern int isMarked(pObject ob);
extern void threadReference(pObject *ref);

/* Class */

extern pClass java_lang_Class;

extern pClass defineClass(char *classname, char *data, int offset, int len,
                          pObject class_loader);
extern void linkClass(pClass class);
extern pClass initClass(pClass class);
extern pClass findSystemClass(char *);
extern pClass findSystemClass0(char *);
extern pClass loadSystemClass(char *);

extern pClass findHashedClass(char *, pObject );
extern pClass findPrimitiveClass(char);
extern pClass findArrayClassFromClassLoader(char *, pObject );

extern pObject getSystemClassLoader();

extern int bootClassPathSize();
extern pObject bootClassPathResource(char *filename, int index);

#define findArrayClassFromClass(name, class) \
             findArrayClassFromClassLoader(name, CLASS_CB(class)->class_loader)
#define findArrayClass(name) findArrayClassFromClassLoader(name, NULL)

extern pClass findClassFromClassLoader(char *, pObject );
#define findClassFromClass(name, class) \
             findClassFromClassLoader(name, CLASS_CB(class)->class_loader)

extern void freeClassData(pClass class);
extern void freeClassLoaderData(pObject class_loader);

extern char *getClassPath();
extern char *getBootClassPath();

extern void markBootClasses();
extern void markLoaderClasses(pObject loader, int mark);
extern void threadBootClasses();
extern void threadLoaderClasses(pObject class_loader);
extern void newLibraryUnloader(pObject class_loader, void *entry);
extern void initialiseClass(InitArgs *args);

extern pObject bootPackage(char *package_name);
extern pObject bootPackages();

/* resolve */

extern pFieldBlock findField(pClass , char *, char *);
extern pMethodBlock findMethod(pClass class, char *methodname, char *type);
extern pFieldBlock lookupField(pClass , char *, char *);
extern pMethodBlock lookupMethod(pClass class, char *methodname, char *type);
extern pMethodBlock lookupVirtualMethod(pObject ob, pMethodBlock mb);
extern pClass resolveClass(pClass class, int index, int init);
extern pMethodBlock resolveMethod(pClass class, int index);
extern pMethodBlock resolveInterfaceMethod(pClass class, int index);
extern pFieldBlock resolveField(pClass class, int index);
extern uintptr_t resolveSingleConstant(pClass class, int index);
extern int peekIsFieldLong(pClass class, int index);

/* cast */

extern char isSubClassOf(pClass class, pClass test);
extern char isInstanceOf(pClass class, pClass test);
extern char arrayStoreCheck(pClass class, pClass test);

/* execute */

extern void *executeMethodArgs(pObject ob, pClass class, pMethodBlock mb, ...);
extern void *executeMethodVaList(pObject ob, pClass class, pMethodBlock mb,
                                  va_list args);
extern void *executeMethodList(pObject ob, pClass class, pMethodBlock mb,
                               u8 *args);

#define executeMethod(ob, mb, args...) \
    executeMethodArgs(ob, ob->class, mb, ##args)

#define executeStaticMethod(clazz, mb, args...) \
    executeMethodArgs(NULL, clazz, mb, ##args)

/* excep */

extern pObject exceptionOccurred();
extern void signalChainedExceptionEnum(int excep_enum, char *excep_mess,
                                       pObject cause);
extern void signalChainedExceptionName(char *excep_name, char *excep_mess,
                                       pObject cause);
extern void signalChainedExceptionClass(pClass excep_class, char *excep_mess,
                                        pObject cause);
extern void setException(pObject excep);
extern void clearException();
extern void printException();
extern CodePntr findCatchBlock(pClass exception);
extern pObject setStackTrace0(ExecEnv *ee, int max_depth);
extern pObject convertStackTrace(pObject vmthrwble);
extern int mapPC2LineNo(pMethodBlock mb, CodePntr pc_pntr);
extern void markVMThrowable(pObject vmthrwble, int mark);
extern void initialiseException();

#define exceptionOccurred0(ee) \
    ee->exception

#define signalException(excep_name, excep_mess) \
    signalChainedExceptionEnum(EXCEPTION_ENUM(excep_name), excep_mess, NULL)

#define signalChainedException(excep_name, excep_mess, cause) \
    signalChainedExceptionEnum(EXCEPTION_ENUM(excep_name), excep_mess, cause)

#define signalExceptionClass(excep_class, excep_mess) \
    signalChainedExceptionClass(excep_class, excep_mess, NULL)

#define setStackTrace() \
    setStackTrace0(getExecEnv(), INT_MAX)

/* interp */

extern uintptr_t *executeJava();
extern void shutdownInterpreter();
extern void initialiseInterpreter(InitArgs *args);

/* String */

extern pObject findInternedString(pObject string);
extern pObject createString(char *utf8);
extern pObject createStringFromUnicode(unsigned short *unicode, int len);
extern char *String2Cstr(pObject string);
extern char *String2Buff(pObject string, char *buff, int buff_len);
extern int getStringLen(pObject string);
extern unsigned short *getStringChars(pObject string);
extern pObject getStringCharsArray(pObject string);
extern int getStringUtf8Len(pObject string);
extern char *String2Utf8(pObject string);
extern char *StringRegion2Utf8(pObject string, int start, int len, char *utf8);
extern void freeInternedStrings();
extern void threadInternedStrings();
extern void initialiseString();

#define Cstr2String(cstr) createString(cstr)

/* Utf8 */

extern int utf8Len(char *utf8);
extern int utf8Hash(char *utf8);
extern int utf8Comp(char *utf81, char *utf82);
extern void convertUtf8(char *utf8, unsigned short *buff);
extern char *findHashedUtf8(char *string, int add_if_absent);
extern char *copyUtf8(char *string);
extern int utf8CharLen(unsigned short *unicode, int len);
extern char *unicode2Utf8(unsigned short *unicode, int len, char *utf8);
extern char *slash2dots(char *utf8);
extern char *slash2dots2buff(char *utf8, char *buff, int buff_len);
extern void initialiseUtf8();

#define findUtf8(string) \
    findHashedUtf8(string, FALSE)

#define newUtf8(string) \
    findHashedUtf8(string, TRUE)

/* Dll */

extern void *resolveNativeMethod(pMethodBlock mb);
extern int resolveDll(char *name, pObject loader);
extern char *getDllPath();
extern char *getBootDllPath();
extern char *getDllName(char *name);
extern void initialiseDll(InitArgs *args);
extern uintptr_t *resolveNativeWrapper(pClass class, pMethodBlock mb,
                                       uintptr_t *ostack);
extern void unloaderUnloadDll(uintptr_t entry);
extern void unloadClassLoaderDlls(pObject loader);
extern void threadLiveClassLoaderDlls();

/* OS */

extern char *nativeLibPath();
extern char *nativeLibError();
extern void *nativeLibOpen(char *path);
extern void nativeLibClose(void *handle);
extern char *nativeLibMapName(char *name);
extern void *nativeLibSym(void *handle, char *symbol);
extern void *nativeStackBase();
extern int nativeAvailableProcessors();

/* Threading */

extern void initialiseThreadStage1(InitArgs *args);
extern void initialiseThreadStage2(InitArgs *args);
extern ExecEnv *getExecEnv();

extern void createJavaThread(pObject jThread, long long stack_size);
extern void mainThreadSetContextClassLoader(pObject loader);
extern void mainThreadWaitToExitVM();
extern void uncaughtException();
extern void exitVM(int status);
extern void scanThreads();

/* Monitors */

extern void initialiseMonitor();

/* jni */

extern int initJNILrefs();
extern void initialiseJNI();
extern void *getJNIInterface();
extern void markJNIGlobalRefs();
extern void scanJNIWeakGlobalRefs();
extern void markJNIClearedWeakRefs();

/* properties */

extern void initialiseProperties(InitArgs *args);
extern void addCommandLineProperties(pObject properties);
extern void addDefaultProperties(pObject properties);
extern char *getCommandLineProperty(char *key);
extern char *getCwd();

/* access */

extern int checkClassAccess(pClass class1, pClass class2);
extern int checkMethodAccess(pMethodBlock mb, pClass class);
extern int checkFieldAccess(pFieldBlock fb, pClass class);

/* frame */

extern Frame *getCallerFrame(Frame *last);
extern pClass getCallerCallerClass();

/* native */

extern void initialiseNatives();

/* init */

extern void setDefaultInitArgs(InitArgs *args);
extern unsigned long parseMemValue(char *str);
extern void initVM(InitArgs *args);
extern int VMInitialising();

/* shutdown */

extern void shutdownVM(int status);

/* hooks */

extern void initialiseHooks(InitArgs *args);
extern void jam_fprintf(FILE *stream, const char *fmt, ...);
extern void jamvm_exit(int status);

#define jam_printf(fmt, ...) jam_fprintf(stdout, fmt, ## __VA_ARGS__)

/* inlining */

extern void freeMethodInlinedInfo(pMethodBlock mb);
extern int  initialiseInlining(InitArgs *args);
extern void showRelocatability();
extern void shutdownInlining();

/* symbol */

extern void initialiseSymbol();

/* time */

extern void getTimeoutAbsolute(struct timespec *ts, long long millis,
                        long long nanos);
extern void getTimeoutRelative(struct timespec *ts, long long millis,
                        long long nanos);

/* sig */

extern int sigElement2Size(char element);

