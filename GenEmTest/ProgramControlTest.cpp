#include "stdafx.h"
#include "..\CPU68K\68KCPU.h"
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace GenEmTest
{
	[TestClass]
	public ref class ProgramControlTest
	{
	public: 
		[TestMethod]
		void TstZeroTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x4A,0x80};	//Test D0 against 0 
			unsigned int ExpectedValue = 1;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->StatusRegisterRead()&0x0000000C)>>2;

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void TstNegativeTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x4A,0x80};	//Test D0 against 0 
			unsigned int ExpectedValue = 2;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0xFFFFFFFF);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->StatusRegisterRead()&0x0000000C)>>2;

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void TstPositiveTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x4A,0x80};	//Test D0 against 0 
			unsigned int ExpectedValue = 0;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x56);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->StatusRegisterRead()&0x0000000C)>>2;

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void Bcc8bitTest()
		{

			//test if the bcc 8 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x64,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x56);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void Bcc16bitTest()
		{

			//test if the bcc 8 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x64,0x00, 0x00,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x56);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}

		[TestMethod]
		void Bcc32bitTest()
		{

			//test if the bcc 32 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x64,0xFF,0x00,0x00,0x00,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->StatusRegisterWrite(0x00);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void Bra8BitTest()
		{

			//test if the bcc 8 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x60,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->StatusRegisterWrite(0x00);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void Bra16BitTest()
		{

			//test if the bcc 8 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x60,0x00, 0x00,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->StatusRegisterWrite(0x00);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void Bra32BitTest()
		{

			//test if the bcc 8 bit displacment command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x60,0xFF, 0x00,0x00,0x00,0x02};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->StatusRegisterWrite(0x00);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void JMPTest()
		{

			//test if the JMP command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x4E,0xF8, 0x00,0x04};	//Test D0 against 0 
			unsigned int ExpectedValue = 4;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->StatusRegisterWrite(0x00);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = (mcpu->ProgramCounterRead());

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
	};
}
