#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "..\CPU68K\68KCPU.h"

struct BINHeader
{
	unsigned int InitialStackPtr;		//0x00 - 0x03
	unsigned int EntryPointPtr;			//0x04 - 0x07
	unsigned int BusErrorExceptionPtr;	//0x08 - 0x0b
	unsigned int AddressErrorExceptionPtr; //0x0c - 0x0f

	unsigned int IllegalInstructionExceptionPtr;		//0x10 - 0x13
	unsigned int DivByZeroExceptionPtr;					//0x14 - 0x17
	unsigned int CHKExceptionPtr;						//0x18 - 0x1b
	unsigned int TRAPVExceptionPtr;						//0x1c - 0x1f
		
	unsigned int PrivilegeExceptionPtr;		//0x20 - 0x23
	unsigned int TRACEExceptionPtr;			//0x24 - 0x27
	unsigned int LineAExceptionPtr;			//0x28 - 0x2b
	unsigned int LineFExceptionPtr;			//0x2c - 0x2f

	unsigned int Unused[12];				//0x30 -0x5F
	unsigned int SpuriousExceptionPtr;		//0x60 - 0x63
	unsigned int IRQPtrs[7];				//0x64 - 0x7F
	unsigned int TRAPExceptionPtr[16];		//0x80 - 0xBF
	unsigned int Unused2[16];				//0xC0 - 0xFF


	unsigned char ConsoleName[16];			//0x100 - 0x10F
	unsigned char CopywrightNotice[16];		//0x110 - 0x11F
	unsigned char DomesticGameName[48];		//0x120 - 0x14F
	unsigned char ForeignGameName[48];		//0x150	- 0x17F
	unsigned char ProductType[2];			//0x180 - 0x181
	unsigned char Reserved1;				//0x182
	unsigned char ProductCode[8];			//0x183 - 0x18A
	unsigned char Reserved2;				//0x18B
	unsigned char VersionNumber[2];			//0x18C - 0x18D
	unsigned char CheckSum[2];				//0x18E - 0x18F
	unsigned int  ROM_StartAddress;			//0x190 - 0x193
	unsigned int  ROM_End_Address;			//0x194 - 0x197
	unsigned int  RAM_Start_Address;		//0x198 - 0x19B
	unsigned int  RAM_End_Address;			//0x19C - 0x19F
	unsigned char SRAM_Info[4];				//0x1A0 - 0x1A3
	unsigned int  SRAM_Start_Address;		//0x1A4 - 0x1A7
	unsigned int  SRAM_End_Address;			//0x1A8 - 0x1AB
	unsigned char Modem_Info[12];			//0x1AC - 0x1B8
	unsigned char Notes[40];				//0x1B9 - 0x1E0
	unsigned char Country_Codes[16];		//0x1E1 - 0x1F0
	unsigned char Padding[15];				//0x1F1 - 0x1FF

};

void ByteSwap16_Array(void *buffer, unsigned int size)
{
	if(buffer && size)
	{
		
		short * ptr = (short*)buffer;
		for(int x = 0;x<size/2;x++)
		{
			short CurrentWord = *ptr;
			short HiByte = (CurrentWord&0xFF00)>>8;
			short lowByte = CurrentWord&0x00FF;
			*ptr = lowByte<<8 | HiByte;
			ptr++;
		}
	}
}

unsigned char TestRom[] = {0x2901 , 0xEF01};
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpcmdLine,int nCmdShow)
{
	FILE *fp;
	BINHeader *RomHeader;
	CPU68K m68cpu;

	wchar_t OutputString[100] = {0};

	OutputDebugString(L"Opening ROM File\r\n");
	fp = fopen("C:/gensdk/sample/sprite/out/rom.bin"/*"C:/GenesisEmulator/Sonic.bin"*/,"rb");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		int Size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		if(Size&1)
			Size++;

		swprintf_s(OutputString,100,L"\tRom File Size: %i\n",Size);
		OutputDebugString(OutputString);
		unsigned char *RomData = new unsigned char[Size];
		
		int res = 0;
		res = fread(RomData,sizeof(char),Size,fp);
		fclose(fp);


		if(res > 0)
		{
			//ByteSwap16_Array(RomData,Size);
			OutputDebugString(L"\n\nROM File Info\r\n");
			RomHeader = (BINHeader*)RomData;
			
			
			//swprintf_s(OutputString,100,L"\tRom Name: %hs\n",RomHeader->DomesticGameName); //This wont write correctly till i write a function to convert from multibyte to wide char
			//OutputDebugString(OutputString);

			//Now that we have read the ROM and got some basic information. Lets initialize our system
			m68cpu.Initialize((unsigned int)RomData);

			m68cpu.Reset();


			//here we run the main loop which for now just runs through the rom decoding the opcodes and printing them
			
			for(int code = 0;code< 5000000;code++)
			{
				//Fetch the contents of PC and decode it
				short OpCode = m68cpu.FetchInstruction();
				InstructionPtr instruct = m68cpu.DecodeInstruction(OpCode);
				m68cpu.ExecuteInstruction(OpCode,instruct);

			}

		}
		else
		{
			swprintf_s(OutputString,100,L"\tERROR reading File: Error code %i\n",res);
			OutputDebugString(OutputString);
		}
		delete [] RomData;
		
	}
	else
	{
		OutputDebugString(L"Couldnt Load Bin File\n");
	}
	system("pause");
	return 0;
}