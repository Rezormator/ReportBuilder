#pragma once

#include <string>
#include <vector>

#include "../Product/TargetGroup.h"

namespace SizePriority {
    inline std::vector<std::string> MEN_TEXTILE {
        "M", "L", "S", "XL", "XS", "2XL", "2XS"
    };

    inline std::vector<std::string> MEN_PANTS {
        "48", "50", "46", "52", "48S", "50S", "46S", "44", "54", "44S", "52S", "56"
    };

    inline std::vector<std::string> MEN_JEANS {
        "32", "33", "34", "31", "30", "36", "38", "28", "35", "40"
    };

    inline std::vector<std::string> WOMEN_TEXTILE {
        "S", "M", "XS", "L", "XL", "2XS", "2XL"
    };

    inline std::vector<std::string> WOMEN_BRA {
        "MCD", "SCD", "MAB", "SAB", "LCD", "LAB", "XSCD", "XSAB", "XLCD", "XLAB",
        "MEG", "LEG", "SEG", "XLEG", "2XCD", "2XAB", "2XSCD", "2XSAB", "3XCD",
        "2XEG", "3XEG", "4XEG", "XSEG"
    };

    inline std::vector<std::string> WOMEN_JEANS_1 {
        "2832", "2732", "2932", "2830", "2730", "2930", "2632", "3032", "3132", "2630",
        "2834", "2934", "3034", "2734", "3232", "3432", "3634", "3030", "3130", "3230",
        "2836", "2936", "3036", "3136", "2736", "2634", "2636", "3134", "3234", "3236",
        "3430", "3434", "3436", "3630", "3636"
    };

    inline std::vector<std::string> WOMEN_JEANS_2 {
        "38", "40", "36", "42", "44", "34", "46", "32", "30", "48", "28"
    };

    inline std::vector<std::string> KIDS_TEXTILE_1 {
        "74", "80", "86", "68", "92", "98", "62", "104"
    };

    inline std::vector<std::string> KIDS_TEXTILE_2 {
        "128", "140", "116", "152", "110", "164", "104", "170"
    };

    inline std::vector<std::string> KIDS_TEXTILE_3 {
         "140", "152", "164", "128", "116", "176", "104"
    };

    inline std::vector<std::string> KIDS_TEXTILE_4 {
        "110", "116", "122", "104", "128", "98", "140", "92"
    };

    inline std::vector<std::string> KIDS_TEXTILE_5 {
        "146", "152", "158", "140", "164", "128", "176"
    };

    inline std::vector<std::string> MEN_FOOTWEAR {
        "8-", "8", "9", "9-", "10", "10-", "7", "7-", "11", "11-", "6", "6-",
        "12", "12-", "13", "13-", "14"
    };

    inline std::vector<std::string> MEN_UNISEX_FOOTWEAR {
        "8-", "8", "9", "9-", "10", "10-", "11", "11-","12", "12-", "13", "13-", "14"
    };

    inline std::vector<std::string> WOMEN_FOOTWEAR {
        "5-", "5", "6", "6-", "4", "4-", "7", "7-", "8", "8-", "3-", "3"
    };

    inline std::vector<std::string> WOMEN_UNISEX_FOOTWEAR {
        "5-", "5", "6", "6-", "4", "4-", "7", "7-", "3-", "3"
    };


    inline std::vector<std::string> UNISEX_FOOTWEAR {
        "5-", "5", "6", "6-", "4", "4-", "7", "7-", "8", "8-", "3-", "3", "8",
        "8-", "9", "9-", "10", "10-", "7", "7-", "11", "11-", "6", "6-", "12",
        "12-", "13", "13-", "14"
    };

    inline std::vector<std::string> KIDS_FOOTWEAR_1 {
        "32", "33", "33-", "34", "35", "3", "3-", "4", "4-", "5", "5-", "31",
        "31-", "30", "30-", "29", "28", "28-"
    };

    inline std::vector<std::string> KIDS_FOOTWEAR_2 {
        "22", "23", "23-", "24", "25", "25-", "21", "26", "26-", "20", "27", "19"
    };

    inline std::vector<std::string> KIDS_FOOTWEAR_3 {
        "18", "19", "20", "17", "21", "16"
    };

    const std::vector<std::pair<TargetGroup, std::vector<std::string>>> ALL_PRIORITIES = {
        {TargetGroup::Men, MEN_TEXTILE},
        {TargetGroup::Men, MEN_JEANS},
        {TargetGroup::Men, MEN_PANTS},
        {TargetGroup::Women, WOMEN_TEXTILE},
        {TargetGroup::Women, WOMEN_BRA},
        {TargetGroup::Women, WOMEN_JEANS_1},
        {TargetGroup::Women, WOMEN_JEANS_2},
        {TargetGroup::Kids, KIDS_TEXTILE_1},
        {TargetGroup::Kids, KIDS_TEXTILE_2},
        {TargetGroup::Kids, KIDS_TEXTILE_3},
        {TargetGroup::Kids, KIDS_TEXTILE_4},
        {TargetGroup::Kids, KIDS_TEXTILE_5},
        {TargetGroup::Unisex,  MEN_TEXTILE},
        {TargetGroup::Men, MEN_FOOTWEAR},
        {TargetGroup::Men, UNISEX_FOOTWEAR},
        {TargetGroup::Women, WOMEN_FOOTWEAR},
        {TargetGroup::Kids, KIDS_FOOTWEAR_1},
        {TargetGroup::Kids, KIDS_FOOTWEAR_2},
        {TargetGroup::Kids, KIDS_FOOTWEAR_3},
        {TargetGroup::Unisex, UNISEX_FOOTWEAR}
    };
}
