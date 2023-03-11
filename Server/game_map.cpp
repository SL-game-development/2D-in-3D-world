#include "game_map.h"
//�����Ķ���
int Ilength = 0;//��������
Sitem items[1000];
std::map<Sitem, int> unitems;//��������ķ���
int Elength = 0;//ʵ������
Sentity entitys[1000];
std::map<Sentity, int> unentitys;//��������ķ���
void initall()
{
	//��ӷ�������items[i]=Stiem();
	items[0] = Sitem(NULL, NULL, NULL, "null");
	unitems[items[0]] = 0;
	//���ʵ������entitys[i]=new Sentity();
	entitys[0] = Sentity(NULL, NULL, NULL, "null");
	unitems[items[0]] = 0;
}
//������
void Item::UpdateItem()
{
	this->Update(this);
}
int Item::PlaceItem()
{
	return this->Place(this);
}
int Item::DestroyItem()
{
	return this->Destroy(this);
}
Item::Item(Iupdate _update, Iplace _place, Idestroy _destroy, gmap* _map, std::string _id)
{
	this->Update = _update;
	this->Place = _place;
	this->Destroy = _destroy;
	this->Map = _map;
	this->id = _id;
}
Item::Item(Sitem _item, gmap* _map)
{
	this->Update = _item._update;
	this->Place = _item._place;
	this->Destroy = _item._destroy;
	this->Map = _map;
	this->id = _item._id;
}
Item::Item()
{
	this->Update = NULL;
	this->Place = NULL;
	this->Destroy = NULL;
	this->Map = NULL;
	this->id = "";
}
Item::~Item() {};
Addres Item::get_addres() { return this->addres; }
void Item::set_addres(Addres _addres) { this->addres = _addres; }
bool Item::operator==(const Item& I) const
{
	return this->id == id;
}//��д����
Item& Item::operator=(const Item& I)
{
	this->Update = I.Update;
	this->Place = I.Place;
	this->Destroy = I.Destroy;
	this->Map = I.Map;
	this->id = I.id;
	return *this;
}//��д��ֵ
//ʵ����
Entity::Entity(Eupdate _update,
	Esummon _summon,
	Ekill _kill,
	gmap* _map,
	std::string _id)
{
	this->Update = _update;
	this->Summon = _summon;
	this->Kill = _kill;
	this->Map = _map;
	this->id = _id;
}
Entity::Entity(Sentity _entity, gmap* _map)
{
	this->Update = _entity._update;
	this->Summon = _entity._summon;
	this->Kill = _entity._kill;
	this->Map = _map;
	this->id = _entity._id;
}
Entity::Entity()
{
	this->Update = NULL;
	this->Summon = NULL;
	this->Kill = NULL;
	this->Map = NULL;
	this->id = "";
}
Entity::~Entity() {}
void Entity::UpdateEntity()
{
	Update(this);
}
int Entity::SummonEntity()
{
	return Summon(this);
}
int Entity::KillEntity()
{
	return Kill(this);
}
Addres Entity::get_addres() { return this->addres; }
void Entity::set_addres(Addres _addres) { this->addres = _addres; }
//������
int news(int x, int y, int seed, Addres nums[], int type[])
{
	seed + x * 10000000 + y;
	int n = 0;
	srand(seed);
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			int rands = rand() % 100;
			//���估���ʣ�Ҫ΢���Լ�΢��ȥ
			if (rands >= 0 && rands < 15)
			{
				type[n] = 1;
				nums[n].first = i;
				nums[n++].second = j;
			}
			if (rands >= 15 && rands < 20)
			{
				type[n] = 2;
				nums[n].first = i;
				nums[n++].second = j;
			}
			else
			{
				type[n] = 0;
				nums[n].first = i;
				nums[n++].second = j;
			}

		}
	return n;
}
void randprint(int ch, Addres begin, int mod, Item** m, gmap* g)
{//			   ����ַ� ��  ʼ  λ  ��  %�ϵ���   ��ͼ
	int x = begin.first;
	int y = begin.second;
	if (mod == 0)
		return;
	if(x >= 0 && x < 256 && y >= 0 && y < 256)
		m[x][y] = *(new Item(items[ch], g));
	if (rand() % mod != 0 && x + 1 < 256)
		if(m[x + 1][y] == *(new Item(items[0], g)))
			randprint(ch, Addres(x + 1, y), mod - 1, m, g);
	if (rand() % mod != 0 && x - 1 < 256)
		if (m[x - 1][y] == *(new Item(items[0], g)))
			randprint(ch, Addres(x + 1, y), mod - 1, m, g);
	if (rand() % mod != 0 && y + 1 < 256)
		if (m[x][y + 1] == *(new Item(items[0], g)))
			randprint(ch, Addres(x, y + 1), mod - 1, m, g);
	if (rand() % mod != 0 && y - 1 < 256)
		if (m[x][y - 1] == *(new Item(items[0], g)))
			randprint(ch, Addres(x, y - 1), mod - 1, m, g);
}
Block::Block() {}//����Ĺ��캯��,��Ҫд���ɣ�seed;
Block::~Block(){}//������Ļ���
void Block::init(int seed)
{
	Addres T[65536];
	int type[65536];
	int n = news(this->x, this->y, seed, T, type);
	for (int i = 0; i < n; i++)
	{
		randprint(type[i], T[i], 10, , this->);
	}
}
void Block::update()
{
	entity.getcur()->UpdateEntity();
	while (!entity.curadd())
	{
		entity.getcur()->UpdateEntity();
	}
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			m[i][j].UpdateItem();
}
std::pair<int, int> Block::get_block_id()
{
	return make_pair(this->x, this->y);
}
Item Block::get_char(int x, int y)
{
	return this->m[x][y];
}