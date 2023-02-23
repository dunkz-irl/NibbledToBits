#pragma once

struct ObjectCSV {
	std::string name;
	int spriteID[5];
	int group;
	int id;
};

std::vector<ObjectCSV> ReadObjectsCSV();

int GetSpriteIDFromObjectID(int objID, int rot = 0);