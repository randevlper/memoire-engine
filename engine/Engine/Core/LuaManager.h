typedef struct lua_State lua_State;


class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	void test();

private:
	lua_State* _L;
};