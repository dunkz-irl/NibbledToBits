#pragma once

typedef std::pair<std::string, int> InventoryPair;

class LevelLoader
{
public:
	std::vector<std::string> TokeniseStringByComma(std::string line);
	void LoadLevel(const char* levelName);

private:
	std::vector<InventoryPair> m_vInventoryPairs;
};