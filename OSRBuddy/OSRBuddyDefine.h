#pragma once
#include <string>
#include <utility>
#include <vector>

// GambleBot




// EnchantBot  


#define TO_ENUM(enumtype, number) (static_cast<enumtype>(number))
#define TO_INT(enumnum) (static_cast<int>(enumnum))

/*
enum class SkillType
{
    Turnaround,
    Back_Move_Mach,
    Defense_Up,
    Concentration,
    Frenzy,
    Berserker,
    Silence,
    Purchasing_Shop,
    Selling_Shop,
    Hyper_Moving,
    Chain_Rolling,
    Overbooster,
    Evasion_Up,
    Missile_Shot,
    Fire_Shot,
    Hyper_Shot,
    Shield_Paralyze,
    Camouflage,
    Snare_Shot,
    Ground_Accelerator,
    Barrier,
    Remedy,
    Siege_Defense,
    Collision_Absorption,
    Air_Siege_Mode,
    Siege_Mode,
    Inverted_Bell_Formation,
    Bell_Formation,
    Wedge_Formation,
    Echelon_A_Formation,
    Purify,
    Full_Recovery,
    Scanning,
    Call_of_Hero,
    Smart_SP,
    Fuel_Replenish,
    Reverse_Engine,
    Invincible,
    Raging_Evasion,
    Raging_Defense,
    Raging_Fire,
    Energize_Target,
    Energizing_Field,
    Heal_Target,
    Drain,
    Red_Light,
    Pressure,
    Yellow_Light,
    Lockdown,
    Breakdown,
    Forcefield,
    Teleport,
    Release,
    Cross_Formation,
    Inverted_Wedge_Formation,
    Echelon_B_Formation,
    Star_Formation,
    Deploy_Chaff,
    Reduce_Damage,
    Air_Bombing_Mode,
    Charge_Shot,
    Healing_Field,
    Elevation,
    Big_Boom,
    Invisible,
    Deploy_Chaffs,
    Multitarget_Mode,
    Ground_Bombing_Mode,
};
*/
enum class SkillType : int
{
    Turnaround,
    Back_Move_Mach,
    Defense_Up,
    Concentration,
    Frenzy,
    Berserker,
    Silence,
    Purchasing_Shop,
    Selling_Shop,
    Hyper_Moving,
    Chain_Rolling,
    Overbooster,
    Evasion_Up,
    Missile_Shot,
    Fire_Shot,
    Hyper_Shot,
    Shield_Paralyze,
    Camouflage,
    Snare_Shot,
    Ground_Accelerator,
    Barrier,
    Remedy,
    Siege_Defense,
    Collision_Absorption,
    Air_Siege_Mode,
    Siege_Mode,
    Purify,
    Full_Recovery,
    Scanning,
    Call_of_Hero,
    Smart_SP,
    Fuel_Replenish,
    Reverse_Engine,
    Invincible,
    Raging_Evasion,
    Raging_Defense,
    Raging_Fire,
    Repair_Target,
    Repair_Field,
    Heal_Target,
    Release,
    Deploy_Chaff,
    Reduce_Damage,
    Air_Bombing_Mode,
    Charge_Shot,
    Healing_Field,
    Elevation,
    Big_Boom,
    Invisible,
    Deploy_Chaffs,
    Multitarget_Mode,
    Ground_Bombing_Mode,
    Unknown,
};

enum class GearType
{
    IGear,
    BGear,
    MGear,
    AGear
};

enum class MapNumber
{
    WatermelonIsland = 9002,
    InvasionWorld = 9050,

};

enum class EnchantItemType
{
    None,
    Accuracy,
    Reattack,
    MinMax,
    Speed,
    Overheating,
    Range,
    Time,
    Weight,
    Shield,
    Energy,
    EnergyShield,
    EnchantProtectE1,
    EnchantProtectE5,
    EnchantChance3P,
    EnchantChance5P,
    EnchantChance8P
};

using EnchantTextPair = std::pair<EnchantItemType, std::string>;
using EnchantListType = std::vector<EnchantTextPair>;

enum class Desparam
{
    AdvancedAccuracy = 21,
    StandardAccuracy = 20,
    AdvancedQuickFire = 32,
    StandardQuickFire = 31,
    AdvancedAttack = 19,
    StandardAttack = 18,
    StandardOverheating = 73,
    Shield = 89,
    Energy = 13,
    AdvancedSpeed = 176,
    AdvancedRange = 36,
    StandardRange = 35,
    Suffix = 94,
    Prefix = 93,
    EnchantChance = 192,
    EnchantItemProtect = 190,
    AdvancedTime = 49,
    StandardTime = 48,
    StandardWeight = 75, 
    AdvancedWeight = 76,
};

enum class ItemNumber : int
{
    StandardQuickFireCard = 7000650,
    AdvancedQuickFireCard = 7000660,
    StandardProbabilityCard = 7008230,
    AdvancedProbabilityCard = 7008240,
    StandardAttackCard = 7000630,
    AdvancedAttackCard = 7000640,
    StandardOverheatingCard = 7008220,
    EnergyShieldCard = 7004650,
    BGearShieldCard = 7008320,
    IGearShieldCard = 7008330,
    MGearShieldCard = 7008340,
    AGearShieldCard = 7008350,
    EnergyCard = 7004570,
    AdvancedSpeedCard = 7004580,
    StandardRangeCard = 7008150,
    AdvancedRangeCard = 7008160,
    EnchantChance3PercentCard = 7029600,
    EnchantChance5PercentCard = 7029610,
    EnchantChance8PercentCard = 7029620,
    EnchantItemProtectCard = 7001170,
    EnchantItemProtectCard2 = 7010270,
    BasicItemProtectCard = 7001171,
    StandardTimeCard = 7002540,
    AdvancedTimeCard = 7002550,
    AdvancedWeightCard = 7002530,
    StandardWeightCard = 7000670,

