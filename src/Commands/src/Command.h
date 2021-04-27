#ifndef C_OOKIECLIKER_COMMAND_H
#define C_OOKIECLIKER_COMMAND_H

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    ~Command() =default;
};


#endif //C_OOKIECLIKER_COMMAND_H
