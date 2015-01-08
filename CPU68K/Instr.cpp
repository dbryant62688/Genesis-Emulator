#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>


//Data Movement Prototypes
extern void exg_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fsmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fdmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fmovem_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void lea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void link_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void move_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void move16_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movem_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movep_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void moveq_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void pea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void unlk_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//Program Control prototypes
extern void bcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void dbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fdbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void scc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fscc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bra_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void jmp_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void jsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void nop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fnop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void rtd_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void rtr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void rts_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void tst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void ftst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);


//Integer Arithmetic Instructions
extern void add_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void adda_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void addi_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void addq_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void addx_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void clr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void cmp_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void cmpa_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void cmpi_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void cmpm_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void cmp2_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void divs_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void divsl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void ext_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void extb_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void muls_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void neg_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void negx_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void sub_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void suba_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void subi_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void subq_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void subx_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//Logical intruction prototypes
extern void and_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void andi_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void eor_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void eori_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void not_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void or_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void ori_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//Shift and Rotate Instructions
extern void asl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void asr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void lsl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void lsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void rol_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void ror_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void roxl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void roxr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void swap_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//Bit Manipulation Instructions
extern void bchg_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bclr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bset_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void btst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//BitField Instructions
extern void bfchg_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bfclr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bfexts_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bfextu_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bffo_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bfins_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bfset_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bftst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);

//Binary Coded Decimal Instructions
extern void abcd_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void nbcd_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void pack_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void sbcd_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void unpk_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);


//system control Instructions
extern void anditosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void eoritosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void frestore_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void fsave_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movetosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movefromsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void moveusp_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movec_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void moves_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void oritosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void reset_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void rte_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void stop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void bkpt_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void chk_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void chk2_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void illegal_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void trap_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void trapcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void ftrapcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void trapv_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void anditoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void eoritoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movetoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void movefromccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);
extern void oritoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr);



bool CheckOpcode(short Op,Instruction instr)
{
	if((Op & instr.Mask) == instr.Opcode)
		return true;

	return false;
}



