#include "68kCPU.h"
#include "MemoryRegion.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

extern Instruction GlobalInstructionList[];




void CPU68K::Initialize(unsigned int romaddr)
{
	//Initialize will clear all the registers and set up the instruction list
	BaseAddress = romaddr;
	ProgramCounter = 0;

	for(int x = 0; x< 8;x++)
		DataRegisterBank[x] = 0;

	for(int x = 0; x< 7;x++)
		AddressRegisterBank[x] = 0;

	StackPointer = 0;

	//clear internal ram
	memset(internalramaddr,0,0xFFFF);

	InstructionList = GlobalInstructionList;

	Memory.regioncnt = 2;

	//ROM region
	Memory.memregion[0].StartAddress	= 0x000000;
	Memory.memregion[0].EndAddress		= 0x3FFFFF;
	Memory.memregion[0].RealOffset		= romaddr;
	Memory.memregion[0].Flag			= MEMORY;
	Memory.memregion[0].WriteFunc		= NULL;
	Memory.memregion[0].ReadFunc		= NULL;

	//Z80 region
	/*Memory.memregion[1].StartAddress	=0xA00000;
	Memory.memregion[1].EndAddress		=0xA0FFFF;
	Memory.memregion[1].RealOffset		=*/

	//68000 ram space
	Memory.memregion[1].StartAddress	=0xFF0000;
	Memory.memregion[1].EndAddress		=0xFFFFFF;
	Memory.memregion[1].RealOffset		= (unsigned int)(&internalramaddr);
	Memory.memregion[1].Flag			= MEMORY;
	Memory.memregion[1].WriteFunc		= NULL;
	Memory.memregion[1].ReadFunc		= NULL;

}

void CPU68K::Reset()
{
	// THis funtion will simulate a hardware or software reset. It will clear the registers read from the mem location $000000 the supervisor stack pointer
	//and read mem location $000004 for the entry point. at this point we are ready for the Fetch/decode/execute cycle
	//MEMORY MAP WILL NEED TO BE SETUP BEFORE THIS FUNCTION IS CALLED. CPU DOES NOT INITIALIZE MEM MAP
	wchar_t OutputString[100] = {0};
	//Clear all registers
	
	//Get Stack Pointer
	unsigned int SSP = FetchLong();

	//Get Entry Point
	unsigned int EntryPoint =FetchLong();

	//Now lets set up our stack pointer and entry point
	swprintf_s(OutputString,100,L"\tResetting PC to contents of (0x%X)\n",EntryPoint);
	OutputDebugString(OutputString);
	
	StackPointerWrite(SSP);
	ProgramCounterWrite(EntryPoint);
}


short CPU68K::FetchWord()
{
	unsigned short Contents =MemoryReadWord(ProgramCounter);
	ProgramCounter +=2; //This is processor fetches words so we need to increment by two to support that
	return Contents;
}

char CPU68K::FetchByte()
{
	//Bytes are inside words so we need to Fetch 
	char Contents = MemoryReadWord(ProgramCounter);
	ProgramCounter +=2; //This is processor fetches words so we need to increment by two to support that
	return Contents;
}
unsigned int CPU68K::FetchLong()
{
	unsigned int Contents = MemoryReadLong(ProgramCounter);
	ProgramCounter +=4; //This is processor just fetched two words so we need to increment by four to support that
	return Contents;
}
/***
FetchInstruction
*/
short CPU68K::FetchInstruction()
{
		//Error checking will be added later. THis is just a basic implementation
		wchar_t OutputString[100] = {0};
		short PCounter = ProgramCounter;
		short Contents = FetchWord();
		//swprintf_s(OutputString,100,L"\tFETCHED:(0x%X) Opcode (0x%X)\n",PCounter,Contents);
		//OutputDebugString(OutputString);
		
		return Contents;
}

InstructionPtr CPU68K::DecodeInstruction(short opcode)
{
	//THis function will look through the opcode table and find the "closest" match and return the Instruction reference
	wchar_t OutputString[300] = {0};
	InstructionPtr ptr = NULL;

	for(int x = 0;x<100;x++)
	{
		if(CheckOpcode(opcode,InstructionList[x]))
		{
			swprintf_s(OutputString,300,L"\tSuccessfully Decoded:(0x%.4X): Name: %s \n",opcode,InstructionList[x].Name);
			OutputDebugString(OutputString);
			ptr = &InstructionList[x];
			break;
		}
	}
	return ptr;
}
void CPU68K::ExecuteInstruction(short Op,InstructionPtr instruction)
{
	//Each instructin has a function reference to its appropriate behavior. we will call this function and return 
	//A return value is not necessary because the CCR register will be updated if there is an error
	if(instruction && instruction->ExecutionPtr)
		instruction->ExecutionPtr(this,Op,instruction);
	return;	
}


