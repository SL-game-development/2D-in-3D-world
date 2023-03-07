#include <utility>
#include <map>
#include <string>

using std::make_pair;

extern int len = 0;
extern std::string Itemlist[1 << 16];
typedef void (*update)(Item);//���·�������
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
	Item m[256][256];//�������Ϣ
	int x, y;//����ı��
};
struct gmap//��ͼ�ṹ��û�и��ӵĹ�����ʵ�֣�ʹ�ú�ṹ��
{
	std::map<std::pair<int, int>, Block> blocks;
	Item get_item(int x, int y)
	{
		blocks[make_pair(x / 256, y / 256)].get_char(x % 256, y % 256);
	}
};
