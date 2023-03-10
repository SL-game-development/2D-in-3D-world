//ͷ�ļ�
#include <utility>
#include <map>
#include <string>
//�����������
class Item;
class Entity;
class Block;
class gmap;
//using(��Ҫusing namespace std;
using std::make_pair;
//���͵�������
typedef std::pair<int, int> Addres;
//��������
	//����
typedef void (*Iupdate)(Item*);//���·�������
typedef int (*Iplace)(Item*);//���÷���
typedef int (*Idestroy)(Item*);//�ƻ�����
	//ʵ��
typedef void (*Eupdate)(Entity*);//����ʵ������
typedef int (*Esummon)(Entity*);//����ʵ��
typedef int (*Ekill)(Entity*);//ɱ��ʵ��
//һЩ����struct�������붨��
struct Sitem//item ���ֵ
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
struct GList//��������cur����Լ������Ҵ����㣬�ú�����
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
	void del()//ɾ��ǵ�delete����һ�
	{
		prev->next = next;
		next->prev = prev;
		delete me;
	}
	void add(_list* newone)//�ں����
	{
		_list* lnext = next;
		next = newone;
		newone->prev = this;
		newone->next = lnext;
	}
};
//ȫ�ֱ������������ǵü�extern������ͬ����.cpp�ж���
extern int Ilength = 0;//��������
extern Sitem items[1000];
extern int Elength = 0;//ʵ������
extern Sentity entitys[1000];
//Ȼ��������������
class Item//������
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
class Entity//ʵ���࣬����뷽����һ��
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
class Block//�����࣬Ϊ�˴��ͼ�����ɼ�ʡ�ռ�
{
public:
	Block();
	~Block();
	GList<Entity> entity;
	std::pair<int, int> get_block_id();
	Item get_char(int x, int y);
private:
	Item m[256][256];//�������Ϣ
	int x, y;//����ı��
};
class gmap//��ͼ�ṹ
{
public:
	std::map<std::pair<int, int>, Block> blocks;
	Item get_item(int x, int y)
	{
		blocks[make_pair(x / 256, y / 256)].get_char(x % 256, y % 256);
	}
};