    // kits
    S_Type_RepairKit_1 = 7010290,
    S_Type_RepairKit_2 = 7022940,
    A_Type_RepairKit_1 = 7003060,
    A_Type_RepairKit_2 = 7016920,
    B_Type_RepairKit   = 7003040,
    C_Type_RepairKit   = 7003020,

    S_Type_ShieldKit_1 = 7010300,
    S_Type_ShieldKit_2 = 7022950,
    A_Type_ShieldKit_1 = 7003070,
    A_Type_ShieldKit_2 = 7016930,
    B_Type_ShieldKit   = 7003050,
    C_Type_ShieldKit   = 7003030,

    A_Type_SkillPKit_1 = 7002840,
    A_Type_SkillPKit_2 = 7016940,
    B_Type_SkillPKit   = 7002850,
    C_Type_SkillPKit   = 7002860,
    A_Type_SkillPit_MG = 7002841,
    B_Type_SkillPKit_MG = 7002851,
    C_Type_SkillPKit_MG = 7002861,

    AmmunitionRechargeBox = 7022120,
    B_Type_CondensedFuel = 7008100,
    C_Type_CondensedFuel = 7008090,
    D_Type_CondensedFuel = 7008080,
    E_Type_CondensedFuel =  7000790,
              
    // Watermelon Bot
    Square_Watermelon_Gift = 7023970,

