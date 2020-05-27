#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

//Manages and Initializes files of a 
// Includes iostream & fstream
class GameFileManager {
	std::ofstream fo; //File Out
	std::string filename;

	public:
	GameFileManager(const std::string& _filename) :
		fo(_filename),
		filename(_filename)
	{ ; }

	void write(const std::string& str) {
		if (fo.is_open())	{
			fo << str << std::endl;
		} else {
			std::cout << "Unable to open: " << filename;
		}
	}
	// overide function
	void write(const std::vector<std::string>& vec) {
		if(fo.is_open()) {

			//for-range loop (better for loop)
			for(const std::string& i : vec ){
				fo << i << std::endl; 
			}

		} else { 
			std::cout << "Unable to open: " << filename;
		}
	}

	void close(){
		fo.close();
	}
};

class Room {
	public:
		std::string name;
		std::string description;
		size_t id;
		// std::vector<Item> items;
		// std::vector<Character> characters; 

		std::set<Room*> connected_rooms;

//	public:
		Room() = default;
		Room(std::string _name, std::string _description) :
			name(_name),
		 	description(_description)
		{ ; }

		void addConnection(Room* room) {
			connected_rooms.insert(room);
		}
 		
		bool connectedTo(Room* roomTo) {
			return connected_rooms.find(roomTo) != connected_rooms.end();
		}
};


// Contains the stats of the entity
class Stats {
	protected:
		int health;
		int magic_points;
		int strength;
		int defense;
		int agility;
		int luck; 
		int intellegence;
};

// Keeps Desc and Stats of each species
class Species {
	protected: 
		Stats stats;	
//tiger //human //snake //rat //ott //croc //raccon
	void setStats();

};

class Character {
	protected:
		Species species;
		Stats stats;
		size_t id;
		Room* current_room;
	public:
		Character(Room* _current_room) :
			current_room(_current_room)
		{ ; }
		virtual bool moveTo(Room*) = 0;
};

class Player : public Character {
	public:
		Player(Room* current_room) :
			Character(current_room)
		{ ; }
		// Tries to move player to new room
		bool moveTo(Room* room) override {
			if (current_room->connectedTo(room)) {
				current_room = room;
				return true;
			} else {
				return false;	
			}
		}



};

class Item {
	std::string description;
};


void movePlayer(Player& p, Room* dest) {
	if (p.moveTo(dest)) {
		std::cout << "Moved player to " << dest->name << std::endl;
	} else {
		std::cout << "Player can't go there from here." << std::endl;
	}
}




int main()  {
	GameFileManager gfm("billyBob.txt");

	//Intlizate without copy assign
	std::vector<std::string> testvec {"a","b","c","c","c","c","c","D"};

	std::cout << "Testing stuff:" << std::endl;
	gfm.write("Hello~");
	std::cout << "String write done" << std::endl;
	gfm.write(testvec);
	std::cout << "Vector write done" << std::endl;
/*
	std::cout << "Hello world";

	Room livingroom("Living Room", "Where you live");
	Room bathroom("Bathroom", "Place where you shit");
	Room bedroom("Bedroom", "Where you sleep");
	Room happyplace("Happy Place", "where you go when you're stressed");

	Player koor(&livingroom);

	livingroom.addConnection(&bedroom);
	bedroom.addConnection(&bathroom);
	bedroom.addConnection(&livingroom);
	bathroom.addConnection(&bedroom);
	bedroom.addConnection(&happyplace);

	movePlayer(koor, &happyplace);
	movePlayer(koor, &bedroom);

	movePlayer(koor, &bathroom);

	movePlayer(koor, &bedroom);


	movePlayer(koor, &happyplace);
*/

}