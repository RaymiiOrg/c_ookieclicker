#ifndef C_OOKIECLIKER_ACHIEVEMENTREPOSITORY_H
#define C_OOKIECLIKER_ACHIEVEMENTREPOSITORY_H

#include "CookieNumbers.h"
#include <string>
#include <vector>

struct AchievementMilestone
{
    CookieNumber amount;
    std::string name;
};

class AchievementRepository
{
public:
    static std::vector<AchievementMilestone> getCookieAmountMilestones()
    {
        return {
            { CookieNumber("1"),                                       "Wake and bake" },
            { CookieNumber("1000"),                                    "Making some dough" },
            { CookieNumber("100000"),                                  "So baked right now" },
            { CookieNumber("1000000"),                                 "Fledgling bakery" },
            { CookieNumber("100000000"),                               "Affluent bakery" },
            { CookieNumber("1000000000"),                              "World-famous bakery" },
            { CookieNumber("100000000000"),                            "Cosmic bakery" },
            { CookieNumber("1000000000000"),                           "Galactic bakery" },
            { CookieNumber("100000000000000"),                         "Universal bakery" },
            { CookieNumber("1000000000000000"),                        "Timeless bakery" },
            { CookieNumber("100000000000000000"),                      "Infinite bakery" },
            { CookieNumber("1000000000000000000"),                     "Immortal bakery" },
            { CookieNumber("100000000000000000000"),                   "Don't stop me now" },
            { CookieNumber("1000000000000000000000"),                  "You can stop now" },
            { CookieNumber("100000000000000000000000"),                "Cookies all the way down" },
            { CookieNumber("1000000000000000000000000"),               "Overdose" },
            { CookieNumber("100000000000000000000000000"),             "How?" },
            { CookieNumber("1000000000000000000000000000"),            "The land of milk and cookies" },
            { CookieNumber("100000000000000000000000000000"),          "He who controls the cookies controls the universe - \"The milk must flow!\"" },
            { CookieNumber("1000000000000000000000000000000"),         "Tonight on Hoarders" },
            { CookieNumber("100000000000000000000000000000000"),       "Are you gonna eat all that?" },
            { CookieNumber("1000000000000000000000000000000000"),      "We're gonna need a bigger bakery" },
            { CookieNumber("100000000000000000000000000000000000"),    "In the mouth of madness - \"A cookie is just what we tell each other it is.\"" },
            { CookieNumber("1000000000000000000000000000000000000"),   "Brought to you by the letter Money" },
            { CookieNumber("100000000000000000000000000000000000000"), "The dreams in which I'm baking are the best I've ever had" },
            { CookieNumber("1000000000000000000000000000000000000000"),         "Set for life" },
            { CookieNumber("100000000000000000000000000000000000000000"),       "Panic! at Nabisco" },
            { CookieNumber("1000000000000000000000000000000000000000000"),      "Bursting at the seams" },
            { CookieNumber("100000000000000000000000000000000000000000000"),    "Just about full" },
            { CookieNumber("1000000000000000000000000000000000000000000000"),   "Hungry for more" },
            { CookieNumber("100000000000000000000000000000000000000000000000"), "Feed me, Orteil" },
            { CookieNumber("1000000000000000000000000000000000000000000000000"),     "And then what?" },
            { CookieNumber("100000000000000000000000000000000000000000000000000"),   "I think it's safe to say you've got it made" },
            { CookieNumber("1000000000000000000000000000000000000000000000000000"),  "A sometimes food" },
            { CookieNumber("100000000000000000000000000000000000000000000000000000"), "Not enough of a good thing" },
            { CookieNumber("1000000000000000000000000000000000000000000000000000000"),    "Horn of plenty" },
            { CookieNumber("100000000000000000000000000000000000000000000000000000000"),  "Large and in charge" },
            { CookieNumber("1000000000000000000000000000000000000000000000000000000000"), "Absolutely stuffed" },
            { CookieNumber("100000000000000000000000000000000000000000000000000000000000"), "It's only wafer-thin - \"Just the one!\"" },
        };
    }

