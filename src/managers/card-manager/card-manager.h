#ifndef FCARD_CARDMANAGER_H_
#define FCARD_CARDMANAGER_H_

#include "../manager/manager.h"

class CardManager : public Manager
{
private:
    static CardManager *instancePtr;
    CardManager();

public:
    static CardManager *getInstance();

    ~CardManager();

    const void startUp() override;
    const void shutDown() override;
};
#endif