    // Skills
    IG_Turnaround_2 = 7832022,
    IG_Turnaround_1 = 7832021,
    IG_Back_Move_Mach_4 = 7832014,
    IG_Back_Move_Mach_3 = 7832013,
    IG_Back_Move_Mach_2 = 7832012,
    IG_Back_Move_Mach_1 = 7832011,
    IG_Defense_Up_6 = 7831016,
    IG_Defense_Up_5 = 7831015,
    IG_Defense_Up_4 = 7831014,
    IG_Defense_Up_3 = 7831013,
    IG_Defense_Up_2 = 7831012,
    IG_Defense_Up_1 = 7831011,
    IG_Concentration_7 = 7830047,
    IG_Concentration_6 = 7830046,
    IG_Concentration_5 = 7830045,
    IG_Concentration_4 = 7830044,
    IG_Concentration_3 = 7830043,
    IG_Concentration_2 = 7830042,
    IG_Concentration_1 = 7830041,
    IG_Frenzy_9 = 7830039,
    IG_Frenzy_8 = 7830038,
    IG_Frenzy_7 = 7830037,
    IG_Berserker_4 = 7833054,
    IG_Berserker_3 = 7833053,
    IG_Berserker_2 = 7833052,
    IG_Berserker_1 = 7833051,
    IG_Silence_1 = 7833041,
    IG_Purchasing_Shop_1 = 7833031,
    IG_Selling_Shop_1 = 7833021,
    IG_Hyper_Moving_1 = 7833011,
    IG_Chain_Rolling_1 = 7832041,
    IG_Overbooster_1 = 7832031,
    IG_Turnaround_4 = 7832024,
    IG_Turnaround_3 = 7832023,
    IG_Evasion_Up_7 = 7831027,
    IG_Evasion_Up_6 = 7831026,
    IG_Evasion_Up_5 = 7831025,
    IG_Evasion_Up_4 = 7831024,
    IG_Evasion_Up_3 = 7831023,
    IG_Evasion_Up_2 = 7831022,
    IG_Evasion_Up_1 = 7831021,
    IG_Defense_Up_7 = 7831017,
    IG_Frenzy_6 = 7830036,
    IG_Frenzy_5 = 7830035,
    IG_Frenzy_4 = 7830034,
    IG_Frenzy_3 = 7830033,
    IG_Frenzy_2 = 7830032,
    IG_Frenzy_1 = 7830031,
    IG_Missile_Shot_9 = 7830029,
    IG_Missile_Shot_8 = 7830028,
    IG_Missile_Shot_7 = 7830027,
    IG_Missile_Shot_6 = 7830026,
    IG_Missile_Shot_5 = 7830025,
    IG_Missile_Shot_4 = 7830024,
    IG_Missile_Shot_3 = 7830023,
    IG_Missile_Shot_2 = 7830022,
    IG_Missile_Shot_1 = 7830021,
    IG_Fire_Shot_9 = 7830019,
    IG_Fire_Shot_8 = 7830018,
    IG_Fire_Shot_7 = 7830017,
    IG_Fire_Shot_6 = 7830016,
    IG_Fire_Shot_5 = 7830015,
    IG_Fire_Shot_4 = 7830014,
    IG_Fire_Shot_3 = 7830013,
    IG_Fire_Shot_2 = 7830012,
    IG_Fire_Shot_1 = 7830011,
    AG_Hyper_Shot_4 = 7823064,
    AG_Hyper_Shot_3 = 7823063,
    AG_Hyper_Shot_2 = 7823062,
    AG_Hyper_Shot_1 = 7823061,
    AG_Shield_Paralyze_1 = 7823051,
    AG_Camouflage_1 = 7823041,
    AG_Purchasing_Shop_1 = 7823031,
    AG_Selling_Shop_1 = 7823021,
    AG_Snare_Shot_3 = 7823013,
    AG_Snare_Shot_2 = 7823012,
    AG_Snare_Shot_1 = 7823011,
    AG_Ground_Accelerator_3 = 7822013,
    AG_Ground_Accelerator_2 = 7822012,
    AG_Ground_Accelerator_1 = 7822011,
    AG_Barrier_1 = 7821061,
    AG_Remedy_7 = 7821057,
    AG_Remedy_6 = 7821056,
    AG_Remedy_5 = 7821055,
    AG_Remedy_4 = 7821054,
    AG_Remedy_3 = 7821053,
    AG_Remedy_2 = 7821052,
    AG_Remedy_1 = 7821051,
    AG_Siege_Defense_4 = 7821044,
    AG_Siege_Defense_3 = 7821043,
    AG_Siege_Defense_2 = 7821042,
    AG_Siege_Defense_1 = 7821041,
    AG_Collision_Absorption_1 = 7821031,
    AG_Evasion_Up_7 = 7821027,
    AG_Evasion_Up_6 = 7821026,
    AG_Evasion_Up_5 = 7821025,
    AG_Evasion_Up_4 = 7821024,
    AG_Evasion_Up_3 = 7821023,
    AG_Evasion_Up_2 = 7821022,
    AG_Evasion_Up_1 = 7821021,
    AG_Defense_Up_7 = 7821017,
    AG_Defense_Up_6 = 7821016,
    AG_Defense_Up_5 = 7821015,
    AG_Defense_Up_4 = 7821014,
    AG_Defense_Up_3 = 7821013,
    AG_Defense_Up_2 = 7821012,
    AG_Defense_Up_1 = 7821011,
    AG_Air_Siege_Mode_6 = 7820066,
    AG_Air_Siege_Mode_5 = 7820065,
    AG_Air_Siege_Mode_4 = 7820064,
    AG_Air_Siege_Mode_3 = 7820063,
    AG_Air_Siege_Mode_2 = 7820062,
    AG_Air_Siege_Mode_1 = 7820061,
    AG_Siege_Mode_9 = 7820059,
    AG_Siege_Mode_8 = 7820058,
    AG_Siege_Mode_4 = 7820054,
    AG_Siege_Mode_3 = 7820053,
    AG_Siege_Mode_2 = 7820052,
    AG_Siege_Mode_1 = 7820051,
    AG_Concentration_7 = 7820037,
    AG_Concentration_6 = 7820036,
    AG_Concentration_5 = 7820035,
    AG_Concentration_4 = 7820034,
    AG_Concentration_3 = 7820033,
    AG_Concentration_2 = 7820032,
    AG_Concentration_1 = 7820031,
    AG_Missile_Shot_9 = 7820029,
    AG_Missile_Shot_8 = 7820028,
    AG_Missile_Shot_7 = 7820027,
    AG_Missile_Shot_6 = 7820026,
    AG_Missile_Shot_5 = 7820025,
    AG_Missile_Shot_4 = 7820024,
    AG_Missile_Shot_3 = 7820023,
    AG_Missile_Shot_2 = 7820022,
    _Inverted_Bell_Formation_1 = 7813131,
    _Bell_Formation_1 = 7813111,
    _Wedge_Formation_1 = 7813101,
    _Echelon_A_Formation_1 = 7813091,
    MG_Purify_1 = 7813081,
    MG_Full_Recovery_4 = 7813074,
    MG_Full_Recovery_3 = 7813073,
    MG_Full_Recovery_2 = 7813072,
    MG_Full_Recovery_1 = 7813071,
    MG_Scanning_1 = 7813061,
    MG_Purchasing_Shop_1 = 7813051,
    MG_Selling_Shop_1 = 7813041,
    MG_Call_of_Hero_1 = 7813031,
    MG_Smart_SP_3 = 7813023,
    MG_Smart_SP_2 = 7813022,
    MG_Smart_SP_1 = 7813021,
    MG_Fuel_Replenish_3 = 7813013,
    MG_Fuel_Replenish_2 = 7813012,
    MG_Fuel_Replenish_1 = 7813011,
    MG_Reverse_Engine_1 = 7812021,
    MG_Invincible_1 = 7811101,
    MG_Raging_Evasion_9 = 7811099,
    MG_Raging_Evasion_8 = 7811098,
    MG_Raging_Evasion_7 = 7811097,
    MG_Raging_Evasion_6 = 7811096,
    MG_Raging_Evasion_5 = 7811095,
    MG_Raging_Evasion_4 = 7811094,
    MG_Raging_Evasion_3 = 7811093,
    MG_Raging_Evasion_2 = 7811092,
    MG_Raging_Evasion_1 = 7811091,
    MG_Raging_Defense_9 = 7811089,
    MG_Raging_Defense_8 = 7811088,
    MG_Raging_Defense_7 = 7811087,
    MG_Raging_Defense_6 = 7811086,
    MG_Raging_Defense_5 = 7811085,
    MG_Raging_Defense_4 = 7811084,
    MG_Raging_Defense_3 = 7811083,
    MG_Raging_Defense_2 = 7811082,
    MG_Raging_Defense_1 = 7811081,
    MG_Raging_Fire_9 = 7811079,
    MG_Raging_Fire_8 = 7811078,
    MG_Raging_Fire_7 = 7811077,
    MG_Raging_Fire_6 = 7811076,
    MG_Raging_Fire_5 = 7811075,
    MG_Raging_Fire_4 = 7811074,
    MG_Raging_Fire_3 = 7811073,
    MG_Raging_Fire_2 = 7811072,
    MG_Raging_Fire_1 = 7811071,
    MG_Energize_Target_9 = 7811069,
    MG_Energize_Target_8 = 7811068,
    MG_Energize_Target_7 = 7811067,
    MG_Energize_Target_3 = 7811063,
    MG_Energize_Target_2 = 7811062,
    MG_Energize_Target_1 = 7811061,
    MG_Energizing_Field_9 = 7811059,
    MG_Energizing_Field_8 = 7811058,
    MG_Energizing_Field_7 = 7811057,
    MG_Energizing_Field_6 = 7811056,
    MG_Energizing_Field_5 = 7811055,
    MG_Energizing_Field_4 = 7811054,
    MG_Energizing_Field_3 = 7811053,
    MG_Energizing_Field_2 = 7811052,
    MG_Energizing_Field_1 = 7811051,
    MG_Heal_Target_9 = 7811049,
    MG_Heal_Target_8 = 7811048,
    MG_Heal_Target_7 = 7811047,
    MG_Heal_Target_6 = 7811046,
    MG_Heal_Target_5 = 7811045,
    MG_Heal_Target_4 = 7811044,
    MG_Heal_Target_3 = 7811043,
    MG_Heal_Target_2 = 7811042,
    MG_Heal_Target_1 = 7811041,
    AG_Siege_Mode_7 = 7820057,
    AG_Siege_Mode_6 = 7820056,
    AG_Siege_Mode_5 = 7820055,
    AG_Missile_Shot_1 = 7820021,
    AG_Fire_Shot_9 = 7820019,
    AG_Fire_Shot_8 = 7820018,
    AG_Fire_Shot_7 = 7820017,
    AG_Fire_Shot_6 = 7820016,
    AG_Fire_Shot_5 = 7820015,
    AG_Fire_Shot_4 = 7820014,
    AG_Fire_Shot_3 = 7820013,
    AG_Fire_Shot_2 = 7820012,
    AG_Fire_Shot_1 = 7820011,
    _Drain_1 = 7813281,
    _Red_Light_1 = 7813271,
    _Pressure_1 = 7813261,
    _Yellow_Light_1 = 7813251,
    _Lockdown_1 = 7813241,
    _Breakdown_1 = 7813231,
    _Forcefield_1 = 7813221,
    _Teleport_1 = 7813211,
    _Full_Recovery_1 = 7813201,
    _Purify_1 = 7813191,
    MG_Release_1 = 7813181,
    _Cross_Formation_1 = 7813171,
    _Inverted_Wedge_Formation_1 = 7813161,
    _Echelon_B_Formation_1 = 7813151,
    _Star_Formation_1 = 7813141,
    BG_Deploy_Chaff_1 = 7801041,
    BG_Reduce_Damage_9 = 7801039,
    BG_Reduce_Damage_8 = 7801038,
    BG_Reduce_Damage_7 = 7801037,
    BG_Reduce_Damage_6 = 7801036,
    BG_Reduce_Damage_5 = 7801035,
    BG_Reduce_Damage_4 = 7801034,
    BG_Reduce_Damage_3 = 7801033,
    BG_Reduce_Damage_2 = 7801032,
    BG_Reduce_Damage_1 = 7801031,
    BG_Evasion_Up_7 = 7801027,
    BG_Evasion_Up_6 = 7801026,
    BG_Evasion_Up_5 = 7801025,
    BG_Evasion_Up_4 = 7801024,
    BG_Air_Bombing_Mode_4 = 7800074,
    BG_Air_Bombing_Mode_3 = 7800073,
    BG_Air_Bombing_Mode_2 = 7800072,
    BG_Air_Bombing_Mode_1 = 7800071,
    BG_Charge_Shot_6 = 7800066,
    BG_Charge_Shot_5 = 7800065,
    BG_Charge_Shot_4 = 7800064,
    BG_Charge_Shot_3 = 7800063,
    MG_Energize_Target_6 = 7811066,
    MG_Energize_Target_5 = 7811065,
    MG_Energize_Target_4 = 7811064,
    MG_Healing_Field_9 = 7811039,
    MG_Healing_Field_8 = 7811038,
    MG_Healing_Field_7 = 7811037,
    MG_Healing_Field_6 = 7811036,
    MG_Healing_Field_5 = 7811035,
    MG_Healing_Field_4 = 7811034,
    MG_Healing_Field_3 = 7811033,
    MG_Healing_Field_2 = 7811032,
    MG_Healing_Field_1 = 7811031,
    MG_Evasion_Up_7 = 7811027,
    MG_Evasion_Up_6 = 7811026,
    MG_Evasion_Up_5 = 7811025,
    MG_Evasion_Up_4 = 7811024,
    MG_Evasion_Up_3 = 7811023,
    MG_Evasion_Up_2 = 7811022,
    MG_Evasion_Up_1 = 7811021,
    MG_Defense_Up_7 = 7811017,
    MG_Defense_Up_6 = 7811016,
    MG_Defense_Up_5 = 7811015,
    MG_Defense_Up_4 = 7811014,
    MG_Defense_Up_3 = 7811013,
    MG_Defense_Up_2 = 7811012,
    MG_Defense_Up_1 = 7811011,
    MG_Elevation_8 = 7810048,
    MG_Elevation_7 = 7810047,
    MG_Elevation_6 = 7810046,
    MG_Elevation_5 = 7810045,
    MG_Elevation_4 = 7810044,
    MG_Elevation_3 = 7810043,
    MG_Elevation_2 = 7810042,
    MG_Elevation_1 = 7810041,
    MG_Concentration_7 = 7810037,
    MG_Concentration_6 = 7810036,
    MG_Concentration_5 = 7810035,
    MG_Concentration_4 = 7810034,
    MG_Concentration_3 = 7810033,
    MG_Concentration_2 = 7810032,
    MG_Concentration_1 = 7810031,
    MG_Missile_Shot_9 = 7810029,
    MG_Missile_Shot_8 = 7810028,
    MG_Missile_Shot_7 = 7810027,
    MG_Missile_Shot_6 = 7810026,
    MG_Missile_Shot_5 = 7810025,
    MG_Missile_Shot_4 = 7810024,
    MG_Missile_Shot_3 = 7810023,
    MG_Missile_Shot_2 = 7810022,
    MG_Missile_Shot_1 = 7810021,
    MG_Fire_Shot_9 = 7810019,
    MG_Fire_Shot_8 = 7810018,
    MG_Fire_Shot_7 = 7810017,
    MG_Fire_Shot_6 = 7810016,
    MG_Fire_Shot_5 = 7810015,
    MG_Fire_Shot_4 = 7810014,
    MG_Fire_Shot_3 = 7810013,
    MG_Fire_Shot_2 = 7810012,
    MG_Fire_Shot_1 = 7810011,
    BG_Big_Boom_4 = 7803044,
    BG_Big_Boom_3 = 7803043,
    BG_Big_Boom_2 = 7803042,
    BG_Big_Boom_1 = 7803041,
    BG_Invisible_1 = 7803031,
    BG_Purchasing_Shop_1 = 7803021,
    BG_Selling_Shop_1 = 7803011,
    BG_Turnaround_3 = 7802023,
    BG_Turnaround_2 = 7802022,
    BG_Turnaround_1 = 7802021,
    BG_Back_Move_Mach_3 = 7802013,
    BG_Back_Move_Mach_2 = 7802012,
    BG_Back_Move_Mach_1 = 7802011,
    BG_Deploy_Chaffs_7 = 7801047,
    BG_Deploy_Chaffs_6 = 7801046,
    BG_Deploy_Chaffs_5 = 7801045,
    BG_Deploy_Chaffs_4 = 7801044,
    BG_Deploy_Chaffs_3 = 7801043,
    BG_Deploy_Chaff_2 = 7801042,
    BG_Evasion_Up_3 = 7801023,
    BG_Evasion_Up_2 = 7801022,
    BG_Evasion_Up_1 = 7801021,
    BG_Defense_Up_7 = 7801017,
    BG_Defense_Up_6 = 7801016,
    BG_Defense_Up_5 = 7801015,
    BG_Defense_Up_4 = 7801014,
    BG_Defense_Up_3 = 7801013,
    BG_Defense_Up_2 = 7801012,
    BG_Defense_Up_1 = 7801011,
    BG_Air_Bombing_Mode_7 = 7800077,
    BG_Air_Bombing_Mode_6 = 7800076,
    BG_Air_Bombing_Mode_5 = 7800075,
    BG_Charge_Shot_2 = 7800062,
    BG_Charge_Shot_1 = 7800061,
    BG_Multitarget_Mode_8 = 7800058,
    BG_Multitarget_Mode_7 = 7800057,
    BG_Multitarget_Mode_6 = 7800056,
    BG_Multitarget_Mode_5 = 7800055,
    BG_Multitarget_Mode_4 = 7800054,
    BG_Multitarget_Mode_3 = 7800053,
    BG_Multitarget_Mode_2 = 7800052,
    BG_Multitarget_Mode_1 = 7800051,
    BG_Ground_Bombing_Mode_9 = 7800049,
    BG_Ground_Bombing_Mode_8 = 7800048,
    BG_Ground_Bombing_Mode_7 = 7800047,
    BG_Ground_Bombing_Mode_6 = 7800046,
    BG_Ground_Bombing_Mode_5 = 7800045,
    BG_Ground_Bombing_Mode_4 = 7800044,
    BG_Ground_Bombing_Mode_3 = 7800043,
    BG_Ground_Bombing_Mode_2 = 7800042,
    BG_Ground_Bombing_Mode_1 = 7800041,
    BG_Concentration_7 = 7800037,
    BG_Concentration_6 = 7800036,
    BG_Concentration_5 = 7800035,
    BG_Concentration_4 = 7800034,
    BG_Concentration_3 = 7800033,
    BG_Concentration_2 = 7800032,
    BG_Concentration_1 = 7800031,
    BG_Missile_Shot_9 = 7800029,
    BG_Missile_Shot_8 = 7800028,
    BG_Missile_Shot_7 = 7800027,
    BG_Missile_Shot_6 = 7800026,
    BG_Missile_Shot_5 = 7800025,
    BG_Missile_Shot_4 = 7800024,
    BG_Missile_Shot_3 = 7800023,
    BG_Missile_Shot_2 = 7800022,
    BG_Missile_Shot_1 = 7800021,
    BG_Fire_Shot_9 = 7800019,
    BG_Fire_Shot_8 = 7800018,
    BG_Fire_Shot_7 = 7800017,
    BG_Fire_Shot_6 = 7800016,
    BG_Fire_Shot_5 = 7800015,
    BG_Fire_Shot_4 = 7800014,
    BG_Fire_Shot_3 = 7800013,
    BG_Fire_Shot_2 = 7800012,
    BG_Fire_Shot_1 = 7800011,           
};

