#ifndef C_OOKIECLIKER_STATUSVIEW_H
#define C_OOKIECLIKER_STATUSVIEW_H
#include "IWalletReader.h"
#include "View.h"

/** Current amount of cookies and cookies per second **/
class StatusView : public View
{
private:
    const IWalletReader *wallet;
    const std::string _name {"Status"};

public:
    const std::string &name() override { return _name; };
    explicit StatusView(const IWalletReader *wallet) :
        wallet(wallet) {};
    void render() override;
    void handleInput(const std::string &input) override;
};

#endif //C_OOKIECLIKER_STATUSVIEW_H