    static std::vector<AchievementMilestone> getCookiesPerSecondMilestones()
    {
        return {
            { CookieNumber("1"),                                    "Casual Baking" },
            { CookieNumber("10"),                                   "Hardcore Baking" },
            { CookieNumber("100"),                                  "Steady tasty stream" },
            { CookieNumber("1000"),                                 "Cookie Monster" },
            { CookieNumber("10000"),                                "Mass producer" },
            { CookieNumber("1000000"),                              "Cookie vortex" },
            { CookieNumber("10000000"),                             "Cookie pulsar" },
            { CookieNumber("100000000"),                            "Cookie quasar" },
            { CookieNumber("1000000000"),                           "Oh hey, you're still here" },
            { CookieNumber("10000000000"),                          "Let's never bake again" },
            { CookieNumber("100000000000"),                         "A world filled with cookies" },
            { CookieNumber("1000000000000"),                        "When this baby hits 36 quadrillion cookies per hour" },
            { CookieNumber("100000000000000"),                      "Fast and delicious" },
            { CookieNumber("1000000000000000"),                     "Cookiehertz : a really, really tasty hertz. - \"Tastier than a hertz donut, anyway.\"" },
            { CookieNumber("10000000000000000"),                    "Woops, you solved world hunger" },
            { CookieNumber("1000000000000000000"),                  "Turbopuns" },
            { CookieNumber("10000000000000000000"),                 "Faster menner" },
            { CookieNumber("100000000000000000000"),                "And yet you're still hungry" },
            { CookieNumber("1000000000000000000000"),               "The Abakening" },
            { CookieNumber("10000000000000000000000"),              "There's really no hard limit to how long these achievement names can be and to be quite honest I'm rather curious to see how far we can go." },
            { CookieNumber("1000000000000000000000000"),            "Fast" },
            { CookieNumber("10000000000000000000000000"),           "Knead for speed" },
            { CookieNumber("100000000000000000000000000"),          "Well the cookies start coming and they don't stop coming" },
            { CookieNumber("1000000000000000000000000000"),         "I don't know if you've noticed but all these icons are very slightly off-center" },
            { CookieNumber("10000000000000000000000000000"),        "The proof of the cookie is in the baking" },
            { CookieNumber("1000000000000000000000000000000"),      "If it's worth doing, it's worth overdoing" },
            { CookieNumber("10000000000000000000000000000000"),     "Panic at nabisco" },
            { CookieNumber("100000000000000000000000000000000"),    "Bursting at the seams" },
            { CookieNumber("1000000000000000000000000000000000"),   "Just about full" },
            { CookieNumber("10000000000000000000000000000000000"),  "Hungry for more" },
            { CookieNumber("1000000000000000000000000000000000000"),    "Leisurely pace" },
            { CookieNumber("10000000000000000000000000000000000000"),   "Hypersonic" },
            { CookieNumber("100000000000000000000000000000000000000"),  "Gotta go fast" },
            { CookieNumber("1000000000000000000000000000000000000000"), "Bake him away, toys" },
            { CookieNumber("10000000000000000000000000000000000000000"),    "You're #1 so why try harder" },
            { CookieNumber("1000000000000000000000000000000000000000000"),  "Haven't even begun to peak" },
            { CookieNumber("10000000000000000000000000000000000000000000"), "What did we even eat before these" },
            { CookieNumber("100000000000000000000000000000000000000000000"), "Heavy flow" },
            { CookieNumber("1000000000000000000000000000000000000000000000"), "More you say?" },
        };
    }

    static std::vector<AchievementMilestone> getCookiesViaInputMilestones()
    {
        return {
            { CookieNumber("10"),                       "Nice Keyboard!" },
            { CookieNumber("1000"),                     "Clicktastic" },
            { CookieNumber("100000"),                   "Clickathlon" },
            { CookieNumber("10000000"),                 "Clickolympics" },
            { CookieNumber("1000000000"),               "Clickorama" },
            { CookieNumber("100000000000"),             "Clickasmic" },
            { CookieNumber("10000000000000"),           "Clickageddon" },
            { CookieNumber("1000000000000000"),         "Clicknarok" },
            { CookieNumber("100000000000000000"),       "Clickastrophe" },
            { CookieNumber("10000000000000000000"),     "Clickataclysm" },
            { CookieNumber("1000000000000000000000"),   "The ultimate clickdown" },
            { CookieNumber("100000000000000000000000"), "All the other kids with the pumped up clicks" },
            { CookieNumber("10000000000000000000000000"),  "One...more...click..." },
            { CookieNumber("1000000000000000000000000000"), "Clickety split" },
        };
    }
};

#endif //C_OOKIECLIKER_ACHIEVEMENTREPOSITORY_H
