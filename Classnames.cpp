
#include "Classnames.h"
#include "ServerClass.h"

namespace SMClassnames
{
	using namespace SMServerClass;
	cell_t FactoryCount(IPluginContext* pCtx, const cell_t* params)
	{
		return get_dict()->m_Factories.Count();
	}

	cell_t InvalidIndex(IPluginContext* pCtx, const cell_t* params)
	{
		return get_dict()->m_Factories.InvalidIndex();
	}

	cell_t FirstFactory(IPluginContext* pCtx, const cell_t* params)
	{
		return get_dict()->m_Factories.First();
	}

	cell_t NextFactory(IPluginContext* pCtx, const cell_t* params)
	{
		ucell_t i = params[1];
		return get_dict()->m_Factories.Next(i);
	}

	cell_t FactoryName(IPluginContext* pCtx, const cell_t* params)
	{
		ucell_t i = params[1];

		pCtx->StringToLocal(params[2], params[3], get_dict()->m_Factories.GetElementName(i));
		return 0;
	}

	cell_t EntitySize(IPluginContext* pCtx, const cell_t* params)
	{
		ucell_t i = params[1];

		return get_dict()->m_Factories.Element(i)->GetEntitySize();
	}

	const sp_nativeinfo_t natives[] =
	{
		{ "EntityFactory.FactoryCount",		SMClassnames::FactoryCount	},
		{ "EntityFactory.InvalidIndex",		SMClassnames::InvalidIndex	},
		{ "EntityFactory.FirstFactory",		SMClassnames::FirstFactory	},
		{ "EntityFactory.NextFactory",		SMClassnames::NextFactory	},
		{ "EntityFactory.FactoryName",		SMClassnames::FactoryName	},
		{ "EntityFactory.EntitySize",		SMClassnames::EntitySize	},
		{ NULL,								NULL						}
	};
}