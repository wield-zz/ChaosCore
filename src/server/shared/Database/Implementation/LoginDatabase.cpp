/*
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "LoginDatabase.h"

bool LoginDatabaseConnection::Open(const std::string& infoString)
{
    if (!MySQLConnection::Open(infoString))
        return false;

    m_stmts.resize(MAX_LOGINDATABASE_STATEMENTS);

    /*
        ##################################
        LOAD YOUR PREPARED STATEMENTS HERE
        ##################################
    */
    PrepareStatement(LOGIN_GET_REALMLIST, "SELECT id, name, address, port, icon, color, timezone, allowedSecurityLevel, population, gamebuild FROM realmlist WHERE color <> 3 ORDER BY name");
    PrepareStatement(LOGIN_SET_VS, "UPDATE account SET v = ?, s = ? WHERE username = ?");
    PrepareStatement(LOGIN_SET_LOGONPROOF, "UPDATE account SET sessionkey = ?, last_ip = ?, last_login = NOW(), locale = ?, failed_logins = 0 WHERE username = ?");
    PrepareStatement(LOGIN_GET_LOGONCHALLENGE, "SELECT a.sha_pass_hash,a.id,a.locked,a.last_ip,aa.gmlevel,a.v,a.s FROM account a LEFT JOIN account_access aa ON (a.id = aa.id) WHERE a.username = ?");

    return true;
}