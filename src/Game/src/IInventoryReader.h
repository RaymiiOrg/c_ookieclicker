#ifndef C_OOKIECLIKER_IINVENTORYREADER_H
#define C_OOKIECLIKER_IINVENTORYREADER_H

#include "CookieNumbers.h"
#include <map>
#include <string>

class IInventoryReader
{
public:
    virtual ~IInventoryReader() = default;
    virtual CookieNumber getItemCount(const std::string &itemName) const = 0;
    virtual const std::map<std::string, CookieNumber> &getInventory() const = 0;
};

#endif //C_OOKIECLIKER_IINVENTORYREADER_H
