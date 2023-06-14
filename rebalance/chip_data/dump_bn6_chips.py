import struct
import json
import yaml

charset = [" ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "*", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "RV", "BX", "EX", "SP", "FZ", "ウ", "ア", "イ", "オ", "エ", "ケ", "コ", "カ", "ク", "キ", "セ", "サ", "ソ", "シ", "ス", "テ", "ト", "ツ", "タ", "チ", "ネ", "ノ", "ヌ", "ナ", "ニ", "ヒ", "ヘ", "ホ", "ハ", "フ", "ミ", "マ", "メ", "ム", "モ", "ヤ", "ヨ", "ユ", "ロ", "ル", "リ", "レ", "ラ", "ン", "熱", "斗", "ワ", "ヲ", "ギ", "ガ", "ゲ", "ゴ", "グ", "ゾ", "ジ", "ゼ", "ズ", "ザ", "デ", "ド", "ヅ", "ダ", "ヂ", "ベ", "ビ", "ボ", "バ", "ブ", "ピ", "パ", "ペ", "プ", "ポ", "ゥ", "ァ", "ィ", "ォ", "ェ", "ュ", "ヴ", "ッ", "ョ", "ャ", "-", "×", "=", ":", "%", "?", "+", "█", "[bat]", "ー", "!", "&", ",", "゜", ".", "・", ";", "'", "\"", "~", "/", "(", ")", "「", "」", "�", "_", "ƶ", "[L]", "[B]", "[R]", "[A]", "あ", "い", "け", "く", "き", "こ", "か", "せ", "そ", "す", "さ", "し", "つ", "と", "て", "た", "ち", "ね", "の", "な", "ぬ", "に", "へ", "ふ", "ほ", "は", "ひ", "め", "む", "み", "も", "ま", "ゆ", "よ", "や", "る", "ら", "り", "ろ", "れ", "[END]", "ん", "を", "わ", "研", "げ", "ぐ", "ご", "が", "ぎ", "ぜ", "ず", "じ", "ぞ", "ざ", "で", "ど", "づ", "だ", "ぢ", "べ", "ば", "び", "ぼ", "ぶ", "ぽ", "ぷ", "ぴ", "ぺ", "ぱ", "ぅ", "ぁ", "ぃ", "ぉ", "ぇ", "ゅ", "ょ", "っ", "ゃ", "容", "量", "全", "木", "[MB]", "無", "現", "実", "[circle]", "×", "緑", "道", "不", "止", "彩", "起", "父", "集", "院", "一", "二", "三", "四", "五", "六", "七", "八", "陽", "十", "百", "千", "万", "脳", "上", "下", "左", "右", "手", "来", "日", "目", "月", "獣", "各", "人", "入", "出", "山", "口", "光", "電", "気", "綾", "科", "次", "名", "前", "学", "校", "省", "祐", "室", "世", "界", "高", "朗", "枚", "野", "悪", "路", "闇", "大", "小", "中", "自", "分", "間", "系", "花", "問", "究", "門", "城", "王", "兄", "化", "葉", "行", "街", "屋", "水", "見", "終", "新", "桜", "先", "生", "長", "今", "了", "点", "井", "子", "言", "太", "属", "風", "会", "性", "持", "時", "勝", "赤", "代", "年", "火", "改", "計", "画", "職", "体", "波", "回", "外", "地", "員", "正", "造", "値", "合", "戦", "川", "秋", "原", "町", "晴", "用", "金", "郎", "作", "数", "方", "社", "攻", "撃", "力", "同", "武", "何", "発", "少", "教", "以", "白", "早", "暮", "面", "組", "後", "文", "字", "本", "階", "明", "才", "者", "向", "犬", "々", "ヶ", "連", "射", "舟", "戸", "切", "土", "炎", "伊", "夫", "鉄", "国", "男", "天", "老", "師", "堀", "杉", "士", "悟", "森", "霧", "麻", "剛", "垣", "★", "[bracket1]", "[bracket2]", "[.]"]

def dump_simple_text_script(f, offset, num_scripts):
    f.seek(offset)

    script_offsets = []

    for i in range(num_scripts):
        script_offsets.append(struct.unpack("<H", f.read(2))[0])

    text_scripts = []

    for script_offset in script_offsets:
        f.seek(offset + script_offset)
        cur_text_script = ""
        while True:
            cur_byte = ord(f.read(1))
            if cur_byte == 0xe6:
                break
            cur_text_script += charset[cur_byte]

        text_scripts.append(cur_text_script)

    return text_scripts

all_chip_codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZ*"

CHIP_DATA_OFFSET = 0x21da8
CHIP_NAMES_POINTERS_OFFSET = 0x42068
NUM_CHIPS = 411

def read_ptr_as_file_offset(f, offset):
    f.seek(offset)
    return struct.unpack("<I", f.read(4))[0] - 0x8000000



class ChipDataReader:
    __slots__ = ("_rom_file", "_chip_id")

    def __init__(self, rom_file):
        self._rom_file = rom_file
        self._chip_id = 0

    def set_chip_id(self, chip_id):
        self._chip_id = chip_id

    def _seek(self, offset):
        self._rom_file.seek(CHIP_DATA_OFFSET + self._chip_id * 0x2c + offset)

    def read_byte(self, offset):
        self._seek(offset)
        return ord(self._rom_file.read(1))

    def read_hword(self, offset):
        self._seek(offset)
        return struct.unpack("<H", self._rom_file.read(2))[0]

    def read_word(self, offset):
        self._seek(offset)
        return struct.unpack("<I", self._rom_file.read(4))[0]

CHIP_LIBRARY_STANDARD = 0
CHIP_LIBRARY_MEGA = 1
CHIP_LIBRARY_GIGA = 2
CHIP_LIBRARY_NONE = 3
CHIP_LIBRARY_PA = 4

GREGAR_CHIP_ID = 312

attack_element_enum_to_names = {
    0x0: "none",
    0x1: "heat",
    0x2: "aqua",
    0x3: "elec",
    0x4: "wood"
}

chip_element_icon_enum_to_names = {
    0x00: "fire",
    0x01: "aqua",
    0x02: "elec",
    0x03: "wood",
    0x04: "plus",
    0x05: "sword",
    0x06: "cursor",
    0x07: "obstacle",
    0x08: "wind",
    0x09: "break",
    0x0a: "none",
    0x0b: "elementless"
}

library_type_enum_to_names = {
    CHIP_LIBRARY_STANDARD: "standard",
    CHIP_LIBRARY_MEGA: "mega",
    CHIP_LIBRARY_GIGA: "giga",
    CHIP_LIBRARY_NONE: "none",
    CHIP_LIBRARY_PA: "pa"
}

class HexInt(int):
    pass

def representer(dumper, data):
    return yaml.ScalarNode("tag:yaml.org,2002:int", hex(data))

def test_bit(val, bit):
    return (val & (1 << bit)) != 0

lockon_type_enum_to_names = {
    0x0: "LOCKON_NONE",
    0x1: "LOCKON_JUMP_1_FORWARD_ON_SUCCESSIVE_USE",
    0x2: "LOCKON_1ST_PANEL_IN_FRONT",
    0x3: "LOCKON_1ST_PANEL_IN_FRONT_MIDDLE_OF_COLUMN",
    0x4: "LOCKON_2ND_PANEL_IN_FRONT",
    0x5: "LOCKON_3RD_PANEL_IN_FRONT",
    0x6: "LOCKON_06",
    0x7: "LOCKON_07",
    0x8: "LOCKON_08",
    0x9: "LOCKON_2ND_PANEL_IN_FRONT_MIDDLE_OF_COLUMN",
    0xa: "LOCKON_FURTHEST_PANEL_FROM_TARGET",
    0xb: "LOCKON_0B",
    0xc: "LOCKON_0C",
    0xd: "LOCKON_0D",
    0xe: "LOCKON_CENTER_BACK_PANEL",
    0xf: "LOCKON_0F",
    0x10: "LOCKON_3RD_PANEL_IN_FRONT_MIDDLE_OF_COLUMN",
    0x11: "LOCKON_11",
    0x12: "LOCKON_12",
}

def main():
    yaml.add_representer(HexInt, representer)

    INPUT_ROM_BASENAME = "bn6f.gba"

    if INPUT_ROM_BASENAME == "bn6f.gba":
        CHIP_NAMES_POINTERS_OFFSET = 0x42068
    else:
        CHIP_NAMES_POINTERS_OFFSET = 0x42038

    INPUT_ROM = f"../../{INPUT_ROM_BASENAME}"

    with open(INPUT_ROM, "rb") as f:
        chip_names_pt1_ptr = read_ptr_as_file_offset(f, CHIP_NAMES_POINTERS_OFFSET)
        chip_names_pt2_ptr = read_ptr_as_file_offset(f, CHIP_NAMES_POINTERS_OFFSET + 4)

        chip_names_pt1 = dump_simple_text_script(f, chip_names_pt1_ptr, 256)
        chip_names_pt2 = dump_simple_text_script(f, chip_names_pt2_ptr, NUM_CHIPS - 256)

    chip_names = chip_names_pt1 + chip_names_pt2
    output = ""

    chip_data = {}

    with open(INPUT_ROM, "rb") as f:
        chip_data_reader = ChipDataReader(f)

        for chip_id, chip_name in enumerate(chip_names):
            chip_data_reader.set_chip_id(chip_id)
            chip_library_as_num = chip_data_reader.read_byte(7)
            chip_effect_flags = chip_data_reader.read_byte(9)

            if (chip_library_as_num in {CHIP_LIBRARY_STANDARD, CHIP_LIBRARY_MEGA} and chip_effect_flags & 0x40 != 0) or (chip_library_as_num == CHIP_LIBRARY_GIGA and chip_id < GREGAR_CHIP_ID) or (chip_library_as_num == CHIP_LIBRARY_PA):
                chip_info = {}
                chip_info["id"] = chip_id
                chip_info["name"] = chip_name

                chip_codes = []
                for i in range(4):
                    chip_code_as_num = chip_data_reader.read_byte(i)
                    if chip_code_as_num == 0xff:
                        break
                    chip_codes.append(all_chip_codes[chip_code_as_num])

                chip_info["codes"] = chip_codes
                attack_element_and_types = chip_data_reader.read_byte(4)
                attack_element_name = attack_element_enum_to_names[attack_element_and_types & 0xf]
                is_break = test_bit(attack_element_and_types, 4)
                is_wind = test_bit(attack_element_and_types, 5)
                is_cursor = test_bit(attack_element_and_types, 6)
                is_sword = test_bit(attack_element_and_types, 7)

                # attack_element_and_types_dict = {
                #     "attackElement": attack_element_name,
                #     "isBreak": is_break,
                #     "isWind": is_wind,
                #     "isCursor": is_cursor,
                #     "isSword": is_sword
                # }

                chip_info["attackElement"] = attack_element_name
                chip_info["isBreak"] = is_break
                chip_info["isWind"] = is_wind
                chip_info["isCursor"] = is_cursor
                chip_info["isSword"] = is_sword

                chip_element_icon = chip_data_reader.read_byte(6)
                try:
                    chip_element_icon_name = chip_element_icon_enum_to_names[chip_element_icon]
                except KeyError:
                    raise RuntimeError(f"Unknown chip element {chip_element_icon}! chip_name: {chip_name}")
                chip_info["chipElement"] = chip_element_icon_name
                chip_info["libraryType"] = library_type_enum_to_names[chip_library_as_num]

                chip_info["mb"] = chip_data_reader.read_byte(8)

                chip_effect_flags_dict = {}
                chip_effect_flags_dict["isDimming"] = test_bit(chip_effect_flags, 0)
                chip_effect_flags_dict["showAttackPower"] = test_bit(chip_effect_flags, 1)
                chip_effect_flags_dict["isNaviChip"] = test_bit(chip_effect_flags, 2)
                chip_effect_flags_dict["unkBit0x3"] = test_bit(chip_effect_flags, 3)
                chip_effect_flags_dict["questionAttackPower"] = test_bit(chip_effect_flags, 4)
                chip_effect_flags_dict["isDarkChip"] = test_bit(chip_effect_flags, 5)
                chip_effect_flags_dict["appearsInLibrary"] = test_bit(chip_effect_flags, 6)
                chip_effect_flags_dict["variableAttackPower"] = test_bit(chip_effect_flags, 7)

                chip_info["effectFlags"] = chip_effect_flags_dict

                stamina_damage_counter_frames = chip_data_reader.read_byte(0xa)
                is_damage_dealing_dimming = test_bit(stamina_damage_counter_frames, 7)
                chip_info["staminaDamageCounterFrames"] = stamina_damage_counter_frames & 0x7f
                chip_info["isDamageDealingDimming"] = is_damage_dealing_dimming

                chip_info["attackFamily"] = HexInt(chip_data_reader.read_byte(0xb))
                chip_info["attackSubFamily"] = HexInt(chip_data_reader.read_byte(0xc))
                chip_info["darkSoulUsage"] = HexInt(chip_data_reader.read_byte(0xd))
                chip_info["unk0xe"] = HexInt(chip_data_reader.read_byte(0xe))
                chip_info["lockOnEnable"] = test_bit(chip_data_reader.read_byte(0xf), 0)
                chip_info["attackParam1"] = chip_data_reader.read_byte(0x10)
                chip_info["attackParam2"] = chip_data_reader.read_byte(0x11)
                chip_info["attackParam3"] = chip_data_reader.read_byte(0x12)
                chip_info["attackParam4"] = chip_data_reader.read_byte(0x13)
                chip_info["lockoutFrames"] = chip_data_reader.read_byte(0x14)
                chip_info["libraryNum"] = chip_data_reader.read_byte(0x15)

                library_flags = chip_data_reader.read_byte(0x16)
                library_flags_dict = {}
                library_flags_dict["secretLibraryChip"] = test_bit(library_flags, 0)
                library_flags_dict["unkBit0x1"] = test_bit(library_flags, 1)
                library_flags_dict["gregarGigaChip"] = test_bit(library_flags, 2)
                library_flags_dict["falzarGigaChip"] = test_bit(library_flags, 3)
                library_flags_dict["untradable"] = test_bit(library_flags, 4)
                library_flags_dict["doesNotAppearInPack"] = test_bit(library_flags, 5)
                library_flags_dict["attachmentChip"] = test_bit(library_flags, 6)
                library_flags_dict["unkBit0x7"] = test_bit(library_flags, 7)
                chip_info["libraryFlags"] = library_flags_dict

                chip_info["lockOnType"] = lockon_type_enum_to_names[chip_data_reader.read_byte(0x17)]
                chip_info["alphabetSortPos"] = chip_data_reader.read_hword(0x18)
                chip_info["attackPower"] = chip_data_reader.read_hword(0x1a)
                chip_info["idSortPos"] = chip_data_reader.read_hword(0x1c)
                chip_info["chipGateUsageLimit"] = chip_data_reader.read_byte(0x1e)
                chip_info["darkChipId"] = chip_data_reader.read_byte(0x1f)

                chip_data[chip_name] = chip_info

    with open("chip_data.yml", "w+") as f:
        yaml.dump(chip_data, f, sort_keys=False)

if __name__ == "__main__":
    main()
