/**
 * vim: set ts=4 :
 * =============================================================================
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"

#include "ServerClass.h"
#include "Classnames.h"
#include "SendProp.h"

#include <toolframework/itoolentity.h>

class SMEntPropUtils : public SDKExtension
{
public:
	bool SDK_OnLoad(char* error, size_t maxlength, bool late) override;

public:
#ifdef SMEXT_CONF_METAMOD
	bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlength, bool late) override;
#endif
};

#ifdef SMEXT_CONF_METAMOD
static IServerTools* servertools;
#endif

static SMServerClass::CEntityFactoryDictionary* GetEntityFactoryDictionary()
{
	using EntFactory = SMServerClass::CEntityFactoryDictionary;
	static EntFactory* dict = nullptr;

#ifdef SMEXT_CONF_METAMOD
	dict = reinterpret_cast<EntFactory*>(servertools->GetEntityFactoryDictionary());
#else
	IGameConfig* gc;

	if (!dict)
	{
		void* addr;
		gameconfs->LoadGameConfigFile("sdktools.games", &gc, NULL, NULL);

		if (gc->GetMemSig("EntityFactoryFinder", (void**)&addr) && addr)
		{
			int offset;
			if (!gc->GetOffset("EntityFactoryOffset", &offset) || !offset)
			{
				gameconfs->CloseGameConfigFile(gc);
				return nullptr;
			}

			dict = *reinterpret_cast<EntFactory**>((intptr_t)addr + offset);
		}
	}

	if (!dict)
	{
		void* addr;
		if (!gc->GetMemSig("EntityFactory", &addr) || !addr)
		{
			int offset;

			if (!gc->GetMemSig("EntityFactoryCaller", &addr) || !addr)
			{
				gameconfs->CloseGameConfigFile(gc);
				return nullptr;
			}

			if (!gc->GetOffset("EntityFactoryCallOffset", &offset))
			{
				gameconfs->CloseGameConfigFile(gc);
				return nullptr;
			}

			// Get relative offset to function
			uintptr_t funcOffset = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(addr) + offset);

			// Get real address of function
			// Address of signature + offset of relative offset + sizeof(int32_t) offset + relative offset
			addr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(addr) + offset + 4 + funcOffset);
		}

		auto call = reinterpret_cast<EntFactory*(*)()>(addr);
		if (call)
			dict = call();
	}
	gameconfs->CloseGameConfigFile(gc);
#endif

	return dict;
}

bool SMEntPropUtils::SDK_OnLoad(char* error, size_t maxlength, bool late)
{
	SMServerClass::get_dict = std::bind(GetEntityFactoryDictionary);

	sharesys->AddNatives(myself, SMServerClass::natives);
	sharesys->AddNatives(myself, SMClassnames::natives);
	sharesys->AddNatives(myself, SMSendProp::natives);

	return true;
}

#ifdef SMEXT_CONF_METAMOD
bool SMEntPropUtils::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{

	GET_V_IFACE_CURRENT(GetServerFactory, servertools, IServerTools, VSERVERTOOLS_INTERFACE_VERSION);
	return true;
}
#endif

SMEntPropUtils g_SMEntPropUtils;
SMEXT_LINK(&g_SMEntPropUtils);