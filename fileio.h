#include "json.hpp"
#include <fstream>

using jsonf = nlohmann::json;

jsonf LoadSave(string name){
	jsonf save;
	ifstream save_file("saves/"+name+".json", ifstream::binary);
	if (save_file.good()){
		save_file >> save;
		save_file.close();
	}else{
		save_file.close();
		throw -1;
	}
	return save;
}

void NewSave(string name){
	jsonf save_json;
	ifstream fstrm("saves/"+name+".json", ifstream::binary);
	if (!fstrm.good()){
		fstrm.close();
		save_json["credits"]=0;
		ofstream save_file("saves/"+name+".json");
		save_file << save_json;
		save_file.close();
	}else{
		fstrm.close();
		throw -1;
	}
}
