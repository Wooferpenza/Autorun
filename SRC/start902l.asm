;==========================================================================
; F2MC-16 Family SOFTUNE C Compiler sample startup routine,
; ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 1986
; LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
;==========================================================================

;===<< WARNING >>==========================================================
; This startup routine is for running programs on simulator.
; This program does not contain enough initializations for real CPU
; though enough initializations for simulator are contained.
;--------------------------------------------------------------------------

;===<< WARNING >>==========================================================
; The label DCLEAR_S/DTRANS_S must be located at the top of the
; DCLEAR/DTRANS section to run this startup routine correctly.
; If the area of the variable specified with __far type qualifier is
; initialized by using DCLEAR/DTRANS section, please pay attention to
; the link order of the startup routine.  This startup routine must be
; linked before linking modules containing definitions of variables
; specified with __far type qualifier.
;
; To check the link order, please define __CHECK_DTRANS_DCLEAR__.
;
; #define	__CHECK_DTRANS_DCLEAR__
;--------------------------------------------------------------------------

;==========================================================================
; Sample program for initialization (large model)
;--------------------------------------------------------------------------

		.PROGRAM	start
		.TITLE		start

;--------------------------------------------------------------------------
; external declaration of symbols
;--------------------------------------------------------------------------
		.EXPORT		__start
		.IMPORT		_main

;--------------------------------------------------------------------------
; definition to stack area
;--------------------------------------------------------------------------
		.SECTION	STACK,	  STACK,    ALIGN=1
		.RES.B		254
SSTACK_TOP:
		.RES.B		2
		.RES.B		(1024*4)-260
USTACK_TOP:
		.RES.B		2

;--------------------------------------------------------------------------
; definition to start address of data, const and code section
;--------------------------------------------------------------------------
		.SECTION	DIRDATA,  DIR,	    ALIGN=2
DIRDATA_S:
		.SECTION	DIRINIT,  DIR,	    ALIGN=2
DIRINIT_S:
		.SECTION	DATA,	  DATA,	    ALIGN=2
DATA_S:
		.SECTION	INIT,	  DATA,	    ALIGN=2
INIT_S:
		.SECTION	LIBDATA,  DATA,	    ALIGN=2
LIBDATA_S:
		.SECTION	LIBINIT,  DATA,	    ALIGN=2
LIBINIT_S:
		.SECTION	DIRCONST, DIRCONST, ALIGN=2
DIRCONST_S:
		.SECTION	DCONST,	  CONST,    ALIGN=2
DCONST_S:
		.SECTION	CONST,	  CONST,    ALIGN=2
CONST_S:
		.SECTION	LIBDCONST,CONST,    ALIGN=2
LIBDCONST_S:
		.SECTION	DTRANS,	  CONST,    ALIGN=2
DTRANS_S:
		.SECTION	DCLEAR,	  CONST,    ALIGN=2
DCLEAR_S:


;--------------------------------------------------------------------------
; code area
;--------------------------------------------------------------------------
		.SECTION	CODE,	  CODE,	    ALIGN=1
__start:
;--------------------------------------------------------------------------
; set register bank is 0
;--------------------------------------------------------------------------
		MOV	RP, #0

;--------------------------------------------------------------------------
; set ILM to the lowest level
;--------------------------------------------------------------------------
		MOV	ILM, #7

;--------------------------------------------------------------------------
; set direct page register
;--------------------------------------------------------------------------
		MOV	A, #PAGE DIRDATA_S
		MOV	DPR, A

;--------------------------------------------------------------------------
; set system stack
;--------------------------------------------------------------------------
		AND	CCR, #0x20
		MOV	A, #BNKSYM SSTACK_TOP
		MOV	SSB, A
		MOVW	A, #SSTACK_TOP
		MOVW	SP, A
		AND	CCR, #0x00DF