enum class MonsterIndex : unsigned int
{
    Watermelon_Z = 2090600,
    Watermelon_Tank = 2090700,
    Easter_Egg = 2082300,
};

// gamble items

#define SUPERGAMBLE_STD_PREFIX_1		7001180		// from snowmen
#define SUPERGAMBLE_STD_SUFFIX_1		7001200		// from snowmen
#define SUPERGAMBLE_ADV_PREFIX_1		7001210		// from snowmen
#define SUPERGAMBLE_ADV_SUFFIX_1		7001220		// from snowmen

#define SUPERGAMBLE_STD_PREFIX_2		7010280		// normal
#define SUPERGAMBLE_STD_SUFFIX_2		7010400		// normal
#define SUPERGAMBLE_ADV_PREFIX_2		7010410		// normal
#define SUPERGAMBLE_ADV_SUFFIX_2		7010420		// normal

#define INITIALIZATION_PREFIX_1			7001150		// from snowmen
#define INITIALIZATION_SUFFIX_1			7001160		// from snowmen

#define INITIALIZATION_PREFIX_2			7010660		// normal  
#define INITIALIZATION_SUFFIX_2			7010670		// normal



// pierce 
#define HYPERFIX_STD_PREFIX_ARCHRIVAL			2010
#define HYPERFIX_STD_PREFIX_BANDIT				2011
#define HYPERFIX_STD_PREFIX_ADVERSARY			2012
#define HYPERFIX_STD_PREFIX_BANE				2013
#define HYPERFIX_STD_PREFIX_CHALLENGER			2014
#define HYPERFIX_STD_PREFIX_TRAITOR				2015
#define HYPERFIX_STD_PREFIX_STRONGHOLD			2027


