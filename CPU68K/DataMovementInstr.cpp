#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>


void exg_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{

}
void fmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{

}
void fsmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{

}
 void fdmove_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
 
 }
 void fmovem_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
 
 }
 void link_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
 
 }

 void movea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	  wchar_t OutputString[100] = {0};
	
	 //calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Size = (InstrData&0x3000)>>12;
	char DestReg		= (InstrData&0x0E00)>>9;
	char SrcAddrMode	= (InstrData&0x0038)>>3;
	char SrcAddrReg		= (InstrData&0x0007);

	char OpSize = 0;
	if(Size == 3)
		OpSize = 1;
	else 
		OpSize = 2;
	//Get Operand 
	unsigned int Operand = cpu->GetOperandUsingEffectiveAddress(SrcAddrMode,SrcAddrReg,OpSize,true);
	//always move the whole long value
	cpu->SetOperandUsingEffectiveAddress(0x1,DestReg,2,Operand);
 }
 void move16_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
 }

 void movep_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	
	 //calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	short DataReg = (InstrData&0x0e00)>>9;
	short OpMode = (InstrData&0x01C0)>>6;
	short AddrMode = (InstrData&0x0038)>>3;
	short AddrReg  = (InstrData&0x0007);

	//Get the 16-bit Displacement value
	short Displacement = cpu->FetchWord();

	unsigned int DataRegisterOperand = cpu->DataRegisterRead(DataReg);

	unsigned int EA = cpu->AddressRegisterRead(AddrReg) + Displacement;
	unsigned int MemoryOperand = cpu->MemoryReadLong(EA);

	switch(OpMode)
	{
		case 4: // Transfer word from memory to register
			cpu->SetOperandUsingEffectiveAddress(0x00,DataReg,0x01,MemoryOperand);
			break;
		case 5: // Transfer long from memory to register
			cpu->SetOperandUsingEffectiveAddress(0x00,DataReg,0x02,MemoryOperand);
			break;
		case 6: // Transfer word from register to memeory
			cpu->MemoryWriteWord(EA,(unsigned short)(DataRegisterOperand&0x0000FFFF));
		case 7: // Transfer long from register to memory
			cpu->MemoryWriteWord(EA,(unsigned short)(DataRegisterOperand&0x0000FFFF));
			break;
	}

 }
 void moveq_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	
	 //calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	short DataReg = (InstrData&0x0e00)>>9;
	char DataByte = (InstrData&0x00FF);
	int Data = (int)DataByte;

	swprintf_s(OutputString,100,L"\tMOVEQ: Moving  Operand 0x%X to Data Register %d\n",Data,DataReg);
	OutputDebugString(OutputString);

	//Move data byte into 32 bit register
	cpu->SetOperandUsingEffectiveAddress(0x000,DataReg,0x2,Data);
 }
 void pea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	 wchar_t OutputString[100] = {0};
	
	 //calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	short AddrMode = (InstrData&0x0038)>>3;
	short AddrReg  = (InstrData&0x0007);

	//Increment the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() - 4);

	//Get Effective Address
	unsigned int EA = cpu->GetEffectiveAddress(AddrMode,AddrReg,2);

	//Add effective address to stack
	cpu->MemoryWriteLong(cpu->StackPointerRead(),EA);


 }
 void unlk_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
 {
	wchar_t OutputString[100] = {0};
	
	 //calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	short AddrReg  = (InstrData&0x0007);

	//Set Stack pointer to Address reg
	cpu->StackPointerWrite(cpu->AddressRegisterRead(AddrReg));
	
	//Grab the contents of memory at the stack pointer and place it into the address register
	cpu->AddressRegisterWrite(AddrReg,cpu->MemoryReadLong(cpu->StackPointerRead()));

	//Decrement stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() + 4);


 }


