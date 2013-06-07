/*
 * SD Name: Npc Premium Master.
 * SD Custom Script.
 * SD Special For Vip Account Patch.
 * SD Complete 100%.
 * SD Autor (Crispi).
 * SD Data 02.01.2012.
 */

#include "ScriptPCH.h"

#define CONST_ARENA_RENAME 500
#define CONST_ARENA_CUSTOMIZE 500
#define CONST_ARENA_CHANGE_FACTION 1000
#define CONST_ARENA_CHANGE_RACE 1000

#define EMOTE_NO_VIP "Sorry Im Only For VIP Players..."
#define EMOTE_COOLDOWN "Can Not Do It This Time..."
#define EMOTE_NO_SICKENSS "You Dont Have Resurrection Sickness Aura!"
#define EMOTE_NO_DESERTER "You Dont Have Deserter Aura!"
#define EMOTE_COMBAT "You Are In Combat!"
#define EMOTE_NO_ARENA_POINTS "You Have Enough Arena Points!"
#define EMOTE_ALREADY_ITEM "You Have Already Item!"

#define MSG_RENAME_COMPLETE "Make Logout and Enter the New Name of the Character. Do not forget After Name Change, to Bowl off And remove From the Client Cache Folder!"
#define MSG_CUSTOMIZE_COMPLETE "Make Logout and Change Appearance of the Character. Do not forget After Appearance Change, to Bowl off And remove From the Client Cache Folder!"
#define MSG_CHANGE_FACTION_COMPLETE "Make Logout and Change Fraction of the Character. Do not forget After Appearance Change, to Bowl off And remove From the Client Cache Folder!" 
#define MSG_CHANGE_RACE_COMPLETE "Make Logout and Change Race of the Character. Do not forget After Race of Appearance, to Bowl off And remove From the Client Cache Folder!"
#define MSG_MAX_SKILL "You Skills Up To Maximum!"
#define MSG_REMOVE_SICKNESS_COMPLETE "Resurrection Sickness Removed and Restore Full Health and Mana."
#define MSG_REMOVE_DESERTER_COMPLETE "Deserter Removed! You Can Again Will Return In The Battleground!"
#define MSG_RIDING_COMPLETE "Your Riding Skill Up To Maximum"
#define MSG_RESET_COOLDOWN "Your Cooldown Has Been Reset!"
#define MSG_CHARACTER_SAVE_TO_DB "You Character Has Been Saved!"
#define MSG_RESET_QUEST_STATUS_COMPLETE "Your Daily and Weeekly Quest Cooldown Has Been Reset!"

