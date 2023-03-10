#include "game_map.h"
//变量的定义
int Ilength = 0;//方块数量
Sitem items[1000];
int Elength = 0;//实体数量
Sentity entitys[1000];

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
Item::~Item() {};
Addres Item::get_addres() { return this->addres; }
void Item::set_addres(Addres _addres) { this->addres = _addres; }
//实体类
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
//区块类
Block::Block(){}//区块的构造函数,需要写生成，seed;
Block::~Block(){}//区块类的回收
std::pair<int, int> Block::get_block_id()
{
	return make_pair(this->x, this->y);
}
Item Block::get_char(int x, int y)
{
	return this->m[x][y];
}