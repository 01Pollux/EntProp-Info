
#ifndef SERVER_CLASS_SM_NATIVES
#define SERVER_CLASS_SM_NATIVES

#include "extension.h"
#include <functional>
#include "utldict.h"

class IServerNetworkable;

namespace SMServerClass
{
	class IEntityFactory
	{
	public:
		virtual IServerNetworkable * Create(const char* pClassName) abstract;
		virtual void Destroy(IServerNetworkable* pNetworkable) abstract;
		virtual size_t GetEntitySize() abstract;
	};

	class IEntityFactoryDictionary
	{
	public:
		virtual void InstallFactory(IEntityFactory * pFactory, const char* pClassName) abstract;
		virtual IServerNetworkable* Create(const char* pClassName) abstract;
		virtual void Destroy(const char* pClassName, IServerNetworkable* pNetworkable) abstract;
		virtual IEntityFactory* FindFactory(const char* pClassName) abstract;
		virtual const char* GetCannonicalName(const char* pClassName) abstract;
	};

	class CEntityFactoryDictionary : public IEntityFactoryDictionary
	{
	private:
		IEntityFactory* FindFactory(const char* pClassName);
	public:
		CUtlDict<IEntityFactory*, unsigned short> m_Factories;
	};

	extern const sp_nativeinfo_t natives[];
	extern std::function<CEntityFactoryDictionary*()> get_dict;
}


#endif