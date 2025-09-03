#include "settings.h"
#include "precomp.h"
#include "Map.h"

namespace Tmpl8 {
	Layer::Layer(const char* name, IntArray tiles) : name(name), tiles(tiles) {
		
	}

	const char* Map::ReadBetweenAsString(const char* start, const char* end) {

		int length = end - start;
		char* string = (char*)MALLOC64(length + 1);
		for (int i = 0; i < length; i++) {
			string[i] = start[i];
		}
		string[length] = 0;
		return string;
	}

	int Map::ReadBetweenAsInt(const char* start, const char* end) {
		int i = 0;
		int length = 0;
		while (start + i != end) {
			if (start[i] != '\n' && start[i] != '\t') {
				length++;
			}
			i++;
		}
		i = 0;
		char* snum = (char*)MALLOC64(length + 1);
		while (start + i != end) {
			snum[i] = start[i];
			i++;
		}
		snum[length] = 0;
		int num = atoi(snum);
		FREE64(snum);
		return num;
	}

	IntArray Map::ReadBetweenAsIntArr(const char* start, const char* end, const char* separator, int length) {

		IntArray result(length);
		const char* cursor = start;
		for (int i = 0; i < length; i++) {
			const char* nextvalue = strstr(cursor, separator);
			int value = ReadBetweenAsInt(cursor, nextvalue);
			result[i] = value;
			cursor += (nextvalue - cursor) + 1;
		}
		return result;
	}

	const char* Map::ReadFromFile(const char* filename) const {
		FILE* file;
		file = fopen(filename, "rb");
		if (file == nullptr) {
			FatalError("File not found: %s", filename);
			return false;
		}

		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* rawcontents = (char*)MALLOC64(size + 1);
		fread(rawcontents, size, 1, file);
		rawcontents[size] = 0;
		fclose(file);

		long toremove = 0;
		for (long c = 0; c < size; c++) {
			if (rawcontents[c] == '\n' || rawcontents[c] == '\r') {
				toremove++;
			}
		}
		//printf("\ntoremove: %d\n", toremove);

		char* contents = (char*)MALLOC64(size + 1 - toremove);
		long writeindex = 0;
		long readindex = 0;
		for (; readindex < size; readindex++) {
			if (rawcontents[readindex] == '\n' || rawcontents[readindex] == '\r') {
				continue;
			}
			contents[writeindex++] = rawcontents[readindex];
		}

		FREE64(rawcontents);

		//printf(contents);

		return contents;
	}

	bool Map::ReadFromTMX(const char* filename) {
		// read file

		const char* contents = ReadFromFile(filename);
		int contentsLength = strlen(contents);
		int layerCount = 0;

		const char* cursor = contents;
		while (true) {
			cursor = strstr(cursor, "<layer id=");
			if (cursor == nullptr) {
				break;
			}
			cursor += 9;
			layerCount++;
		}

		layers = Array<Layer>(layerCount);

		cursor = contents;

		for (int l = 0; l < 2; l++){

			cursor = strstr(cursor, "<layer") + 6;
			const char* hnamestart = strstr(cursor, "name=") + 5;
			const char* hnameend = strstr(hnamestart, "\"");
			const char* hidstart = strstr(cursor, "id=\"") + 4;
			const char* hidend = strstr(hidstart, "\"");

			int id = ReadBetweenAsInt(hidstart, hidend);
			//printf("%d   ", id);

			const char* name = ReadBetweenAsString(hnamestart, hnameend);
			//printf(name);

			const char* hdatastart = strstr(cursor, "<data encoding=\"csv\">") + 21;
			const char* hdataend = strstr(cursor, "</data>");

			IntArray data = ReadBetweenAsIntArr(hdatastart, hdataend, ",", MAP_WIDTH * MAP_HEIGHT);
			//printf(hdatastart);
			//printf("\n\nlength: %d\n", data.GetLength());
			/*for (int i = 0; i < data.GetLength(); i++) {
				printf("%d, ", data[i]);
			}
			printf("\n");*/

			layers[l] = Layer(name, data);
		}

		// parse file and build the mapj

		return true;
	}

	int2 Map::GetCoordinateByIndex(int index) const {
		return int2(
			(index % tileCount.x) * tileSize.x, 
			(index / tileCount.x) * tileSize.y);
	}

	void Map::Init(uint2 tileCount, uint2 tileSize) {
		this->tileCount = tileCount;
		this->tileSize = tileSize;
	}
}