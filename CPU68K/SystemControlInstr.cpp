#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void anditosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	

	unsigned short ImmediateData = cpu->FetchWord();

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg & ImmediateData;
	swprintf_s(OutputString,100,L"\tANDI to CCR: 0x%X & 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
}
void anditoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	

	unsigned short ImmediateData = cpu->FetchWord()&0x00FF;

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg & ImmediateData;
	swprintf_s(OutputString,100,L"\tANDI to CCR: 0x%X & 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
 }
 void eoritosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	unsigned short ImmediateData = cpu->FetchWord();

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg ^ ImmediateData;

	swprintf_s(OutputString,100,L"\tEORI to SR: 0x%X & 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
}
void eoritoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	unsigned short ImmediateData = cpu->FetchWord()&0x00FF;

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg ^ ImmediateData;

	swprintf_s(OutputString,100,L"\tEORI to CCR: 0x%X & 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
}
 void oritoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	

	unsigned short ImmediateData = cpu->FetchWord()&0x00FF;

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg | ImmediateData;
	swprintf_s(OutputString,100,L"\tORI to CCR: 0x%X | 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
 }

 void oritosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	wchar_t OutputString[100] = {0};
	

	unsigned short ImmediateData = cpu->FetchWord();

	unsigned short CCRReg = cpu->StatusRegisterRead();

	unsigned short Result = CCRReg | ImmediateData;
	swprintf_s(OutputString,100,L"\tORI to SR: 0x%X | 0x%X = 0x%X\n",CCRReg,ImmediateData,Result);
	OutputDebugString(OutputString);

	cpu->StatusRegisterWrite(Result,0xFFFF);
 }
 void frestore_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	swprintf_s(OutputString,100,L"\tFRESTORE: \n");
	OutputDebugString(OutputString);
}
 void fsave_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	swprintf_s(OutputString,100,L"\tFSAVE: \n");
	OutputDebugString(OutputString);
 }
 void movetosr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	char SrcAddrMode	= (InstrData&0x0038)>>3;
	char SrcAddrReg		= (InstrData&0x0007);


	//Move always moves the source to the destination so lets get the source operand 
	//and the destination ptr
	unsigned int Operand = cpu->GetOperandUsingEffectiveAddress(SrcAddrMode,SrcAddrReg,1);
		
	swprintf_s(OutputString,100,L"\tMove to SR: Moving Operand 0x%X to SR register\n",Operand);
	OutputDebugString(OutputString);

	//THis function writes to the top half so lets set the mask accordingly
	cpu->StatusRegisterWrite(Operand,0xFF00);
 }
 void movefromsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	swprintf_s(OutputString,100,L"\tMove from SR: \n");
	OutputDebugString(OutputString);
 }
 void moveusp_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {

 }
 void movec_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void moves_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 
 void reset_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void rte_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void stop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void bkpt_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void chk_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void chk2_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void illegal_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void trap_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void trapcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void ftrapcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 void trapv_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr){
 }
 
 
 void movetoccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	swprintf_s(OutputString,100,L"\tMove to CCR: \n");
	OutputDebugString(OutputString);
 }
 void movefromccr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	swprintf_s(OutputString,100,L"\tMove from CCR: \n");
	OutputDebugString(OutputString);
 }
 
