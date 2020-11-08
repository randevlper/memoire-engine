typedef struct lua_State lua_State;


class LuaManager
{
public:
	static void init();
	static void destroy();

	static void loadLua(const char* lua);
	static void luaFunction(const char* functionName);

private:
	static lua_State* _L;

	LuaManager(){}
	~LuaManager(){}
};