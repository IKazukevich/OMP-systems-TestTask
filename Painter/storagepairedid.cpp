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
