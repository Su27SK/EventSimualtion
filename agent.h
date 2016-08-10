#ifndef _AGENT_H_
#define _AGENT_H_
#include "BulkNode.h"
class Agent
{
	private:
		BulkNode _node;
		double _time;
		vector<int> _sVector;      //存放session id
	public:
		Agent():Agent() {

		}
		bool recv(int id, BulkLink& link);
		bool send(int id, BulkLink& link);

		double getStoreSize(int sId, unit type = Kb);
		queue<BulkPackets>* getStore(int sId);
		int getStoreAmount(int sId);
		bool sIdExisted(int sId);
		bool getTerminal();
		bool getOriginal();
		void reallocSize(int sId);
		int reallocPackets(int sId);
		void initNodePackets(int sId, queue<BulkPackets> *recv);
		void reallocAll(FILE* handle);
		slist<BulkLink*>* getOutputLink();
		slist<BulkLink*>* getInputLink();
		void addOutputLink(BulkLink* link);
		void addInputLink(BulkLink* link);
};
#endif
