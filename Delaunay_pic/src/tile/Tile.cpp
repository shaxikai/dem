#include "Tile.h"

tileElement::tileElement()
{
    x = -1;
    y = -1;
}

tileElement::tileElement(int _x, int _y) : x(_x), y(_y)
{
    hashIndex = hashVal();
}

int tileManager::getTile(int x, int y, std::shared_ptr<tileElement> &te) {
    SPtr<tileElement> ret = SPtr<tileElement>(new tileElement(x, y));
    int64_t h = tileElement::hashVal(x, y);

    TileHash::iterator it = m_allTile.find(h);
    bool in_internal_memtory = (it != m_allTile.end());

    if(in_internal_memtory) {
        ret = it->second;
        te = ret;
        return 1;
    } else {
        return 0;
    }
}

int tileManager::setTile(int x, int y, std::shared_ptr<tileElement> &te) {
    te->x = x;
    te->y = y;

    int64_t h = tileElement::hashVal(x, y);
    te->hashIndex = h;

    TileHash::iterator it = m_allTile.find(h);
    bool in_internal_memtory = (it != m_allTile.end());

    if(in_internal_memtory) {
        it->second = te;
        return 1;
    } else {
        m_allTile[h] = te;
        return 2;
    }
}
