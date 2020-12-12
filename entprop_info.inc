#if defined _ENT_PROP_INFO
 #endinput
#endif
#define _ENT_PROP_INFO

#define INVALID_SERVER_CLASS 	view_as<SendProp>(0)
#define INVALID_SEND_TABLE 		view_as<SendTable>(0)
#define INVALID_SEND_PROP 		view_as<ServerClass>(0)

methodmap EntityFactory
{
	public static native int FactoryCount();
	
	public static native EntityFactory InvalidIndex();
	
	public static native EntityFactory FirstFactory();
	
	public native EntityFactory NextFactory();
	
	public native void FactoryName(char[] buffer, int maxlen);
	
	public native int EntitySize();
}

methodmap SendProp
{
	property int Type {
		public native get();
	}
	
	property int Bits {
		public native get();
	}
	
	property float LowValue {
		public native get();
	}
	
	property float HighValue {
		public native get();
	}
	
	property int Flags {
		public native get();
	}
	
	property int Offset {
		public native get();
	}
	
	property Address ExtraData {
		public native get();
	}
	
	property SendTable DataTable {
		public native get();
	}
	
	property SendProp Array {
		public native get();
	}
	
	property int ArraySize {
		public native get();
	}
	
	property int ArrayDist {
		public native get();
	}
	
	public native void Name(char[] buffer, int maxlen);
}

methodmap SendTable
{
	property int Count {
		public native get();
	}
	
	public native SendProp Prop(int pos);
}

methodmap ServerClass
{
	public static native ServerClass FirstClass();
	
	property ServerClass NextClass {
		public native get();
	}
	
	property int ClassID {
		public native get();
	}
	
	property SendTable SendTable {
		public native get();
	}
	
	public native void Name(char[] name, int maxlen);
}


#if !defined REQUIRE_EXTENSIONS
public __ext_INTERFACE_SetNTVOptional()
{
	MarkNativeAsOptional("ServerClass.FirstClass");
	MarkNativeAsOptional("ServerClass.NextClass.get");
	MarkNativeAsOptional("ServerClass.ClassID.get");
	MarkNativeAsOptional("ServerClass.SendTable.get");
	MarkNativeAsOptional("ServerClass.Name");
	
	MarkNativeAsOptional("EntityFactory.FactoryCount");
	MarkNativeAsOptional("EntityFactory.InvalidIndex");
	MarkNativeAsOptional("EntityFactory.FirstFactory");
	MarkNativeAsOptional("EntityFactory.NextFactory");
	MarkNativeAsOptional("EntityFactory.FactoryName");
	MarkNativeAsOptional("EntityFactory.EntitySize");
	
	MarkNativeAsOptional("SendTable.Count.get");
	MarkNativeAsOptional("SendTable.Prop");
	
	MarkNativeAsOptional("SendProp.Type.get");
	MarkNativeAsOptional("SendProp.Bits.get");
	MarkNativeAsOptional("SendProp.LowValue.get");
	MarkNativeAsOptional("SendProp.HighValue.get");
	MarkNativeAsOptional("SendProp.Flags.get");
	MarkNativeAsOptional("SendProp.Offset.get");
	MarkNativeAsOptional("SendProp.ExtraData.get");
	MarkNativeAsOptional("SendProp.DataTable.get");
	MarkNativeAsOptional("SendProp.Array.get");
	MarkNativeAsOptional("SendProp.ArraySize.get");
	MarkNativeAsOptional("SendProp.ArrayDist.get");
	MarkNativeAsOptional("SendProp.Name");
}
#endif

public Extension __ext_EntProp_Info = 
{
	name = "EntProp Info",
	file = "ent_prop_info.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};