unsigned char CPU68K::MemoryReadByte(unsigned int Address)
{
	return Memory.MemoryReadByte(Address);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		unsigned char Data = (*(unsigned char*)(memLocation));
		return Data;
	}
	else
		return 0;*/
}

unsigned short CPU68K::MemoryReadWord(unsigned int Address)
{
	return Memory.MemoryReadWord(Address);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		//This is done to prevent memory alignment issues.(need to find a faster way to do this...TO MANY CYCLES!!!!)
		unsigned char Byte1 = (unsigned char)(*(unsigned char*)memLocation);
		unsigned char Byte2 = (unsigned char)(*(unsigned char*)(memLocation+1));
		unsigned short Data =  Byte1<<8 | Byte2;	//Assume all data comng from memory is Big Endian so lets swap. This will swap it
		return Data;
	}
	else
		return 0;
		*/
}

unsigned int CPU68K::MemoryReadLong(unsigned int Address)
{
	return Memory.MemoryReadLong(Address);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		//This is done to prevent memory alignment issues.(need to find a faster way to do this...TO MANY CYCLES!!!!)
		unsigned char Byte1 = (unsigned char)(*(unsigned char*)memLocation);
		unsigned char Byte2 = (unsigned char)(*(unsigned char*)(memLocation+1));
		unsigned char Byte3 = (unsigned char)(*(unsigned char*)(memLocation+2));
		unsigned char Byte4 = (unsigned char)(*(unsigned char*)(memLocation+3));

		unsigned long Data =  Byte1<<24 | Byte2<<16 | Byte3<<8 | Byte4;	//Assume all data is BIG endian so lets swap
		return Data;
	}
	else
		return 0;*/
}
void CPU68K::MemoryWriteByte(unsigned int Address, unsigned char Value)
{
	Memory.MemoryWriteByte(Address,Value);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		(*(unsigned char*)memLocation) = Value;
	
	}*/	
}
void CPU68K::MemoryWriteWord(unsigned int Address, unsigned short Value)
{
	Memory.MemoryWriteWord(Address,Value);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		unsigned char Data1 = (Value&0xFF00)>> 8;
		unsigned char Data2 = (Value&0x00FF);

		//Assume all writes are Little endian so lets swap
		(*(unsigned char*)memLocation) = Data2;
		(*(unsigned char*)(memLocation+1)) = Data1;
	
	}	*/
}
void CPU68K::MemoryWriteLong(unsigned int Address, unsigned int Value)
{
	Memory.MemoryWriteLong(Address,Value);
	/*unsigned int memLocation =  Memory.GetRealAddress(Address);
	if(memLocation)
	{
		unsigned char Data1 = (Value&0xFF000000)>> 24;
		unsigned char Data2 = (Value&0x00FF0000)>>16;
		unsigned char Data3 = (Value&0x0000FF00)>>8;
		unsigned char Data4 = (Value&0x000000FF);

		//assume all writes are little endian so we need to swap
		(*(unsigned char*)memLocation)	   = Data4;
		(*(unsigned char*)(memLocation+1)) = Data3;
		(*(unsigned char*)(memLocation+2)) = Data2;
		(*(unsigned char*)(memLocation+3)) = Data1;

	
	}*/	
}
void CPU68K::DataRegisterWrite(int n, unsigned int value)
{
	//This function will write into the specified data register
	DataRegisterBank[n] = value;
}
unsigned int CPU68K::DataRegisterRead(int n)
{
	//This function will read from the specified data register
	return DataRegisterBank[n];
}

void CPU68K::AddressRegisterWrite(int n,unsigned int value)
{
	//THis ifunction will write to the specified address register
	AddressRegisterBank[n] = value;
}
unsigned int CPU68K::AddressRegisterRead(int n)
{
	//This function will read from the specified address register
	return AddressRegisterBank[n];
}

void CPU68K::StatusRegisterWrite(unsigned short value,unsigned short flag)
{
	//this function will write to the status register(lower 8 bits of CCR). there is a seperate function to write to the top 8 bits(supervisor mode)
	ConditionCodeRegister &= value&flag;
}
unsigned short CPU68K::StatusRegisterRead()
{
	//This function will read the status register
	return ConditionCodeRegister;
}

