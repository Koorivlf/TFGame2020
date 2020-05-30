#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <array>

//Manages and Initializes files of a 
// Includes iostream & fstream
class Display{

public:
	void gameStart(){
		std::cout << "Program start:" << std::endl;
	};

};
// Manages the game
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
//Creates Item entities
class Item {
	// Vars
	std::string name;
	std::string description;
	int id;

	public:
		Item() = default;

		Item(std::string _name,std::string _description, int _id)
			: name(_name),  
			description(_description),
			id(_id)
		{ ; }
	// Functions
	
	// Set||Get
	std::string getName()	{
		return name;
	}
	void setName(const std::string& _name) {
		name = _name;	
	}
	// Operators
	bool operator==(const Item& other) {
		return name == other.name;
	}
};
//Creates room entities
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
//Manages Battles
class BattleManager{

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
//Directions
struct Direction
{
	enum dir{north,northEast,east,southEast,south,southWest,West,northWest};
};
// Keeps Desc and Stats of each species
class Species {
	protected: 
		Stats stats;	
//tiger //human //snake //rat //ott //croc //raccon
	void setStats();

};
//Is template for character entities 
class Character {
	protected:
		Species species;
		Stats stats;
		size_t id;
		Room* current_room;

	public:
		//Basic
		Character(Room* _current_room) :
			current_room(_current_room)
		{ ; }
		virtual bool moveTo(Room*) = 0;
};
//Enemies
class NPC : Character {

};
//Manages inventory needs <algorithm>
class Inventory {

	//Use a array instead?
	std::vector<Item> itemList;
	size_t bagSize;
public:
	Inventory(size_t& _bagSize) :
	bagSize(_bagSize)
	{ ; }

	int sizeOfInv(){
		return bagSize;
	};

	int numoOfItems(){
		return itemList.size();
	};

	bool isInvFull(){
		return itemList.size() >= bagSize;
	};

	bool addToInv(Item _item){
		if(!isInvFull()){
			itemList.push_back(_item);
			std::cout << "item pushed" << std::endl;
			return true;
		} else {
			std::cout << "item not pushed" << std::endl;
			return false;
		}

	};
	/* Vector of items
	void addToInv(const std::vector<Item>& _items){
	};
	*/

	bool removeFromInv(Item _item) {
		auto it = std::find(
			itemList.begin(),
			itemList.end(),
			_item
		);
		if (it != itemList.end()) {
			itemList.erase(it);
			std::cout << "item removed" << std::endl;
			return true;
		} else {
			std::cout << "item failed to removes" << std::endl;
			return false;
		}
	};
};
//Creates player entities
class Player : public Character {
	//vars
	Inventory inv;
	

	public:
		Player(Room* current_room, size_t _inv) :
			Character(current_room),
			inv(_inv)
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
		void addItem(const Item& _item){
			inv.addToInv(_item);
		};
};
//Creates a storage item
class Storage : Item{

};
//Func: Moves the player through mapps
void movePlayer(Player& p, Room* dest) {
	if (p.moveTo(dest)) {
		std::cout << "Moved player to " << dest->name << std::endl;
	} else {
		std::cout << "Player can't go there from here." << std::endl;
	}
}
// MainGame Loop
int main()  {
	//Keep this around	
	Display gd;
	gd.gameStart();
	//Write Below Here
	Room livingroom("Living Room", "Where you live");

	Player koor(&livingroom, 3);

	Item item_pe("Pencil Eraser", "Can Erase Pencils", 1);
	Item item_ee("Eraser", "Eraser", 2);
	Item item_b("bbbbbr", "b stuff", 3);
	Item item_c("cccccc", "stuff of c", 4);
	Item item_d("ddddd", "woah D", 5);

	std::array<Item, 5> itemArr = {item_pe, item_ee, item_b, item_c, item_d};
	

	for (const auto& i : itemArr)	{
		std::cout << "Attempt to add to koor:" << std::endl;
		koor.addItem(i);
	};
	
	
	
	
	
	
	
	
	
	
	// GameFileManager gfm("billyBob.txt");

	//Intlizate without copy assign
	/*
	std::vector<std::string> testvec {"a","b","c","c","c","c","c","D"};

	std::cout << "Testing stuff:" << std::endl;
	gfm.write("Hello~");
	std::cout << "String write done" << std::endl;
	gfm.write(testvec);
	std::cout << "Vector write done" << std::endl;
	*/
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