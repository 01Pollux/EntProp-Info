# Entity Prop Info
A helper extension that provides exported methods like `FindSendPropInfo`, SendProps, SendTables and ServerClasses lookup

# Enumerate all classnames
```SourcePawn
void EnumerateAllClassnames()
{
  EntityFactory ef = EntityFactory.FirstFactory();
	EntityFactory ief = EntityFactory.InvalidIndex();
	
	char name[48];
	
	while (ef != ief)
	{
		ef.FactoryName(name, sizeof(name));
		PrintToServer("EntFactory[%i] (classname = %s) / (size = %i)", ef, name, ef.EntitySize());
		
		ef = ef.NextFactory();
	}
	
	PrintToServer("EntityFactory.Size = %i", EntityFactory.FactoryCount());
}
```

# Example usage for ServerClass methodmap
```SourcePawn
void SMDrawSendTable(SendTable pTable, int level = 1)
{
	SendTable table;
	SendProp prop;
	char name[64];
	
	int count = pTable.Count;
	for (int i; i < count; i++)
	{
		prop = pTable.Prop(i);
		table = prop.DataTable;
		prop.Name(name, sizeof(name));
		
		if (table != INVALID_SEND_TABLE)
		{
			PrintToServer("Table: %s (offset %i) (deep %i)", name, prop.Offset, level);
			SMDrawSendTable(table, level + 1);
		}
		else {
			PrintToServer("Member: %s, (offset %i) (type: %i) (bits %i)", name, prop.Offset, prop.Type, prop.Bits);
		}
	}
}

SendTable FindSendTableInServerClass(const char[] target)
{
	ServerClass sc = ServerClass.FirstClass();
	char name[48];
	
	while (sc)
	{
		sc.Name(name, sizeof(name));
		if (!strcmp(name, target))
			return sc.SendTable;
		
		sc = sc.NextClass;
	}
	
	return INVALID_SEND_TABLE;
}
```
Useful for finding unsupported props offset
