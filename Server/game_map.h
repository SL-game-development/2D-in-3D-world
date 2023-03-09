#include <utility>
#include <map>
#include <string>
class Item;
class Entity;
class Block;
class gmap;
using std::make_pair;

extern int len = 0;
typedef void (*Iupdate)(Item*);//���·�������
typedef int (*Iplace)(Item*);//���÷���
typedef int (*Idestroy)(Item*);//�ƻ�����
class Item
{
public:
	Item(Iupdate, Iplace, Idestroy, gmap*);
	~Item();
	std::map<std::string, std::string> date;
	void UpdateItem();
	int PlaceItem();
	int DestroyItem();
	gmap* Map;
private:
	int id;
	std::pair<int, int> address;
	Iupdate Update;
	Iplace Place;
	Idestroy Destroy;
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
class gmap//��ͼ�ṹ��û�и��ӵĹ�����ʵ�֣�ʹ�ú�ṹ��
{
public:
	std::map<std::pair<int, int>, Block> blocks;
	Item get_item(int x, int y)
	{
		blocks[make_pair(x / 256, y / 256)].get_char(x % 256, y % 256);
	}
};
