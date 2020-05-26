#include <iostream>
#include <string>
#include <vector>
#include <set>

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
	int hp; //health
	int mp; //Magic Points
	int str; //Strength
};

// Keeps Desc and Stats of each species
class Species {
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
};