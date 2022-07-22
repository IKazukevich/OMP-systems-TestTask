#ifndef STORAGEPAIREDID_H
#define STORAGEPAIREDID_H

#include <QObject>

class StoragePairedID : public QObject
{
	Q_OBJECT

public:

	explicit StoragePairedID(QObject *parent = nullptr);
	void addID(int,int);
	void delID(int);
	const int getID1(int);
	const int getID2(int);
	void clearAll();
	const int getSize();
	static bool LineContains(int x1, int y1, int x2, int y2, int x, int y);

signals:

private:
	struct Pair{
		int id1, id2;
		Pair(int _id1, int _id2):id1(_id1), id2(_id2){};
	};

	QVector<Pair> IDs;
};

#endif // STORAGEPAIREDID_H
