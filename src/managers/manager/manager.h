#ifndef FCARD_MANAGER_H_
#define FCARD_MANAGER_H_

/// <summary>
/// Manager and it's child classes are derived from:
/// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
/// </summary>
class Manager
{
private:
public:
	virtual void startUp() = 0;
	virtual void shutDown() = 0;
};

#endif