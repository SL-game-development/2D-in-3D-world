#include "game_map.h"

int len = 0;
std::string Itemlist[1 << 16];

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
Item::Item(Iupdate _update, Iplace _place, Idestroy _destroy, gmap* _map)
{
	this->Update = _update;
	this->Place = _place;
	this->Destroy = _destroy;
	this->Map = _map;
}

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

