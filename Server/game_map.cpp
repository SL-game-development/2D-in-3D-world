#include "game_map.h"

int len = 0;
std::string Itemlist[1 << 16];

Block::Block(){}//����Ĺ��캯��
Block::~Block(){}//������Ļ���
std::pair<int, int> Block::get_block_id()
{
	return make_pair(this->x, this->y);
}
Item Block::get_char(int x, int y)
{
	return this->m[x][y];
}

