#ifndef C_OOKIECLIKER_IRESETTABLE_H
#define C_OOKIECLIKER_IRESETTABLE_H

class IResettable
{
public:
    virtual ~IResettable() = default;
    virtual void reset() = 0;
};

#endif //C_OOKIECLIKER_IRESETTABLE_H
