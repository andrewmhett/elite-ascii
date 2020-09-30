#include "json.hpp"
#include <fstream>

using jsonf = nlohmann::json;

jsonf LoadSave(string name){
	ifstream save_file("saves/"+name+".json", ifstream::binary);
	jsonf save;
	save_file >> save;
	save_file.close();
	return save;
}

void NewSave(string name){
	jsonf save_json;
	save_json["credits"]=0;
	ofstream save_file("saves/"+name+".json");
	save_file << save_json;
	save_file.close();
}
