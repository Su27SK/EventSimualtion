#ifndef _PACKET_H_
#define _PACKET_H_
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;
enum unit{
	Byte = 1,
	Kb = 2,
	Mb = 3,
	Gb = 4
};

class Packet
{
	private:
		double _size;
		unit _type;
	public:
		Packet():_size(1), _type(Kb) {}
		Packet(double size, unit type);
		Packet& setPacketSize(double size);
		Packet& setPacketType(unit type);
		explicit Packet(const Packet& P);
		Packet(Packet& P);
		string getPacketInfo();
		double getPacketSize() const;
		string getPacketUnit();
		Packet& operator = (const Packet& packet);
		bool convertToType(int degree, bool isLarge = true);
		virtual ~Packet(){}
};
#endif
