#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H
#include "CookieNumbers.h"
#include "IAchievementRewarder.h"
#include "IResettable.h"
#include "IWalletMutator.h"
#include "IWalletReader.h"
#include "Subject.h"

class Wallet : public Subject, public IAchievementRewarder, public IWalletReader, public IWalletMutator, public IResettable
{
public:
    inline static const CookieNumber maxAchievementBonus {"0.5"};

    CookieNumber getCookieAmount() const override;
    CookieNumber getCps() const override;
    CookieNumber getEffectiveCps() const override;
    CookieNumber getCookiesViaInput() const override;
    void incrementCookieAmount(const CookieNumber &amount) override;
    void incrementCookieViaInput(const CookieNumber &amount) override;
    void decrementCookieAmount(const CookieNumber &amount) override;
    void incrementCps(const CookieNumber &amount) override;
    void decrementCps(const CookieNumber &amount) override;
    CookieNumber getTotalcookies() const;
    CookieNumber getAchievementBonusMultiplier() const override;
    void addAchievementBonus(const CookieNumber &step);
    void reset() override;

private:
    CookieNumber _cps = 0;
    CookieNumber _cookiesViaInput = 0;
    CookieNumber _cookieAmount = 0;
    CookieNumber _totalcookies = 0;
    CookieNumber _achievementBonusMultiplier = 0;
    void setCps(const CookieNumber &cps);
    void setCookieAmount(const CookieNumber &cookieAmount);
    void setTotalcookies(const CookieNumber &totalcookies);
    void setAchievementBonusMultiplier(const CookieNumber &multiplier);
    friend class Save;
};

#endif
