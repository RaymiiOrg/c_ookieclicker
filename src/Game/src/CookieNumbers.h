/**
    Copyright 2021  - Remy van Elst - https://raymii.org
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef C_OOKIECLIKER_COOKIENUMBERS_H
#define C_OOKIECLIKER_COOKIENUMBERS_H

#include <sstream>
#include <vector>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "cmakeConfig.h"


#ifdef USEBOOST_MPP

#include <boost/serialization/nvp.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int CookieInt;
typedef boost::multiprecision::cpp_dec_float_50 CookieFloater;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>> CookieNumber;
#else
#include "RegularCookieNumber.h"
typedef RegularCookieNumber<long double> CookieInt;
typedef RegularCookieNumber<long double> CookieFloater;
typedef RegularCookieNumber<long double> CookieNumber;
#endif


class CookieNumberPrinter {
private:

    static std::vector<std::string> cookieNumberNames() {
        std::vector<std::string> allCookieNumberNames{"thousand", "million", "billion", "trillion", "quadrillion",
                                                      "quintillion", "sextillion", "septillion", "octillion",
                                                      "nonillion"};
        std::vector<std::string> prefixes{"", "un", "duo", "tre", "quattuor", "quin", "sex", "septen", "octo", "novem"};
        std::vector<std::string> suffixes{"decillion", "vigintillion", "trigintillion", "quadragintillion",
                                          "quinquagintillion", "sexagintillion", "septuagintillion", "octogintillion",
                                          "nonagintillion", "centillion", "unviginticent", "unsexagintacent", "ducent",
                                          "trecent", "duotrigintatrecent", "quadringent", "quingent", "sescent",
                                          "septuagintisescent",
                                          "septingent", "octingent", "nongent", "millillion", "dumill",
                                          "dumillinonagintanongent",
                                          "trimill", "trimilliduotrigintatrecent", "trimillisexoctogintaoctingent",
                                          "quadrimill",
                                          "quadrimilliquattuordecicent", "quinmill", "sexmill", "septimill", "octimill",
                                          "nonimill",
                                          "myr", "decimilliquinsexagintasescent", "dumyr",
                                          "unquadragintamilliunquinquagintacent",
                                          "centimill", "micr", "nan", "pic", "femt", "att", "zept", "yoct",
                                          " ( probably will never get to these suffixes, ) ",
                                          " ( otherwise you're an awesome player! ) ",
                                          " ( please send me an email with a screenshot! ) ",
                                          " ( Psalm 121, KJV ) ",
                                          " ( 1 I will lift up mine eyes unto the hills, from whence cometh my help. ) ",
                                          " ( 2 My help cometh from the Lord, which made heaven and earth. ) ",
                                          " ( 3 He will not suffer thy foot to be moved: he that keepeth thee will not slumber. ) ",
                                          " ( 4 Behold, he that keepeth Israel shall neither slumber nor sleep. ) ",
                                          " ( 5 The Lord is thy keeper: the Lord is thy shade upon thy right hand. ) ",
                                          " ( 6 The sun shall not smite thee by day, nor the moon by night. ) ",
                                          " ( 7 The Lord shall preserve thee from all evil: he shall preserve thy soul. ) ",
                                          " ( 8 The Lord shall preserve thy going out and thy coming in from this time forth, and even for evermore. ) ",
                                          " ( 1 Corinthians 15, KJV. ) ",
                                          " ( 50 Now this I say, brethren, that flesh and blood cannot inherit the kingdom of God; neither doth corruption inherit incorruption. ) ",
                                          " ( 51 Behold, I shew you a mystery; We shall not all sleep, but we shall all be changed, ) ",
                                          " ( 52 In a moment, in the twinkling of an eye, at the last trump: for the trumpet shall sound, and the dead shall be raised incorruptible, and we shall be changed. ) ",
                                          " ( 53 For this corruptible must put on incorruption, and this mortal must put on immortality. ) ",
                                          " ( 54 So when this corruptible shall have put on incorruption, and this mortal shall have put on immortality, then shall be brought to pass the saying that is written, Death is swallowed up in victory. ) ",
                                          " ( 55 O death, where is thy sting? O grave, where is thy victory? ) ",
                                          " ( Psalm 84, KJV. ) ",
                                          " ( How amiable are thy tabernacles, O Lord of hosts! ) ",
                                          " ( 2 My soul longeth, yea, even fainteth for the courts of the Lord: my heart and my flesh crieth out for the living God. ) ",
                                          " ( 3 Yea, the sparrow hath found an house, and the swallow a nest for herself, where she may lay her young, even thine altars, O Lord of hosts, my King, and my God. ) ",
                                          " ( 4 Blessed are they that dwell in thy house: they will be still praising thee. Selah. ) ",
                                          " ( 5 Blessed is the man whose strength is in thee; in whose heart are the ways of them. ) ",
                                          " ( 6 Who passing through the valley of Baca make it a well; the rain also filleth the pools. ) ",
                                          " ( 7 They go from strength to strength, every one of them in Zion appeareth before God. ) ",
                                          " ( 8 O Lord God of hosts, hear my prayer: give ear, O God of Jacob. Selah. ) ",
                                          " ( 9 Behold, O God our shield, and look upon the face of thine anointed. ) ",
                                          " ( 10 For a day in thy courts is better than a thousand. I had rather be a doorkeeper in the house of my God, than to dwell in the tents of wickedness. ) ",
                                          " ( 11 For the Lord God is a sun and shield: the Lord will give grace and glory: no good thing will he withhold from them that walk uprightly. ) ",
                                          " ( 12 O Lord of hosts, blessed is the man that trusteth in thee. ) ",
                                          " ( Matthew 6, KJV ) ",
                                          " ( Take heed that ye do not your alms before men, to be seen of them: otherwise ye have no reward of your Father which is in heaven. ) ",
                                          " ( 2 Therefore when thou doest thine alms, do not sound a trumpet before thee, as the hypocrites do in the synagogues and in the streets, that they may have glory of men. Verily I say unto you, They have their reward. ) ",
                                          " ( 3 But when thou doest alms, let not thy left hand know what thy right hand doeth: ) ",
                                          " ( 4 That thine alms may be in secret: and thy Father which seeth in secret himself shall reward thee openly. ) ",
                                          " ( 5 And when thou prayest, thou shalt not be as the hypocrites are: for they love to pray standing in the synagogues and in the corners of the streets, that they may be seen of men. Verily I say unto you, They have their reward. ) ",
                                          " ( 6 But thou, when thou prayest, enter into thy closet, and when thou hast shut thy door, pray to thy Father which is in secret; and thy Father which seeth in secret shall reward thee openly. ) ",
                                          " ( 7 But when ye pray, use not vain repetitions, as the heathen do: for they think that they shall be heard for their much speaking. ) ",
                                          " ( 8 Be not ye therefore like unto them: for your Father knoweth what things ye have need of, before ye ask him. ) ",
                                          " ( 9 After this manner therefore pray ye: Our Father which art in heaven, Hallowed be thy name. ) ",
                                          " ( 10 Thy kingdom come, Thy will be done in earth, as it is in heaven. ) ",
                                          " ( 11 Give us this day our daily bread. ) ",
                                          " ( 12 And forgive us our debts, as we forgive our debtors. ) ",
                                          " ( 13 And lead us not into temptation, but deliver us from evil: For thine is the kingdom, and the power, and the glory, for ever. Amen. ) ",
                                          " ( 14 For if ye forgive men their trespasses, your heavenly Father will also forgive you: ) ",
                                          " ( 15 But if ye forgive not men their trespasses, neither will your Father forgive your trespasses. ) ",
                                          " ( 16 Moreover when ye fast, be not, as the hypocrites, of a sad countenance: for they disfigure their faces, that they may appear unto men to fast. Verily I say unto you, They have their reward. ) ",
                                          " ( 17 But thou, when thou fastest, anoint thine head, and wash thy face; ) ",
                                          " ( 18 That thou appear not unto men to fast, but unto thy Father which is in secret: and thy Father, which seeth in secret, shall reward thee openly. ) ",
                                          " ( 19 Lay not up for yourselves treasures upon earth, where moth and rust doth corrupt, and where thieves break through and steal: ) ",
                                          " ( 20 But lay up for yourselves treasures in heaven, where neither moth nor rust doth corrupt, and where thieves do not break through nor steal: ) ",
                                          " ( 21 For where your treasure is, there will your heart be also. ) ",
                                          " ( 22 The light of the body is the eye: if therefore thine eye be single, thy whole body shall be full of light. ) ",
                                          " ( 23 But if thine eye be evil, thy whole body shall be full of darkness. If therefore the light that is in thee be darkness, how great is that darkness! ) ",
                                          " ( 24 No man can serve two masters: for either he will hate the one, and love the other; or else he will hold to the one, and despise the other. Ye cannot serve God and mammon. ) ",
                                          " ( 25 Therefore I say unto you, Take no thought for your life, what ye shall eat, or what ye shall drink; nor yet for your body, what ye shall put on. Is not the life more than meat, and the body than raiment? ) ",
                                          " ( 26 Behold the fowls of the air: for they sow not, neither do they reap, nor gather into barns; yet your heavenly Father feedeth them. Are ye not much better than they? ) ",
                                          " ( 27 Which of you by taking thought can add one cubit unto his stature? ) ",
                                          " ( 28 And why take ye thought for raiment? Consider the lilies of the field, how they grow; they toil not, neither do they spin: ) ",
                                          " ( 29 And yet I say unto you, That even Solomon in all his glory was not arrayed like one of these. ) ",
                                          " ( 30 Wherefore, if God so clothe the grass of the field, which to day is, and to morrow is cast into the oven, shall he not much more clothe you, O ye of little faith? ) ",
                                          " ( 31 Therefore take no thought, saying, What shall we eat? or, What shall we drink? or, Wherewithal shall we be clothed? ) ",
                                          " ( 32 (For after all these things do the Gentiles seek:) for your heavenly Father knoweth that ye have need of all these things. ) ",
                                          " ( 33 But seek ye first the kingdom of God, and his righteousness; and all these things shall be added unto you. ) ",
                                          " ( 34 Take therefore no thought for the morrow: for the morrow shall take thought for the things of itself. Sufficient unto the day is the evil thereof. ) ",
                                          " ( 1 Corinthians 15, KJV.   ) ",
                                          " ( 1 Moreover, brethren, I declare unto you the gospel which I preached unto you, which also ye have received, and wherein ye stand; ) ",
                                          " ( 2 By which also ye are saved, if ye keep in memory what I preached unto you, unless ye have believed in vain. ) ",
                                          " ( 3 For I delivered unto you first of all that which I also received, how that Christ died for our sins according to the scriptures; ) ",
                                          " ( 4 And that he was buried, and that he rose again the third day according to the scriptures: ) ",
                                          " ( 5 And that he was seen of Cephas, then of the twelve: ) ",
                                          " ( 6 After that, he was seen of above five hundred brethren at once; of whom the greater part remain unto this present, but some are fallen asleep. ) ",
                                          " ( 7 After that, he was seen of James; then of all the apostles. ) ",
                                          " ( 8 And last of all he was seen of me also, as of one born out of due time. ) ",
                                          " ( 9 For I am the least of the apostles, that am not meet to be called an apostle, because I persecuted the church of God. ) ",
                                          " ( 10 But by the grace of God I am what I am: and his grace which was bestowed upon me was not in vain; but I laboured more abundantly than they all: yet not I, but the grace of God which was with me. ) ",
                                          " ( 11 Therefore whether it were I or they, so we preach, and so ye believed. ) ",
                                          " ( 12 Now if Christ be preached that he rose from the dead, how say some among you that there is no resurrection of the dead? ) ",
                                          " ( 13 But if there be no resurrection of the dead, then is Christ not risen: ) ",
                                          " ( 14 And if Christ be not risen, then is our preaching vain, and your faith is also vain. ) ",
                                          " ( 15 Yea, and we are found false witnesses of God; because we have testified of God that he raised up Christ: whom he raised not up, if so be that the dead rise not. ) ",
                                          " ( 16 For if the dead rise not, then is not Christ raised: ) ",
                                          " ( 17 And if Christ be not raised, your faith is vain; ye are yet in your sins. ) ",
                                          " ( 18 Then they also which are fallen asleep in Christ are perished. ) ",
                                          " ( 19 If in this life only we have hope in Christ, we are of all men most miserable. ) ",
                                          " ( 20 But now is Christ risen from the dead, and become the firstfruits of them that slept. ) ",
                                          " ( 21 For since by man came death, by man came also the resurrection of the dead. ) ",
                                          " ( 22 For as in Adam all die, even so in Christ shall all be made alive. ) ",
                                          " ( 23 But every man in his own order: Christ the firstfruits; afterward they that are Christ's at his coming. ) ",
                                          " ( 24 Then cometh the end, when he shall have delivered up the kingdom to God, even the Father; when he shall have put down all rule and all authority and power. ) ",
                                          " ( 25 For he must reign, till he hath put all enemies under his feet. ) ",
                                          " ( 26 The last enemy that shall be destroyed is death. ) ",
                                          " ( 27 For he hath put all things under his feet. But when he saith all things are put under him, it is manifest that he is excepted, which did put all things under him. ) ",
                                          " ( 28 And when all things shall be subdued unto him, then shall the Son also himself be subject unto him that put all things under him, that God may be all in all. ) ",
                                          " ( 29 Else what shall they do which are baptized for the dead, if the dead rise not at all? why are they then baptized for the dead? ) ",
                                          " ( 30 And why stand we in jeopardy every hour? ) ",
                                          " ( 31 I protest by your rejoicing which I have in Christ Jesus our Lord, I die daily. ) ",
                                          " ( 32 If after the manner of men I have fought with beasts at Ephesus, what advantageth it me, if the dead rise not? let us eat and drink; for to morrow we die. ) ",
                                          " ( 33 Be not deceived: evil communications corrupt good manners. ) ",
                                          " ( 34 Awake to righteousness, and sin not; for some have not the knowledge of God: I speak this to your shame. ) ",
                                          " ( 35 But some man will say, How are the dead raised up? and with what body do they come? ) ",
                                          " ( 36 Thou fool, that which thou sowest is not quickened, except it die: ) ",
                                          " ( 37 And that which thou sowest, thou sowest not that body that shall be, but bare grain, it may chance of wheat, or of some other grain: ) ",
                                          " ( 38 But God giveth it a body as it hath pleased him, and to every seed his own body. ) ",
                                          " ( 39 All flesh is not the same flesh: but there is one kind of flesh of men, another flesh of beasts, another of fishes, and another of birds. ) ",
                                          " ( 40 There are also celestial bodies, and bodies terrestrial: but the glory of the celestial is one, and the glory of the terrestrial is another. ) ",
                                          " ( 41 There is one glory of the sun, and another glory of the moon, and another glory of the stars: for one star differeth from another star in glory. ) ",
                                          " ( 42 So also is the resurrection of the dead. It is sown in corruption; it is raised in incorruption: ) ",
                                          " ( 43 It is sown in dishonour; it is raised in glory: it is sown in weakness; it is raised in power: ) ",
                                          " ( 44 It is sown a natural body; it is raised a spiritual body. There is a natural body, and there is a spiritual body. ) ",
                                          " ( 45 And so it is written, The first man Adam was made a living soul; the last Adam was made a quickening spirit. ) ",
                                          " ( 46 Howbeit that was not first which is spiritual, but that which is natural; and afterward that which is spiritual. ) ",
                                          " ( 47 The first man is of the earth, earthy; the second man is the Lord from heaven. ) ",
                                          " ( 48 As is the earthy, such are they also that are earthy: and as is the heavenly, such are they also that are heavenly. ) ",
                                          " ( 49 And as we have borne the image of the earthy, we shall also bear the image of the heavenly. ) ",
                                          " ( 50 Now this I say, brethren, that flesh and blood cannot inherit the kingdom of God; neither doth corruption inherit incorruption. ) ",
                                          " ( 51 Behold, I shew you a mystery; We shall not all sleep, but we shall all be changed, ) ",
                                          " ( 52 In a moment, in the twinkling of an eye, at the last trump: for the trumpet shall sound, and the dead shall be raised incorruptible, and we shall be changed. ) ",
                                          " ( 53 For this corruptible must put on incorruption, and this mortal must put on immortality. ) ",
                                          " ( 54 So when this corruptible shall have put on incorruption, and this mortal shall have put on immortality, then shall be brought to pass the saying that is written, Death is swallowed up in victory. ) ",
                                          " ( 55 O death, where is thy sting? O grave, where is thy victory? ) ",
                                          " ( 56 The sting of death is sin; and the strength of sin is the law. ) ",
                                          " ( 57 But thanks be to God, which giveth us the victory through our Lord Jesus Christ. ) ",
                                          " ( 58 Therefore, my beloved brethren, be ye stedfast, unmoveable, always abounding in the work of the Lord, forasmuch as ye know that your labour is not in vain in the Lord. ) ",
        };
        for (const auto &suffix : suffixes) {
            for (const auto &prefix : prefixes) {
                std::string newString = prefix;
                newString.append(suffix);
                allCookieNumberNames.push_back(newString);
            }
        }
        return allCookieNumberNames;
    };

public:
    static void removeTrailingZeroes(std::string &integerpart) {
        integerpart.erase(integerpart.find_last_not_of('0') + 1, std::string::npos);
    }

    static void removeLeadingZeroes(std::string &integerpart) {
        integerpart.erase(0, std::min(integerpart.find_first_not_of('0'), integerpart.size() - 1));
    }

    static std::pair<std::string, std::string> splitStringNumber(const std::string &largeNumber) {
        std::istringstream iss(largeNumber);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, '.')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        std::string integerpart;
        std::string fractionalpart;
        switch (tokens.size()) {
            case 1:
                integerpart = tokens.at(0);
                break;
            case 2:
                integerpart = tokens.at(0);
                fractionalpart = tokens.at(1);
                break;
            default:
                integerpart = largeNumber;
                break;
        }
        removeTrailingZeroes(fractionalpart);

        return {integerpart, fractionalpart};
    }

    template<typename T>
    std::string print(const T &c) const {
        size_t base(0);
        std::string returnString;
        std::string cAsString = c.str(0, std::ios_base::fixed);
        T tmp = c;
        T smallerTmp = c;
        std::string suffix;

        if (tmp >= T(1000000)) {
            tmp /= T(1000);
#ifdef USEBOOST_MPP
            while (boost::multiprecision::round(tmp) >= T(1000)) {
#else
                while (tmp.round() >= T(1000)) {
#endif
                tmp /= T(1000);
                base++;
            }
            if (base >= cookieNumberNames().size()) {
                // poor man's string to pseudo-scientific notation
                size_t len = cAsString.size() - 1;
                std::string beforeDot = cAsString.substr(0, 3);
                std::string afterDot = cAsString.substr(4, 3);
                std::stringstream result;
                result << beforeDot << "." << afterDot << "e+" << std::to_string(len) << " (too large for a suffix) ";
                return result.str();
            } else {
                suffix = cookieNumberNames().at(base);
            }
            smallerTmp = ((tmp * T(1000)) / T(1000));
        }

        std::string smallerTmpAsString = smallerTmp.str(0, std::ios_base::fixed);
        auto splitString = splitStringNumber(smallerTmpAsString);
        std::string integerpart = splitString.first;
        std::string fractionalpart = splitString.second;

        returnString.append(integerpart);
        if (base == 0 && !fractionalpart.empty()) {
            returnString.append(".");
            returnString.append(fractionalpart);
        } else if (base > 0) {
            std::string next3Numbers = cAsString.substr(integerpart.size(), 3);
            removeTrailingZeroes(next3Numbers);
            if (!next3Numbers.empty()) {
                returnString.append(",");
                returnString.append(next3Numbers);
            }
        }

        returnString.append(" ");
        returnString.append(suffix);
        return returnString;
    }

};

typedef CookieNumberPrinter cnp;

static const CookieNumberPrinter cp;

#endif //C_OOKIECLIKER_COOKIENUMBERS_H
