#include <utility>
#include <map>
#include <string>

using std::make_pair;

extern int len = 0;
extern std::string Itemlist[1 << 16];
typedef void (*update)(Item);//更新方块数据
//template<typename T1, typename T2>
class Item
{
public:
	Item();
	~Item();
private:
	int id;
	std::pair<int, int> address;
};
class Block
{
public:
	Block();
	~Block();
	std::pair<int, int> get_block_id();
	Item get_char(int x, int y);
private:
	Item m[256][256];//区块的信息
	int x, y;//区块的编号
};
struct gmap//地图结构，没有复杂的功能需实现，使用后结构体
{
	std::map<std::pair<int, int>, Block> blocks;
	Item get_item(int x, int y)
	{
		blocks[make_pair(x / 256, y / 256)].get_char(x % 256, y % 256);
	}
};
