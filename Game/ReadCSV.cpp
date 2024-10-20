#include "Play.h"
#include "PanelItem.h"
#include "ReadCSV.h"

extern std::vector<ObjectCSV> g_vObjects;
extern std::map<std::string, int> g_idMap;
extern std::vector<std::string> g_v_idToStringTable;

std::vector<ObjectCSV> ReadObjectsCSV() {
    // Open the objects csv file
    std::ifstream objectsFile("data/objects.csv");

    if (!objectsFile) {
        throw std::runtime_error("Failed to open objects.csv");
    }

    // Ignore the first line
    std::string header;
    std::getline(objectsFile, header);

    std::vector<ObjectCSV> objects;
    int id = 0;

    while (objectsFile) {
        // Read a line from the file
        std::string line;
        std::getline(objectsFile, line);

        // Ignore empty lines
        if (line.empty()) {
            continue;
        }

        // Tokenize the line by comma
        std::istringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Create a new ObjectCSV instance
        ObjectCSV obj;
        obj.name = tokens[0];

        // Map the group name to the corresponding enum value
        static const std::unordered_map<std::string, ItemType> groupMap = {
            {"CONFIGURATION", CONFIGURATION},
            {"ENVIRONMENT", ENVIRONMENT},
            {"PROTECTIVE", PROTECTIVE},
            {"REWARD", REWARD},
            {"HAZARD", HAZARD},
        };
        auto it = groupMap.find(tokens[1]);
        if (it != groupMap.end()) {
            obj.group = it->second;
        }
        else {
            continue;
        }

        // Get the sprite IDs
        std::string baseSprite = tokens[2];
        obj.spriteID[4] = Play::GetSpriteId((baseSprite + "_panel").c_str());
        for (int i = 0; i < 4; ++i) {
            obj.spriteID[i] = Play::GetSpriteId((baseSprite + "_R" + std::string(1, 'A' + i)).c_str());
        }

		// Set valid entry directions
		if (tokens[4] != "N")
		{
            uint8_t upBit = 0x0;
            uint8_t rightBit = 0x0;
            uint8_t downBit = 0x0;
            uint8_t leftBit = 0x0;

			for (char c : tokens[4])
			{
                switch (c)
                {
                case 'U': // Up
                    upBit = 1;
                    break;
                case 'R': // Right
                    rightBit = 1;
                    break;
                case 'D': // Down
                    downBit = 1;
                    break;
                case 'L': // Left
                    leftBit = 1;
                    break;
                default:
                    break;
                }
			}

            uint8_t dirs = upBit | rightBit << 1 | downBit << 2 | leftBit << 3;

            obj.entryDirections = dirs;
		}

        obj.id = id++;
        objects.push_back(std::move(obj));

        // Update idToString and idMap
        g_v_idToStringTable.push_back(tokens[3]);
        g_idMap[tokens[3]] = obj.id;
    }

    return objects;
}

int GetSpriteIDFromObjectID(int objID, int rot) {
	for (ObjectCSV objCSV : g_vObjects) {
		if (objCSV.id == objID) {
			return objCSV.spriteID[rot];
		}
	}
	return -1;
}