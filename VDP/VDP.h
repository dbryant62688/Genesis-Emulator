#ifndef _VDP_H
#define _VDP_H


class VDProcessor
{
public:
	void Reset();
	short DataRegisterRead(int index);
	void DataRegisterWrite(int index, short value);

private:
	short DataRegisters[25];
};
#endif