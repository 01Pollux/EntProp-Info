
#include "ServerClass.h"

namespace SMServerClass
{
	
	inline cell_t ToCell(void* cls)
	{
		return reinterpret_cast<cell_t>(cls);
	}
	inline ServerClass* FromCell(cell_t param)
	{
		return reinterpret_cast<ServerClass*>(param);
	}


	cell_t FirstClass(IPluginContext* pCtx, const cell_t* params)
	{
		return ToCell(gamedll->GetAllServerClasses());
	}

	cell_t NextClass(IPluginContext* pCtx, const cell_t* params)
	{
		ServerClass* cls = FromCell(params[1]);
		return ToCell(cls->m_pNext);
	}

	cell_t Name(IPluginContext* pCtx, const cell_t* params)
	{
		ServerClass* cls = FromCell(params[1]);
		pCtx->StringToLocal(params[2], params[3], cls->m_pNetworkName);
		return 0;
	}

	cell_t ClassID(IPluginContext* pCtx, const cell_t* params)
	{
		ServerClass* cls = FromCell(params[1]);
		return cls->m_ClassID;
	}

	cell_t GetSendTable(IPluginContext* pCtx, const cell_t* params)
	{
		ServerClass* cls = FromCell(params[1]);
		return ToCell(cls->m_pTable);
	}

	const sp_nativeinfo_t natives[] =
	{
		{ "ServerClass.FirstClass",			SMServerClass::FirstClass	},
		{ "ServerClass.NextClass.get",		SMServerClass::NextClass	},
		{ "ServerClass.ClassID.get",		SMServerClass::ClassID		},
		{ "ServerClass.SendTable.get",		SMServerClass::GetSendTable	},
		{ "ServerClass.Name",				SMServerClass::Name			},


		{ NULL, NULL }
	};
	std::function<CEntityFactoryDictionary* ()> get_dict;
}