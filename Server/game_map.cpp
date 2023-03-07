#include "game_map.h"

int len = 0;
std::string Itemlist[1 << 16];

Block::Block(){}//区块的构造函数
Block::~Block(){}//区块类的回收
std::pair<int, int> Block::get_block_id()
{
	return make_pair(this->x, this->y);
}
Item Block::get_char(int x, int y)
{
	return this->m[x][y];
}