#define HYPERFIX_ADV_PREFIX_ARCHRIVAL			2510
#define HYPERFIX_ADV_PREFIX_BANDIT				2511
#define HYPERFIX_ADV_PREFIX_ADVERSARY			2512
#define HYPERFIX_ADV_PREFIX_BANE				2513
#define HYPERFIX_ADV_PREFIX_CHALLENGER			2514
#define HYPERFIX_ADV_PREFIX_TRAITOR				2515
#define HYPERFIX_ADV_PREFIX_STRONGHOLD			2527


// reatttack / prob	
#define HYPERFIX_STD_PREFIX_METEO				1439
#define HYPERFIX_STD_PREFIX_SILENCE				1442
#define HYPERFIX_STD_PREFIX_BIO					1443
#define HYPERFIX_STD_PREFIX_ATTACK				1446
#define HYPERFIX_STD_PREFIX_LEGEND				1447

#define HYPERFIX_ADV_PREFIX_METEO				1843
#define HYPERFIX_ADV_PREFIX_SILENCE				1846
#define HYPERFIX_ADV_PREFIX_BIO					1847
#define HYPERFIX_ADV_PREFIX_ATTACK				1850
#define HYPERFIX_ADV_PREFIX_LEGEND				1851

#define HYPERFIX_STD_SUFFIX_METEO				5438
#define HYPERFIX_STD_SUFFIX_SILENCE				5441
#define HYPERFIX_STD_SUFFIX_BIO					5442
#define HYPERFIX_STD_SUFFIX_ATTACK				5445
#define HYPERFIX_STD_SUFFIX_LEGEND				5446

