#include "stdafx.h"
#include "..\CPU68K\68KCPU.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace GenEmTest
{
	[TestClass]
	public ref class UnitTest1
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void AbsoluteShortAddressModeByteTest()
		{
			//THe goal here is to test if the Absolute short Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x38,0x00,0x04,0x34,0x12,0x78,0x56};	//Move byte from Contents of Address (0x04) to D0 - this uses Absolute word addressing
			unsigned int ExpectedValue = 0x234;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x200);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};

		[TestMethod]
		void AbsoluteShortAddressModeWordTest()
		{
			//THe goal here is to test if the Absolute short Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x38,0x00,0x04,0x12,0x34,0x78,0x56};	//Move WORD from Contents of Address (0x04) to D0 - this uses Absolute word addressing
			unsigned int ExpectedValue = 0x1234;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x200);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void AbsoluteShortAddressModeLongTest()
		{
			//THe goal here is to test if the Absolute short Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x38,0x00,0x04,0x12,0x34,0x56,0x78};	//Move LONG from Contents of Address (0x04) to D0 - this uses Absolute word addressing
			unsigned int ExpectedValue = 0x12345678;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x200);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ImmediateAddressModeByteTest()
		{
			//THe goal here is to test if the Immeidate Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x3c,0x00,0x04,0x34,0x12,0x78,0x56};	//Move 0x04 to D0 - this uses immediate addressing
			unsigned int ExpectedValue = 0x204;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x200);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ImmediateAddressModeWordTest()
		{
			//THe goal here is to test if the Immeidate Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x3c,0x12,0x34,0x78,0x56};	//Move 0x1234 to D0 - this uses immediate addressing
			unsigned int ExpectedValue = 0x1234;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x01);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ImmediateAddressModeLongTest()
		{
			//THe goal here is to test if the Immeidate Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x3c,0x12,0x34,0x56,0x78};	//Move 0x12345678 to D0 - this uses immediate addressing
			unsigned int ExpectedValue = 0x12345678;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x200);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void DRDirectAddressModeByteTest()
		{
			//THe goal here is to test if the DAta Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x01};	//Move.b D1 to D0 - this uses data register direct addressing
			unsigned int ExpectedValue = 0x504;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->DataRegisterWrite(1,0x204);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void DRDirectAddressModeWordTest()
		{
			//THe goal here is to test if the DAta Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x01};	//Move.w D1 to D0 - this uses data register direct addressing
			unsigned int ExpectedValue = 0x2134;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->DataRegisterWrite(1,ExpectedValue);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void DRDirectAddressModeLongTest()
		{
			//THe goal here is to test if the DAta Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x01};	//Move.l D1 to D0 - this uses data register direct addressing
			unsigned int ExpectedValue = 0x21345612;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->DataRegisterWrite(1,ExpectedValue);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};

		[TestMethod]
		void ARDirectAddressModeByteTest()
		{
			//THe goal here is to test if the Address Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x09};	//Move.b A1 to D0 - this uses address register direct addressing
			unsigned int ExpectedValue = 0x504;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x204);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARDirectAddressModeWordTest()
		{
			//THe goal here is to test if the Address Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x09};	//Move.w A1 to D0 - this uses address register direct addressing
			unsigned int ExpectedValue = 0x2134;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,ExpectedValue);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARDirectAddressModeLongTest()
		{
			//THe goal here is to test if the Address Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x09};	//Move.l A1 to D0 - this uses address register direct addressing
			unsigned int ExpectedValue = 0x21345612;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,ExpectedValue);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};

		[TestMethod]
		void ARInDirectAddressModeByteTest()
		{
			//THe goal here is to test if the Address Register InDirect Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x010,0x11,0x34,0x56,0x78,0x12};	//Move.b (A1) to D0 
			unsigned int ExpectedValue = 0x556;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x03);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeWordTest()
		{
			//THe goal here is to test if the Address Register InDirect Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x11,0x34,0x78,0x56,0x12};	//Move.w (A1) to D0
			unsigned int ExpectedValue = 0x7856;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x03);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeLongTest()
		{
			//THe goal here is to test if the Address Register Direct Address Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x11,0x56,0x34,0x12,0x78};	//Move.l (A1) to D0
			unsigned int ExpectedValue = 0x56341278;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x02);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
	};
}
