/*  Revil Format Library
    Copyright(C) 2021 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include "ext_base.hpp"

namespace MT_SBSYD {
static const MtExtensionsStorage extCommon{
    /**/ //
    {"acm", 0x7D47F33A},
    {"aht", 0x57728652},
    {"aol", 0x56D36A7E},
    {"apw", 0x418F819E},
    {"ard", 0x354E1E08},
    {"ase", 0x5A7711B5},
    {"atk", 0x342366F0},
    {"att", 0x20C43967},
    {"bes2", 0x714EC77C}, // dupe
    {"bsd", 0x657CBB77},
    {"bsel", 0x1D3A0E3C},
    {"btf", 0x2416212F},
    {"bth", 0x4D3C70A1},
    {"bts", 0x2BE3A5BA},
    {"ccd", 0x4D469B43},
    {"clt", 0x6F4D08},
    {"cmw", 0xE711FE6},
    {"col", 0x5B9071CF},
    {"cst", 0x635AA43A},
    {"ddt", 0x780B98EE},
    {"dli", 0x3D485AA3},
    {"dlo", 0x5DCC3306},
    {"dlw", 0x393B2B12},
    {"dmt", 0x4A1D2F4C},
    {"drm", 0x1DA853DE},
    {"e2d", 0x276DE8B7},
    {"ean", 0x4E397417},
    {"ebd", 0x7AA8F618},
    {"ecc", 0x3823CABE},
    {"ecd", 0x76CFB2FC},
    {"eco", 0x76042FD2},
    {"ecp", 0x4FE235C1},
    {"efd", 0x170E88C6},
    {"efl", 0x6D5AE854},
    {"efp", 0x1F2FA472},
    {"egc", 0x76D68C75},
    {"ein", 0x3D2E1661},
    {"emg", 0x3CD26CFD},
    {"emp", 0x55E21D03},
    {"ems", 0x62ED419A},
    {"end", 0x4AC1F336},
    {"enp", 0x737C261F},
    {"epm", 0x75E854B1},
    {"equ", 0x2B40AE8F}, // dupe
    {"equr", 0x2B40AE8F},
    {"erl", 0x3ED3FE7},
    {"evs", 0x714EC77C},
    {"fdt", 0x174F75BD},
    {"gfd", 0x2D462600},
    {"gii", 0x7F768AF},
    {"gim002", 0x65AD6356},
    {"gmd", 0x242BB29A},
    {"gra", 0x648822F5},
    {"gui", 0x22948394},
    {"chs", 0x2B81136E},
    {"idx", 0x3B5A0DA5},
    {"itp", 0x7A1F334C},
    {"its", 0xC0EA4CB},
    {"lcm", 0x39C52040},
    {"lma", 0x3AA2277},
    {"lmt", 0x76820D81},
    {"mbd", 0x5160A1F5},
    {"mef", 0x52CCE4E},
    {"mgi", 0x2EA515BF},
    {"mic", 0x4DBD88F9},
    {"mif", 0x2EA515BF}, // dupe
    {"minigame", 0x6F94E4B0},
    {"mod", 0x58A15856},
    {"mpm", 0x20574E7E},
    {"mrl", 0x2749C8A8},
    {"mse", 0x12408FE8},
    {"msf", 0xCF7FB37},
    {"mtm", 0x436A2F3D},
    {"nav", 0x4EF19843},
    {"ofst", 0x404BA9F4},
    {"omt", 0x6091F163},
    {"pba", 0x644C5482},
    {"pla", 0x42EA212F},
    {"pmc", 0x2A0C6CB3},
    {"pot", 0x21F55CD7},
    {"ppc", 0x3CFBE7D5},
    {"ppm", 0xB52347D},
    {"prp", 0x272B80EA},
    {"rdt", 0x19DB4587},
    {"rev_ps3", 0x232E228C}, // dupe
    {"revr", 0x232E228C},
    {"rch", 0x57863AC0},
    {"rtd", 0x6812D2EC},
    {"rtex", 0x7808EA10},
    {"rwp", 0x190223A5},
    {"sbc", 0x51FC779F},
    {"sbd", 0x6677C6A3},
    {"sbkr", 0x15D782FB},
    {"scn", 0x6246E90D},
    {"scs", 0xECD7DF4}, // dupe
    {"scsr", 0xECD7DF4},
    {"sdl", 0x4C0DB839},
    {"sds", 0x315E81F},
    {"smi", 0x280C9CB7},
    {"smx", 0x30FC745F}, // dupe
    {"smxr", 0x30FC745F},
    {"spkg", 0x2358E1A},
    {"spr", 0x3DA61F2A},
    {"srl", 0x5A88413C},
    {"srq", 0x1BCC4966},
    {"ssb", 0x5089998D},
    {"ssc", 0x49B5A885}, // dupe
    {"sscr", 0x49B5A885},
    {"sst", 0x15D1B6B},
    {"stex", 0x4323D83A},
    {"stq", 0x167DBBFF},
    {"stw", 0x752E181F},
    {"svc", 0x1E1E93BB},
    {"tex", 0x241F5DEB},
    {"thk", 0x62A68441},
    {"ttb", 0x62A68441}, // dupe
    {"upa", 0x1AF35122},
    {"uut", 0x535D0BEE},
    {"visr", 0x530D12A5},
    {"way", 0x5F36B659},
    {"wbd", 0x41006DF2},
    {"wpn", 0x2141D3A9},
    {"wpp", 0x2141D3A9}, // dupe
    {"zon", 0x1B520B68},
};

static const MtExtFixupStorage fixups{
    /**/ //
    {0x0ECD7DF4, "scsr"},
    {0x2141D3A9, "wpn"},
    {0x232E228C, "revr"},
    {0x2B40AE8F, "equr"},
    {0x2EA515BF, "mgi"},
    {0x30FC745F, "smxr"},
    {0x49B5A885, "sscr"},
    {0x62A68441, "thk"},
    {0x714EC77C, "evs"},
};

static const TitleSupport suppPS3{
    ARC_PS3_GENERIC,
    ModSupport{0xD3},
    TexSupport{0x9D},
    LmtSupport{67},
};

static const TitleSupport suppPS4{
    ARC_WINPC_GENERIC,
    ModSupport{0xD3, true},
    TexSupport{0x9D, true},
    LmtSupport{67, true},
};

static const TitleSupports supp{
    Platform::PS3, suppPS3, //
    Platform::PS4, suppPS4, //
};
} // namespace MT_SBSYD

static const MtExtensions extSBSYD{MT_SBSYD::extCommon, MT_SBSYD::fixups,
                                   MT_SBSYD::supp, Platform::PS3};