#define HYPERFIX_ADV_SUFFIX_METEO				5843
#define HYPERFIX_ADV_SUFFIX_SILENCE				5846
#define HYPERFIX_ADV_SUFFIX_BIO					5847
#define HYPERFIX_ADV_SUFFIX_ATTACK				5850
#define HYPERFIX_ADV_SUFFIX_LEGEND				5851


// minmax / prob
#define HYPERFIX_STD_PREFIX_NAVAS				1359
#define HYPERFIX_STD_PREFIX_AGARETH				1364
#define HYPERFIX_STD_PREFIX_ASMODI				1369
#define HYPERFIX_STD_PREFIX_KOBAL				1374
#define HYPERFIX_STD_PREFIX_WARRIOR			    4505
#define HYPERFIX_STD_PREFIX_HOUND			    1378
#define HYPERFIX_STD_PREFIX_PROSON			    1363
#define HYPERFIX_STD_PREFIX_ALOKEN			    1368
#define HYPERFIX_STD_PREFIX_TOBIT			    1373

#define HYPERFIX_ADV_PREFIX_NAVAS				1763
#define HYPERFIX_ADV_PREFIX_AGARETH				1768
#define HYPERFIX_ADV_PREFIX_ASMODI				1773
#define HYPERFIX_ADV_PREFIX_KOBAL				1778
#define HYPERFIX_ADV_PREFIX_WARRIOR 			4506
#define HYPERFIX_ADV_PREFIX_HOUND			    1782
#define HYPERFIX_ADV_PREFIX_PROSON			    1767
#define HYPERFIX_ADV_PREFIX_ALOKEN			    1772
#define HYPERFIX_ADV_PREFIX_TOBIT			    1777
    
#define HYPERFIX_STD_SUFFIX_NAVAS				5358
#define HYPERFIX_STD_SUFFIX_AGARETH				5363
#define HYPERFIX_STD_SUFFIX_ASMODI				5358
#define HYPERFIX_STD_SUFFIX_KOBAL				5367
#define HYPERFIX_STD_SUFFIX_WARRIOR				9507
#define HYPERFIX_STD_SUFFIX_HOUND			    5377
#define HYPERFIX_STD_SUFFIX_PROSON			    5362
#define HYPERFIX_STD_SUFFIX_ALOKEN			    5367
#define HYPERFIX_STD_SUFFIX_TOBIT			    5372
      
#define HYPERFIX_ADV_SUFFIX_NAVAS				5763
#define HYPERFIX_ADV_SUFFIX_AGARETH				5768
#define HYPERFIX_ADV_SUFFIX_ASMODI				5773
#define HYPERFIX_ADV_SUFFIX_KOBAL				5778
#define HYPERFIX_ADV_SUFFIX_WARRIOR				9508
#define HYPERFIX_ADV_SUFFIX_HOUND			    5782
#define HYPERFIX_ADV_SUFFIX_PROSON			    5767
#define HYPERFIX_ADV_SUFFIX_ALOKEN			    5772 
#define HYPERFIX_ADV_SUFFIX_TOBIT			    5777
 

