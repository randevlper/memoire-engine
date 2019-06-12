class Input
{
public:
	//GetKeyDown
	static bool getKeyDown(int key);
	static bool getKeyUp(int key);
	static bool getKey(int key);
	//GetKeyUp
	//GetKey
private:
	Input();
	~Input();
	static void poll();

	//lastPoll
	//currentPoll
};