class npc_premium_master : public CreatureScript
{
public:
    npc_premium_master() : CreatureScript("npc_premium_master") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
		if (!player->GetSession()->IsPremium() && !player->isGameMaster())
		{
			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper(EMOTE_NO_VIP, player->GetGUID(), true);
			return true;
		}
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(5, "Remove Resurrection Sickness", GOSSIP_SENDER_MAIN, 1209);
		player->ADD_GOSSIP_ITEM(5, "Remove Deserter", GOSSIP_SENDER_MAIN, 1210);
		player->ADD_GOSSIP_ITEM(5, "Heal Me", GOSSIP_SENDER_MAIN, 1202);
		player->ADD_GOSSIP_ITEM(5, "Save Me Please", GOSSIP_SENDER_MAIN, 1213);
		player->ADD_GOSSIP_ITEM(3, "Reset Talents", GOSSIP_SENDER_MAIN, 1207);
		player->ADD_GOSSIP_ITEM(3, "Reset Cooldown", GOSSIP_SENDER_MAIN, 1212);
		player->ADD_GOSSIP_ITEM(3, "Reset Quest Cooldown", GOSSIP_SENDER_MAIN, 1215);
		player->ADD_GOSSIP_ITEM(3, "Update To Max Skills", GOSSIP_SENDER_MAIN, 1204);
		player->ADD_GOSSIP_ITEM(3, "Riding", GOSSIP_SENDER_MAIN, 1211);
		player->ADD_GOSSIP_ITEM(7, "Give Me Please 36 Slot Bag", GOSSIP_SENDER_MAIN, 1216);
		player->ADD_GOSSIP_ITEM(9, "Mounts Rare ->", GOSSIP_SENDER_MAIN, 1208);
		player->ADD_GOSSIP_ITEM(9, "Mounts Elite ->", GOSSIP_SENDER_MAIN, 1217);
		player->ADD_GOSSIP_ITEM(9, "Mounts Proto ->", GOSSIP_SENDER_MAIN, 1218);
		player->ADD_GOSSIP_ITEM(6, "Morph ->", GOSSIP_SENDER_MAIN, 1203);
		player->ADD_GOSSIP_ITEM(6, "Buffs ->", GOSSIP_SENDER_MAIN, 1206);
		player->ADD_GOSSIP_ITEM(8, "Customize ->", GOSSIP_SENDER_MAIN, 1205);
		player->ADD_GOSSIP_ITEM(8, "Movie ->", GOSSIP_SENDER_MAIN, 1214);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
		return true;
	}
	
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 action)
	{
		if (!player->getAttackers().empty())
		{
			creature->MonsterWhisper(EMOTE_COMBAT, player->GetGUID(), true);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{

		case 1202: // Heal
			if (player->HasAura(45523))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterWhisper(EMOTE_COOLDOWN, player->GetGUID(), true);
                }
                else
                {
					player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player, 25840, true);
                    player->CastSpell(player, 45523, true);
                }
                break;
            case 1207: // Reset talents
                player->CLOSE_GOSSIP_MENU();
                player->SendTalentWipeConfirm(creature->GetGUID());
                break;
            case 1203: // Morphs
				player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "Star Craft Murlock", GOSSIP_SENDER_MAIN, 499);
                player->ADD_GOSSIP_ITEM(5, "Ambrose Boltspark", GOSSIP_SENDER_MAIN, 500);
                player->ADD_GOSSIP_ITEM(5, "Jonathan The Revelator", GOSSIP_SENDER_MAIN, 501);
                player->ADD_GOSSIP_ITEM(5, "Magi", GOSSIP_SENDER_MAIN, 502);
				player->ADD_GOSSIP_ITEM(5, "Worgen", GOSSIP_SENDER_MAIN, 503);
				player->ADD_GOSSIP_ITEM(5, "Pandaren Monk", GOSSIP_SENDER_MAIN, 504);
				player->ADD_GOSSIP_ITEM(5, "Crok Scourgebane", GOSSIP_SENDER_MAIN, 505);
				player->ADD_GOSSIP_ITEM(5, "Iron Mender", GOSSIP_SENDER_MAIN, 506);
				player->ADD_GOSSIP_ITEM(5, "Druid", GOSSIP_SENDER_MAIN, 507);
				player->ADD_GOSSIP_ITEM(5, "Priest", GOSSIP_SENDER_MAIN, 508);
				player->ADD_GOSSIP_ITEM(5, "Paladin", GOSSIP_SENDER_MAIN, 509);
				player->ADD_GOSSIP_ITEM(5, "Rogue", GOSSIP_SENDER_MAIN, 510);
				player->ADD_GOSSIP_ITEM(5, "Death Knight", GOSSIP_SENDER_MAIN, 511);
				player->ADD_GOSSIP_ITEM(5, "Warlock", GOSSIP_SENDER_MAIN, 512);
				player->ADD_GOSSIP_ITEM(5, "Warrior", GOSSIP_SENDER_MAIN, 513);
				player->ADD_GOSSIP_ITEM(5, "Mage", GOSSIP_SENDER_MAIN, 514);
				player->ADD_GOSSIP_ITEM(5, "Shaman", GOSSIP_SENDER_MAIN, 515);
				player->ADD_GOSSIP_ITEM(5, "Hunter", GOSSIP_SENDER_MAIN, 516);
				player->ADD_GOSSIP_ITEM(5, "Draenei Girl White", GOSSIP_SENDER_MAIN, 517);
				player->ADD_GOSSIP_ITEM(5, "Draenei Girl Black", GOSSIP_SENDER_MAIN, 518);
				player->ADD_GOSSIP_ITEM(0, "Demorph", GOSSIP_SENDER_MAIN, 519);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            case 499:
                player->CLOSE_GOSSIP_MENU(); // Starcraft Murlock
                player->SetDisplayId(29348);
                break;
            case 500:
                player->CLOSE_GOSSIP_MENU(); // Ambrose Boltspark
                player->SetDisplayId(28586);
                break;
            case 501:
                player->CLOSE_GOSSIP_MENU(); // Jonathan The Revelator
                player->SetDisplayId(15867);
                break;
            case 502:
                player->CLOSE_GOSSIP_MENU(); // Shattered Sun Magi
                player->SetDisplayId(22959);
                break;
            case 503:
                player->CLOSE_GOSSIP_MENU(); // Worgen
                player->SetDisplayId(657);
                break;
            case 504:
                player->CLOSE_GOSSIP_MENU(); // Pandaren Monk
                player->SetDisplayId(30414);
                break;
            case 505:
                player->CLOSE_GOSSIP_MENU(); // Crok Scourgebane
                player->SetDisplayId(30911);
                break;
            case 506:
                player->CLOSE_GOSSIP_MENU(); // Iron Mender
                player->SetDisplayId(26239);
                break;
            case 507:
                player->CLOSE_GOSSIP_MENU(); // Druid
                player->SetDisplayId(30472);
                break;
            case 508:
                player->CLOSE_GOSSIP_MENU(); // Priest
                player->SetDisplayId(21419);
                break;
            case 509:
                player->CLOSE_GOSSIP_MENU(); // Paladin
				player->SetDisplayId(29774);
				break;
			case 510:
				player->CLOSE_GOSSIP_MENU(); // Rogue
				player->SetDisplayId(30485);
				break;
			case 511:
				player->CLOSE_GOSSIP_MENU(); // Death Knight
				player->SetDisplayId(27153);
				break;
			case 512:
				player->CLOSE_GOSSIP_MENU(); // Warlock
				player->SetDisplayId(30487);
				break;
			case 513:
				player->CLOSE_GOSSIP_MENU(); // Warrior
				player->SetDisplayId(30474);
				break;
			case 514:
				player->CLOSE_GOSSIP_MENU(); // Mage
				player->SetDisplayId(30477);
				break;
			case 515:
				player->CLOSE_GOSSIP_MENU(); // Shaman 
				player->SetDisplayId(29768);
				break;
			case 516:
				player->CLOSE_GOSSIP_MENU(); // Hunter
				player->SetDisplayId(21379);
				break;
			case 517:
				player->CLOSE_GOSSIP_MENU(); // Coliseum Champion
				player->SetDisplayId(30634);
				break;
			case 518:
				player->CLOSE_GOSSIP_MENU(); // Coliseum Champion
				player->SetDisplayId(30771);
				break;
			case 519: // Demorph Player (remove all morphs)
				player->CLOSE_GOSSIP_MENU();
                player->DeMorph();
                break;
            case 1206: // Buffs
				player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "Power Word Fortitude", GOSSIP_SENDER_MAIN, 4000);
				player->ADD_GOSSIP_ITEM(5, "Prayer of Spirit", GOSSIP_SENDER_MAIN, 4001);
				player->ADD_GOSSIP_ITEM(5, "Shadow Protection", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(5, "Greater Blessing of Kings", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(5, "Greater Bleesing of Might", GOSSIP_SENDER_MAIN,4004);
                player->ADD_GOSSIP_ITEM(5, "Greater Blessing of Wisdom", GOSSIP_SENDER_MAIN, 4005);
				player->ADD_GOSSIP_ITEM(5, "Greater Blessing of Sanctuary", GOSSIP_SENDER_MAIN, 4006);
				player->ADD_GOSSIP_ITEM(5, "Arane Intellect", GOSSIP_SENDER_MAIN, 4007);
				player->ADD_GOSSIP_ITEM(5, "Dampen Magic", GOSSIP_SENDER_MAIN, 4008);
				player->ADD_GOSSIP_ITEM(5, "Amplify Magic", GOSSIP_SENDER_MAIN, 4009);
                player->ADD_GOSSIP_ITEM(5, "Gift of the Wild", GOSSIP_SENDER_MAIN, 4010);
                player->ADD_GOSSIP_ITEM(5, "Thorns", GOSSIP_SENDER_MAIN, 4011);
				player->ADD_GOSSIP_ITEM(5, "Brilliance Intellect", GOSSIP_SENDER_MAIN, 4012);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            case 4000: // Power Word Fortitude
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48162, true);
                break;
            case 4001: // Prayer of Spirit
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48074, true);
                break;
            case 4002: // Shadow Protection
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48170, true);
                break;
            case 4003: // Greater Blessing of Kings
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 43223, true);
                break;
            case 4004: // Greater Bleesing of Might
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48934, true);
                break;
            case 4005: // Greater Blessing of Wisdom
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48938, true);
                break;
            case 4006: // Greater Blessing of Sanctuary
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 25899, true);
                break;
            case 4007: // Arane Intellect
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 36880, true);
                break;
            case 4008: // Dampen Magic
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 43015, true);
                break;
			case 4009: // Amplify Magic
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 43017, true);
				break;
			case 4010: // Gift of the Wild
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 69381, true);
				break;
			case 4011: // Thorns
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 467, true);
				break;
			case 4012: // Brilliance Intellect
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 69994, true);
				break;
			case 1205:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(0, "Rename [500 Arena Points]", GOSSIP_SENDER_MAIN, 2000);
				player->ADD_GOSSIP_ITEM(0, "Customize [500 Arena Points]", GOSSIP_SENDER_MAIN, 2001);
				player->ADD_GOSSIP_ITEM(0, "Change Faction [1000 Arena Points]", GOSSIP_SENDER_MAIN, 2002);
				player->ADD_GOSSIP_ITEM(0, "Change Race [1000 Arena Points]", GOSSIP_SENDER_MAIN, 2003);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				break;
			case 2000: // Rename
				if (player->GetArenaPoints() < CONST_ARENA_RENAME)
				{
					creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->SetAtLoginFlag(AT_LOGIN_RENAME);
					player->ModifyArenaPoints(-CONST_ARENA_RENAME);
					creature->MonsterWhisper(MSG_RENAME_COMPLETE, player->GetGUID());
				}
				break;
			case 2001: // Customize
				if (player->GetArenaPoints() < CONST_ARENA_CUSTOMIZE)
				{
					creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
					player->ModifyArenaPoints(-CONST_ARENA_CUSTOMIZE);
					creature->MonsterWhisper(MSG_CUSTOMIZE_COMPLETE, player->GetGUID());
				}
				break;
			case 2002: // Change Faction
				if (player->GetArenaPoints() < CONST_ARENA_CHANGE_FACTION)
				{
					creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
					player->ModifyArenaPoints(-CONST_ARENA_CHANGE_FACTION);
					creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
				}
				break;
			case 2003: // Change Race
				if (player->GetArenaPoints() < CONST_ARENA_CHANGE_RACE)
				{
					creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
					player->ModifyArenaPoints(-CONST_ARENA_CHANGE_RACE);
					creature->MonsterWhisper(MSG_CHANGE_RACE_COMPLETE, player->GetGUID());
				}
				break;
			case 1204: // Max Skills
				player->CLOSE_GOSSIP_MENU();
				player->UpdateSkillsToMaxSkillsForLevel();
				creature->MonsterWhisper(MSG_MAX_SKILL, player->GetGUID());
				break;
			case 1208: // Mounts Ground
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(5, "Black Qiraji Resonating Crystal", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Amani War Bear", GOSSIP_SENDER_MAIN, 101);
				player->ADD_GOSSIP_ITEM(5, "Big Battle Bear", GOSSIP_SENDER_MAIN, 102);
				player->ADD_GOSSIP_ITEM(5, "Deathcharger's Reins", GOSSIP_SENDER_MAIN, 103);
				player->ADD_GOSSIP_ITEM(5, "Fiery Warhorse's Reins", GOSSIP_SENDER_MAIN, 104);
				player->ADD_GOSSIP_ITEM(5, "Swift Burgundy Wolf", GOSSIP_SENDER_MAIN, 105);
				player->ADD_GOSSIP_ITEM(5, "Great Brewfest Kodo", GOSSIP_SENDER_MAIN, 106);
				player->ADD_GOSSIP_ITEM(5, "Horn of the Frostwolf Howler", GOSSIP_SENDER_MAIN, 107);
				player->ADD_GOSSIP_ITEM(5, "Magic Rooster Egg", GOSSIP_SENDER_MAIN, 108);
				player->ADD_GOSSIP_ITEM(5, "Reins of the White Polar Bear", GOSSIP_SENDER_MAIN, 109);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Brown Polar Bear", GOSSIP_SENDER_MAIN, 110);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Crimson Deathcharger", GOSSIP_SENDER_MAIN, 111);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Raven Lord", GOSSIP_SENDER_MAIN, 112);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Swift Spectral Tiger", GOSSIP_SENDER_MAIN, 113);
				player->ADD_GOSSIP_ITEM(5, "Sea Turtle", GOSSIP_SENDER_MAIN, 114);
				player->ADD_GOSSIP_ITEM(5, "Swift Razzashi Raptor", GOSSIP_SENDER_MAIN, 115);
				player->ADD_GOSSIP_ITEM(5, "Swift White Hawkstrider", GOSSIP_SENDER_MAIN, 116);
				player->ADD_GOSSIP_ITEM(5, "Swift Zhevra", GOSSIP_SENDER_MAIN, 117);
				player->ADD_GOSSIP_ITEM(5, "Swift Zulian Tiger", GOSSIP_SENDER_MAIN, 118);
				player->ADD_GOSSIP_ITEM(5, "The Horseman's Reins", GOSSIP_SENDER_MAIN, 119);
				player->ADD_GOSSIP_ITEM(5, "Wooly White Rhino", GOSSIP_SENDER_MAIN, 120);
				player->ADD_GOSSIP_ITEM(5, "Four Qiraji Resonating Crystal", GOSSIP_SENDER_MAIN, 121);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				break;
			case 100: // Black Qiraji Resonating Crystal
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(21176, 1);
				break;
			case 101: // Amani War Bear
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(33809, 1);
				break;
			case 102: // Big Battle Bear
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(38576, 1);
				break;
			case 103: // Deathcharger's Reins
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(13335, 1);
				break;
			case 104: // Fiery Warhorse's Reins
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(30480, 1);
				break;
			case 105: // Swift Burgundy Wolf
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 65646, true); // Cast Metod Because Item (Faction Flag)
				break;
			case 106: // Great Brewfest Kodo
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(37828, 1);
				break;
			case 107: // Horn of the Frostwolf Howler
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 23509, true); // Cast Metod Because Item (Faction Flag)
				break;
			case 108: // Magic Rooster Egg
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(46778, 1);
				break;
			case 109: // Reins of the White Polar Bear
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43962, 1);
				break;
			case 110: // Reins of the Brown Polar Bear
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43963, 1);
				break;
			case 111: // Reins of the Crimson Deathcharger
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(52200, 1);
				break;
			case 112: // Reins of the Raven Lord
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(32768, 1);
				break;
			case 113: // Reins of the Swift Spectral Tiger
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(33225, 1);
				break;
			case 114: // Sea Turtle
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(46109, 1);
				break;
			case 115: // Swift Razzashi Raptor
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(19872, 1);
				break;
			case 116: // Swift White Hawkstrider
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(35513, 1);
				break;
			case 117: // Swift Zhevra
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(37719, 1);
				break;
			case 118: // Swift Zulian Tiger
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(19902, 1);
				break;
			case 119: // The Horseman's Reins
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(37012, 1);
				break;
			case 120: // Wooly White Rhino
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(54068, 1);
				break;
			case 121: // Four Qiraji Resonating Crystal
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(21218, 1); // Blue Qiraji Resonating Crystal
				player->AddItem(21323, 1); // Green Qiraji Resonating Crystal
				player->AddItem(21321, 1); // Red Qiraji Resonating Crystal
				player->AddItem(21324, 1); // Yellow Qiraji Resonating Crystal
				break;
			case 1217: // Mounts Fly
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(5, "Argent Hippogryph", GOSSIP_SENDER_MAIN, 122);
				player->ADD_GOSSIP_ITEM(5, "Ashes of Alar", GOSSIP_SENDER_MAIN, 123);
				player->ADD_GOSSIP_ITEM(5, "Big Love Rocket", GOSSIP_SENDER_MAIN, 124);
				player->ADD_GOSSIP_ITEM(5, "Blazing Hippogryph", GOSSIP_SENDER_MAIN, 125);
				player->ADD_GOSSIP_ITEM(5, "Swift Nether Drake", GOSSIP_SENDER_MAIN, 126);
				player->ADD_GOSSIP_ITEM(5, "Vengeful Nether Drake", GOSSIP_SENDER_MAIN, 127);
				player->ADD_GOSSIP_ITEM(5, "Merciless Nether Drake", GOSSIP_SENDER_MAIN, 128);
				player->ADD_GOSSIP_ITEM(5, "Brutal Nether Drake", GOSSIP_SENDER_MAIN, 129);
				player->ADD_GOSSIP_ITEM(5, "Celestial Steed", GOSSIP_SENDER_MAIN, 130);
				player->ADD_GOSSIP_ITEM(5, "Deadly Gladiators Frost Wyrm", GOSSIP_SENDER_MAIN, 131);
				player->ADD_GOSSIP_ITEM(5, "Furious Gladiators Frost Wyrm", GOSSIP_SENDER_MAIN, 132);
				player->ADD_GOSSIP_ITEM(5, "Relentless Gladiators Frost Wyrm", GOSSIP_SENDER_MAIN, 133);
				player->ADD_GOSSIP_ITEM(5, "Wrathful Gladiators Frost Wyrm", GOSSIP_SENDER_MAIN, 134);
				player->ADD_GOSSIP_ITEM(5, "Invincibles Reins", GOSSIP_SENDER_MAIN, 135);
				player->ADD_GOSSIP_ITEM(5, "Mimirons Head", GOSSIP_SENDER_MAIN, 136);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Albino Drake", GOSSIP_SENDER_MAIN, 137);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Azure Drake", GOSSIP_SENDER_MAIN, 138);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Black Drake", GOSSIP_SENDER_MAIN, 139);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Blue Drake", GOSSIP_SENDER_MAIN, 140);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Bronze Drake", GOSSIP_SENDER_MAIN, 141);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Twilight Drake", GOSSIP_SENDER_MAIN, 152);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Onyxian Drake", GOSSIP_SENDER_MAIN, 142);
				player->ADD_GOSSIP_ITEM(5, "X-51 Nether-Rocket X-TREME", GOSSIP_SENDER_MAIN, 143);
				player->ADD_GOSSIP_ITEM(5, "X-53 Touring Rocket", GOSSIP_SENDER_MAIN, 144);
				player->ADD_GOSSIP_ITEM(5, "Frozen Frost Wyrm Heart", GOSSIP_SENDER_MAIN, 145);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				break;
			case 122: // Argent Hippogryph
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(45725, 1);
				break;
			case 123: // Ashes of Alar
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(32458, 1);
				break;
			case 124: // Big Love Rocket
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(50520, 1);
				break;
			case 125: // Blazing Hippogryph
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(54069, 1);
				break;
			case 126: // Swift Nether Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(30609, 1);
				break;
			case 127: // Vengeful Nether Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(37676, 1);
				break;
			case 128: // Merciless Nether Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(34092, 1);
				break;
			case 129: // Brutal Nether Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43516, 1);
				break;
			case 130: // Celestial Steed
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(54811, 1);
				break;
			case 131: // Deadly Gladiator's Frost Wyrm
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(46708, 1);
				break;
			case 132: // Furious Gladiator's Frost Wyrm
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(46171, 1);
				break;
			case 133: // Relentless Gladiator's Frost Wyrm
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(47840, 1);
				break;
			case 134: // Wrathful Gladiator's Frost Wyrm
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(50435, 1);
				break;
			case 135: // Invincibles Reins
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(50818, 1);
				break;
			case 136: // Mimiron's Head
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(45693, 1);
				break;
			case 137: // Reins of the Albino Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44178, 1);
				break;
			case 138: // Reins of the Azure Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43952, 1);
				break;
			case 139: // Reins of the Black Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43986, 1);
				break;
			case 140: // Reins of the Blue Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43953, 1);
				break;
			case 141: // Reins of the Bronze Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43951, 1);
				break;
			case 142: // Reins of the Onyxian Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(49636, 1);
				break;
			case 152: // Reins of the Twilight Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(43954, 1);
				break;
			case 143: // X-51 Nether-Rocket X-TREME
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(35226, 1);
				break;
			case 144: // X-53 Touring Rocket
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(54860, 1);
				break;
			case 145: // Frozen Frost Wyrm Heart
				player->CLOSE_GOSSIP_MENU();   // 33182 Swift Flying Broom // // 33184 Swift Magic Broom // 37011 Magic Broom // 33183 ld Magic Broom
				player->AddItem(38690, 1);
				break;
			case 1218:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(5, "Reins of the Black Proto-Drake", GOSSIP_SENDER_MAIN, 160);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Blue Proto-Drake", GOSSIP_SENDER_MAIN, 161);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Green Proto-Drake", GOSSIP_SENDER_MAIN, 162);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Ironbound Proto-Drake", GOSSIP_SENDER_MAIN, 163);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Plagued Proto-Drake", GOSSIP_SENDER_MAIN, 164);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Red Proto-Drake", GOSSIP_SENDER_MAIN, 165);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Rusted Proto-Drake", GOSSIP_SENDER_MAIN, 166);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Time-Lost Proto-Drake", GOSSIP_SENDER_MAIN, 167);
				player->ADD_GOSSIP_ITEM(5, "Reins of the Violet Proto-Drake", GOSSIP_SENDER_MAIN, 168);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				break;
			case 160: // Reins of the Black Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44164, 1);
				break;
			case 161: // Reins of the Blue Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44151, 1);
				break;
			case 162: // Reins of the Green Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44707, 1);
				break;
			case 163: // Reins of the Ironbound Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(45801, 1);
				break;
			case 164: // Reins of the Plagued Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44175, 1);
				break;
			case 165: // Reins of the Red Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44160, 1);
				break;
			case 166: // Reins of the Rusted Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(45802, 1);
				break;
			case 167: // Reins of the Time-Lost Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44168, 1);
				break;
			case 168: // Reins of the Violet Proto-Drake
				player->CLOSE_GOSSIP_MENU();
				player->AddItem(44177, 1);
				break;
			case 1209: // Remove Resurrection Sickness Aura
				if(!player->HasAura(15007))
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterTextEmote(EMOTE_NO_SICKENSS, 0, true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->RemoveAurasDueToSpell(15007);
					player->SetHealth(player->GetMaxHealth()); //Restore Health
					player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA)); // Restore Mana
					creature->MonsterWhisper(MSG_REMOVE_SICKNESS_COMPLETE, player->GetGUID());
				}
				break;
			case 1210: // Remove Deserter Aura
				if(!player->HasAura(26013))
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterTextEmote(EMOTE_NO_DESERTER, 0, true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->RemoveAurasDueToSpell(26013);
					creature->MonsterWhisper(MSG_REMOVE_DESERTER_COMPLETE, player->GetGUID());
				}
				break;
			case 1211: // Riding Skills
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, 33389, true); // Apprentice Riding
				player->CastSpell(player, 33392, true); // Journeyman Riding
				player->CastSpell(player, 34092, true); // Expert Riding
				player->CastSpell(player, 34093, true); // Artisan Riding
				player->CastSpell(player, 54197, true); // Allows you to ride flying mounts in Northrend.
				creature->MonsterWhisper(MSG_RIDING_COMPLETE, player->GetGUID());
				break;
			case 1212: // Reset Cooldown
				player->CLOSE_GOSSIP_MENU();
				player->RemoveAllSpellCooldown();
				creature->MonsterWhisper(MSG_RESET_COOLDOWN, player->GetGUID());
				break;
			case 1213: // Save Character Online
				player->CLOSE_GOSSIP_MENU();
				player->SaveToDB();
				creature->MonsterWhisper(MSG_CHARACTER_SAVE_TO_DB, player->GetGUID());
				break;
			case 1214: // Movie Menu
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(5, "World of Warcraft", GOSSIP_SENDER_MAIN, 250);
				player->ADD_GOSSIP_ITEM(5, "The Wrath Gate", GOSSIP_SENDER_MAIN, 251);
				player->ADD_GOSSIP_ITEM(5, "Fall of The Lich King", GOSSIP_SENDER_MAIN, 252);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				break;
			case 250: // Classic
				player->CLOSE_GOSSIP_MENU();
				player->SendMovieStart(2);
				break;
			case 251: // The Wrath Gate
				player->CLOSE_GOSSIP_MENU();
				player->SendMovieStart(14);
				break;
			case 252: // Fall of The Lich King
				player->CLOSE_GOSSIP_MENU();
				player->SendMovieStart(16);
				break;
			case 1215: // Reset Daily and Weekly Quest Cooldown
				player->CLOSE_GOSSIP_MENU();
				player->ResetDailyQuestStatus();
				player->ResetWeeklyQuestStatus();
				creature->MonsterWhisper(MSG_RESET_QUEST_STATUS_COMPLETE, player->GetGUID());
				break;
			case 1216: // 36 Slot Bag
				if (player->HasItemCount(23162,4))
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterTextEmote(EMOTE_ALREADY_ITEM, 0, true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->AddItem(23162, 4);
				}
				break;
		}
		return true;
	}
};

void AddSC_npc_premium_master()
{
	new npc_premium_master;
}