// minmax / reatt

#define HYPERFIX_MMREA_STD_PREFIX_RUKIEPER	    1407
#define HYPERFIX_MMREA_STD_PREFIX_SQUIRE		1411
#define HYPERFIX_MMREA_STD_PREFIX_MAJOR		    1414 
#define HYPERFIX_MMREA_STD_PREFIX_MAX			1415
                                                
#define HYPERFIX_MMREA_ADV_PREFIX_RUKIEPER	    1811
#define HYPERFIX_MMREA_ADV_PREFIX_SQUIRE		1815
#define HYPERFIX_MMREA_ADV_PREFIX_MAJOR		    1818 
#define HYPERFIX_MMREA_ADV_PREFIX_MAX			1819

#define HYPERFIX_MMREA_STD_SUFFIX_RUKIEPER	    5406
#define HYPERFIX_MMREA_STD_SUFFIX_SQUIRE		5410
#define HYPERFIX_MMREA_STD_SUFFIX_MAJOR		    5413
#define HYPERFIX_MMREA_STD_SUFFIX_MAX			5414
  
#define HYPERFIX_MMREA_ADV_SUFFIX_RUKIEPER	    5811
#define HYPERFIX_MMREA_ADV_SUFFIX_SQUIRE		5815
#define HYPERFIX_MMREA_ADV_SUFFIX_MAJOR		    5818
#define HYPERFIX_MMREA_ADV_SUFFIX_MAX			5819


#define FIXSELECTION_NONE                       ((int)0)
#define FIXSELECTION_ONLY_GOOD                  ((int)1)
#define FIXSELECTION_ONLY_BEST                  ((int)2)



const int g_GoodPiercePrefixList[] =
{
    HYPERFIX_STD_PREFIX_ARCHRIVAL,
    HYPERFIX_STD_PREFIX_BANDIT,
    HYPERFIX_STD_PREFIX_ADVERSARY,
    HYPERFIX_STD_PREFIX_BANE,
    HYPERFIX_STD_PREFIX_CHALLENGER,
    HYPERFIX_STD_PREFIX_TRAITOR,
    HYPERFIX_STD_PREFIX_STRONGHOLD,

    HYPERFIX_ADV_PREFIX_ARCHRIVAL,
    HYPERFIX_ADV_PREFIX_BANDIT,
    HYPERFIX_ADV_PREFIX_ADVERSARY,
    HYPERFIX_ADV_PREFIX_BANE,
    HYPERFIX_ADV_PREFIX_CHALLENGER,
    HYPERFIX_ADV_PREFIX_TRAITOR,
    HYPERFIX_ADV_PREFIX_STRONGHOLD
};

const int g_BestPiercePrefixList[] =
{
    HYPERFIX_STD_PREFIX_BANDIT,
    HYPERFIX_STD_PREFIX_TRAITOR,

    HYPERFIX_ADV_PREFIX_BANDIT,
    HYPERFIX_ADV_PREFIX_TRAITOR,
};

const int g_GoodProbReattackPrefixList[] =
{
    HYPERFIX_STD_PREFIX_METEO,				
    HYPERFIX_STD_PREFIX_SILENCE,				
    HYPERFIX_STD_PREFIX_BIO,					
    HYPERFIX_STD_PREFIX_ATTACK,				
    HYPERFIX_STD_PREFIX_LEGEND,				

    HYPERFIX_ADV_PREFIX_METEO,				
    HYPERFIX_ADV_PREFIX_SILENCE,				
    HYPERFIX_ADV_PREFIX_BIO,					
    HYPERFIX_ADV_PREFIX_ATTACK,				
    HYPERFIX_ADV_PREFIX_LEGEND,	
};

const int g_GoodProbReattackSuffixList[] =
{
    HYPERFIX_STD_SUFFIX_METEO,				
    HYPERFIX_STD_SUFFIX_SILENCE,				
    HYPERFIX_STD_SUFFIX_BIO,					
    HYPERFIX_STD_SUFFIX_ATTACK,				
    HYPERFIX_STD_SUFFIX_LEGEND,				

    HYPERFIX_ADV_SUFFIX_METEO,				
    HYPERFIX_ADV_SUFFIX_SILENCE,				
    HYPERFIX_ADV_SUFFIX_BIO,					
    HYPERFIX_ADV_SUFFIX_ATTACK,				
    HYPERFIX_ADV_SUFFIX_LEGEND,				
};

const int g_BestProbReattackPrefixList[] =
{
    HYPERFIX_STD_PREFIX_BIO,
    HYPERFIX_STD_PREFIX_LEGEND,

    HYPERFIX_ADV_PREFIX_BIO,
    HYPERFIX_ADV_PREFIX_LEGEND,
};

const int g_BestProbReattackSuffixList[] =
{  
    HYPERFIX_STD_SUFFIX_BIO,
    HYPERFIX_STD_SUFFIX_LEGEND,
      
    HYPERFIX_ADV_SUFFIX_BIO,
    HYPERFIX_ADV_SUFFIX_LEGEND,
};

