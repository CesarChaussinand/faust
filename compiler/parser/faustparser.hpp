/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WITH = 258,
     LETREC = 259,
     MIX = 260,
     SPLIT = 261,
     SEQ = 262,
     PAR = 263,
     REC = 264,
     NE = 265,
     GE = 266,
     GT = 267,
     EQ = 268,
     LE = 269,
     LT = 270,
     OR = 271,
     SUB = 272,
     ADD = 273,
     RSH = 274,
     LSH = 275,
     XOR = 276,
     AND = 277,
     MOD = 278,
     DIV = 279,
     MUL = 280,
     POWOP = 281,
     FDELAY = 282,
     DELAY1 = 283,
     DOT = 284,
     APPL = 285,
     MEM = 286,
     PREFIX = 287,
     INTCAST = 288,
     FLOATCAST = 289,
     FFUNCTION = 290,
     FCONSTANT = 291,
     FVARIABLE = 292,
     BUTTON = 293,
     CHECKBOX = 294,
     VSLIDER = 295,
     HSLIDER = 296,
     NENTRY = 297,
     VGROUP = 298,
     HGROUP = 299,
     TGROUP = 300,
     HBARGRAPH = 301,
     VBARGRAPH = 302,
     SOUNDFILE = 303,
     ATTACH = 304,
     ACOS = 305,
     ASIN = 306,
     ATAN = 307,
     ATAN2 = 308,
     COS = 309,
     SIN = 310,
     TAN = 311,
     EXP = 312,
     LOG = 313,
     LOG10 = 314,
     POWFUN = 315,
     SQRT = 316,
     ABS = 317,
     MIN = 318,
     MAX = 319,
     FMOD = 320,
     REMAINDER = 321,
     FLOOR = 322,
     CEIL = 323,
     RINT = 324,
     RDTBL = 325,
     RWTBL = 326,
     SELECT2 = 327,
     SELECT3 = 328,
     INT = 329,
     FLOAT = 330,
     LAMBDA = 331,
     WIRE = 332,
     CUT = 333,
     ENDDEF = 334,
     VIRG = 335,
     LPAR = 336,
     RPAR = 337,
     LBRAQ = 338,
     RBRAQ = 339,
     LCROC = 340,
     RCROC = 341,
     DEF = 342,
     IMPORT = 343,
     COMPONENT = 344,
     LIBRARY = 345,
     ENVIRONMENT = 346,
     WAVEFORM = 347,
     ROUTE = 348,
     ENABLE = 349,
     CONTROL = 350,
     IPAR = 351,
     ISEQ = 352,
     ISUM = 353,
     IPROD = 354,
     INPUTS = 355,
     OUTPUTS = 356,
     STRING = 357,
     FSTRING = 358,
     IDENT = 359,
     EXTRA = 360,
     DECLARE = 361,
     CASE = 362,
     ARROW = 363,
     FLOATMODE = 364,
     DOUBLEMODE = 365,
     QUADMODE = 366,
     FIXEDPOINTMODE = 367,
     BDOC = 368,
     EDOC = 369,
     BEQN = 370,
     EEQN = 371,
     BDGM = 372,
     EDGM = 373,
     BLST = 374,
     ELST = 375,
     BMETADATA = 376,
     EMETADATA = 377,
     DOCCHAR = 378,
     NOTICE = 379,
     LISTING = 380,
     LSTTRUE = 381,
     LSTFALSE = 382,
     LSTDEPENDENCIES = 383,
     LSTMDOCTAGS = 384,
     LSTDISTRIBUTED = 385,
     LSTEQ = 386,
     LSTQ = 387
   };
#endif
/* Tokens.  */
#define WITH 258
#define LETREC 259
#define MIX 260
#define SPLIT 261
#define SEQ 262
#define PAR 263
#define REC 264
#define NE 265
#define GE 266
#define GT 267
#define EQ 268
#define LE 269
#define LT 270
#define OR 271
#define SUB 272
#define ADD 273
#define RSH 274
#define LSH 275
#define XOR 276
#define AND 277
#define MOD 278
#define DIV 279
#define MUL 280
#define POWOP 281
#define FDELAY 282
#define DELAY1 283
#define DOT 284
#define APPL 285
#define MEM 286
#define PREFIX 287
#define INTCAST 288
#define FLOATCAST 289
#define FFUNCTION 290
#define FCONSTANT 291
#define FVARIABLE 292
#define BUTTON 293
#define CHECKBOX 294
#define VSLIDER 295
#define HSLIDER 296
#define NENTRY 297
#define VGROUP 298
#define HGROUP 299
#define TGROUP 300
#define HBARGRAPH 301
#define VBARGRAPH 302
#define SOUNDFILE 303
#define ATTACH 304
#define ACOS 305
#define ASIN 306
#define ATAN 307
#define ATAN2 308
#define COS 309
#define SIN 310
#define TAN 311
#define EXP 312
#define LOG 313
#define LOG10 314
#define POWFUN 315
#define SQRT 316
#define ABS 317
#define MIN 318
#define MAX 319
#define FMOD 320
#define REMAINDER 321
#define FLOOR 322
#define CEIL 323
#define RINT 324
#define RDTBL 325
#define RWTBL 326
#define SELECT2 327
#define SELECT3 328
#define INT 329
#define FLOAT 330
#define LAMBDA 331
#define WIRE 332
#define CUT 333
#define ENDDEF 334
#define VIRG 335
#define LPAR 336
#define RPAR 337
#define LBRAQ 338
#define RBRAQ 339
#define LCROC 340
#define RCROC 341
#define DEF 342
#define IMPORT 343
#define COMPONENT 344
#define LIBRARY 345
#define ENVIRONMENT 346
#define WAVEFORM 347
#define ROUTE 348
#define ENABLE 349
#define CONTROL 350
#define IPAR 351
#define ISEQ 352
#define ISUM 353
#define IPROD 354
#define INPUTS 355
#define OUTPUTS 356
#define STRING 357
#define FSTRING 358
#define IDENT 359
#define EXTRA 360
#define DECLARE 361
#define CASE 362
#define ARROW 363
#define FLOATMODE 364
#define DOUBLEMODE 365
#define QUADMODE 366
#define FIXEDPOINTMODE 367
#define BDOC 368
#define EDOC 369
#define BEQN 370
#define EEQN 371
#define BDGM 372
#define EDGM 373
#define BLST 374
#define ELST 375
#define BMETADATA 376
#define EMETADATA 377
#define DOCCHAR 378
#define NOTICE 379
#define LISTING 380
#define LSTTRUE 381
#define LSTFALSE 382
#define LSTDEPENDENCIES 383
#define LSTMDOCTAGS 384
#define LSTDISTRIBUTED 385
#define LSTEQ 386
#define LSTQ 387




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 81 "faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 321 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

