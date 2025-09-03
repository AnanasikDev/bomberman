#pragma once

#include "settings.h"
#include "tarray.h"

namespace Tmpl8 {
	class Layer {
	public:
		const char* name;
		IntArray tiles;

		Layer() : name(0){

		}

		Layer(const char* name, IntArray tiles);
	};

	class Map {
		const char* ReadFromFile(const char* filename) const;

	public:
		Array<Layer> layers;
		uint2 tileCount;
		uint2 tileSize;

		Map() : tileCount(0), tileSize(0) { }

		Map(uint2 tileCount, uint2 tileSize) : tileCount(tileCount), tileSize(tileSize) {

		}

		void Init(uint2 tileCount, uint2 tileSize);
		bool ReadFromTMX(const char* filename);
		const char* ReadBetweenAsString(const char* start, const char* end);
		int ReadBetweenAsInt(const char* start, const char* end);
		IntArray ReadBetweenAsIntArr(const char* start, const char* end, const char* separator, int length);
		int2 GetCoordinateByIndex(int index) const;
	};
}