const int g_GoodProbDamagePrefixList[] =
{
    HYPERFIX_STD_PREFIX_NAVAS,				
    HYPERFIX_STD_PREFIX_AGARETH,				
    HYPERFIX_STD_PREFIX_ASMODI,				
    HYPERFIX_STD_PREFIX_KOBAL,				
    HYPERFIX_STD_PREFIX_WARRIOR,
    HYPERFIX_STD_PREFIX_HOUND,			    
    HYPERFIX_STD_PREFIX_PROSON,			    
    HYPERFIX_STD_PREFIX_ALOKEN,
    HYPERFIX_STD_PREFIX_TOBIT,
        
    HYPERFIX_ADV_PREFIX_NAVAS,				
    HYPERFIX_ADV_PREFIX_AGARETH,				
    HYPERFIX_ADV_PREFIX_ASMODI,				
    HYPERFIX_ADV_PREFIX_KOBAL,				
    HYPERFIX_ADV_PREFIX_WARRIOR,
    HYPERFIX_ADV_PREFIX_HOUND,
    HYPERFIX_ADV_PREFIX_PROSON,
    HYPERFIX_ADV_PREFIX_ALOKEN,
    HYPERFIX_ADV_PREFIX_TOBIT,
};

const int g_GoodProbDamageSuffixList[] =
{
    HYPERFIX_STD_SUFFIX_NAVAS,				
    HYPERFIX_STD_SUFFIX_AGARETH,				
    HYPERFIX_STD_SUFFIX_ASMODI,				
    HYPERFIX_STD_SUFFIX_KOBAL,				
    HYPERFIX_STD_SUFFIX_WARRIOR,
    HYPERFIX_STD_SUFFIX_PROSON,
    HYPERFIX_STD_SUFFIX_ALOKEN,
    HYPERFIX_STD_SUFFIX_TOBIT,
            
    HYPERFIX_ADV_SUFFIX_NAVAS,				
    HYPERFIX_ADV_SUFFIX_AGARETH,				
    HYPERFIX_ADV_SUFFIX_ASMODI,				
    HYPERFIX_ADV_SUFFIX_KOBAL,				
    HYPERFIX_ADV_SUFFIX_WARRIOR,
    HYPERFIX_ADV_SUFFIX_HOUND,
    HYPERFIX_ADV_SUFFIX_PROSON,
    HYPERFIX_ADV_SUFFIX_ALOKEN,
    HYPERFIX_ADV_SUFFIX_TOBIT,
};

const int g_BestProbDamagePrefixList[] =
{
    HYPERFIX_STD_PREFIX_NAVAS,
    HYPERFIX_STD_PREFIX_AGARETH,
    HYPERFIX_STD_PREFIX_ASMODI,
    HYPERFIX_STD_PREFIX_KOBAL,
    HYPERFIX_STD_PREFIX_WARRIOR,

    HYPERFIX_ADV_PREFIX_NAVAS,
    HYPERFIX_ADV_PREFIX_AGARETH,
    HYPERFIX_ADV_PREFIX_ASMODI,
    HYPERFIX_ADV_PREFIX_KOBAL,
    HYPERFIX_ADV_PREFIX_WARRIOR,
};

const int g_BestProbDamageSuffixList[] =
{
    HYPERFIX_STD_SUFFIX_NAVAS,
    HYPERFIX_STD_SUFFIX_AGARETH,
    HYPERFIX_STD_SUFFIX_ASMODI,
    HYPERFIX_STD_SUFFIX_KOBAL,
    HYPERFIX_STD_SUFFIX_WARRIOR,

    HYPERFIX_ADV_SUFFIX_NAVAS,
    HYPERFIX_ADV_SUFFIX_AGARETH,
    HYPERFIX_ADV_SUFFIX_ASMODI,
    HYPERFIX_ADV_SUFFIX_KOBAL,
    HYPERFIX_ADV_SUFFIX_WARRIOR,
};

const int g_GoodReattackDamagePrefixList[] =
{
    HYPERFIX_MMREA_STD_PREFIX_RUKIEPER,	    
    HYPERFIX_MMREA_STD_PREFIX_SQUIRE,		
    HYPERFIX_MMREA_STD_PREFIX_MAJOR,		     
    HYPERFIX_MMREA_STD_PREFIX_MAX,			

    HYPERFIX_MMREA_ADV_PREFIX_RUKIEPER,    
    HYPERFIX_MMREA_ADV_PREFIX_SQUIRE,		
    HYPERFIX_MMREA_ADV_PREFIX_MAJOR,		     
    HYPERFIX_MMREA_ADV_PREFIX_MAX,	
};

const int g_GoodReattackDamageSuffixList[] =
{  
     HYPERFIX_MMREA_STD_SUFFIX_RUKIEPER,	    
     HYPERFIX_MMREA_STD_SUFFIX_SQUIRE,		
     HYPERFIX_MMREA_STD_SUFFIX_MAJOR,		    
     HYPERFIX_MMREA_STD_SUFFIX_MAX,			

     HYPERFIX_MMREA_ADV_SUFFIX_RUKIEPER,	    
     HYPERFIX_MMREA_ADV_SUFFIX_SQUIRE,		
     HYPERFIX_MMREA_ADV_SUFFIX_MAJOR,		    
     HYPERFIX_MMREA_ADV_SUFFIX_MAX,			 
};

const int g_BestReattackDamagePrefixList[] =
{
    HYPERFIX_MMREA_STD_PREFIX_SQUIRE,
    HYPERFIX_MMREA_STD_PREFIX_MAX,

    HYPERFIX_MMREA_ADV_PREFIX_SQUIRE,
    HYPERFIX_MMREA_ADV_PREFIX_MAX,
};

const int g_BestReattackDamageSuffixList[] =
{
     HYPERFIX_MMREA_STD_SUFFIX_SQUIRE,
     HYPERFIX_MMREA_STD_SUFFIX_MAX,

     HYPERFIX_MMREA_ADV_SUFFIX_SQUIRE,
     HYPERFIX_MMREA_ADV_SUFFIX_MAX,
};

