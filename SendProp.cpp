#include "SendProp.h"

namespace SMSendProp
{
	inline cell_t ToCell(const void* data)
	{
		return reinterpret_cast<cell_t>(data);
	}

	inline SendProp* ToSP(const cell_t data)
	{
		return reinterpret_cast<SendProp*>(data);
	}

	inline SendTable* ToDT(const cell_t param)
	{
		return reinterpret_cast<SendTable*>(param);
	}


	cell_t DTCount(IPluginContext* pCtx, const cell_t* params)
	{
		SendTable* pTable = ToDT(params[1]);
		return pTable->m_nProps;
	}

	cell_t DTProp(IPluginContext* pCtx, const cell_t* params)
	{
		SendTable* pTable = ToDT(params[1]);
		cell_t pos = params[2];
		
		if (pos < 0 || pos >= pTable->m_nProps)
			return pCtx->ThrowNativeError("Invalid data access %i (limit: %i)", pos, pTable->m_nProps);

		return ToCell(pTable->GetProp(pos));
	}

#define NATIVEPROP_DATA_RETURN(NAME, CODE) \
	cell_t Prop##NAME(IPluginContext* pCtx, const cell_t* params) \
	{ \
		SendProp* pProp = ToSP(params[1]); \
		CODE \
	}

	NATIVEPROP_DATA_RETURN(Type,		return pProp->m_Type;);
	NATIVEPROP_DATA_RETURN(Bits,		return pProp->m_nBits;);
	NATIVEPROP_DATA_RETURN(LowValue,	return sp_ftoc(pProp->m_fLowValue););
	NATIVEPROP_DATA_RETURN(HighValue,	return sp_ftoc(pProp->m_fHighValue););
	NATIVEPROP_DATA_RETURN(Flags,		return pProp->GetFlags(););
	NATIVEPROP_DATA_RETURN(Offset,		return pProp->GetOffset(););
	NATIVEPROP_DATA_RETURN(ExtraData,	return ToCell(pProp->GetExtraData()););
	NATIVEPROP_DATA_RETURN(DataTable,	return ToCell(pProp->GetDataTable()););

	NATIVEPROP_DATA_RETURN(ArrayProp,	return ToCell(pProp->m_pArrayProp););
	NATIVEPROP_DATA_RETURN(ArraySize,	return pProp->m_nElements;);
	NATIVEPROP_DATA_RETURN(ArrayDist,	return pProp->m_ElementStride;);

	NATIVEPROP_DATA_RETURN(Name, pCtx->StringToLocal(params[2], params[3], pProp->GetName()); return 0;);

	const sp_nativeinfo_t natives[] =
	{
		{ "SendTable.Count.get",	SMSendProp::DTCount			},
		{ "SendTable.Prop",			SMSendProp::DTProp			},

		{ "SendProp.Type.get",		SMSendProp::PropType		},
		{ "SendProp.Bits.get",		SMSendProp::PropBits		},
		{ "SendProp.LowValue.get",	SMSendProp::PropLowValue	},
		{ "SendProp.HighValue.get",	SMSendProp::PropHighValue	},
		{ "SendProp.Flags.get",		SMSendProp::PropFlags		},
		{ "SendProp.Offset.get",	SMSendProp::PropOffset		},
		{ "SendProp.ExtraData.get",	SMSendProp::PropExtraData	},
		{ "SendProp.DataTable.get",	SMSendProp::PropDataTable	},
		{ "SendProp.Array.get",		SMSendProp::PropArrayProp	},
		{ "SendProp.ArraySize.get",	SMSendProp::PropArraySize	},
		{ "SendProp.ArrayDist.get",	SMSendProp::PropArrayDist	},

		{ "SendProp.Name",			SMSendProp::PropName		},

		{ NULL, NULL }
	};
}