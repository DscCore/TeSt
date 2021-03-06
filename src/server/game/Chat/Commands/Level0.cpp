/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "World.h"
#include "Player.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"
#include "math.h"
#include "ArenaTeamMgr.h"

bool ChatHandler::HandleHelpCommand(const char* args)
{
    char* cmd = strtok((char*)args, " ");
    if (!cmd)
    {
        ShowHelpForCommand(getCommandTable(), "help");
        ShowHelpForCommand(getCommandTable(), "");
    }
    else
    {
        if (!ShowHelpForCommand(getCommandTable(), cmd))
            SendSysMessage(LANG_NO_HELP_CMD);
    }

    return true;
}

bool ChatHandler::HandleCommandsCommand(const char* /*args*/)
{
    ShowHelpForCommand(getCommandTable(), "");
    return true;
}

bool ChatHandler::HandleStartCommand(const char* /*args*/)
{
    // Jail mod start:
    if (m_session->GetPlayer()->m_jail_isjailed)
    {
        SendSysMessage(LANG_JAIL_DENIED);
        return true;
    }
    // Jail mod end.  
    Player* player = m_session->GetPlayer();

    if (player->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    if (player->isInCombat())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    if (player->isDead() || player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
    {
        // if player is dead and stuck, send ghost to graveyard
        player->RepopAtGraveyard();
        return true;
    }

    // cast spell Stuck
    player->CastSpell(player, 8690, false);
    return true;
}

bool ChatHandler::HandleServerInfoCommand(const char* /*args*/)
{
    uint32 playersNum = sWorld->GetPlayerCount();
    uint32 maxPlayersNum = sWorld->GetMaxPlayerCount();
    uint32 activeClientsNum = sWorld->GetActiveSessionCount();
    uint32 queuedClientsNum = sWorld->GetQueuedSessionCount();
    uint32 maxActiveClientsNum = sWorld->GetMaxActiveSessionCount();
    uint32 maxQueuedClientsNum = sWorld->GetMaxQueuedSessionCount();
    std::string uptime = secsToTimeString(sWorld->GetUptime());
    uint32 updateTime = sWorld->GetUpdateTime();
	PSendSysMessage("Сервер был сделан под заказ сервера WoW Tenerby!");
	PSendSysMessage("Данная сборка не является паблик сборкой и не распостраняется.");
    PSendSysMessage("Желаем приятной игры у нас на сервере.");
	
    PSendSysMessage(" ");
    PSendSysMessage("-- Информация");
    SendSysMessage(_FULLVERSION);
    PSendSysMessage(LANG_CONNECTED_PLAYERS, playersNum, maxPlayersNum);
    //PSendSysMessage(LANG_CONNECTED_USERS, activeClientsNum, maxActiveClientsNum, queuedClientsNum, maxQueuedClientsNum);
    PSendSysMessage(LANG_UPTIME, uptime.c_str());
    PSendSysMessage(LANG_UPDATE_DIFF, updateTime);
    //! Can't use sWorld->ShutdownMsg here in case of console command
    if (sWorld->IsShuttingDown())
        PSendSysMessage(LANG_SHUTDOWN_TIMELEFT, secsToTimeString(sWorld->GetShutDownTimeLeft()).c_str());
    PSendSysMessage(" ");

    return true;
}

bool ChatHandler::HandleDismountCommand(const char* /*args*/)
{
    Player* player = m_session->GetPlayer();

    //If player is not mounted, so go out :)
    if (!player->IsMounted())
    {
        SendSysMessage(LANG_CHAR_NON_MOUNTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (player->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    player->Dismount();
    player->RemoveAurasByType(SPELL_AURA_MOUNTED);
    return true;
}

bool ChatHandler::HandleSaveCommand(const char* /*args*/)
{
    Player* player = m_session->GetPlayer();
    
	// Jail by Airus special for WoW Tenerby
    if (player->m_jail_isjailed)
    {
        SendSysMessage(LANG_JAIL_DENIED);
        return true;
    }
  
    // save GM account without delay and output message
    if (!AccountMgr::IsPlayerAccount(m_session->GetSecurity()))
    {
        if (Player* target = getSelectedPlayer())
            target->SaveToDB();
        else
            player->SaveToDB();
        SendSysMessage(LANG_PLAYER_SAVED);
        return true;
    }

    // save if the player has last been saved over 20 seconds ago
    uint32 save_interval = sWorld->getIntConfig(CONFIG_INTERVAL_SAVE);
    if (save_interval == 0 || (save_interval > 20 * IN_MILLISECONDS && player->GetSaveTimer() <= save_interval - 20 * IN_MILLISECONDS))
        player->SaveToDB();

    return true;
}

/// Display the 'Message of the day' for the realm
bool ChatHandler::HandleServerMotdCommand(const char* /*args*/)
{
    PSendSysMessage(LANG_MOTD_CURRENT, sWorld->GetMotd());
    return true;
}
// Jail by Airus special for WoW Tenerby
bool ChatHandler::HandleJailInfoCommand(const char* args)
{
    time_t localtime;
    localtime = time(NULL);
    Player *chr = m_session->GetPlayer();

    if (chr->m_jail_release > 0)
    {
        uint32 min_left = (uint32)floor(float(chr->m_jail_release - localtime) / 60);

        if (min_left <= 0)
        {
            chr->m_jail_release = 0;
            chr->_SaveJail();
            SendSysMessage(LANG_JAIL_NOTJAILED_INFO);
            return true;
        }
        else
        {
            if (min_left >= 60) PSendSysMessage(LANG_JAIL_JAILED_H_INFO, (uint32)floor(float(chr->m_jail_release - localtime) / 60 / 60));
            else PSendSysMessage(LANG_JAIL_JAILED_M_INFO, min_left);
            PSendSysMessage(LANG_JAIL_REASON, chr->m_jail_gmchar.c_str(), chr->m_jail_reason.c_str());

            return true;
        }
    }
    else
    {
        SendSysMessage(LANG_JAIL_NOTJAILED_INFO);
        return true;
    }
    return false;
}