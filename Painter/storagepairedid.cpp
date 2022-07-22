#include "storagepairedid.h"

StoragePairedID::StoragePairedID(QObject *parent)
	: QObject{parent}
{

}

void StoragePairedID::addID(int id1, int id2)
{
	if(id1 == id2)return;
	for(int i = 0; i < IDs.size(); i++){
		if((IDs[i].id1 == id1 && IDs[i].id2 == id2) || (IDs[i].id1 == id2 && IDs[i].id2 == id1)){
			return;
		}
	} // Для исключения повторений

	IDs.append(Pair(id1, id2));
}

void StoragePairedID::delID(int Del_ID)
{
	for(int i = IDs.size() - 1; i >= 0; i--){
		if(IDs[i].id1 == Del_ID || IDs[i].id2 == Del_ID){ // Удалена связанная фигура
			IDs.remove(i);
			continue;
		}

		if(IDs[i].id1 > Del_ID)IDs[i].id1--; // Двигаем оставшиеся связи, если нужно
		if(IDs[i].id2 > Del_ID)IDs[i].id2--;
	}
}

const int StoragePairedID::getID1(int Num_ID)
{
	return IDs[Num_ID].id1;
}

const int StoragePairedID::getID2(int Num_ID)
{
	return IDs[Num_ID].id2;
}

void StoragePairedID::clearAll()
{
	IDs.clear();
}

const int StoragePairedID::getSize()
{
	return IDs.size();
}

bool StoragePairedID::LineContains(int x1, int y1, int x2, int y2, int x, int y)
{
	int cross = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1); // точка лежит на линии.

	if(cross != 0)return false;

	if (abs(x2 - x1) >= abs(y2 - y1)) // точка лежит между концами линии
	  return (x2 - x1) > 0 ?
		x1 <= x && x <= x2:
		x2 <= x && x <= x1;
	else
	  return (y2 - y1) > 0 ?
		y1 <= y && y <= y2 :
		y2 <= y && y <= y1;
}
