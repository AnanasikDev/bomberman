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

		int GetTileIDAtIndex(int index) const;
		int GetTileIDAtGridPosition(uint2 pos) const;
	};

	class Map {
		const char* ReadFromFile(const char* filename) const;

	public:
		Array<Layer> layers;

		Map() = default;

		bool ReadFromTMX(const char* filename);
		const char* ReadBetweenAsString(const char* start, const char* end);
		int ReadBetweenAsInt(const char* start, const char* end);
		IntArray ReadBetweenAsIntArr(const char* start, const char* end, const char* separator, int length);
		
		static int2 GetGridCoordinateByIndex(int index);
		static int GetIndexByGridCoordinate(uint2 pos);
		static int2 GridToWorld(int2 grid);
		static int2 GridToWorld(uint2 grid);
		static int2 WorldToGrid(int2 world);
		static bool IsGridPosOnMap(int2 pos);
	};
}