void CPU68K::ProgramCounterWrite(unsigned int value)
{
	//THis function will set the progam counter
	ProgramCounter = value;
}
unsigned int CPU68K::ProgramCounterRead()
{
	//This function will read the program counter register
	return ProgramCounter;
}
void CPU68K::ProgramCounterIncrement()
{
	//THis function will incrementh the program counter register
	ProgramCounter++;
}
void CPU68K::ProgramCounterDecrement()
{
	//This function will decrement theg Program COunter register
	ProgramCounter--;
}

void CPU68K::StackPointerWrite(unsigned int value)
{
	//THis function will write to the Stack Pointer register
	StackPointer = value;
}
unsigned int CPU68K::StackPointerRead()
{
	//THis function will read the stack pointer register
	return StackPointer;
}

/**
	GetEffectiveAddress - Returns the Effective Address of the operand being used in the current instruction
*/
unsigned int CPU68K::GetEffectiveAddress(char AddrMode,char AddrReg,char OpSize)
{
	wchar_t OutputString[100] = {0};
	unsigned int EA = 0;
	switch(AddrMode)
	{
	case 0:	//Data Register Direct
		{
			//In the Data Register Direct mode, the effective address is specified in the Data register
			//EA = Dn
			EA = AddrReg;
		}
		break;
	case 1:	//Address Register direct
		{
			//In the Address Register Direct mode, the effective address is specified in the Address register
			//EA = An
			EA = AddrReg;
		}
		break;

	case 2: //Address Register Indirect
		{
			//In the Address Register Indirect mode the effective address is contained in memory and the Address register
			//contains the address memory to look
			//EA = (An)
			EA = AddressRegisterRead(AddrReg);
			
		}
		break;
	case 3:	//Address Register Mode with Post Increment
		{
			//in this mode the operand is contained in memory and the address register points to the memory location
			//after the Addr register contents is retreived it is incremented by the size of the EA that is found in memory
			//EA = (An)+
			EA = AddressRegisterRead(AddrReg);
			unsigned int NewEA = EA;
			if(OpSize == 0)
				NewEA +=1;
			else if(OpSize == 1)
				NewEA +=2;
			else if(OpSize == 2)
				NewEA +=4;
			
			AddressRegisterWrite(AddrReg,NewEA);
		}
		break;
	case 4:	//Address Register Mode with Pre Decrement
		{
			//in this mode the operand is contained in memory and the address register points to the memory location
			//Before the Addr register contents is retreived it is decremented by the size of the EA that is found in memory
			EA = AddressRegisterRead(AddrReg);
			if(OpSize == 0)
				EA -=1;
			else if(OpSize == 1)
				EA -=2;
			else if(OpSize == 2)
				EA -=4;
			AddressRegisterWrite(AddrReg,EA);
			
		}
		break;
	case 5:	//Address Register Mode with Displacement
		{
			//in this mode the operand is contained in memory and the address register points to the memory location
			//plus the extension containing the displacement
			//EA = (An) + d16
			unsigned int AddrInMem = AddressRegisterRead(AddrReg);
			unsigned int Displacement = (unsigned int)FetchWord();

			EA = AddrInMem + Displacement;			
		}
		break;
		case 6:	//Address Register Mode with 8 bit Displacement
		{
			//in this mode the operan is contained in memory and the address register points to the memory location
			//plus the extension containing the index register
			//EA = (An) + (xn) + d8
			unsigned int AddrInMem = AddressRegisterRead(AddrReg);
			unsigned short ExtensionWord = FetchWord();
			unsigned int IndexRegisterContents = 0;

			char ExtensionWordMode = (ExtensionWord&0x8000)>>15;	//This will tell us which registers to use (Data or Address)
			char ExtensionWordIndexReg = (ExtensionWord&0x7000)>>12; //THis will give me the Index Reg
			char ExtensionWordSize = (ExtensionWord&0x0800)>>11;	//THis is the size of the data
			char ExtensionWordScale = (ExtensionWord&0x0600)>>9;	//This is the scale of the extension word
			char ExtensionWordType = (ExtensionWord&0x0100)>>8;		//THis is the type of extension word this will tell us if we are using a breif or full

			int scalefactor = 1;
			if(ExtensionWordScale > 0)
			  scalefactor= 2^(ExtensionWordScale);

			if(ExtensionWordType == 0)
			{
				//THis a breif extension word so we are just looking for the displacement value to add to the Index
				//EA = (PC) + (Xn) + d8
				char ExtensionWordDisplacement = (ExtensionWord&0x00FF);
				int Displacement = (int)ExtensionWordDisplacement;
				

				unsigned int Xn = 0;
				if(ExtensionWordMode == 0)
				{
					Xn =DataRegisterRead(ExtensionWordIndexReg)*scalefactor; 
									
				}
				else if(ExtensionWordMode == 1)
				{
					Xn =AddressRegisterRead(ExtensionWordIndexReg)*scalefactor; 	
				}
				EA = AddrInMem + Xn + Displacement;
			}
			else if(ExtensionWordType == 1)
			{
				//THis is a full extension word so we need to gather more information
				//EA = (PC) + (Xn) + bd
				char BaseRegisterSuppress = (ExtensionWord&0x0080)>>7;
				char IndexSuppress = (ExtensionWord&0x0040)>>6;
				char BaseDisplacementSize = (ExtensionWord&0x0030)>>4;
				char IndexIndirectSelection = (ExtensionWord&0x0007);
			}			
		}
		break;
		case 7:
			{
				//We must now look at the EARegField
				switch(AddrReg)
				{
					case 0:	//Absolute short address mode
						{
							//In this addressing mode, the operand is in memory, and the address of the operand is in the
							//extension word. The 16-bit address is sign-extended to 32 bits before it is used.
							EA =  FetchWord();
						}
						break;
					case 1:	//absolute long address mode
						{
							//In this addressing mode, the operand is in memory, and the address of the operand is in the
							//extension word. The 1st extension contains the high order address the second contains the low
							EA = FetchLong();
						}
						break;
					case 2:	//Program Counter Indirect With Displacement
						{
							/*In this mode, the operand is in memory. The address of the operand is the sum of the
							address in the program counter (PC) and the sign-extended 16-bit displacement integer in
							the extension word. The value in the PC is the address of the extension word. This is a
							program reference allowed only for reads. */
							//EA = (PC)+d16
							EA = ProgramCounterRead();
							unsigned int Displacement = FetchWord();
							EA = EA+Displacement;
						}
						break;
					case 3:// Program Counter Indirect With Index Mode
						{
							/* The operand is in memory.The operand’s address is the sum of the address in the PC, the sign-extended displacement
							integer in the extension word’s lower eight bits, and the sized, scaled, and sign-extended
							index operand. The value in the PC is the address of the extension word. This is a program
							reference allowed only for reads. The user must include the displacement, the PC, and the
							index register when specifying this addressing mode*/
							unsigned int AddrInMem = ProgramCounterRead();
							unsigned short ExtensionWord = FetchWord();
							unsigned int IndexRegisterContents = 0;

							char ExtensionWordMode = (ExtensionWord&0x8000)>>15;	//This will tell us which registers to use (Data or Address)
							char ExtensionWordIndexReg = (ExtensionWord&0x7000)>>12; //THis will give me the Index Reg
							char ExtensionWordSize = (ExtensionWord&0x0800)>>11;	//THis is the size of the data
							char ExtensionWordScale = (ExtensionWord&0x0600)>>9;	//This is the scale of the extension word
							char ExtensionWordType = (ExtensionWord&0x0100)>>8;		//THis is the type of extension word this will tell us if we are using a breif or full

							int scalefactor = 1;
							if(ExtensionWordScale > 0)
							  scalefactor= 2^(ExtensionWordScale);

							if(ExtensionWordType == 0)
							{
								//THis a breif extension word so we are just looking for the displacement value to add to the Index
								//EA = (PC) + (Xn) + d8
								char ExtensionWordDisplacement = (ExtensionWord&0x00FF);
								int Displacement = (int)ExtensionWordDisplacement;
				

								unsigned int Xn = 0;
								if(ExtensionWordMode == 0)
								{
									Xn =DataRegisterRead(ExtensionWordIndexReg)*scalefactor; 
									
								}
								else if(ExtensionWordMode == 1)
								{
									Xn =AddressRegisterRead(ExtensionWordIndexReg)*scalefactor; 	
								}
								EA = AddrInMem + Xn + Displacement;
							}
							else if(ExtensionWordType == 1)
							{
								//THis is a full extension word so we need to gather more information
								//EA = (PC) + (Xn) + bd
								char BaseRegisterSuppress = (ExtensionWord&0x0080)>>7;
								char IndexSuppress = (ExtensionWord&0x0040)>>6;
								char BaseDisplacementSize = (ExtensionWord&0x0030)>>4;
								char IndexIndirectSelection = (ExtensionWord&0x0007);
							}
						}
						break;
					case 4:	//immediate Mode
						{
							/*In this addressing mode, the operand is in one or two extension words.*/
							// either way we just pass back the address which is in the program counter
							
							
							if(OpSize == 0)//If we are reading a byte than we need to read from the lower bits so lets add 1
								EA = this->ProgramCounterRead() + 1;
							else	//read normally
								EA = this->ProgramCounterRead();

							//We always fetch a word so we need to increment by two
							this->ProgramCounterIncrement();
							this->ProgramCounterIncrement();
						}
						break;
					case 5:
					case 6:
					case 7:
						break;
				}
			}
			break;
	
	}
	return EA;
}
/**
	THe purpose of this function is to get the Operand which can be one of the 14 addresing modes that this chip utilizes
*/
unsigned int CPU68K::GetOperandUsingEffectiveAddress(char AddrMode,char AddrReg,char OpSize,bool SignExtend)
{
	unsigned Operand = 0;
	unsigned int EA = 0;
	EA = GetEffectiveAddress(AddrMode,AddrReg,OpSize);

	if(AddrMode <2)
	{
		if(AddrMode == 0)
		{
			Operand = DataRegisterRead(EA);
			if(OpSize == 0) //byte
			{
				if(SignExtend)
				{
					char opword = Operand & 0x000000FF;
					Operand = (int)opword;

				}
				Operand &= 0x000000FF;
			}
			else if(OpSize == 1)	//Word
			{
				if(SignExtend)
				{
					short opword = Operand & 0x0000FFFF;
					Operand = (int)opword;

				}
				else
					Operand &= 0x0000FFFF;
			}			
		}
		else if(AddrMode == 1)
		{
			Operand = AddressRegisterRead(EA);
			if(OpSize == 0) //byte
			{
				Operand &= 0x000000FF;
			}
			else if(OpSize == 1)	//Word
			{
				Operand &= 0x0000FFFF;
			}			
		}
	}
	else
	{
		if(OpSize == 0)
			Operand = MemoryReadByte(EA);
		else if(OpSize == 1)
			Operand = MemoryReadWord(EA);
		else if(OpSize == 2)
			Operand = MemoryReadLong(EA);
	}
	return Operand;
}
void CPU68K::SetOperandUsingEffectiveAddress(char AddrMode, char AddrReg,char OpSize,unsigned int Operand)
{
	unsigned int EA = 0;
	EA = GetEffectiveAddress(AddrMode,AddrReg,OpSize);

	if(AddrMode <2)
	{
		unsigned int Data = 0;
		if(AddrMode == 0)
		{
			Data = DataRegisterRead(EA);
			if(OpSize == 0) //byte
			{
				Data &= 0xFFFFFF00;
				Data = Data | (Operand&0x000000FF);
			}
			else if(OpSize == 1)	//Word
			{
				Data &= 0xFFFF0000;
				Data = Data | (Operand&0x0000FFFF);
			}
			else if(OpSize == 2)
			{
				Data = Operand;
			}
			DataRegisterWrite(EA,Data);
		}
		else if(AddrMode == 1)
		{
			Data = AddressRegisterRead(EA);
			if(OpSize == 0) //byte - the restof the long should be unaffected
			{
				Data &= 0xFFFFFF00;
				Data = Data | (Operand&0x000000FF);
			}
			else if(OpSize == 1)	//Word the restof the long should be unaffected
			{
				Data &= 0xFFFF0000;
				Data = Data | (Operand&0x0000FFFF);
			}
			else if(OpSize == 2)
			{
				Data = Operand;
			}
			AddressRegisterWrite(EA,Data);
		}
	}
	else
	{
		if(OpSize == 0)
			MemoryWriteByte(EA,Operand);
		else if(OpSize == 1)
			MemoryWriteWord(EA,Operand);
		else if(OpSize == 2)
			MemoryWriteLong(EA,Operand);
	}
}





void CPU68K::SetCarryFlag()
{
	ConditionCodeRegister |= 1;	
}
void CPU68K::SetOverflowFlag()
{
	ConditionCodeRegister |= 1<< 1;	
}
void CPU68K::SetZeroFlag()
{
	ConditionCodeRegister |= 1<< 2;	
}
void CPU68K::SetNegativeFlag()
{
	ConditionCodeRegister |= 1<< 3;	
}

void CPU68K::SetExtendFlag()
{
	ConditionCodeRegister |= 1<< 4;	
}



void CPU68K::ClearCarryFlag()
{
	ConditionCodeRegister &= ~(1);
}

void CPU68K::ClearOverflowFlag()
{
	ConditionCodeRegister &= ~(1<< 1);
}
void CPU68K::ClearZeroFlag()
{
	ConditionCodeRegister &= ~(1<< 2);	
}
void CPU68K::ClearNegativeFlag()
{
	ConditionCodeRegister &= ~(1<< 3);
}
void CPU68K::ClearExtendFlag()
{
	ConditionCodeRegister &= ~(1<< 4);
}