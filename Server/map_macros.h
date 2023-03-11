#define newitem(update, place, destroy, id, n) items[n] = Sitem(update, place, destroy, id);unitems[items[n]] = n
#define newentity(update, summon, kill, id, n) entitys[n] = Sentity(update, summon, kill, id);unentitys[entitys[n]] = n
#define ITEM_NULL items[0]
#define ENTITY_NULL items[0]