Instruction GlobalInstructionList[] = 
	{
		{L"ORI to CCR"	,0x003C,0xFFFF,oritoccr_cmd},
		{L"ORI to SR"	,0x007C,0xFFFF,oritosr_cmd}, 
		{L"ORI"			,0x0000,0xFF00,ori_cmd}, 
		{L"ANDI to CCR"	,0x023C,0xFFFF,anditoccr_cmd}, 
		{L"ANDI to SR"	,0x027C,0xFFFF,anditosr_cmd}, 
		{L"ANDI"		,0x0200,0xFF00,andi_cmd}, 
		{L"SUBI"		,0x0400,0xFF00,NULL}, 
		{L"ADDI"		,0x0600,0xFF00,NULL},
		{L"EORI to CCR"	,0x0A3C,0xFFFF,eoritoccr_cmd},
		{L"EORI to SR"	,0x0A7C,0xFFFF,eoritosr_cmd},
		{L"EORI"		,0x0A00,0xFF00,eori_cmd},
		{L"CMPI"		,0x0C00,0xFF00,NULL},
		{L"BTST"		,0x0800,0xFFC0,NULL},
		{L"BCHG"		,0x0840,0xFFC0,NULL},
		{L"BCLR"		,0x0880,0xFFC0,NULL},
		{L"BSET"		,0x08C0,0xFFC0,NULL},
		{L"BTSTL"		,0x0900,0xFFC0,NULL},
		{L"BCHGL"		,0x0940,0xFFC0,NULL},
		{L"BCLRL"		,0x0980,0xFFC0,NULL},
		{L"BSETL"		,0x09C0,0xFFC0,NULL},
		{L"MOVEP"		,0x0108,0xF138,movep_cmd},
		{L"MOVEA"		,0x0040,0xC1C0,movea_cmd},
		{L"MOVE"		,0x0000,0xC000,move_cmd},	//May have issue with this and ORI
		
		
		{L"MOVE from SR",0x40C0,0xFFC0,movefromccr_cmd},
		{L"MOVE to CCR"	,0x44C0,0xFFC0,movetoccr_cmd},
		{L"MOVE to SR"	,0x46C0,0xFFC0,movetosr_cmd},
		{L"NEGX"		,0x4000,0xFF00,NULL},
		{L"CLR"			,0x4200,0xFF00,NULL},
		{L"NEG"			,0x4400,0xFF00,NULL},
		{L"NOT"			,0x4600,0xFF00,not_cmd},
		{L"EXT"			,0x4880,0xFFB8,NULL},
		{L"NBCD"		,0x4800,0xFFC0,NULL},
		{L"SWAP"		,0x4840,0xFFF8,swap_cmd},
		{L"PEA"			,0x4840,0xFFC0,pea_cmd},	//May have a problem with this and SWAP
		{L"ILLEGAL"		,0x4AFC,0xFFFF,NULL},
		{L"TAS"			,0x4AC0,0xFFC0,NULL},
		{L"TST"			,0x4A00,0xFF00,tst_cmd},
		{L"TRAP"		,0x4E40,0xFFF0,NULL},
		{L"LINK"		,0x4E50,0xFFF8,link_cmd},
		{L"UNLK"		,0x4E58,0xFFF8,unlk_cmd},
		{L"MOVE USP"	,0x4E60,0xFFF0,NULL},
		{L"RESET"		,0x4E70,0xFFFF,NULL},
		{L"NOP"			,0x4E71,0xFFFF,nop_cmd},
		{L"STOP"		,0x4E72,0xFFFF,NULL},
		{L"RTE"			,0x4E73,0xFFFF,NULL},
		{L"RTS"			,0x4E75,0xFFFF,NULL},
		{L"TRAPV"		,0x4E76,0xFFFF,NULL},
		{L"RTR"			,0x4E77,0xFFFF,NULL},
		{L"JSR"			,0x4E80,0xFFC0,jsr_cmd},
		{L"JMP"			,0x4EC0,0xFFC0,jmp_cmd},
		{L"MOVEM"		,0x4880,0xFB80,movem_cmd},
		{L"LEA"			,0x41C0,0xF1C0,lea_cmd},
		{L"CHK"			,0x4180,0xF1C0,NULL},
		
		{L"DBcc"		,0x50C8,0xF0C8,dbcc_cmd},
		{L"Scc"			,0x50C0,0xF0C0,scc_cmd},
		{L"ADDQ"		,0x5000,0xF100,NULL},
		{L"SUBQ"		,0x5100,0xF100,NULL},
		
		{L"BRA"			,0x6000,0xFF00,bra_cmd},
		{L"BSR"			,0x6100,0xFF00,bsr_cmd},
		{L"Bcc"			,0x6000,0xF000,bcc_cmd},	//May have a problem wit this and BRA
		
		{L"MOVEQ"		,0x7000,0xF100,moveq_cmd},
		
		{L"DIVU"		,0x80C0,0xF1C0,NULL},
		{L"DIVS"		,0x81C0,0xF1C0,NULL},
		{L"SBCD"		,0x8100,0xF1F0,NULL},
		{L"OR"			,0x8000,0xF000,NULL},
		
		{L"SUB"			,0x9000,0xF000,NULL},
		{L"SUBX"		,0x9100,0xF100,NULL},
		{L"SUBA"		,0x90C0,0xF0C0,NULL},
		
		{L"EOR"			,0xB100,0xF100,NULL},
		{L"CMPM"		,0xB101,0xF138,NULL},
		{L"CMP"			,0xB000,0xF100,NULL},
		{L"CMPA"		,0xB0C0,0xF0C0,NULL},
		
		{L"MULU"		,0xC0C0,0xF1C0,NULL},
		{L"MULS"		,0xC1C0,0xF1C0,NULL},
		{L"ABCD"		,0xC100,0xF1F0,NULL},
		{L"EXG"			,0xC100,0xF130,NULL}, //May have probelm with this and ABCD
		{L"AND"			,0xC000,0xF000,NULL},

		{L"ADD"			,0xD000,0xF000,NULL},
		{L"ADDX"		,0xD100,0xF130,NULL},
		{L"ADDA"		,0xD0C0,0xF0C0,NULL},
		
		{L"ASd"			,0xE0C0,0xFEC0,NULL},
		{L"LSd"			,0xE2C0,0xFEC0,NULL},
		{L"ROXd"		,0xE4C0,0xFEC0,NULL},
		{L"ROd"			,0xE6C0,0xFEC0,NULL},
		{L"ASd"			,0xE000,0xF018,NULL},
		{L"LSd"			,0xE008,0xF018,NULL},
		{L"ROXd"		,0xE010,0xF018,NULL},
		{L"ROd"			,0xE018,0xF018,NULL}

};