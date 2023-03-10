//头文件
#include <utility>
#include <map>
#include <string>
//基础类的声明
class Item;
class Entity;
class Block;
class gmap;
//using(不要using namespace std;
using std::make_pair;
//类型的重命名
typedef std::pair<int, int> Addres;
//函数参数
	//方块
typedef void (*Iupdate)(Item*);//更新方块数据
typedef int (*Iplace)(Item*);//放置方块
typedef int (*Idestroy)(Item*);//破坏方块
	//实体
typedef void (*Eupdate)(Entity*);//更新实体数据
typedef int (*Esummon)(Entity*);//生成实体
typedef int (*Ekill)(Entity*);//杀死实体
//一些辅助struct的声明与定义
struct Sitem//item 类的值
{
	Iupdate _update;
	Iplace _place;
	Idestroy _destroy;
	std::string _id;
};
struct Sentity
{
	Eupdate _update;
	Esummon _summon;
	Ekill _kill;
	std::string _id;
};
template<typename T>
struct GList//链表，单向，cur你敢自己操作我打死你，用函数！
{
	T pool[100];
	int now = 0;
	_list first;
	GList(T* me)
	{
		this->first.prev = NULL;
		this->first.next = NULL;
		this->first.me = me;
	}
	_list *cur;
	int curadd()
	{
		if (cur->next != NULL)
		{
			cur = cur->next;
			return 0;
		}
		return 1;
	}
	void curless()
	{
		if (cur->prev != NULL)
		{
			cur = cur->prev;
			return 0;
		}
		return 1;
	}
	T* getcur()
	{
		return cur->me;
	}
	T* getnew()
	{
		if (now == 100)
		{
			pool = new T[100];
			now = 0;
		}
		return T[now++];
	}
};
struct _list
{
	_list* prev;
	_list* next;
	void* me;
	void del()//删完记得delete这个家伙
	{
		prev->next = next;
		next->prev = prev;
		delete me;
	}
	void add(_list* newone)//在后面加
	{
		_list* lnext = next;
		next = newone;
		newone->prev = this;
		newone->next = lnext;
	}
};
//全局变量的声明，记得加extern并且在同名的.cpp中定义
extern int Ilength = 0;//方块数量
extern Sitem items[1000];
extern int Elength = 0;//实体数量
extern Sentity entitys[1000];
//然后就是类的声明了
class Item//方块类
{
public:
	Item(Iupdate, Iplace, Idestroy, gmap*, std::string);
	Item();
	Item(Sitem, gmap*);
	~Item();
	std::map<std::string, std::string> date;
	void UpdateItem();
	int PlaceItem();
	int DestroyItem();
	Addres get_addres();
	void set_addres(Addres);
	gmap* Map;
	std::string id;
private:
	Addres addres;
	Iupdate Update;
	Iplace Place;
	Idestroy Destroy;
};
class Entity//实体类，大多与方块类一致
{
public:
	Entity(Eupdate, Esummon, Ekill, gmap*, std::string);
	Entity(Sentity, gmap*);
	~Entity();
	std::map<std::string, std::string> date;
	void UpdateEntity();
	int SummonEntity();
	int KillEntity();
	Addres get_addres();
	void set_addres(Addres);
	gmap* Map;
	std::string id;
private:
	Addres addres;
	Eupdate Update;
	Esummon Summon;
	Ekill Kill;
};
class Block//区块类，为了大地图的生成及省空间
{
public:
	Block();
	~Block();
	GList<Entity> entity;
	std::pair<int, int> get_block_id();
	Item get_char(int x, int y);
private:
	Item m[256][256];//区块的信息
	int x, y;//区块的编号
};
class gmap//地图结构
{
public:
	std::map<std::pair<int, int>, Block> blocks;
	Item get_item(int x, int y)
	{
		blocks[make_pair(x / 256, y / 256)].get_char(x % 256, y % 256);
	}
};