void lea_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	short DestAddrReg = (InstrData&0x0e00)>>9;
	short SrcAddrMode = (InstrData&0x0038)>>3;
	short SrcXn		  = (InstrData&0x0007);

	//Now lets get THe EFfective Address
	unsigned int EA = cpu->GetEffectiveAddress(SrcAddrMode,SrcXn,2);

	//Load it to either the Stack pointer or other address registers
	swprintf_s(OutputString,100,L"\tLEA: Loading Effective Address 0x%X to Address Register %d\n",EA,DestAddrReg);
	OutputDebugString(OutputString);
	
	if(DestAddrReg == 7)
		cpu->StackPointerWrite(EA);
	else
		cpu->AddressRegisterWrite(DestAddrReg,EA);
}
void move_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[400] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Size = (InstrData&0x3000)>>12;
	char DestAddrReg	= (InstrData&0x0E00)>>9;
	char DestAddrMode	= (InstrData&0x01C0)>>6;
	char SrcAddrMode	= (InstrData&0x0038)>>3;
	char SrcAddrReg		= (InstrData&0x0007);


	//Src size is weird so lets convert it
	char SrcSize = 0;
	if(Size == 1)
		SrcSize = 0; //Byte
	else if(Size == 2)
		SrcSize = 2; //Long
	else if(Size == 3)
		SrcSize = 1;//Word

	//Move always moves the source to the destination so lets get the source operand 
	//and the destination ptr
	unsigned int Operand = cpu->GetOperandUsingEffectiveAddress(SrcAddrMode,SrcAddrReg,SrcSize);
	
	//Set necessary flags
	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();

	if(Operand > 0x7FFFFFFF)
		cpu->SetNegativeFlag();

	if(Operand == 0)
		cpu->SetZeroFlag();


	swprintf_s(OutputString,100,L"\tMOVE: Moving Source: %d , %d Operand 0x%X to Destination: %d , %d\n",SrcAddrMode, SrcAddrReg, Operand,DestAddrMode,DestAddrReg);
	OutputDebugString(OutputString);

	//Perform move
	cpu->SetOperandUsingEffectiveAddress(DestAddrMode,DestAddrReg,SrcSize,Operand);
		
}
void movem_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Direction = (InstrData&0x0400)>>10;
	char Size = (InstrData&0x0040)>>6;
	char AddrMode = (InstrData&0x0038)>>3;
	char AddrReg = (InstrData&0x0007);

	//Lets get the Mask List from ROM
	short RegisterMask = cpu->FetchWord();

	if(Direction == 0)
	{
		//we are going from register to memeory 
		for(int x = 0;x<16;x++)
		{
			char RegBit = (RegisterMask >> x)&0x0001;
			if(RegBit)
			{
				unsigned int Operand; //= cpu->GetOperandUsingEffectiveAddress(AddrMode,AddrReg,Size+1);
				if(x< 8)
				{
					
					Operand = cpu->AddressRegisterRead((7-x));
					swprintf_s(OutputString,100,L"\tMOVEM: Moving Operand 0x%X from data Register %d to memory\n",Operand,(7-x));
				}
				else
				{
					
					Operand = cpu->DataRegisterRead((15-x));
					swprintf_s(OutputString,100,L"\tMOVEM: Moving Operand 0x%X from address Register %d to memory \n",Operand,(15-x));
				}

				OutputDebugString(OutputString);
				cpu->SetOperandUsingEffectiveAddress(AddrMode,AddrReg,Size,Operand);
			}
		}

	}
	else
	{
		//we are going from memory to register
		for(int x = 0;x<16;x++)
		{
			char RegBit = (RegisterMask >> x)&0x0001;
			if(RegBit)
			{
				unsigned int Operand = cpu->GetOperandUsingEffectiveAddress(AddrMode,AddrReg,Size+1);
				if(x< 8)
				{
					swprintf_s(OutputString,100,L"\tMOVEM: Moving Operand 0x%X to  data Register %d \n",Operand,(x));
					cpu->DataRegisterWrite(x,Operand);
				}
				else
				{
					swprintf_s(OutputString,100,L"\tMOVEM: Moving Operand 0x%X to  address Register %d \n",Operand,(x-8));
					cpu->AddressRegisterWrite(x-8,Operand);
				}
				OutputDebugString(OutputString);
			}
		}
	}
	

}