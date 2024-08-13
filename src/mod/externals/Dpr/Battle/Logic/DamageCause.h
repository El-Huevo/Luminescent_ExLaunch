#pragma once

#include "externals/il2cpp-api.h"

namespace Dpr::Battle::Logic {
    enum class DamageCause : uint8_t {
        OTHER = 0,
        WEATHER = 1,
        KONRAN = 2,
        WAZA = 3,
        WAZA_KICKBACK = 4,
        ICHIGEKI = 5,
        NEEDLEGUARD = 6,
        HAJIKERUHONOO_SPARKLE = 7,
        JIBAKU = 8,
        OKIMIYAGE = 9,
        MIKAZUKINOMAI = 10,
        IYASINONEGAI = 11,
        MITIDURE = 12,
        INOTIGAKE = 13,
        MIGAWARI = 14,
        NOROI = 15,
        ITAMIWAKE = 16,
        HARADAIKO = 17,
        WARUAGAKI = 18,
        TOBIGERI_FAILED = 19,
        SAMEHADA = 20,
        TETUNOTOGE = 21,
        YUUBAKU = 22,
        SUNPOWER = 23,
        KANSOUHADA = 24,
        NIGHTMARE = 25,
        HEDOROEKI = 26,
        TOBIDASUNAKAMI = 27,
        JAPO_RENBU = 28,
        INOTINOTAMA = 29,
        KUROIHEDORO = 30,
        KUTTUKIBARI = 31,
        GOTUGOTUMETTO = 32,
        STEALTHROCK = 33,
        MAKIBISI = 34,
        BURNING = 35,
        SIDE_GSHOCK_HONOO = 36,
        SIDE_GSHOCK_IWA = 37,
        SICK_YADORIGINOTANE = 38,
        SICK_BIND = 39,
        SICK_DOKU = 40,
        SICK_YAKEDO = 41,
        SICK_AKUMU = 42,
        SICK_NOROI = 43,
        SICK_HOROBINOUTA = 44,
        SICK_FUNJIN = 45,
    };
}