;--------------------------------------------------------------------------
; copy initial value *CONST section to *INIT section
;--------------------------------------------------------------------------
#macro		ICOPY	src_addr, dest_addr, src_section, dest_section
		MOV	A, #BNKSYM \src_addr
		MOV	ADB, A
		MOV	A, #BNKSYM \dest_addr
		MOV	DTB, A
		MOVW	RW0, #SIZEOF (\src_section)
		MOVW	A, #\dest_section
		MOVW	A, #\src_section
		MOVSI	DTB, ADB
#endm

		ICOPY	DIRCONST_S, DIRINIT_S, DIRCONST,  DIRINIT
		ICOPY	DCONST_S,   INIT_S,    DCONST,	  INIT
		ICOPY	LIBDCONST_S,LIBINIT_S, LIBDCONST, LIBINIT

;--------------------------------------------------------------------------
; zero clear of *VAR section
;--------------------------------------------------------------------------
#macro		FILL0	src_addr, src_section
		MOV	A, #BNKSYM \src_addr
		MOV	DTB, A
		MOVW	RW0, #SIZEOF (\src_section)
		MOVW	A, #\src_section
		MOVN	A, #0
		FILSI	DTB
#endm

		FILL0	DIRDATA_S, DIRDATA
		FILL0	DATA_S,	   DATA
		FILL0	LIBDATA_S, LIBDATA

;--------------------------------------------------------------------------
; copy initial value DCONST_module section to INIT_module section
;--------------------------------------------------------------------------
#ifdef	__CHECK_DTRANS_DCLEAR__
		MOVL	A, #DCLEAR_S
		MOVL	RL0, A
		MOVL	A, #DCLEAR
		CMPL	A, RL0
		BNE	LABEL8
		MOVL	A, #DTRANS_S
		MOVL	RL0, A
		MOVL	A, #DTRANS
		CMPL	A, RL0
		BEQ	LABEL9
LABEL8:		BRA	LABEL8	; Please check the link-order
				;	when this loop is executed.
LABEL9:
#endif
		MOV	A, #BNKSYM DTRANS_S
		MOV	DTB, A
		MOVW	RW1, #DTRANS_S
		BRA	LABEL2
LABEL1:
		MOVW	A, @RW1+6
		MOV	USB, A
		MOVW	A, @RW1+2
		MOV	ADB, A
		MOVW	A, @RW1+4
		MOVW	A, @RW1
		MOVW	RW0, @RW1+8
		MOVSI	SPB, ADB
		MOVN	A, #10
		ADDW	RW1, A
LABEL2:
		MOVW	A, RW1
		SUBW	A, #DTRANS_S
		CMPW	A, #SIZEOF (DTRANS)
		BNE	LABEL1

;--------------------------------------------------------------------------
; zero clear of DATA_module section
;--------------------------------------------------------------------------
		MOV	A, #BNKSYM DCLEAR_S
		MOV	DTB, A
		MOVW	RW1, #DCLEAR_S
		BRA	LABEL4
LABEL3:
		MOV	A, @RW1+2
		MOV	ADB, A
		MOVW	RW0, @RW1+4
		MOVW	A, @RW1
		MOVN	A, #0
		FILSI	ADB
		MOVN	A, #6
		ADDW	RW1, A
LABEL4:
		MOVW	A, RW1
		SUBW	A, #DCLEAR_S
		CMPW	A, #SIZEOF (DCLEAR)
		BNE	LABEL3

;--------------------------------------------------------------------------
; set data bank register
;--------------------------------------------------------------------------
		MOV	A, #BNKSYM DATA_S
		MOV	DTB, A

;--------------------------------------------------------------------------
; set user stack
;--------------------------------------------------------------------------
		MOV	A, #BNKSYM USTACK_TOP
		MOV	USB, A
		MOVW	A, #USTACK_TOP
		MOVW	SP, A

;--------------------------------------------------------------------------
; call main routine
;--------------------------------------------------------------------------
		CALLP	_main
end:		jmp	end
		.END	__start
